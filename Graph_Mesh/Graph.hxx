#include "Graph.h"

// Constructores y Destructor
template <class T>
Graph<T>::Graph(){}

template <class T>
Graph<T>::~Graph(){}


template <class T>
bool Graph<T>::addNode(T nNode){
    
    if (findNode(nNode).first) 
        return false;

    // Si el nodo no existe, se inserta.
    adjacency_list[nNode];
    return true;
}

template <class T>
bool Graph<T>::deleteNode(T nNode){
    
    //Se usa .first ya que la funcion devuelve un std::pair
    if (!findNode(nNode).first) {
        return false; 
    }
    
    // Si el nodo existe, se elimina la pareja clave-valor del map
    adjacency_list.erase(nNode);

    // Eliminamos las aristas de entrada
    //Aca tenemos que usar typename para que el compilador no se confunda y sepa que es un tipo de dato
    //Se crea iterador para el map
    typename std::map<T, std::vector<std::pair<T, float>>>::iterator it_mapa;

    //Se recorrera el mapa para ir en busca de todas las aristas entrantes
    for (it_mapa = adjacency_list.begin(); it_mapa != adjacency_list.end(); ++it_mapa) {
        //Se inicializa un iterador en el second del map, el cual es el vector pair para las aristas y su peso
        typename std::vector<std::pair<T, float>>::iterator it_vector = it_mapa->second.begin();
        //ciclo while para eliminar la arista
        while (it_vector != it_mapa->second.end()) {
            if (it_vector->first == nNode) {
                it_vector = it_mapa->second.erase(it_vector);
            } else {
                ++it_vector;
            }
        }
    }
    return true; 
}

//La función devuelve un pair dados los requerimientos de implementación
template <class T>
std::pair<bool, typename std::map<T, std::vector<std::pair<T, float>>>::iterator> Graph<T>::findNode (T nNode){
    //Se utiliza la función find del map que devuelve un iterador a donde se ubica el elemento si se encontró
    typename std::map<T, std::vector<std::pair<T, float>>>::iterator it = adjacency_list.find(nNode);
    //Si el find no devolvió el end el node se encontró - se devuelve true y el iterador
    if (it != adjacency_list.end()) {
        return std::pair<bool, typename std::map<T, std::vector<std::pair<T, float>>>::iterator>(true, it);
    } else {
        return std::pair<bool, typename std::map<T, std::vector<std::pair<T, float>>>::iterator>(false, adjacency_list.end());
    }
}


template <class T>
bool Graph<T>::addEdge(T source, T destination, float weight){
    
    //Se buscan ambos nodos en el map
    if (!findNode(source).first || !findNode(destination).first) {
        return false; 
    }

    //Se verifica que la arista exista o no en el grafo
    std::pair<bool, float> edge_check = findEdge(source, destination);

    // Si la arista no exite ya en el grafo
    if (edge_check.first == false){
        
        //Se crea nuevo par con el peso de la arista y el peso
        std::pair<T, float> new_edge = {destination, weight};
        //Se añade al vector pair el nuevo par
        adjacency_list[source].push_back(new_edge);
        
        //Si es dirigido entonces se debe ubicar también la arista de vuelta
        if (!is_directed) {
            std::pair<T, float> reverse_edge = {source, weight};
            adjacency_list[destination].push_back(reverse_edge);
        }
        
        return true;
    }
    
    // La arista ya existía.
    return false;
}

//Esta función devuelve un booleano y se ayuda de la función auxiliar de eliminar arista.
//Esta funcion maneja si el grafo es dirigido o no
template <class T>
bool Graph<T>::deleteEdge(T source, T destination){

    //Se asigna a variables booleanas el resultado de la eliminación
    bool edge_source_dest = deleteEdgeAux(source, destination);
    bool edge_dest_source = deleteEdgeAux(destination, source);
    
    //Si el grado no es dirigido las aristas de salida y de entrada se debieron haber eliminado para que en realidad se haya eliminado una arista con éxito
    if (!is_directed){
        return (edge_source_dest && edge_dest_source);
    }else{
        //Si es dirigido únicamente basta con eliminar la arista de salida
        return(edge_source_dest);
    }
}

template <class T>
bool Graph<T>::deleteEdgeAux(T source, T destination){
    
    bool edge_eliminada = false; 
    
    //Si no existen los nodes
    if (!findNode(source).first || !findNode(destination).first){ 
        return false;
    }
    
    //Se inicializa el iterador en la ubicacion del elemento del map que retorne el map 
    typename std::map<T, std::vector<std::pair<T, float>>>::iterator it_mapa = adjacency_list.find(source);
    
    //Se inicializa un iterador en en el vector de aristas del nodo encontrado
    typename std::vector<std::pair<T, float>>::iterator it_vector = it_mapa->second.begin();

    //Se elimina la arista si se encuentra
    while (it_vector != it_mapa->second.end()) {
        if (it_vector->first == destination) {
            it_vector = it_mapa->second.erase(it_vector);
            edge_eliminada = true;
        } else {
            ++it_vector;
        }
    }

    return edge_eliminada;
}

//La función retorna un pair dados los requerimientos de implementación
template <class T>
std::pair<bool, float> Graph<T>::findEdge (T source , T destination){
    
    //Si no existen los nodes se devuelve falso y un peso inválido
    if (!findNode(source).first || !findNode(destination).first){
        return std::pair<bool, float>(false, -1.0f);
    }
    //Se ubica el iterador en el node encontrado
    typename std::map<T, std::vector<std::pair<T, float>>>::iterator it_mapa = adjacency_list.find(source);

    if (it_mapa == adjacency_list.end()) {
        return std::pair<bool, float>(false, -1.0f);
    }
    
    typename std::vector<std::pair<T, float>>::iterator it_vector = it_mapa->second.begin();
    //Si se encuentra la arista se retorna true 
    while(it_vector != it_mapa->second.end()){
        if (it_vector->first == destination){
            return std::pair<bool, float>(true, it_vector->second);
        }else{
            ++it_vector;
        }
    }
    
    //Si no se encuentra la arista se retorna falso y un peso inválido
    return std::pair<bool, float>(false, -1.0f);
}


template <class T>
void Graph<T>::BFS(T startNode) {

    // 1. Verificar si el nodo de inicio existe
    if (!findNode(startNode).first) {
        std::cout << "El nodo de inicio no existe." << std::endl;
        return;
    }

    //Creación de la cola para poder saber los nodes de cada nivel
    std::queue<T> q;
    // Se crea un mapa para saber si los nodes están visitados o no
    std::map<T, bool> visited; 

    //Insertar a la cola el nodo start
    q.push(startNode);
    // Marcar como visitado el nodo start usando la notación mi_mapa[clave] = true (valor)
    visited[startNode] = true; 

    //Mientras que la cola no esté vacia
    while (!q.empty()) {
        //Se guarda el nodo que esté en el front de la cola
        T currentNode = q.front();
        //borrar elemento de la cola
        q.pop();

        // visitar el nodo
        std::cout << currentNode << " ";

        // Se recorrer todos los neighbors del nodo actual
        // Necesitamos el tipo completo del iterador del mapa y la ubicación del nodo actual para ir teniendo referencia de este
        typename std::map<T, std::vector<std::pair<T, float>>>::iterator it_mapa = adjacency_list.find(currentNode);

        // Recorremos la lista de adyacencia
        // Se usa const y & para no generar copias innecesarias y usar el valor original del pair
        for (const std::pair<T, float>& edge : it_mapa->second) {
            //El vecino es el primer elemento del pair
            T neighbor = edge.first; 

            // Si el vecino no ha sido visitado
            // Usamos find() en el map para verificar si existe la clave, o la creamos y chequeamos el valor
            if (visited.find(neighbor) == visited.end() || visited[neighbor] == false) {
                // Marcar como visitado
                visited[neighbor] = true; 
                q.push(neighbor);
            }
        }
    }
    std::cout << std::endl;
}


// Función publica 
template <class T>
void Graph<T>::DFS(T startNode) {
    if (!findNode(startNode).first) {
        std::cout << "El nodo de inicio no existe." << std::endl;
        return;
    }
    std::map<T, bool> visited; 
    
    //Llamar a la función recurrente
    DFS_Recursive(startNode, visited);
    std::cout << std::endl;
}

// Función recursiva 
template <class T>
void Graph<T>::DFS_Recursive(T currentNode, std::map<T, bool>& visited) {
    
    //Se marca el nodo actual como visitado
    visited[currentNode] = true;
    
    //visitar el nodo 
    std::cout << currentNode << " "; 

    //Inicializar el iterador en el nodo actual usando la funcion find de map
    typename std::map<T, std::vector<std::pair<T, float>>>::iterator it_mapa = adjacency_list.find(currentNode);

    // Se recorren todos los neighbora del node actual
    for (const std::pair<T, float>& edge : it_mapa->second) {

        // El vecino es el primer elemento del pair
        T neighbor = edge.first; 

        //Si el vecino no ha sido visitado se llama recursivamente
        // Se verifica si la clave no existe o si existe y es false
        if (visited.find(neighbor) == visited.end() || visited[neighbor] == false) {
            DFS_Recursive(neighbor, visited);
        }
    }
}

template <class T>
void Graph<T>::setDirected(bool directed) {
    this->is_directed = directed; 
}

template <class T>
std::vector<long> Graph<T>::Dijkstra(long start_id, long end_id, const std::vector<Point>& vector_aux_puntos){
    
}