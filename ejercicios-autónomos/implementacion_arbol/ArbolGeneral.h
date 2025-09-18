#ifndef __ARBOLGENERAL_H__
#define __ARBOLGENERAL_H__

#include "NodoGeneral.h"
#include <queue>

template <class T>
class ArbolGeneral {
protected:
    NodoGeneral<T>* raiz;
    bool insertarNodo(NodoGeneral<T>* nodo, T padre, T n);
    bool eliminarNodoRec(NodoGeneral<T>* nodo, T n);
    bool buscarRec(NodoGeneral<T>* nodo, T n);
    int altura(NodoGeneral<T>* nodo);
    unsigned int tamanoRec(NodoGeneral<T>* nodo);
    void preOrdenRec(NodoGeneral<T>* nodo);
    void posOrdenRec(NodoGeneral<T>* nodo);
    void inordenRec(NodoGeneral<T>* nodo);
public:
    ArbolGeneral();
    ArbolGeneral(T val);
    ~ArbolGeneral();
    bool esVacio();
    NodoGeneral<T>* obtenerRaiz();
    void fijarRaiz(NodoGeneral<T>* nraiz);
    bool insertarNodo(T padre, T n);
    bool eliminarNodo(T n);
    bool buscar(T n);
    int altura();
    unsigned int tamano();
    void preOrden();
    void posOrden();
    void inorden();
    void nivelOrden();
};

#include "ArbolGeneral.hxx"

#endif