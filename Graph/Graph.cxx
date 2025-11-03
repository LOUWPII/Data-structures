
#include "Graph.h"

    template <class T>
    Graph<T>::Graph(){}

    template <class T>
    Graph<T>::~Graph(){}

    template <class T>
    bool Graph<T>::addNode(T nNode){
        //Si el nodo ya existe entonces no se puede insertar
        if (findNode(nNode))
            return false;

        adjacency_list[nNode];    
        return true;
    }

template <class T>
bool Graph<T>::addEdge(T source, T destination, float weight){
    
    // Verificar si los nodos existen 
    if (!findNode(source) || !findNode(destination)) {
        return false; 
    }

    // se llama a la función de findEdge que devuelve un pair
    std::pair<bool, float> edge_check = findEdge(source, destination);

    // Si la arista no exite ya en el grafo
    if (edge_check.first == false){

        //Se Define la arista con su destino y peso
        std::pair<T, float> new_edge = {destination, weight};

        //Añadir la arista en la lista de adyacencia  
        adjacency_list[source].push_back(new_edge);

        // Se verifica si es dirigido o no
        if (!is_directed) {
            std::pair<T, float> reverse_edge = {source, weight};
            adjacency_list[destination].push_back(reverse_edge);
        }
        
        return true;
    }
    
    // La arista como ya existia pued no se puede insertar arista
    return false;
}
    

    template <class T>
    bool Graph<T>::deleteNode(T nNode){


        //Primero buscamos si existe el node a eliminar
        if (!findNode(nNode)) {
            return false; 
        }
        
        //Si el node existe se elimina la pareja clave valor del map - que seria el node y sus ||aristas de salida||
        adjacency_list.erase(nNode);

        //Ahora se eliminan las ||aristas de entrada||
        //Primero se crea un iterador para el map
        std::map<T, std::vector<std::pair<T, float>>>::iterator it_mapa;

        //Ahora se recorre el map
        for (it_mapa = adjacency_list.begin(); it_mapa != adjacency_list.end(); ++it_mapa) {
        
        // 1. Iterador para recorrer el vector de aristas - este iterador apunta a la pareja actual a la que apunta el iterador del map
            std::vector<std::pair<T, float>>::iterator it_vector = it_mapa->second.begin();
            
            // Recorremos el vector it_mapa->second
            while (it_vector != it_mapa->second.end()) {
                
                // Verificamos si la arista apunta al node que estamos eliminando.
                if (it_vector->first == nNode) {
                    // Usamos erase() sobre el vector referenciado it_mapa->second.
                    it_vector = it_mapa->second.erase(it_vector);
                } else {
                    // Si la arista no apunta al node a eliminar, avanzamos el iterador.
                    ++it_vector;
                }
            }
        }
        return true
    }

    template <class T>
    bool Graph<T>::deleteEdge(T source, T destination){
        
        bool edge_source_dest = deleteEdgeAux(source, destination);
        bool edge_dest_source = deleteEdgeAux(destination, source);
        if (!is_directed){
            //Si no es dirigido entonces se busca eliminar la arista de ida y de vuelta
            //Se usa una compuerta and ya que la eliminación es exitosa se la arista se elimina tanto del source -> dest y dest -> source
            return (edge_source_dest && edge_dest_source);
        }else{
            //Si es dirigido solamente nos aseguramos de que la arista source -> dest se elimine correctamente
            return(edge_source_dest);
        }

    }

    template <class T>
    bool Graph<T>::deleteEdgeAux(T source, T destination){
    
    bool edge_eliminada = false; 
    
    // 1. Verificar si el source y el destination existe
    if (!findNode(source).first || !findNode(destination).first){ 
        // Alguno de los nodes no existe, la función findNode devolvió false
        return false;
    }
    
    // El source existe
    typename std::map<T, std::vector<std::pair<T, float>>>::iterator it_mapa = adjacency_list.find(source);;
    
    // Obtenemos el iterador del vector
    std::vector<std::pair<T, float>>::iterator it_vector = it_mapa->second.begin();

    // Recorremos el vector y eliminamos arista
    while (it_vector != it_mapa->second.end()) {
        
        // Verificamos si la arista apunta a 'destination'
        if (it_vector->first == destination) {
            
            // Usamos erase() sobre el vector y reasignamos el iterador
            it_vector = it_mapa->second.erase(it_vector);
            edge_eliminada = true;
            
        } else {
            // La arista actual no es la 'destination', avanzamos
            ++it_vector;
        }
    }

    return edge_eliminada;
}
    template <class T>
    std::pair<bool, typename std::map<T, std::vector<std::pair<T, float>>>::iterator> Graph<T>::findNode (T nNode){
    
    // Se busca en el mapa el node
        std::map<T, std::vector<std::pair<T, float>>>::iterator it = adjacency_list.find(nNode);

        // Verificar el resultado de la búsqueda
        if (it != adjacency_list.end()) {
            // Si se encontró el nodo se devuelve true y el iterador a la parte del map donde está el node
            return std::pair<bool, typename std::map<T, std::vector<std::pair<T, float>>>::iterator>(true, it);
        } else {
            //Si no se encontró el nodo se devuelve false y el iterador a end()
            return std::pair<bool, typename std::map<T, std::vector<std::pair<T, float>>>::iterator>(false, adjacency_list.end());
        }
    }

    template <class T>
    std::pair<bool, float> Graph<T>::findEdge (T source , T destination){
    
        // se verifica si existen los node
        if (!findNode(source) || !findNode(destination)){
            //no existen los node, entonces retornamos false y un peso inválido.
            return std::pair<bool, float>(false, -1.0f);
        }
        
        std::map<T, std::vector<std::pair<T, float>>>::iterator it_mapa = adjacency_list.find(source);

        // Si por alguna razón la búsqueda anterior fallo entonces se devuelve el pair
        if (it_mapa == adjacency_list.end()) {
            return std::pair<bool, float>(false, -1.0f);
        }
        
        // Se busca la arista en el vector
        std::vector<std::pair<T, float>>::iterator it_vector = it_mapa->second.begin();
        
        while(it_vector != it_mapa->second.end()){
            if (it_vector->first == destination){
                // si se encuentra la arista se retorna true y el peso de la arista
                return std::pair<bool, float>(true, it_vector->second);
            }else{
                ++it_vector;
            }
        }
    }

    