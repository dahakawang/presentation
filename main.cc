#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<bool> precompute(string& word) {
    }

    vector<vector<bool>> precompute(vector<string>& words) {
        vector<vector<bool>> table;

        for(auto& line : words) {
            table.push_back(precompute(line));
        }
        return table;
    }

    bool is_palindrom(vector<string>& words, vector<vector<bool>>& table, size_t first, size_t second) {
        size_t left = 0, right = 0;
        if (words[first].size() > words[first].size()) {
            size_t mid = words[first].size() + words[second].size();
            if (!table[first][mid]) return false;
        } else {
            size_t mid = table[second].size() - (words[first].size() + words[second].size()) - 1;
            if (!table[second][mid]) return false;
        }

        while(left != 0) {
            if (words[left] != words[right]) return false;
            --left; ++right;
        }
        return true;
    }

    vector<vector<int>> palindromePairs(vector<string>& words) {
        vector<vector<bool>> table = precompute(words);
        vector<vector<int>> result;
        for (size_t first = 0; first < words.size(); ++first) {
            for (size_t second = 0; second < words.size(); ++second) {
                if (first == second) continue;
                if (is_palindrom(words, table, first, second)) {
                    result.push_back({static_cast<int>(first), static_cast<int>(second)});
                }
            }
        }
        return result;
    }
};

int main(int argc, char *argv[]) {
    vector<string> s;
    string line;
    while(cin >> line) {
        s.push_back(line);
    }
    Solution so;
    auto v = so.palindromePairs(s);
    for(auto& v1 : v) {
        for(auto n : v1) {
            std::cout << n << " ";
        }
        std::cout <<std::endl;
    }

    return 0;
}
