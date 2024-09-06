#ifndef DSA_PROJECT_SORT_H
#define DSA_PROJECT_SORT_H

#include <concepts>
#include <iterator>

/**
 * @brief A class containing various sorting algorithms.
 *
 * This class provides static methods for different sorting algorithms
 * that can be used to sort containers of comparable elements.
 */
class Sort {
public:
    /**
     * @brief Sorts the given range using the bubble sort algorithm.
     *
     * @tparam It Iterator type
     * @tparam Comp Comparator type (optional)
     * @param begin Iterator to the beginning of the range
     * @param end Iterator to the end of the range
     * @param comp Comparison function object (default: less)
     */
    template<std::random_access_iterator It, typename Comp = std::less<>>
    static void bubbleSort(It begin, It end, Comp comp = Comp{});

    /**
     * @brief Sorts the given range using the selection sort algorithm.
     *
     * @tparam It Iterator type
     * @tparam Comp Comparator type (optional)
     * @param begin Iterator to the beginning of the range
     * @param end Iterator to the end of the range
     * @param comp Comparison function object (default: less)
     */
    template<std::random_access_iterator It, typename Comp = std::less<>>
    static void selectionSort(It begin, It end, Comp comp = Comp{});

    /**
     * @brief Sorts the given range using the insertion sort algorithm.
     *
     * @tparam It Iterator type
     * @tparam Comp Comparator type (optional)
     * @param begin Iterator to the beginning of the range
     * @param end Iterator to the end of the range
     * @param comp Comparison function object (default: less)
     */
    template<std::random_access_iterator It, typename Comp = std::less<>>
    static void insertionSort(It begin, It end, Comp comp = Comp{});

    /**
     * @brief Sorts the given range using the merge sort algorithm.
     *
     * @tparam It Iterator type
     * @tparam Comp Comparator type (optional)
     * @param begin Iterator to the beginning of the range
     * @param end Iterator to the end of the range
     * @param comp Comparison function object (default: less)
     */
    template<std::random_access_iterator It, typename Comp = std::less<>>
    static void mergeSort(It begin, It end, Comp comp = Comp{});

    /**
     * @brief Sorts the given range using the quick sort algorithm.
     *
     * @tparam It Iterator type
     * @tparam Comp Comparator type (optional)
     * @param begin Iterator to the beginning of the range
     * @param end Iterator to the end of the range
     * @param comp Comparison function object (default: less)
     */
    template<std::random_access_iterator It, typename Comp = std::less<>>
    static void quickSort(It begin, It end, Comp comp = Comp{});

    /**
     * @brief Sorts the given range using the heap sort algorithm.
     *
     * @tparam It Iterator type
     * @tparam Comp Comparator type (optional)
     * @param begin Iterator to the beginning of the range
     * @param end Iterator to the end of the range
     * @param comp Comparison function object (default: less)
     */
    template<std::random_access_iterator It, typename Comp = std::less<>>
    static void heapSort(It begin, It end, Comp comp = Comp{});
};

#endif //DSA_PROJECT_SORT_H