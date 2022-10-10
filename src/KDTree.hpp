
#ifndef SRC_KDTREE_HPP_
#define SRC_KDTREE_HPP_

#include <cmath>
#include <iostream>
#include <set>
#include <stdexcept>
#include <utility>
#include <vector>
#include "Point.hpp"
#include "BoundedPQueue.hpp"

template <size_t N, typename ElemType>
class KDTree {
public:
    typedef std::pair<Point<N>, ElemType> value_type;

    KDTree();

    ~KDTree();

    KDTree(const KDTree& rhs);
    KDTree& operator=(const KDTree& rhs);

    size_t dimension() const;

    size_t size() const;
    bool empty() const;

    bool contains(const Point<N>& pt) const;

    void insert(const Point<N>& pt, const ElemType& value);

    ElemType& operator[](const Point<N>& pt);

    ElemType& at(const Point<N>& pt);
    const ElemType& at(const Point<N>& pt) const;

    ElemType knn_value(const Point<N>& key, size_t k) const;

    std::vector<ElemType> knn_query(const Point<N>& key, size_t k) const;


private:
    size_t dimension_;
    size_t size_;
    struct Node {

        Point<N> key;
        ElemType value;
        size_t level;

        Node* rNodePtr;
        Node* lNodePtr;
    };

    Node* root;
    Node* copyTree(Node* rootNode);
    size_t numElements;
    void deleteNode(Node* currentNode);
    void KNNValueRecurse(const Point<N>& key, BoundedPQueue<Node*>& nearestPQ, Node* currentNode) const;
    ElemType FindMostCommonValueInPQ(BoundedPQueue<Node*> nearestPQ) const;
};

template <size_t N, typename ElemType>
KDTree<N, ElemType>::KDTree() {
    size_ = 0;
    root = NULL;
}

template <size_t N, typename ElemType>
KDTree<N, ElemType>::~KDTree() {
    deleteNode(root);
    size_ = 0;
}

template <size_t N, typename ElemType>
void KDTree<N, ElemType>::deleteNode(Node* currentNode) {
    //Base Case
    if (currentNode == NULL) return;
    //Recursion
    deleteNode(currentNode->rNodePtr);
    deleteNode(currentNode->lNodePtr);
    delete currentNode;
}

template <size_t N, typename ElemType>
KDTree<N, ElemType>::KDTree(const KDTree& rhs) {
    root = copyTree(rhs.root);
    size_ = rhs.size_;
}

template <size_t N, typename ElemType>
KDTree<N, ElemType>& KDTree<N, ElemType>::operator=(const KDTree& rhs) {
    if (this != &rhs) {
        deleteNode(this->root); 

        root = copyTree(rhs.root);
        size_ = rhs.size_;
    }
    return *this;
}

template <size_t N, typename ElemType>
size_t KDTree<N, ElemType>::dimension() const {
    return N;
}

template <size_t N, typename ElemType>
size_t KDTree<N, ElemType>::size() const {
    return size_;
}

template <size_t N, typename ElemType>
bool KDTree<N, ElemType>::empty() const {
    // TODO(me): Fill this in.
    //return true;
    return size() == 0;
}

template <size_t N, typename ElemType>
bool KDTree<N, ElemType>::contains(const Point<N>& pt) const {
    Node* currentNode = root;
    while (currentNode != NULL) {
        if (currentNode->key == pt) return true;
        pt[currentNode->level % N] >= currentNode->key[currentNode->level % N] ? currentNode = currentNode->rNodePtr : currentNode = currentNode->lNodePtr;
    }
    return false;
}

template <size_t N, typename ElemType>
void KDTree<N, ElemType>::insert(const Point<N>& pt, const ElemType& value) {
    Node* currentNode = root;
    Node* prevNode = NULL;
    size_t level = 0;
    while (currentNode != NULL) {
        ++level;
        if (pt == currentNode->key) {//puntos duplicados
            currentNode->value = value;
            return;
        }
        size_t keyIndex = currentNode->level % N;//nivel
        if (pt[keyIndex] < currentNode->key[keyIndex]) {
            prevNode = currentNode;
            currentNode = currentNode->lNodePtr;
        }
        else if (pt[keyIndex] >= currentNode->key[keyIndex]) {
            prevNode = currentNode;
            currentNode = currentNode->rNodePtr;
        }
        else {
            cout << "error al insertar elementos" << endl;
            return;
        }
    }
    ++size_;
    Node* newNode = new Node;//nodo en el kd
    newNode->key = pt;
    newNode->value = value;
    newNode->level = level;
    newNode->rNodePtr = NULL;
    newNode->lNodePtr = NULL;

    if (currentNode == root) {
        root = newNode;
    }
    else {
        pt[prevNode->level % N] >= prevNode->key[prevNode->level % N] ? prevNode->rNodePtr = newNode : prevNode->lNodePtr = newNode;
    }
}

template <size_t N, typename ElemType>
ElemType& KDTree<N, ElemType>::operator[](const Point<N>& pt) {
    Node* currentNode = root;
    Node* prevNode = NULL;
    size_t level = 0;
    while (currentNode != NULL) {
        ++level;
        if (pt == currentNode->key) {
            return currentNode->value;
        }

        size_t keyIndex = currentNode->level % N;
        if (pt[keyIndex] < currentNode->key[keyIndex]) {
            prevNode = currentNode;
            currentNode = currentNode->lNodePtr;
        }
        else if (pt[keyIndex] >= currentNode->key[keyIndex]) {
            prevNode = currentNode;
            currentNode = currentNode->rNodePtr;
        }
        else {
            cout << "Error al insertar elemento" << endl;
        }
    }
    ++size_;
    Node* newNode = new Node;//insert en el kd
    newNode->key = pt;
    newNode->value = ElemType();
    newNode->level = level;
    newNode->rNodePtr = NULL;
    newNode->lNodePtr = NULL;

    if (currentNode == root) {
        root = newNode;
        return newNode->value;
    }
    else {
        pt[prevNode->level % N] >= prevNode->key[prevNode->level % N] ? prevNode->rNodePtr = newNode : prevNode->lNodePtr = newNode;
        return newNode->value;
    }
}

template <size_t N, typename ElemType>
ElemType& KDTree<N, ElemType>::at(const Point<N>& pt) {
    Node* currentNode = root;
    while (currentNode != NULL) {
        if (currentNode->key == pt) {
            return currentNode->value;
        }
        size_t keyIndex = currentNode->level % N;//encontrar el indice del key
        if (pt[keyIndex] < currentNode->key[keyIndex]) {//comparando los keys
            currentNode = currentNode->lNodePtr;
        }
        else {
            currentNode = currentNode->rNodePtr;
        }
    }
    throw out_of_range("no existe el punto");
}

template <size_t N, typename ElemType>
const ElemType& KDTree<N, ElemType>::at(const Point<N>& pt) const {
    Node* currentNode = root;
    while (currentNode != NULL) {
        if (currentNode->key == pt) {
            return currentNode->value;
        }
        size_t keyIndex = currentNode->level % N;
        if (pt[keyIndex] < currentNode->key[keyIndex]) {
            currentNode = currentNode->lNodePtr;
        }
        else {
            currentNode = currentNode->rNodePtr;
        }
    }
    throw out_of_range("");
}

template <size_t N, typename ElemType>
ElemType KDTree<N, ElemType>::knn_value(const Point<N>& key, size_t k) const {
    
    BoundedPQueue<Node*> nearestPQ(k);
    KNNValueRecurse(key, nearestPQ, root);

    return FindMostCommonValueInPQ(nearestPQ);
}

template<size_t N, typename ElemType>
void KDTree<N, ElemType>::KNNValueRecurse(const Point<N>& key, BoundedPQueue<Node*>& nearestPQ, Node* currentNode) const
{
    if (currentNode == NULL) return;
    nearestPQ.enqueue(currentNode, distance(currentNode->key, key));
    size_t keyIndex = currentNode->level % N;
    if (key[keyIndex] < currentNode->key[keyIndex])
    {
        KNNValueRecurse(key, nearestPQ, currentNode->lNodePtr);
        if ((nearestPQ.size() != nearestPQ.maxSize()) || fabs(currentNode->key[keyIndex] - key[keyIndex]) < nearestPQ.worst())
        {
            KNNValueRecurse(key, nearestPQ, currentNode->rNodePtr);
        }
    }
    else
    {
        KNNValueRecurse(key, nearestPQ, currentNode->rNodePtr);
        if ((nearestPQ.size() != nearestPQ.maxSize()) || fabs(currentNode->key[keyIndex] - key[keyIndex]) < nearestPQ.worst())
        {
            KNNValueRecurse(key, nearestPQ, currentNode->lNodePtr);
        }
    }
}

template <size_t N, typename ElemType>
std::vector<ElemType> KDTree<N, ElemType>::knn_query(const Point<N>& key,
    size_t k) const {
    ElemType new_element;
    return new_element;
}
template<size_t N, typename ElemType>
ElemType KDTree<N, ElemType>::FindMostCommonValueInPQ(BoundedPQueue<Node*> nearestPQ) const
{
    multiset<ElemType> values;
    while (!nearestPQ.empty())
    {
        values.insert((nearestPQ.dequeueMin())->value);
    }

    ElemType best;
    size_t bestFrequency = 0;
    for (typename multiset<ElemType>::iterator it = values.begin(); it != values.end(); ++it)
    {
        if (values.count(*it) > bestFrequency)
        {
            best = *it;
            bestFrequency = values.count(*it);
        }
    }
    return best;
}

// TODO(me): finish the implementation of the rest of the KDTree class

#endif  // SRC_KDTREE_HPP_
