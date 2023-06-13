# README - KD-Tree Structure

This repository contains the implementation of a KD-Tree structure, which is a data structure used for efficient multidimensional search operations. The KD-Tree supports insertion, search, and k-nearest neighbor queries in a space of N dimensions. Here is an overview of the files and their features:
* Instantiate a KDTree object with the desired number of dimensions and element type:
```cpp
KDTree<N, ElemType> kdTree;
```

## File: KDTree.hpp
This file defines the KDTree class template, which represents the KD-Tree structure. It includes the necessary header files and provides the implementation for various operations such as construction, destruction, insertion, search, and k-nearest neighbor queries. The class uses a Node struct internally to store the key-value pairs and maintain the tree structure. The KDTree class supports both mutable and immutable access to the elements.
The `KDTree.hpp` file contains the definition of the KDTree class, which includes the following functionality:

- `KDTree()`: Constructor of the KDTree class.
- `~KDTree()`: Destructor of the KDTree class.
- `KDTree(const KDTree& rhs)`: Constructor copy of the KDTree class.
- `KDTree& operator=(const KDTree& rhs)`: Assignment operator of the KDTree class.
- `size_t dimension() const`: Returns the number of dimensions of the tree.
- `size_t size() const`: Returns the number of points stored in the tree.
- `bool empty() const`: Check if the tree is empty.
- `bool contains(const Point<N>& pt) const`: Check if the tree contains a given point.
- `void insert(const Point<N>& pt, const ElemType& value)`: Inserts a point and its associated value into the tree.
- `ElemType& operator[](const Point<N>& pt)`: Overloading of the operator [] to access the value associated with a point in the tree.
- `ElemType& at(const Point<N>& pt)`: Returns a reference to the value associated with a point in the tree.
- `const ElemType& at(const Point<N>& pt) const`: Returns a constant reference to the value associated with a point in the tree.
- `ElemType knn_value(const Point<N>& key, size_t k) const` : Returns the closest value to a given point using the k-nearest neighbors algorithm.
- `std::vector<ElemType> knn_query(const Point<N>& key, size_t k) const`: Returns the values of the k closest points to a given point.

### Implementation Details
The KDTree is implemented using nodes that contain an N-dimensional point and an associated value. Each node is split into subtrees recursively, toggling between dimensions, allowing for efficient point-in-space search.

Some key features of the implementation are:
- `deleteNode(Node* currentNode)`: Recursively deletes all nodes from the tree.
- `copyTree(Node* rootNode)`: Recursively copies all nodes in the tree.
- `KNNValueRecurse(const Point<N>& key, BoundedPQueue<Node*>& nearestPQ, Node* currentNode) const`: Walks the tree recursively to find the nearest k-neighbors to a given point.
- `FindMostCommonValueInPQ(BoundedPQueue<Node*> nearestPQ) const`: Find the most common value among the nearest neighbors.

## File: Point.hpp
This file defines the Point class, which represents a point in N-dimensional space. The Point class is used to store the keys in the KDTree structure.
The `Point.hpp` file contains the definition of the Point class, which includes the following functionality:

- `size_t size() const`: Returns the number of dimensions of the point.
- `double& operator[](size_t index)`: Overload of the operator [] to access the coordinates of the point.
- `double operator[](size_t index) const`: Overloading of the operator [] to access the coordinates of the point constantly.
- `iterator begin()`: Returns an iterator at the beginning of the coordinates of the point.
- `iterator end()`: Returns an iterator at the end of the coordinates of the point.
- `const_iterator begin() const`: Returns a constant iterator at the beginning of the coordinates of the point.
- `const_iterator end() const`: Returns a constant iterator at the end of the coordinates of the point.
- `friend std::ostream& operator<<(std::ostream& out, const Point& lhs)`: Insertion operator overload to print point in the format [ x1 - x2 - ... - xn ].
- `double distance(const Point<N>& one, const Point<N>& two)`: Function to calculate the distance between two points in space.
- `bool operator==(const Point<N>& one, const Point<N>& two)`: Overload of the equality operator to check if two points are equal.
- `bool operator!=(const Point<N>& one, const Point<N>& two)`: Overload of the inequality operator to check if two points are different.

### Use
To use the Point class, the following steps must be followed:
1. Include the `Point.hpp` header file in the program.
2. Create objects of class Point specifying the number of dimensions.
3. Access the coordinates of the point using the [] operator.
4. Use the provided functionalities, such as calculating the distance between points, checking for equality or inequality, and iterating over the coordinates of the point.

### Implementation Details
The Point class is implemented using an array of type `double` to store the coordinates of the point. Overloaded functions and operators are used to make it easier to access and manipulate point coordinates, as well as to perform calculations and comparisons between points.

The `distance` function calculates the Euclidean distance between two points using the appropriate mathematical formula.

### Usage Example
```cpp
#include "Point.hpp"
#include <iostream>

int main() {
   // Create a 3-dimensional point
   Point<3>p;
  
   // Access the coordinates of the point
   p[0] = 1.0;
   p[1] = 2.0;
   p[2] = 3.0;
  
   // Print the point
   std::cout << "Point: " << p << std::endl;
  
   // Calculate the distance between two points
   Point<3>q;
   q[0] = 4.0;
   q[1] = 5.0;
   q[2] = 6.0;
   double dist = distance(p, q);
   std::cout << "Distance between points: " << dist << std::endl;
  
   return 0;
}
```
This is just a basic example of using the Point class. You can use the provided functionalities according to your specific needs.
- Remember that you must include the `KDTree.hpp` and `Point.hpp` header files in your program and compile it correctly in order to use the provided classes and functionality.
## File: BoundedPQueue.hpp
This file defines the BoundedPQueue class, which is a bounded priority queue used in the k-nearest neighbor query implementation. The BoundedPQueue class allows efficient insertion and retrieval of the k nearest nodes based on their distance to a given key.
## Methods
Use the available methods to perform operations on the KD-Tree. Some of the key methods include:

* dimension(): Returns the number of dimensions of the KD-Tree.
* size(): Returns the number of points stored in the KD-Tree.
* empty(): Checks if the KD-Tree is empty.
* contains(const Point<N>& pt): Checks if a point is present in the KD-Tree.
* insert(const Point<N>& pt, const ElemType& value): Inserts a point with its associated value into the KD-Tree.
* operator[](const Point<N>& pt): Accesses the value associated with a specific point in the KD-Tree.
* at(const Point<N>& pt): Accesses the value associated with a specific point in the KD-Tree, with bounds checking.
* knn_value(const Point<N>& key, size_t k): Returns the value of the k-nearest neighbors to a given point in the KD-Tree.
* knn_query(const Point<N>& key, size_t k): Returns a vector of values of the k-nearest neighbors to a given point in the KD-Tree.
## Usage:

* Include the KDTree.hpp, Point.hpp, and BoundedPQueue.hpp header files in your project.
* Instantiate a KDTree object with the desired dimensions and element type, for example:
### KDTree<3, int> tree;
* Use the various member functions provided by the KDTree class to perform operations such as insertion, search, and k-nearest neighbor queries.
### Note: Make sure to compile and link the necessary source files along with your project to properly use the KD-Tree structure.

## Contributing:

If you wish to contribute to this project, you can do so by following these steps:

* Fork this repository and clone it to your local machine.
* Make desired modifications or improvements to the existing files.
* Create a pull request for your changes to be reviewed and incorporated into the main project.
Please adhere to good coding practices, comment your code, and ensure that any modifications align with the existing design and functionality.

I hope this KD-Tree structure proves useful for your multidimensional search needs. If you have any questions or suggestions, feel free to reach out. Happy coding!
