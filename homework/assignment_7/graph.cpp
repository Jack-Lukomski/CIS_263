#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
class Graph 
{
  private:
    int                          _vCt; // num verticies
    std::vector<T>                 _v; // vector of verticies/nodes
    std::vector<std::vector<int> > _e; // edges of verticies

    int noSuccessors(std::vector<T> vCpy, std::vector<std::vector<int> > eCpy)
    {
        for (int i = 0; i < vCpy.size(); ++i) {
            bool isEdge = false;
            for (int j = 0; j < vCpy.size(); ++j) {
                if (eCpy[i][j] != 0) {
                    isEdge = true;
                    break;
                }
            }
            if (!isEdge) {
                return i;
            }
        }
        return -1;
    }

  public:
    Graph(std::vector<T> vertcies) {
        _vCt = vertcies.size();
        _v = vertcies;
        _e.resize(_vCt);
        for (int i = 0; i < _vCt; ++i) {
            _e[i].resize(_vCt, 0);
        }
    }
    
    void addConnection(T first, T second, int weight) 
    {
        auto it1 = std::find(_v.begin(), _v.end(), first);
        auto it2 = std::find(_v.begin(), _v.end(), second);
        int c = std::distance(_v.begin(), it1);
        int r = std::distance(_v.begin(), it2);
        _e[r][c] = weight;
    }
    
    void printTopography()
    {
        std::cout << "   ";
        for (const auto& vertex : _v) {
            std::cout << vertex << "  ";
        }
        std::cout << std::endl;

        for (int i = 0; i < _vCt; ++i) {
            std::cout << _v[i] << "  ";
            for (int j = 0; j < _vCt; ++j) {
                std::cout << _e[i][j] << "  ";
            }
            std::cout << std::endl;
        }
    }

    void topologicalSort()
    {
        std::vector<T> vCpy = _v;
        std::vector<std::vector<int> > eCpy = _e;
        std::vector<T> sortedList;

        while (vCpy.size() > 0) {
            int vIndex = noSuccessors(vCpy, eCpy);

            if (vIndex == -1) {
                throw std::runtime_error("Cannot have a cycle");
            }

            sortedList.push_back(vCpy[vIndex]);

            vCpy.erase(vCpy.begin() + vIndex);
            eCpy.erase(eCpy.begin() + vIndex);
            for (int i = 0; i < eCpy.size(); ++i) {
                eCpy[i].erase(eCpy[i].begin() + vIndex);
            }
        }

        std::reverse(sortedList.begin(), sortedList.end());

        std::cout << "\n";
        for (const auto & i: sortedList) {
            std::cout << i << ", ";
        }
    }
  
};

char list[] = {'s', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 't'};

int main()
{
    std::vector<char> v;
    for (const auto & i: list) {
        v.push_back(i);
    }

    std::vector<int> v2;
    for (int i = 0; i < 6; ++i) {
        v2.push_back(i);
    }

    Graph<int> g(v2);
    g.addConnection(5, 0, 1);
    g.addConnection(5, 2, 1);
    g.addConnection(2, 3, 1);
    g.addConnection(3, 1, 1);
    g.addConnection(4, 1, 1);
    g.addConnection(4, 0, 1);
    g.printTopography();
    g.topologicalSort();

    
    return 0;
}
