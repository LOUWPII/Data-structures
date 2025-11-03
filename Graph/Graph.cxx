
#include "Graph.h"

    template <class T>
    Graph<T>::Graph(){}

    template <class T>
    Graph<T>::~Graph(){}

    template <class T>
    bool Graph<T>::addNode(T nNode){
        if (adjacency_list.find(nNode) != adjacency_list.end()) {
        return false;
    }
        adjacency_list[nNode];    
        return true;
    }

    template <class T>
    bool Graph<T>::addEdge(T source, T destination, float weight){
    // Verificar si los nodos existen 
    // Para simplificar, asumimos que addNode() se llamó antes, o que el map los crea.
    if (adjacency_list.find(source) == adjacency_list.end() ||
        adjacency_list.find(destination) == adjacency_list.end()) {
        return false; 
    }

    //Se Define la arista con su destino y peso
    pair<T, float> new_edge = {destination, weight};

    //Añadir la arista en la lista de adyacencia  
    adjacency_list[source].push_back(new_edge);

    // Se verifica si es dirigido o no
    if (!is_directed) {
        std::pair<T, float> reverse_edge = {source, weight};
        adjacency_list[destination].push_back(reverse_edge);
    }
    
    return true;
}
    

    template <class T>
    bool Graph<T>::deleteNode(T nNode){

    }

    template <class T>
    bool Graph<T>::deleteEdge(T source, T destination){

    }

    template <class T>
    bool Graph<T>::findNode (T nNode){

    }

    template <class T>
    bool Graph<T>::findEdge (T source, T destination){

    }


    

template <class T>
NodoGeneral<T>::NodoGeneral() {
    this->desc.clear();
}

template <class T>
NodoGeneral<T>::~NodoGeneral() {
    typename std::list<NodoGeneral<T>*>::iterator it;
    for (it = this->desc.begin(); it != this->desc.end(); ++it) {
        delete *it;
    }
    this->desc.clear();
}