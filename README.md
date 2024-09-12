# Data Structures and Algorithms (DSA) Project

## Overview

This project is a comprehensive collection of classic data structures and algorithms implemented in C++. It aims to provide efficient, well-tested, and easy-to-understand implementations for educational purposes and practical use in software development.

## Table of Contents

- [Getting Started](#getting-started)
- [Project Structure](#project-structure)
- [Building and Testing](#building-and-testing)
- [Implemented Algorithms and Data Structures](#implemented-algorithms-and-data-structures)
- [Planned Implementations](#planned-implementations)

## Getting Started

To get started with this project, clone the repository and ensure you have the following prerequisites:

- CMake (version 3.10 or higher)
- A C++23 compatible compiler
- Git (for cloning the repository and fetching Google Test)

```bash
git clone https://github.com/MaciejGrzybacz/DSA_Project.git
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
│       ├── topological_sort.h/cpp
│       ├── mst.h/cpp
│   ├── sorting/
│       └── sort.h/cpp
│   ├── string_algorithms/
│   └── data_structures/
│       ├── union_find.h/cpp
│       ├── linked_list.h/cpp
│       ├── stack.h/cpp
│       ├── queue.h/cpp
├── tests/
│   ├── dynamic_programming/
│   ├── graph/
│       ├── dijkstra_test.cpp
│       ├── search_test.cpp
│       ├── topological_sort_test.cpp
│       ├── mst_test.cpp
│   ├── sorting/
│       ├── sort_test.cpp
│   ├── string_algorithms/
│   └── data_structures/
│       ├── union_find_test.cpp
│       ├── linked_list_test.cpp
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
  - Unweighted_graph
    - Graph Search
      - Breadth-First Search (BFS)
        - Iterative Depth-First Search (DFS)
        - Recursive Depth-First Search (DFS)
        - Topological Sort
  - Weighted_graph
    - Dijkstra's Algorithm
    - Minimum Spanning Tree (MST)
      - Prim's Algorithm
      - Kruskal's Algorithm
- Sorting
  - Bubble Sort
  - Quick Sort
  - Merge Sort
  - Heap Sort
  - Bucket Sort
- String
  - LCS
  - LPS

### Data Structures
- Disjoint Set (Union-Find)
- Linked List
- Stack
- Queue

## Planned Implementations

### Algorithms

#### Graph Algorithms
- Tarjan's Algorithm
- Strongly Connected Components (SCC)
- Bellman-Ford Algorithm
- Floyd-Warshall Algorithm
- A* Search Algorithm
- Travelling Salesman Problem (TSP)
- Maximum Flow (Ford-Fulkerson Algorithm)
- Network Flow (Edmonds-Karp Algorithm)

#### Dynamic Programming
- Longest Common Subsequence
- Knapsack Problem
- Longest Increasing Subsequence
- Maximum Subarray Sum
- Minimum Cost Path
- Edit Distance
- Matrix Chain Multiplication

#### String Algorithms
- Knuth-Morris-Pratt (KMP) Algorithm
- Rabin-Karp Algorithm
- Boyer-Moore Algorithm
- Levenshtein Distance (Edit Distance)
- Suffix Array and LCP Array

### Data Structures
- Binary Tree
- Binary Search Tree
- AVL Tree
- Red-Black Tree
- Heap
- Hash Table
- Fenwick Tree (Binary Indexed Tree)

## License

This project is licensed under the MIT License.