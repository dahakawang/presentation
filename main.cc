#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;


vector<int64_t> get_sum(vector<int64_t>& v, int64_t mod) {
    vector<int64_t> sum(v.size() + 1);
    sum[0] = 0;

    for(int i = 0; i < v.size(); ++i) sum[i + 1] = (v[i] + sum[i]) % mod;

    return sum;
}

inline int64_t get_mod(int64_t left, int64_t right, int64_t mod) {
    return (right - left + mod) % mod;
}

int64_t find_max(vector<int64_t>& v, int begin, int mid, int end, int64_t mod) {

}

void merge(vector<int64_t>& v, vector<int64_t>& tmp, int begin, int mid, int end) {
    int left = begin, right = mid;
    for(int i = begin; i < end; ++i) {
        int64_t left_val = (left < mid)? v[left] : LLONG_MAX;
        int64_t right_val = (right_val < end)? v[right] : LLONG_MAX;
        if (left_val < right_val) {
            tmp[i] = left_val;
            ++left;
        } else {
            tmp[i] = right_val;
            ++right;
        }
    }
    std:copy(tmp.begin() + begin, tmp.begin() + end, v.begin() + begin);
}

int64_t find_max(vector<int64_t>& v, vector<int64_t>& tmp, int begin, int end, int64_t mod) {
    if (end - begin == 1) {
        return v[begin];
    }

    int mid = begin + (end - begin) / 2;
    int64_t left = find_max(v, tmp, begin, mid, mod);
    int64_t right = find_max(v, tmp, mid, end, mod);

    //left and right is sorted
    int64_t me = find_max(v, begin, mid, end, mod);

    merge(v, tmp, begin, mid, end);

    return std::max(std::max(left, right), me);
}

int64_t find_max(vector<int64_t>& v, int64_t mod) {
    auto sum = get_sum(v, mod);
    vector<int64_t> tmp;

    return find_max(sum, tmp, 0, sum.size(), mod);
}


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int cntCase;
    cin >> cntCase;

    for(int i = 0; i < cntCase; ++i) {
        int64_t length, mod;
        cin >> length >> mod;
        vector<int64_t> v(length);
        for(int j = 0; j < length; ++j) cin >> v[j];

        cout << find_max(v, mod) << endl;;
    }
    return 0;
}
