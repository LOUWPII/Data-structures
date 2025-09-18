#include "ArbolGeneral.h"
#include <iostream>

template <class T>
ArbolGeneral<T>::ArbolGeneral() {
    this->raiz = nullptr;
}

template <class T>
ArbolGeneral<T>::ArbolGeneral(T val) {
    NodoGeneral<T> *nuevo_nodo = new NodoGeneral<T>();
    nuevo_nodo->fijarDato(val);
    this->raiz = nuevo_nodo;
}

template <class T>
ArbolGeneral<T>::~ArbolGeneral() {
    delete this->raiz; // El destructor de NodoGeneral<T> libera los descendientes
    this->raiz = nullptr;
}

template <class T>
bool ArbolGeneral<T>::esVacio() {
    return this->raiz == nullptr;
}

template <class T>
NodoGeneral<T>* ArbolGeneral<T>::obtenerRaiz() {
    return this->raiz;
}

template <class T>
void ArbolGeneral<T>::fijarRaiz(NodoGeneral<T>* nraiz) {
    this->raiz = nraiz;
}

template <class T>
bool ArbolGeneral<T>::insertarNodo(T padre, T n) {
    if (this->esVacio()) {
        NodoGeneral<T>* nuevo_nodo = new NodoGeneral<T>();
        nuevo_nodo->fijarDato(n);
        this->fijarRaiz(nuevo_nodo);
        return true;
    }
    return insertarNodo(this->raiz, padre, n);
}

template <class T>
bool ArbolGeneral<T>::insertarNodo(NodoGeneral<T>* nodo, T padre, T n) {
    if (!nodo) return false;
    if (nodo->obtenerDato() == padre) {
        nodo->adicionarDesc(n);
        return true;
    }
    typename std::list<NodoGeneral<T>*>::iterator it;
    for (it = nodo->desc.begin(); it != nodo->desc.end(); ++it) {
        if (insertarNodo(*it, padre, n)) {
            return true;
        }
    }
    return false;
}

template <class T>
bool ArbolGeneral<T>::eliminarNodo(T n) {
    if (this->esVacio()) {
        return false;
    }
    if (this->raiz->obtenerDato() == n) {
        delete this->raiz;
        this->raiz = nullptr;
        return true;
    }
    return this->eliminarNodoRec(this->raiz, n);
}

template <class T>
bool ArbolGeneral<T>::eliminarNodoRec(NodoGeneral<T>* nodo, T n) {
    if (nodo->eliminarDesc(n)) {
        return true;
    }
    typename std::list<NodoGeneral<T>*>::iterator it;
    for (it = nodo->desc.begin(); it != nodo->desc.end(); ++it) {
        if (eliminarNodoRec(*it, n)) {
            return true;
        }
    }
    return false;
}

template <class T>
bool ArbolGeneral<T>::buscar(T n) {
    if (this->esVacio())
        return false;
    if (this->raiz->obtenerDato() == n)
        return true;
    return this->buscarRec(this->raiz, n);
}

template <class T>
bool ArbolGeneral<T>::buscarRec(NodoGeneral<T>* nodo, T n) {
    if (nodo->obtenerDato() == n)
        return true;
    typename std::list<NodoGeneral<T>*>::iterator it;
    for (it = nodo->desc.begin(); it != nodo->desc.end(); ++it) {
        if (buscarRec(*it, n))
            return true;
    }
    return false;
}

template <class T>
int ArbolGeneral<T>::altura() {
    if (this->esVacio()) {
        return -1;
    }
    return this->altura(this->raiz);
}

template <class T>
int ArbolGeneral<T>::altura(NodoGeneral<T>* nodo) {
    int alt = -1;
    if (nodo->esHoja()) {
        alt = 0;
    } else {
        int alth;
        typename std::list<NodoGeneral<T>*>::iterator it;
        for (it = nodo->desc.begin(); it != nodo->desc.end(); ++it) {
            alth = this->altura(*it);
            if (alt < alth + 1)
                alt = alth + 1;
        }
    }
    return alt;
}

template <class T>
unsigned int ArbolGeneral<T>::tamano() {
    if (this->esVacio()) {
        return 0;
    }
    return this->tamanoRec(this->raiz);
}

template <class T>
unsigned int ArbolGeneral<T>::tamanoRec(NodoGeneral<T>* nodo) {
    if (nodo == nullptr) {
        return 0;
    }
    unsigned int tam = 1;
    typename std::list<NodoGeneral<T>*>::iterator it;
    for (it = nodo->desc.begin(); it != nodo->desc.end(); ++it) {
        tam += tamanoRec(*it);
    }
    return tam;
}

template <class T>
void ArbolGeneral<T>::preOrden() {
    if (!this->esVacio()) {
        this->preOrdenRec(this->raiz);
    }
}

template <class T>
void ArbolGeneral<T>::preOrdenRec(NodoGeneral<T>* nodo) {
    std::cout << nodo->obtenerDato() << " ";
    typename std::list<NodoGeneral<T>*>::iterator it;
    for (it = nodo->desc.begin(); it != nodo->desc.end(); ++it) {
        this->preOrdenRec(*it);
    }
}

template <class T>
void ArbolGeneral<T>::posOrden() {
    if (!this->esVacio()) {
        this->posOrdenRec(this->raiz);
    }
}

template <class T>
void ArbolGeneral<T>::posOrdenRec(NodoGeneral<T>* nodo) {
    typename std::list<NodoGeneral<T>*>::iterator it;
    for (it = nodo->desc.begin(); it != nodo->desc.end(); ++it) {
        posOrdenRec(*it);
    }
    std::cout << nodo->obtenerDato() << " ";
}

template <class T>
void ArbolGeneral<T>::inorden() {
    if (!this->esVacio()) {
        this->inordenRec(this->raiz);
    }
}

template <class T>
void ArbolGeneral<T>::inordenRec(NodoGeneral<T>* nodo) {
    if (!nodo) return;
    typename std::list<NodoGeneral<T>*>::iterator it = nodo->desc.begin();
    if (it != nodo->desc.end()) {
        inordenRec(*it);
        ++it;
    }
    std::cout << nodo->obtenerDato() << " ";
    for (; it != nodo->desc.end(); ++it) {
        inordenRec(*it);
    }
}

template <class T>
void ArbolGeneral<T>::nivelOrden() {
    if (this->esVacio()) return;
    std::queue<NodoGeneral<T>*> cola;
    cola.push(this->raiz);
    while (!cola.empty()) {
        NodoGeneral<T>* actual = cola.front();
        cola.pop();
        std::cout << actual->obtenerDato() << " ";
        typename std::list<NodoGeneral<T>*>::iterator it;
        for (it = actual->desc.begin(); it != actual->desc.end(); ++it) {
            cola.push(*it);
        }
    }
}