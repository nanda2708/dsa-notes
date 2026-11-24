#include <algorithm>
#include <cassert>
#include <string_view>
#include <vector>

std::vector<int> prefix_function(std::string_view text) {
    int n = static_cast<int>(text.size());
    std::vector<int> prefix(n);
    for (int i = 1; i < n; ++i) {
        int matched = prefix[i - 1];
        while (matched > 0 && text[i] != text[matched])
            matched = prefix[matched - 1];
        if (text[i] == text[matched]) ++matched;
        prefix[i] = matched;
    }
    return prefix;
}

// Empty patterns return no matches by convention.
std::vector<int> kmp(std::string_view text, std::string_view pattern) {
    if (pattern.empty()) return {};
    const auto prefix = prefix_function(pattern);
    const int length = static_cast<int>(pattern.size());
    std::vector<int> positions;
    int matched = 0;
    for (int i = 0; i < static_cast<int>(text.size()); ++i) {
        while (matched > 0 && text[i] != pattern[matched])
            matched = prefix[matched - 1];
        if (text[i] == pattern[matched]) ++matched;
        if (matched == length) {
            positions.push_back(i - length + 1);
            matched = prefix[matched - 1];
        }
    }
    return positions;
}

std::vector<int> z_function(std::string_view text) {
    int n = static_cast<int>(text.size());
    std::vector<int> z(n);
    int left = 0, right = 0;  // Half-open window [left, right).
    for (int i = 1; i < n; ++i) {
        if (i < right) z[i] = std::min(right - i, z[i - left]);
        while (i + z[i] < n && text[z[i]] == text[i + z[i]]) ++z[i];
        if (i + z[i] > right) {
            left = i;
            right = i + z[i];
        }
    }
    return z;
}

int main() {
    assert((kmp("ababa", "aba") == std::vector<int>{0, 2}));
    assert(kmp("abc", "abcd").empty());
    assert(kmp("abc", "").empty());
    assert((z_function("ababa") == std::vector<int>{0, 0, 3, 0, 1}));
    assert((z_function("aaaa") == std::vector<int>{0, 3, 2, 1}));
    assert(z_function("").empty());
}
