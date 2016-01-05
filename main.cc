#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <climits>
#include <functional>
#include <numeric>
#include <utility>
#include <set>
#include <sstream>
#include <map>
#include <cstring>

using std::vector;
using std::string;
using std::pair;
using std::map;

class Solution {
public:
    int minDistance(string word1, string word2) {
        if (word1.empty()) return word2.size();
        if (word2.empty()) return word1.size();

        vector<vector<int>> dist(word1.size(), vector<int>(word2.size(), 0));
        dist[0][0] = (word1[0] == word2[2])? 0 : 1;
        for(int i = 1; i < word1.size(); ++i) dist[i][0] = dist[i-1][0] + 1;
        for(int i = 1; i < word2.size(); ++i) dist[0][i] = dist[0][i-1] + 1;

        for(int i = 1; i < word1.size(); ++i) {
            for(int j = 1; j < word2.size(); ++j) {
                if (word1[i] == word2[j]) {
                    dist[i][j] = dist[i-1][j-1];
                } else {
                    dist[i][j] = std::min(dist[i-1][j], dist[i][j-1]);
                    dist[i][j] = std::min(dist[i][j], dist[i-1][j-1]);
                    ++dist[i][j];
                }
            }
        }

        return dist[word1.size()-1][word2.size()-1];
    }
};

int main() {
    Solution s;
    std::cout << s.minDistance("abcdefgh", "abcdefgh") << std::endl;
    return 0;
}
