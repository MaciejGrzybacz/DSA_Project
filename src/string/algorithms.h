#ifndef STRING_ALGORITHMS_H
#define STRING_ALGORITHMS_H

#include <string>
#include <vector>

/**
 * @brief A class implementing various string algorithms.
 *
 * This class provides implementations of string algorithms such as
 * Longest Common Substring (LCS) and Longest Palindromic Substring (LPS).
 * These algorithms are useful in various applications including
 * bioinformatics, text processing, and data compression.
 */
class StringAlgorithms {
public:
    /**
     * @brief Finds the Longest Common Substring of two strings.
     *
     * This method implements the dynamic programming approach to find
     * the longest substring that appears in both input strings.
     *
     * @param s1 The first input string.
     * @param s2 The second input string.
     * @return The longest common substring.
     *
     * @note The time complexity of this implementation is O(m*n),
     *       where m and n are the lengths of the input strings.
     * @note The space complexity is also O(m*n) due to the DP table.
     */
    [[nodiscard]] static std::string longest_common_substring(const std::string& s1, const std::string& s2);

    /**
     * @brief Finds the Longest Palindromic Substring in a string.
     *
     * This method uses the expand around center approach to find
     * the longest palindromic substring in the input string.
     *
     * @param s The input string.
     * @return The longest palindromic substring.
     *
     * @note The time complexity of this implementation is O(n^2),
     *       where n is the length of the input string.
     * @note The space complexity is O(1) as it uses only a constant amount of extra space.
     */
    [[nodiscard]] static std::string longest_palindromic_substring(const std::string& s);

private:
    /**
     * @brief Helper method for expanding around center in palindrome search.
     *
     * This private method is called by longest_palindromic_substring to
     * expand around a potential center of a palindrome.
     *
     * @param s The input string.
     * @param left The left index of the center.
     * @param right The right index of the center.
     * @return A pair of integers representing the start and length of the palindrome.
     */
    static std::pair<int, int> expand_around_center(const std::string& s, int left, int right);
};

#endif // STRING_ALGORITHMS_H