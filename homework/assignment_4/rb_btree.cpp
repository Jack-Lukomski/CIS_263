#include <iostream>
#include <queue>

enum class Color { RED, BLACK };

struct Node {
    int key;
    Color color;
    Node* parent;
    Node* left;
    Node* right;

    Node(int k, Color c, Node* p = nullptr, Node* l = nullptr, Node* r = nullptr)
        : key(k), color(c), parent(p), left(l), right(r) {}
};

class RedBlackTree {
private:
    Node* nil;
    Node* root;

    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;

        if (y->left != nil) {
            y->left->parent = x;
        }

        y->parent = x->parent;

        if (x->parent == nil) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }

        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;

        if (y->right != nil) {
            y->right->parent = x;
        }

        y->parent = x->parent;

        if (x->parent == nil) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }

        y->right = x;
        x->parent = y;
    }

    void insertFixup(Node* z) {
        while (z->parent->color == Color::RED) {
            if (z->parent == z->parent->parent->left) {
                Node* y = z->parent->parent->right;

                if (y->color == Color::RED) {
                    z->parent->color = Color::BLACK;
                    y->color = Color::BLACK;
                    z->parent->parent->color = Color::RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }

                    z->parent->color = Color::BLACK;
                    z->parent->parent->color = Color::RED;
                    rightRotate(z->parent->parent);
                }
            } else {
                Node* y = z->parent->parent->left;

                if (y->color == Color::RED) {
                    z->parent->color = Color::BLACK;
                    y->color = Color::BLACK;
                    z->parent->parent->color = Color::RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }

                    z->parent->color = Color::BLACK;
                    z->parent->parent->color = Color::RED;
                    leftRotate(z->parent->parent);
                }
            }
        }

        root->color = Color::BLACK;
    }

    void transplant(Node* u, Node* v) {
        if (u->parent == nil) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    Node* minimum(Node* node) {
        while (node->left != nil) {
            node = node->left;
        }
        return node;
    }

    void deleteFixup(Node* x) {
        while (x != root && x->color == Color::BLACK) {
            if (x == x->parent->left) {
                Node* w = x->parent->right;
                if (w->color == Color::RED) {
                    w->color = Color::BLACK;
                    x->parent->color = Color::RED;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == Color::BLACK && w->right->color == Color::BLACK) {
                    w->color = Color::RED;
                    x = x->parent;
                } else {
                    if (w->right->color == Color::BLACK) {
                        w->left->color = Color::BLACK;
                        w->color = Color::RED;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = Color::BLACK;
                    w->right->color = Color::BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                Node* w = x->parent->left;
                if (w->color == Color::RED) {
                    w->color = Color::BLACK;
                    x->parent->color = Color::RED;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == Color::BLACK && w->left->color == Color::BLACK) {
                    w->color = Color::RED;
                    x = x->parent;
                } else {
                    if (w->left->color == Color::BLACK) {
                        w->right->color = Color::BLACK;
                        w->color = Color::RED;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = Color::BLACK;
                    w->left->color = Color::BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = Color::BLACK;
    }

public:
    RedBlackTree() {
        nil = new Node(0, Color::BLACK);
        root = nil;
    }

    void insert(int key) {
        Node* z = new Node(key, Color::RED);
        Node* y = nil;
        Node* x = root;

        while (x != nil) {
            y = x;

            if (z->key < x->key) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        z->parent = y;

        if (y == nil) {
            root = z;
        } else if (z->key < y->key) {
            y->left = z;
        } else {
            y->right = z;
        }

        z->left = nil;
        z->right = nil;
        z->color = Color::RED;
        insertFixup(z);
    }

    void deleteNode(int key) {
        Node* z = root;
        while (z != nil && z->key != key) {
            if (z->key < key) {
                z = z->right;
            } else {
                z = z->left;
            }
        }

        if (z == nil) {
            // The key is not in the tree.
            return;
        }

        Node* y = z;
        Node* x;
        Color y_original_color = y->color;
        
        if (z->left == nil) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == nil) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;

            if (y->parent == z) {
                x->parent = y;
            } else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }

        if (y_original_color == Color::BLACK) {
            deleteFixup(x);
        }

        delete z;
    }

    void print() {
        if (root == nil) {
            std::cout << "Tree is empty." << std::endl;
            return;
        }

        std::queue<Node*> nodeQueue;
        nodeQueue.push(root);

        while (!nodeQueue.empty()) {
            int levelSize = nodeQueue.size();

            for (int i = 0; i < levelSize; i++) {
                Node* current = nodeQueue.front();
                nodeQueue.pop();

                std::cout << "(" << current->key << ",";

                if (current->color == Color::RED) {
                    std::cout << "RED) ";
                } else {
                    std::cout << "BLACK) ";
                }

                if (current->left != nil) {
                    nodeQueue.push(current->left);
                }

                if (current->right != nil) {
                    nodeQueue.push(current->right);
                }
            }

            std::cout << std::endl;
        }
    }
};

static const int nums[] = {
    26,
    41,
    17,
    47,
    14,
    30,
    21,
    28,
    19,
    38,
    23,
    35,
    20,
    29,
    16,
    15,
    10,
    7,
    12,
    3,
};

int main() {
    RedBlackTree tree;
    for (const auto & num: nums) {
        tree.insert(num);
    }

    tree.print();
    tree.deleteNode(12);
    std::cout << "\n\n" << std::endl;
    tree.print();

    return 0;
}