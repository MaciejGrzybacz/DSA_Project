#ifndef DSA_PROJECT_SORT_H
#define DSA_PROJECT_SORT_H

#include <concepts>
#include <iterator>
#include <vector>
#include <algorithm>

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

    /**
     * @brief Sorts the given range using the bucket sort algorithm.
     *
     * @tparam It Iterator type
     * @tparam Comp Comparator type (optional)
     * @param begin Iterator to the beginning of the range
     * @param end Iterator to the end of the range
     * @param bucketCount Number of buckets to use (default: 10)
     * @param comp Comparison function object (default: less)
     */
    template<std::random_access_iterator It, typename Comp = std::less<>>
    static void bucketSort(It begin, It end, size_t bucketCount = 10, Comp comp = Comp{});

private:
    /**
     * @brief Merges two sorted ranges into a single sorted range.
     *
     * @tparam It Iterator type
     * @tparam Comp Comparator type
     * @param begin Iterator to the beginning of the first range
     * @param mid Iterator to the end of the first range and beginning of the second range
     * @param end Iterator to the end of the second range
     * @param buffer_begin Iterator to the beginning of the buffer for merging
     * @param comp Comparison function object
     */
    template<std::random_access_iterator It, typename Comp>
    static void merge(It begin, It mid, It end, It buffer_begin, Comp comp);

    /**
     * @brief Maintains the heap property for a heap rooted at the given iterator.
     *
     * @tparam It Iterator type
     * @tparam Comp Comparator type
     * @param begin Iterator to the beginning of the heap
     * @param end Iterator to the end of the heap
     * @param root Iterator to the root of the sub-heap
     * @param comp Comparison function object
     */
    template<std::random_access_iterator It, typename Comp>
    static void heapify(It begin, It end, It root, Comp comp);
};

template<std::random_access_iterator It, typename Comp>
void Sort::bubbleSort(It begin, It end, Comp comp) {
    if (begin == end) return;
    for (auto i = begin; i != end - 1; ++i) {
        for (auto j = begin; j != end - 1 - std::distance(begin, i); ++j) {
            if (comp(*(j + 1), *j)) {
                std::iter_swap(j, j + 1);
            }
        }
    }
}

template<std::random_access_iterator It, typename Comp>
void Sort::mergeSort(It begin, It end, Comp comp) {
    using T = typename std::iterator_traits<It>::value_type;
    auto const n = std::distance(begin, end);
    std::vector<T> buffer(n);

    for (size_t width = 1; width < n; width *= 2) {
        for (size_t i = 0; i < n; i += 2 * width) {
            auto left = begin + i;
            auto mid = std::min(left + width, end);
            auto right = std::min(mid + width, end);

            merge(left, mid, right, buffer.begin(), comp);
            std::copy(buffer.begin(), buffer.begin() + std::distance(left, right), left);
        }
    }
}

template<std::random_access_iterator It, typename Comp>
void Sort::quickSort(It begin, It end, Comp comp) {
    if (begin >= end) return;

    auto pivot = *std::next(begin, std::distance(begin, end) / 2);
    auto middle1 = std::partition(begin, end, [&](const auto& em) { return comp(em, pivot); });
    auto middle2 = std::partition(middle1, end, [&](const auto& em) { return !comp(pivot, em); });

    quickSort(begin, middle1, comp);
    quickSort(middle2, end, comp);
}

template<std::random_access_iterator It, typename Comp>
void Sort::heapSort(It begin, It end, Comp comp) {
    if (begin == end) return;
    auto n = std::distance(begin, end);

    for (auto i = begin + n / 2 - 1; i >= begin; --i) {
        heapify(begin, end, i, comp);
    }

    for (auto i = end - 1; i > begin; --i) {
        std::iter_swap(begin, i);
        heapify(begin, i, begin, comp);
    }
}

template<std::random_access_iterator It, typename Comp>
void Sort::bucketSort(It begin, It end, size_t bucketCount, Comp comp) {
    if (begin == end) return;

    auto [min_it, max_it] = std::minmax_element(begin, end);
    auto min_val = *min_it;
    auto max_val = *max_it;

    std::vector<std::vector<typename std::iterator_traits<It>::value_type>> buckets(bucketCount);

    for (auto it = begin; it != end; ++it) {
        size_t bucket_index = static_cast<size_t>(
            static_cast<double>(*it - min_val) / (max_val - min_val + 1) * (bucketCount - 1)
        );
        buckets[bucket_index].push_back(*it);
    }

    for (auto& bucket : buckets) {
        std::sort(bucket.begin(), bucket.end(), comp);
    }

    auto it = begin;
    for (const auto& bucket : buckets) {
        it = std::copy(bucket.begin(), bucket.end(), it);
    }
}

template<std::random_access_iterator It, typename Comp>
void Sort::merge(It begin, It mid, It end, It buffer_begin, Comp comp) {
    auto left = begin;
    auto right = mid;
    auto buf = buffer_begin;

    while (left != mid && right != end) {
        if (comp(*left, *right)) {
            *buf++ = std::move(*left++);
        } else {
            *buf++ = std::move(*right++);
        }
    }

    buf = std::move(left, mid, buf);
    buf = std::move(right, end, buf);
}

template<std::random_access_iterator It, typename Comp>
void Sort::heapify(It begin, It end, It root, Comp comp) {
    auto size = std::distance(begin, end);
    auto largest = std::distance(begin, root);
    auto left = 2 * largest + 1;
    auto right = 2 * largest + 2;

    if (left < size && comp(*(begin + largest), *(begin + left))) {
        largest = left;
    }

    if (right < size && comp(*(begin + largest), *(begin + right))) {
        largest = right;
    }

    if (largest != std::distance(begin, root)) {
        std::iter_swap(begin + largest, root);
        heapify(begin, end, begin + largest, comp);
    }
}

#endif //DSA_PROJECT_SORT_H
