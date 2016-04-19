#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iomanip>
using namespace std;

class BigDicimal {
public:
    BigDicimal(int64_t num) {
        while (num != 0) {
            digits.push_back(num % LENGTH);
            num /= LENGTH;
        }
    }

    BigDicimal() = default;

    void _add(const vector<uint64_t>& longer, const vector<uint64_t>& shorter, vector<uint64_t>& r) const {
        r.clear();
        uint64_t addin = 0;
        for (size_t i = 0; i < shorter.size(); ++i) {
            uint64_t sum = longer[i] + shorter[i] + addin;
            r.push_back(sum % LENGTH);
            addin = sum / LENGTH;
        }

        for (size_t i = shorter.size(); i < longer.size(); ++i) {
            uint64_t sum = longer[i] + addin;
            r.push_back(sum % LENGTH);
            addin = sum / LENGTH;
        }
        if (addin != 0) r.push_back(addin);
    }

    void add(const vector<uint64_t>& left, const vector<uint64_t>& right, vector<uint64_t>& r) const {
        if (left.size() < right.size()) {
            _add(right, left, r);
        } else {
            _add(left, right, r);
        }
    }

    BigDicimal operator+(const BigDicimal& other) const {
        BigDicimal r;
        const vector<uint64_t> &left = this->digits, &right = other.digits;
        vector<uint64_t> &result = r.digits;
        add(left, right, result);

        return r;
    }
    void multiply(const vector<uint64_t>& num, uint64_t digit, int offset, vector<uint64_t>& r) const {
        r.clear();
        for (int i = 0; i < offset; i++) r.push_back(0);
        uint64_t addin = 0;
        for (size_t i = 0; i < num.size(); ++i) {
            uint64_t tmp = digit * num[i] + addin;
            r.push_back(tmp % LENGTH);
            addin = tmp / LENGTH;
        }
        if (addin != 0) r.push_back(addin);
    }

    void multiply(const vector<uint64_t>& longer, const vector<uint64_t>& shorter, vector<uint64_t>& r) const {
        r.clear();

        for (size_t i = 0; i < shorter.size(); ++i) {
            vector<uint64_t> tmp, tmp1;
            multiply(longer, shorter[i], i, tmp);
            add(r, tmp, tmp1);
            swap(tmp1, r);
        }
    }

    BigDicimal operator*(const BigDicimal& other) const {
        BigDicimal r;
        const vector<uint64_t> &left = this->digits, &right = other.digits;
        vector<uint64_t> &result = r.digits;
        if (left.size() < right.size()) {
            multiply(right, left, result);
        } else {
            multiply(left, right, result);
        }

        return r;
    }

    string str() {
        stringstream stream;
        stream << std::setfill('0');

        for (int i = (int) digits.size() - 1; i >= 0; --i) {
            if (i == (int) digits.size() - 1) stream << std::setw(0);
            else stream << std::setw(SIZE);
            stream << digits[i];
        }
        return stream.str();
    }

private:
    const static uint64_t LENGTH = 10000000;
    const static uint64_t SIZE = 7;
    vector<uint64_t> digits;
};

string fib(BigDicimal num, BigDicimal num1, int n) {
    for (int i = 0; i < n - 2; i++) {
        BigDicimal num2 = num1 * num1 + num;
        num = num1;
        num1 = num2;
    }

    return num1.str();
}

int main() {
    /*
    int num, num1, n;
    cin >> num >> num1 >> n;
    std::cout << fib(num, num1, n) << std::endl;
    */

    while(1) {
        int64_t a,b;
        cin >> a >> b;
        BigDicimal a1(a), b1(b);
        BigDicimal r = a1 * b1;
        cout << r.str() << endl;
    }

    return 0;

}
