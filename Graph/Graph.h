#ifndef __GRAPH_H__
#define __GRAPH_H__
#include <map>
#include <utility>
using namespace std;

template <class T>
class Graph {
protected:
    std::map<T, std::vector<std::pair<T, float>>> lista_adyacencia;
    bool is_directed;
public:
    Graph();
    ~Graph();
    bool addNode(T nNode);
    bool addEdge(T source, T destination, float weight);
    bool deleteNode(T nNode);
    bool deleteEdge(T source, T destination);
    bool findNode (T nNode);
    bool findEdge (T source, T destination);
};

#endif