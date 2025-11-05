#include "Graph.h"
#include <iostream>
#include <string>

// Es necesario incluir <map>, <vector>, <utility>, <queue> y <set>
// en el archivo que contiene las definiciones de las funciones
// O aquí si no están en el .cpp/header.

void test_grafo_dirigido() {
    std::cout << "========================================" << std::endl;
    std::cout << "       PRUEBA: GRAFO DIRIGIDO" << std::endl;
    std::cout << "========================================" << std::endl;


    Graph<std::string> g_dirigido; 
    g_dirigido.setDirected(true);
    

    // ---  Inserción de Vértices ---
    std::cout << "1. Insertando Nodos (v0 a v6)..." << std::endl;
    g_dirigido.addNode("v0");
    g_dirigido.addNode("v1");
    g_dirigido.addNode("v2");
    g_dirigido.addNode("v3");
    g_dirigido.addNode("v4");
    g_dirigido.addNode("v5");
    g_dirigido.addNode("v6");

    // ---  Inserción de Aristas ---
    std::cout << "2. Insertando Aristas con peso..." << std::endl;
    g_dirigido.addEdge("v0", "v1", 0.5f);
    g_dirigido.addEdge("v0", "v2", 0.5f);
    g_dirigido.addEdge("v1", "v3", 0.6f);
    g_dirigido.addEdge("v2", "v3", 0.7f);
    g_dirigido.addEdge("v2", "v4", 0.6f);
    g_dirigido.addEdge("v3", "v4", 0.3f);
    g_dirigido.addEdge("v3", "v5", 0.3f);
    g_dirigido.addEdge("v3", "v6", 0.6f);
    g_dirigido.addEdge("v4", "v6", 0.2f);
    g_dirigido.addEdge("v5", "v6", 0.4f);

    std::cout << "\nPruebas de Recorridos:" << std::endl;
    std::cout << " BFS (desde v0): ";
    g_dirigido.BFS("v0"); 
    
    std::cout << " DFS (desde v0): ";
    g_dirigido.DFS("v0"); 
}


void test_grafo_no_dirigido() {
    std::cout << "\n\n========================================" << std::endl;
    std::cout << "       PRUEBA: GRAFO NO DIRIGIDO" << std::endl;
    std::cout << "========================================" << std::endl;
    
    Graph<std::string> g_no_dirigido; 
    
    // ---  Inserción de Vértices ---
    std::cout << "1. Insertando Nodos (A, B, D, J, L, P, S, T)..." << std::endl;
    g_no_dirigido.addNode("A"); g_no_dirigido.addNode("B");
    g_no_dirigido.addNode("D"); g_no_dirigido.addNode("J");
    g_no_dirigido.addNode("L"); g_no_dirigido.addNode("P");
    g_no_dirigido.addNode("S"); g_no_dirigido.addNode("T");

    // ---  Inserción de Aristas ---
    std::cout << "2. Insertando Aristas con peso..." << std::endl;
    g_no_dirigido.addEdge("A", "L", 0.32f);
    g_no_dirigido.addEdge("A", "D", 0.28f);
    g_no_dirigido.addEdge("A", "B", 0.35f);
    g_no_dirigido.addEdge("L", "D", 0.19f);
    g_no_dirigido.addEdge("L", "P", 0.29f);
    g_no_dirigido.addEdge("D", "B", 0.37f);
    g_no_dirigido.addEdge("D", "J", 0.10f);
    g_no_dirigido.addEdge("D", "S", 0.34f);
    g_no_dirigido.addEdge("J", "B", 0.38f);
    g_no_dirigido.addEdge("J", "T", 0.58f);
    g_no_dirigido.addEdge("J", "S", 0.26f);
    g_no_dirigido.addEdge("P", "S", 0.17f);
    g_no_dirigido.addEdge("P", "T", 0.52f);
    g_no_dirigido.addEdge("S", "T", 0.40f);
    g_no_dirigido.addEdge("B", "T", 0.93f);


    // --- Pruebas de Recorridos ---
    std::cout << "\n4. Pruebas de Recorridos:" << std::endl;
    std::cout << " BFS (desde A): ";
    g_no_dirigido.BFS("A"); 
    
    std::cout << " DFS (desde A): ";
    g_no_dirigido.DFS("A");
}


int main() {
    test_grafo_dirigido();
    test_grafo_no_dirigido();
    return 0;
}