#include <gtest/gtest.h>
#include "src/string/algorithms.h"

class StringAlgorithmsTest : public ::testing::Test {
protected:
    void SetUp() override { }

    void TearDown() override { }
};

// LCS test
TEST_F(StringAlgorithmsTest, LongestCommonSubstringBasicTest) {
    std::string s1 = "ABABC";
    std::string s2 = "BABCA";
    EXPECT_EQ(StringAlgorithms::longest_common_substring(s1, s2), "BABC");
}

TEST_F(StringAlgorithmsTest, LongestCommonSubstringNoCommonTest) {
    std::string s1 = "ABC";
    std::string s2 = "DEF";
    EXPECT_EQ(StringAlgorithms::longest_common_substring(s1, s2), "");
}

TEST_F(StringAlgorithmsTest, LongestCommonSubstringIdenticalStringsTest) {
    std::string s = "ABCDEF";
    EXPECT_EQ(StringAlgorithms::longest_common_substring(s, s), s);
}

// LPS tests
TEST_F(StringAlgorithmsTest, LongestPalindromicSubstringBasicTest) {
    std::string s = "babad";
    std::string result = StringAlgorithms::longest_palindromic_substring(s);
    EXPECT_TRUE(result == "bab" || result == "aba");
}

TEST_F(StringAlgorithmsTest, LongestPalindromicSubstringEvenLengthTest) {
    std::string s = "cbbd";
    EXPECT_EQ(StringAlgorithms::longest_palindromic_substring(s), "bb");
}

TEST_F(StringAlgorithmsTest, LongestPalindromicSubstringSingleCharTest) {
    std::string s = "a";
    EXPECT_EQ(StringAlgorithms::longest_palindromic_substring(s), "a");
}

TEST_F(StringAlgorithmsTest, LongestPalindromicSubstringNoPalindromeTest) {
    std::string s = "abcd";
    std::string result = StringAlgorithms::longest_palindromic_substring(s);
    EXPECT_TRUE(result.length() == 1);  
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}