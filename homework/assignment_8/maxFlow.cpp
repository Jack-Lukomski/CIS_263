#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>

template <typename T>
class Graph 
{
  private:
    int                          _vCt; // num vertices
    std::map<T, int>               _v; // map of vertices/nodes to indices
    std::vector<T>                _v2; // vector of vertices for output and internal handling
    std::vector<std::vector<int> > _e; // edges of vertices

    bool bfs(Graph<T>& r, T s, T t, std::map<T, T>& parent) {
        std::map<T, bool> visited;
        for (const auto& i : _v2) {
            visited[i] = false;
        }

        std::queue<T> q;
        q.push(s);
        visited[s] = true;
        parent[s] = T(); // initialize the parent map with default value for T

        while (!q.empty()) {
            T u = q.front();
            q.pop();

            std::cout << "Visiting node: " << u << std::endl;

            for (const auto& v : _v2) {
                if (!visited[v] && r._e[_v[u]][_v[v]] > 0) {
                    if (v == t) {
                        parent[v] = u;
                        std::cout << "Path from source to sink: ";
                        for(T v_temp = t; v_temp != s; v_temp = parent[v_temp]) {
                            std::cout << v_temp << " <- ";
                        }
                        std::cout << s << std::endl;

                        return true;
                    }
                    q.push(v);
                    parent[v] = u;
                    visited[v] = true;
                }
            }
        }

        return false;
    }

  public:
    Graph(std::vector<T> vertices) {
        _vCt = vertices.size();
        _v2 = vertices;
        for (int i = 0; i < _vCt; ++i) {
            _v[vertices[i]] = i;
        }
        _e.resize(_vCt);
        for (int i = 0; i < _vCt; ++i) {
            _e[i].resize(_vCt, 0);
        }
    }
    
    void addConnection(T source, T target, int weight) 
    {
        int r = _v[source];
        int c = _v[target];
        _e[r][c] = weight;
    }
    
    void printTopography()
    {
        std::cout << "   ";
        for (const auto& vertex : _v2) {
            std::cout << vertex << "  ";
        }
        std::cout << std::endl;

        for (int i = 0; i < _vCt; ++i) {
            std::cout << _v2[i] << "  ";
            for (int j = 0; j < _vCt; ++j) {
                std::cout << _e[i][j] << "  ";
            }
            std::cout << std::endl;
        }
    }

    int fordFulkerson(T s, T t) {
        int u, v;

        // create resudal graph same size as the origional
        Graph<T> residual(_v2);

        for (u = 0; u < _v2.size(); u++) {
            for (v = 0; v < _v2.size(); v++) {
                residual._e[u][v] = _e[u][v];
            }
        }

        std::map<T, T> parent;

        int maxFlow = 0;

        while (bfs(residual, s, t, parent)) {
            int pathFlow = std::numeric_limits<int>::max();
            for (v = t; v != s; v = parent[v]) {
                u = _v[parent[v]];
                pathFlow = std::min(pathFlow, residual._e[u][_v[v]]);
            }

            for (v = t; v != s; v = parent[v]) {
                u = _v[parent[v]];
                residual._e[u][_v[v]] -= pathFlow;
                residual._e[_v[v]][u] += pathFlow;
            }

            maxFlow += pathFlow;
        }

        return maxFlow;
    }
  
};

char list[] = {'s', 'a', 'b', 'c', 'd', 't'};
char lectureGraph[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

int main()
{
    std::vector<char> v;
    for (const auto & i: list) {
        v.push_back(i);
    }

    Graph<char> g(v);

    // g.addConnection('A', 'B', 4);
    // g.addConnection('A', 'D', 4);
    // g.addConnection('B', 'C', 6);
    // g.addConnection('B', 'E', 2);
    // g.addConnection('B', 'F', 2);
    // g.addConnection('C', 'F', 1);
    // g.addConnection('C', 'G', 2);
    // g.addConnection('C', 'D', 2);
    // g.addConnection('E', 'H', 2);
    // g.addConnection('F', 'H', 1);
    // g.addConnection('G', 'H', 2);

    g.addConnection('s', 'a', 4);
    g.addConnection('s', 'b', 2);
    g.addConnection('a', 'c', 2);
    g.addConnection('a', 'd', 4);
    g.addConnection('a', 'b', 1);
    g.addConnection('b', 'd', 2);
    g.addConnection('c', 't', 3);
    g.addConnection('d', 't', 3);

    g.printTopography();
    int maxFlow = g.fordFulkerson('s', 't');
    std::cout << "The max flow is: " << maxFlow << std::endl;
    
    return 0;
}
