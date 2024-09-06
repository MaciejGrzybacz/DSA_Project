#include <gtest/gtest.h>
#include "src/sorting/sort.h"
#include <vector>
#include <algorithm>
#include <random>
#include <functional>

class SortTest : public ::testing::Test {
protected:
    std::vector<int> empty_vector;
    std::vector<int> single_element{42};
    std::vector<int> sorted_vector{1, 2, 3, 4, 5};
    std::vector<int> reverse_sorted_vector{5, 4, 3, 2, 1};
    std::vector<int> random_vector{3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    std::vector<int> duplicates_vector{3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};

    void SetUp() override {}

    void TearDown() override {}

    template<typename SortFunc>
    void testSortFunction(SortFunc sortFunc) {
        std::vector<int> test_vectors[] = {
                empty_vector, single_element, sorted_vector,
                reverse_sorted_vector, random_vector, duplicates_vector
        };

        for (auto& vec : test_vectors) {
            std::vector<int> expected = vec;
            std::sort(expected.begin(), expected.end());

            std::vector<int> actual = vec;
            sortFunc(actual.begin(), actual.end());

            EXPECT_EQ(actual, expected) << "Sorting failed for vector: "
                                        << ::testing::PrintToString(vec);
        }
    }

    void testSortStability(std::function<void(std::vector<std::pair<int, int>>&)> sortFunc) {
        std::vector<std::pair<int, int>> data = {{3, 1}, {1, 2}, {3, 3}, {1, 4}, {2, 5}};
        std::vector<std::pair<int, int>> expected = {{1, 2}, {1, 4}, {2, 5}, {3, 1}, {3, 3}};

        sortFunc(data);

        EXPECT_EQ(data, expected) << "Sorting is not stable";
    }
};

TEST_F(SortTest, BubbleSortTest) {
    testSortFunction([](auto begin, auto end) { Sort::bubbleSort(begin, end); });
}

TEST_F(SortTest, MergeSortTest) {
    testSortFunction([](auto begin, auto end) { Sort::mergeSort(begin, end); });
}

TEST_F(SortTest, QuickSortTest) {
    testSortFunction([](auto begin, auto end) { Sort::quickSort(begin, end); });
}

TEST_F(SortTest, HeapSortTest) {
    testSortFunction([](auto begin, auto end) { Sort::heapSort(begin, end); });
}

TEST_F(SortTest, BucketSortTest) {
    testSortFunction([](auto begin, auto end) { Sort::bucketSort(begin, end); });
}

TEST_F(SortTest, CustomComparatorTest) {
    std::vector<int> vec = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    std::vector<int> expected = {9, 6, 5, 5, 5, 4, 3, 3, 2, 1, 1};

    Sort::bubbleSort(vec.begin(), vec.end(), std::greater<>());
    EXPECT_EQ(vec, expected) << "Custom comparator (greater) failed for bubbleSort";

    vec = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    Sort::mergeSort(vec.begin(), vec.end(), std::greater<>());
    EXPECT_EQ(vec, expected) << "Custom comparator (greater) failed for mergeSort";

    vec = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    Sort::quickSort(vec.begin(), vec.end(), std::greater<>());
    EXPECT_EQ(vec, expected) << "Custom comparator (greater) failed for quickSort";

    vec = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    Sort::heapSort(vec.begin(), vec.end(), std::greater<>());
    EXPECT_EQ(vec, expected) << "Custom comparator (greater) failed for heapSort";
}

TEST_F(SortTest, StabilityTest) {
    testSortStability([](auto& vec) { Sort::bubbleSort(vec.begin(), vec.end()); });
    testSortStability([](auto& vec) { Sort::mergeSort(vec.begin(), vec.end()); });
}

TEST_F(SortTest, LargeDatasetTest) {
    std::vector<int> large_vector(100000);
    std::mt19937 gen(42);
    std::uniform_int_distribution<> dis(1, 1000000);

    std::generate(large_vector.begin(), large_vector.end(), [&]() { return dis(gen); });

    std::vector<int> expected = large_vector;
    std::sort(expected.begin(), expected.end());

    std::vector<int> actual = large_vector;
    Sort::quickSort(actual.begin(), actual.end()); 

    EXPECT_EQ(actual, expected) << "Sorting failed for large dataset";
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
