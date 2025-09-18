#include "ArbolBinarioOrd.h"
#include <iostream>
#include <queue>

template <class T>
ArbolBinarioOrd<T>::ArbolBinarioOrd() {
    this->raiz = nullptr;
}

template <class T>
ArbolBinarioOrd<T>::~ArbolBinarioOrd() {
    if(this->raiz != nullptr){
        delete this->raiz; // El destructor de NodoGeneral<T> libera los descendientes
        this->raiz = nullptr;
    }
}

template <class T>
bool ArbolBinarioOrd<T>::esVacio() {
    return this->raiz == nullptr;
}

template <class T>
T ArbolBinarioOrd<T>::datoRaiz() {
    return (this->raiz)->obtenerDato();  
}

/*
template <class T>
void ArbolGeneral<T>::fijarRaiz(NodoGeneral<T>* nraiz) {
    this->raiz = nraiz;
}
*/

//PUEDE SER ITERATIVA
template <class T>
bool ArbolBinarioOrd<T>::insertar(T val) {
    NodoBinario<T>* nodo = this->raiz;
    NodoBinario<T>* padre = this->raiz;
    bool insertado = false;
    bool duplicado = false;

    while(nodo != nullptr){
        padre = nodo;
        if (val < nodo->obtenerDato()){
            nodo = nodo->obtenerHijoIzq();
        }else if (val > nodo->obtenerDato()){
            nodo = nodo->obtenerHijoDer();
        }else{
            duplicado = true;
            break;
        }
    }
    if (!duplicado){
        NodoBinario<T>* nuevo = new NodoBinario<T>(val);
        if(nuevo != nullptr){
            if(val < padre->obtenerDato()){
                padre->fijarHijoIzq(nuevo);
            }else
                padre->fijarHijoDer(nuevo);
        }
        insertado = true;
    }
    return insertado;
}

//PUEDE SER ITERATIVA -- por implementar
template <class T>
bool ArbolBinarioOrd<T>::eliminarNodo(T val) {
    //Comparar con dato en nodo para bajar por izq o der
    //y para saber si val esta en el arbol

    /*
        Si val esta en el arbol:
        verificar situacion de eliminacion
        1. nodo hoja, borrarlo
        2. nodo con un solo hijo, usar hijo para reemplazar nodo
        3. nodo con dos hijos, usar maximo del subarbol izquierdo
        para reemplazar el nodo
    */
}



template <class T>
bool ArbolBinarioOrd<T>::buscar(T val) {
    NodoBinario<T>* nodo = this->raiz;
    bool encontrado = false;

    while(nodo != nullptr && !encontrado){
        if (val < nodo->obtenerDato()){
            nodo = nodo->obtenerHijoIzq();
        }else if (val > nodo->obtenerDato()){
            nodo = nodo->obtenerHijoDer();
        }else{
            encontrado = true;
        }
    }
    return encontrado;
}




template <class T>
int ArbolBinarioOrd<T>::altura() {
    if (this->esVacio()) {
        return -1;
    }
    return this->altura(this->raiz);
}


template <class T>
int ArbolBinarioOrd<T>::altura(NodoBinario<T>* nodo) {
    int valt;

    if (nodo->esHoja()){
        valt = 0;
    } else {
        int valt_izq = -1;
        int valt_der = -1;
        //Antes de llamar la función recurrente se verifica si el hijo no es nulo
        if(nodo->obtenerHijoIzq != nullptr)
            valt_izq = this->altura(nodo->obtenerHijoIzq());
        if(nodo->obtenerHijoDer != nullptr)
            valt_der = this->altura(nodo->obtenerHijoDer());
        if(valt_izq > valt_der)
            valt = valt_izq + 1;
        else
            valt = valt_der + 1;
    }

    return valt; 
    
}



//Recurrente -- por implementar
template <class T>
unsigned int ArbolGeneral<T>::tamano() {
    if (this->esVacio()) {
        return 0;
    }
    return this->tamano(this->raiz);
}

template <class T>
unsigned int ArbolGeneral<T>::tamano(NodoGeneral<T>* nodo) {
    if (nodo == nullptr) {
        return 0;
    }
    unsigned int tam = 1;
    typename std::list<NodoGeneral<T>*>::iterator it;
    for (it = nodo->desc.begin(); it != nodo->desc.end(); ++it) {
        tam += tamano(*it);
    }
    return tam;
}


//RECURRENTE -- por implementar
template <class T>
void ArbolBinarioOrd<T>::preOrden() {
    if (!this->esVacio()) {
        this->preOrden(this->raiz);
    }
}

template <class T>
void ArbolBinarioOrd<T>::preOrden(NodoBinario<T>* nodo) {
    std::cout << nodo->obtenerDato() << " ";
    typename std::list<NodoGeneral<T>*>::iterator it;
    for (it = nodo->desc.begin(); it != nodo->desc.end(); ++it) {
        this->preOrden(*it);
    }
}

//-- Por implementar
template <class T>
void ArbolGeneral<T>::posOrden() {
    if (!this->esVacio()) {
        this->posOrden(this->raiz);
    }
}


template <class T>
void ArbolBinarioOrd<T>::posOrden(NodoBinario<T>* nodo) {
    typename std::list<NodoGeneral<T>*>::iterator it;
    for (it = nodo->desc.begin(); it != nodo->desc.end(); ++it) {
        posOrden(*it);
    }
    std::cout << nodo->obtenerDato() << " ";
}

//RECURRENTE
template <class T>
void ArbolBinarioOrd<T>::inOrden() {
    if (!this->esVacio()) {
        this->inOrden(this->raiz);
    }
}

template <class T>
void ArbolBinarioOrd<T>::inOrden(NodoBinario<T>* nodo) {
    if (nodo != nullptr){
        this->inOrden(nodo->obtenerHijoIzq());
        std::cout << nodo->obtenerDato() << " ";
        this->inOrden(nodo->obtenerHijoDer());
    } 
}

//PUEDE SER ITERATIVA
template <class T>
void ArbolBinarioOrd<T>::nivelOrden() {
    if (!this->esVacio()){ 
        
        std::queue<NodoBinario<T>*> cola;
        cola.push(this->raiz);
        while (!cola.empty()) {
            NodoBinario<T>* actual = cola.front();
            cola.pop();
            std::cout << actual->obtenerDato() << " ";
            if(nodo->obtenerHijoIzq != nullptr)
                cola.push(nodo->obtenerHijoIzq());
            if(nodo->obtenerHijoDer != nullptr)
                cola.push(nodo->obtenerHijoDer());
            
        }
    }

}
