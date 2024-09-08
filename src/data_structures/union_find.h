/**
 * @file UnionFind.h
 * @brief Definition of the UnionFind class for disjoint-set data structure with key applications.
 *
 * The Union-Find data structure, also known as Disjoint-Set Union (DSU),
 * is a powerful tool with various important applications in computer science:
 *
 * 1. Kruskal's Minimum Spanning Tree (MST) Algorithm:
 *    - Efficiently detects cycles in graphs during MST construction.
 *
 * 2. Cycle Detection in Graphs:
 *    - Quickly determines if adding an edge will create a cycle in undirected graphs.
 *
 * 3. Finding Connected Components in Graphs:
 *    - Groups nodes into connected components efficiently.
 *    - Useful in social network analysis, image segmentation, and clustering problems.
 *
 * 4. Equivalence Systems in Compilers:
 *    - Tracks aliases and equivalent types in compilers.
 *    - Aids in code optimization and type analysis.
 *
 * 5. Percolation Algorithms in Physics and Modeling:
 *    - Used in percolation simulations studying flow through porous materials.
 *    - Applicable in modeling epidemic spread, forest fires, or conductivity in complex materials.
 *
 * These applications leverage the near-constant time complexity of Union-Find operations,
 * especially when implemented with path compression and union by rank optimizations.
 */

#ifndef UNION_FIND_H
#define UNION_FIND_H

#include <vector>

/**
 * @class UnionFind
 * @brief A class implementing the Union-Find (Disjoint-Set) data structure.
 *
 * This class provides an efficient implementation of the Union-Find data structure,
 * also known as the Disjoint-Set data structure. It supports operations to create
 * disjoint sets, union them, and find the representative element of a set.
 *
 * The implementation uses both path compression and union by rank optimizations
 * to achieve near-constant time complexity for operations.
 */
class UnionFind {
private:
    std::vector<int> parent;
    int number_of_sets;
public:
    /**
     * @brief Constructs a UnionFind object with n elements.
     *
     * Initially, each element is in its own set (i.e., n disjoint sets).
     *
     * @param n The number of elements in the UnionFind structure.
     */
    explicit UnionFind(int n);

    /**
     * @brief Finds the representative (root) of the set containing element x.
     *
     * This method uses path compression optimization. After finding the root,
     * it updates the parent of all traversed elements to point directly to the root.
     *
     * @param x The element to find the representative for.
     * @return The representative (root) of the set containing x.
     */
    int find(int x);

    /**
     * @brief Unites the sets containing elements x and y.
     *
     * If x and y are already in the same set, this operation does nothing.
     * Else, it merges the sets containing x and y into a single set(set which is already containing x).
     *
     * @param x An element of the first set.
     * @param y An element of the second set.
     */
    void unite(int x, int y);

    /**
     * @brief Checks if elements x and y are in the same set.
     *
     * @param x The first element.
     * @param y The second element.
     * @return true if x and y are in the same set, false otherwise.
     */
    bool connected(int x, int y);

    /**
     * @brief Returns the number of disjoint sets.
     *
     * @return The current number of disjoint sets in the structure.
     */
    int count() const;
};

#endif // UNION_FIND_H