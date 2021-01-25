#include <iostream>
#include <vector>

using namespace std;

void read_arr(vector<int> &arr) {
    size_t n;
    cin >> n;
    arr.reserve(n);
    int number;
    for (size_t i = 0; i < n; ++i) {
        cin >> number;
        arr.emplace_back(number);
    }
}

void merge(vector<int> &result, const vector<int> &first, const vector<int> &second) {
    auto it_first = first.begin();
    auto it_second = second.begin();
    result.reserve(first.size() + second.size());
    while (it_first != first.end() && it_second != second.end()) {
        if (*it_first <= *it_second) {
            result.emplace_back(*it_first);
            ++it_first;
        } else {
            result.emplace_back(*it_second);
            ++it_second;
        }
    }
    while (it_first != first.end()) {
        result.emplace_back(*it_first);
        ++it_first;
    }
    while (it_second != second.end()) {
        result.emplace_back(*it_second);
        ++it_second;
    }
}

int main() {
    vector<int> arr_first;
    read_arr(arr_first);

    vector<int> arr_second;
    read_arr(arr_second);

    vector<int> result;
    merge(result, arr_first, arr_second);

    for (int x: result) {
        cout << x << " ";
    }

    arr_first.clear();
    arr_second.clear();
    result.clear();

    return 0;
}
