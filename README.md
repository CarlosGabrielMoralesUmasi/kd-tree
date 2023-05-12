# README - KD-Tree Structure

This repository contains the implementation of a KD-Tree structure, which is a data structure used for efficient multidimensional search operations. The KD-Tree supports insertion, search, and k-nearest neighbor queries in a space of N dimensions. Here is an overview of the files and their features:

## File: KDTree.hpp
This file defines the KDTree class template, which represents the KD-Tree structure. It includes the necessary header files and provides the implementation for various operations such as construction, destruction, insertion, search, and k-nearest neighbor queries. The class uses a Node struct internally to store the key-value pairs and maintain the tree structure. The KDTree class supports both mutable and immutable access to the elements.

## File: Point.hpp
This file defines the Point class, which represents a point in N-dimensional space. The Point class is used to store the keys in the KDTree structure.

## File: BoundedPQueue.hpp
This file defines the BoundedPQueue class, which is a bounded priority queue used in the k-nearest neighbor query implementation. The BoundedPQueue class allows efficient insertion and retrieval of the k nearest nodes based on their distance to a given key.

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
