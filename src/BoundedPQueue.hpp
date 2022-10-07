
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
      * valor de prioridad más pequeño, luego elimina ese elemento
      * de la cola.
      */
    T dequeueMin();

    /**
     size_t size() const;
     bool empty() const;
     Devuelve el número de elementos en la cola y si la cola está vacía, respectivamente.
     */
    size_t size() const;
    bool empty() const;
    
    /*
      Devuelve el número máximo de elementos que se pueden almacenado en la cola.
     */
    size_t maxSize() const;
    
    /*
      best() devuelve la prioridad más pequeña de un elemento
       almacenado en el contenedor (es decir, la prioridad del
       elemento que se sacará de la cola primero usando dequeueMin).
       worst () devuelve la mayor prioridad de un elemento
       almacenado en el contenedor. Si un elemento está en cola
       con una prioridad superior a este valor, automáticamente
       ser eliminado de la cola. Ambas funciones regresan numeric_limits<double>::infinity() si la cola es vacío.
     */
    double best()  const;
    double worst() const;
    void enqueue(const T& value, double priority);

private:
    /*
     Esta clase está superpuesta en una asignación multimapa de prioridades a elementos con esas prioridades.
     */
    multimap<double, T> elems;
    size_t maximumSize;
};

template <typename T>
BoundedPQueue<T>::BoundedPQueue(size_t maxSize) {
    maximumSize = maxSize;
}

/*enqueue agrega el elemento al mapa, luego elimina el último elemento delmap si el tamaño excede el tamaño máximo.
 */
template <typename T>
void BoundedPQueue<T>::enqueue(const T& value, double priority) {
    // Agregue el elemento a la colección.
    elems.insert(make_pair(priority, value));

    // Si hay demasiados elementos en la cola, deje el último.
    if (size() > maxSize()) {
        typename multimap<double, T>::iterator last = elems.end();
        --last; //Ahora apunta al elemento de mayor prioridad
        elems.erase(last);
    }
}

/*
 dequeueMin copia el elemento más bajo del mapa (el señalado por begin()) y luego lo elimina.
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
   Las funciones mejor () y peor () verifican si la cola está vacía, y si es así devuelve infinito.
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