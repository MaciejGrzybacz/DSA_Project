# Data Structures and Algorithms (DSA) Project

## Overview

This project is a comprehensive collection of classic data structures and algorithms implemented in C++. It aims to provide efficient, well-tested, and easy-to-understand implementations for educational purposes and practical use in software development.

## Table of Contents

- [Getting Started](#getting-started)
- [Project Structure](#project-structure)
- [Building and Testing](#building-and-testing)
- [Implemented Algorithms and Data Structures](#implemented-algorithms-and-data-structures)
- [Planned Implementations](#planned-implementations)
- [Contributing](#contributing)
- [License](#license)

## Getting Started

To get started with this project, clone the repository and ensure you have the following prerequisites:

- CMake (version 3.10 or higher)
- A C++23 compatible compiler
- Git (for cloning the repository and fetching Google Test)

```bash
git clone https://github.com/yourusername/DSA_Project.git
cd DSA_Project
mkdir build && cd build
cmake ..
make
```

## Project Structure

The project is structured as follows:

```
DSA_Project/
├── CMakeLists.txt
├── src/
│   ├── dynamic_programming/
│   ├── graph/
│       ├── dijkstra.h/cpp
│       ├── search.h/cpp
│   ├── sorting/
│   ├── string_algorithms/
│   └── data_structures/
├── tests/
│   ├── dynamic_programming/
│   ├── graph/
│       ├── dijkstra_test.cpp
│       ├── search_test.cpp
│   ├── sorting/
│   ├── string_algorithms/
│   └── data_structures/
└── README.md
```

## Building and Testing

To build the project and run tests:

```bash
cd build
cmake ..
make
ctest
```

## Implemented Algorithms and Data Structures

Currently, the project includes the following implementations:

### Algorithms
- Graph
    - Dijkstra's Algorithm

### Data Structures
- (To be added)

## Planned Implementations

### Algorithms

#### Sorting Algorithms
- Bubble Sort
- Quick Sort
- Merge Sort
- Heap Sort
- Insertion Sort
- Selection Sort
- Radix Sort

#### Graph Algorithms
- Depth-First Search (DFS)
- Breadth-First Search (BFS)
- Bellman-Ford Algorithm
- Floyd-Warshall Algorithm
- Kruskal's Algorithm
- Prim's Algorithm
- Topological Sort
- Strongly Connected Components (SCC)
- Dijkstra's Algorithm
- A* Search Algorithm
- Travelling Salesman Problem (TSP)
- Maximum Flow (Ford-Fulkerson Algorithm)
- Network Flow (Edmonds-Karp Algorithm)

#### Dynamic Programming
- Fibonacci Sequence
- Longest Common Subsequence
- Knapsack Problem
- Coin Change Problem
- Longest Increasing Subsequence
- Maximum Subarray Sum
- Minimum Cost Path
- Edit Distance
- Matrix Chain Multiplication

#### String Algorithms
- Knuth-Morris-Pratt (KMP) Algorithm
- Rabin-Karp Algorithm
- Boyer-Moore Algorithm
- Longest Common Substring
- Longest Palindromic Substring
- Levenshtein Distance (Edit Distance)
- Suffix Array and LCP Array

### Data Structures
- Linked List
- Stack
- Queue
- Binary Tree
- Binary Search Tree
- AVL Tree
- Red-Black Tree
- Heap
- Hash Table
- Trie
- Disjoint Set (Union-Find)
- Fenwick Tree (Binary Indexed Tree)


## Contributing

Contributions to this project are welcome! Please follow these steps:

1. Fork the repository
2. Create a new branch for your feature
3. Implement your feature or bug fix
4. Add tests for your implementation
5. Submit a pull request

Please ensure your code adheres to the existing style and passes all tests.

## License

This project is licensed under the MIT License.
