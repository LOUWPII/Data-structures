#ifndef __GRAPH_H__
#define __GRAPH_H__
#include <map>
#include <utility>
#include <iostream>
#include <vector>

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
    bool deleteEdgeAux(T source, T destination);
    std::pair<bool, typename std::map<T, std::vector<std::pair<T, float>>>::iterator> findNode (T nNode);
    std::pair<bool, float> findEdge (T source , T destination);
};

#endif