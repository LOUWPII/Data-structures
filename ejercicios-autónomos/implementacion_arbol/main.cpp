#include "ArbolGeneral.h"
#include <iostream>

int main() {
    ArbolGeneral<int> arbol;
    arbol.insertarNodo(0, 1); // Raíz
    arbol.insertarNodo(1, 14);
    arbol.insertarNodo(1, 16);
    arbol.insertarNodo(1, 17);
    arbol.insertarNodo(14, 5);
    arbol.insertarNodo(5, 2);

    std::cout << "Preorden: ";
    arbol.preOrden();
    std::cout << "\nPosorden: ";
    arbol.posOrden();
    std::cout << "\nInorden: ";
    arbol.inorden();
    std::cout << "\nNivel orden: ";
    arbol.nivelOrden();
    std::cout << "\nAltura: " << arbol.altura();
    std::cout << "\nTamano: " << arbol.tamano() << std::endl;

    return 0;
}