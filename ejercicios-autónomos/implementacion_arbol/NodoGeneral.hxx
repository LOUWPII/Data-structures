#include "NodoGeneral.h"

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

template <class T>
T& NodoGeneral<T>::obtenerDato() {
    return this->dato;
}

template <class T>
void NodoGeneral<T>::fijarDato(T val) {
    this->dato = val;
}

template <class T>
void NodoGeneral<T>::limpiarLista() {
    typename std::list<NodoGeneral<T>*>::iterator it;
    for (it = this->desc.begin(); it != this->desc.end(); ++it) {
        delete *it;
    }
    this->desc.clear();
}

template <class T>
void NodoGeneral<T>::adicionarDesc(T nval) {
    NodoGeneral<T> *nuevo_nodo = new NodoGeneral<T>();
    nuevo_nodo->fijarDato(nval);
    this->desc.push_back(nuevo_nodo);
}

template <class T>
bool NodoGeneral<T>::eliminarDesc(T val) {
    bool eliminado = false;
    typename std::list<NodoGeneral<T>*>::iterator it;
    for (it = this->desc.begin(); it != this->desc.end(); ++it) {
        NodoGeneral<T>* aux = *it;
        if (aux->obtenerDato() == val) {
            delete *it;
            this->desc.erase(it);
            eliminado = true;
            break;
        }
    }
    return eliminado;
}

template <class T>
bool NodoGeneral<T>::esHoja() {
    return this->desc.size() == 0;
}