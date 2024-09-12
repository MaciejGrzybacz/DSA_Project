#include <algorithm>
#include "algorithms.h"

std::string StringAlgorithms::longest_common_substring(const std::string &s1, const std::string &s2) {
    if(s1.empty() || s2.empty()) return "";
    
    int m = s1.size(), n = s2.size();
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
    std::string result = "";

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = std::max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    
    int i = m, j = n;
    while(i > 0 && j > 0) {
        if (s1[i - 1] == s2[j - 1]) {result += s1[i - 1]; --i; --j;}
        else if (dp[i - 1][j] > dp[i][j - 1]) {--i;}
        else {--j;}
    }
    
    std::reverse(result.begin(), result.end());
    
    return result;
}   

std::string StringAlgorithms::longest_palindromic_substring(const std::string &s) {
    if(s.empty()) return "";
    int start = 0, end = 0;
    for(int i = 0; i < s.size(); i++) {
        auto [left1, right1] = expand_around_center(s, i, i);
        auto [left2, right2] = expand_around_center(s, i, i + 1);
        if(right1 - left1 > end - start) {
            start = left1;
            end = right1;
        }
        if(right2 - left2 > end - start) {
            start = left2;
            end = right2;
        }
    }
    return s.substr(start + 1, end - start - 1);
}

std::pair<int, int> StringAlgorithms::expand_around_center(const std::string &s, int left, int right) {
    while(left >= 0 && right < s.size() && s[left] == s[right]) {
        left--;
        right++;
    }
    return {left, right};
}
