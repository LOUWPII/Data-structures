#ifndef __NODOGENERAL_H__
#define __NODOGENERAL_H__
#include <list>

template <class T>
class NodoGeneral {
protected:
    T dato;
public:
    std::list<NodoGeneral<T>*> desc;
    NodoGeneral();
    ~NodoGeneral();
    T& obtenerDato();
    void fijarDato(T val);
    void limpiarLista();
    void adicionarDesc(T nval);
    bool eliminarDesc(T val);
    bool esHoja();
};

#include "NodoGeneral.hxx"

#endif