#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
class Graph 
{
  private:
    int _vCt;
    std::vector<T> _v;
    std::vector<std::vector<int> > _e;
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
  
};

char list[] = {'s', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 't'};

int main()
{
    std::vector<char> v;
    for (const auto & i: list) {
        v.push_back(i);
    }
    
    Graph<char> g(v);
    g.addConnection('s', 'A', 1);
    g.printTopography();

    
    return 0;
}
