
#ifndef BOUNDED_PQUEUE_INCLUDED
#define BOUNDED_PQUEUE_INCLUDED

#include <map>
#include <algorithm>
#include <limits>

using namespace std;

template <typename T>
class BoundedPQueue {
public:
    explicit BoundedPQueue(size_t maxSize);
/*
     * Devuelve el elemento de BoundedPQueue con el
      * valor de prioridad m�s peque�o, luego elimina ese elemento
      * de la cola.
      */
    T dequeueMin();

    /**
     size_t size() const;
     bool empty() const;
     Devuelve el n�mero de elementos en la cola y si la cola est� vac�a, respectivamente.
     */
    size_t size() const;
    bool empty() const;
    
    /*
      Devuelve el n�mero m�ximo de elementos que se pueden almacenado en la cola.
     */
    size_t maxSize() const;
    
    /*
      best() devuelve la prioridad m�s peque�a de un elemento
       almacenado en el contenedor (es decir, la prioridad del
       elemento que se sacar� de la cola primero usando dequeueMin).
       worst () devuelve la mayor prioridad de un elemento
       almacenado en el contenedor. Si un elemento est� en cola
       con una prioridad superior a este valor, autom�ticamente
       ser eliminado de la cola. Ambas funciones regresan numeric_limits<double>::infinity() si la cola es vac�o.
     */
    double best()  const;
    double worst() const;
    void enqueue(const T& value, double priority);

private:
    /*
     Esta clase est� superpuesta en una asignaci�n multimapa de prioridades a elementos con esas prioridades.
     */
    multimap<double, T> elems;
    size_t maximumSize;
};

template <typename T>
BoundedPQueue<T>::BoundedPQueue(size_t maxSize) {
    maximumSize = maxSize;
}

/*enqueue agrega el elemento al mapa, luego elimina el �ltimo elemento delmap si el tama�o excede el tama�o m�ximo.
 */
template <typename T>
void BoundedPQueue<T>::enqueue(const T& value, double priority) {
    // Agregue el elemento a la colecci�n.
    elems.insert(make_pair(priority, value));

    // Si hay demasiados elementos en la cola, deje el �ltimo.
    if (size() > maxSize()) {
        typename multimap<double, T>::iterator last = elems.end();
        --last; //Ahora apunta al elemento de mayor prioridad
        elems.erase(last);
    }
}

/*
 dequeueMin copia el elemento m�s bajo del mapa (el se�alado por begin()) y luego lo elimina.
 */
template <typename T>
T BoundedPQueue<T>::dequeueMin() {
    // Copiamos el mejor valor
    T result = elems.begin()->second;
    
    // Removemos en el map
    elems.erase(elems.begin());
    
    return result;
}
template <typename T>
size_t BoundedPQueue<T>::size() const {
    return elems.size();
}
template <typename T>
bool BoundedPQueue<T>::empty() const {
    return elems.empty();
}
template <typename T>
size_t BoundedPQueue<T>::maxSize() const {
    return maximumSize;
}
/*
   Las funciones mejor () y peor () verifican si la cola est� vac�a, y si es as� devuelve infinito.
  */
template <typename T>
double BoundedPQueue<T>::best() const {
    return empty()? numeric_limits<double>::infinity() : elems.begin()->first;
}

template <typename T>
double BoundedPQueue<T>::worst() const {
    return empty()? numeric_limits<double>::infinity() : elems.rbegin()->first;
}

#endif