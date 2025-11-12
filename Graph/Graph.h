#ifndef __GRAPH_H__
#define __GRAPH_H__

// Inclusiones necesarias
#include <map>
#include <utility>  // Para std::pair
#include <iostream>
#include <vector>
#include <queue>

template <class T>
class Graph {
private:
    std::map<T, std::vector<std::pair<T, float>>> adjacency_list;
    void DFS_Recursive(T currentNode, std::map<T, bool>& visited); //El nodo actual y el map de los visitados
    bool is_directed = false; 
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
    void BFS(T startNode);
    void DFS(T startNode); 
    void setDirected(bool directed);
};

#include "Graph.hxx"

#endif
