#include <iostream>
#include <vector>

using namespace std;

void read_arr(vector<int> &arr, vector<int> &indices) {
    indices.emplace_back(arr.size());
    size_t n;
    cin >> n;
    int number;
    for (size_t i = 0; i < n; ++i) {
        cin >> number;
        arr.push_back(number);
    }
}

void merge(vector<int> &arr, size_t left, size_t mid, size_t right) {
    vector<int> result;
    result.reserve(right - left);
    size_t i = left, j = mid;
    while (i < mid && j < right) {
        if (arr[i] <= arr[j]) {
            result.emplace_back(arr[i]);
            ++i;
        } else {
            result.emplace_back(arr[j]);
            ++j;
        }
    }
    while (i < mid) {
        result.emplace_back(arr[i]);
        ++i;
    }
    while (j < right) {
        result.emplace_back(arr[j]);
        ++j;
    }
    for (i = left; i < right; ++i) {
        arr[i] = result[i - left];
    }
}

void merge_sort(vector<int> &arr, vector<int> &indices, size_t first, size_t last) {
    if (first < last) {
        size_t mid = (first + last) / 2;
        merge_sort(arr, indices, first, mid);
        merge_sort(arr, indices, mid + 1, last);
        merge(arr, indices[first], indices[mid + 1], indices[last + 1]);
    }
}

int main() {
    size_t k;
    cin >> k;

    vector<int> arr;
    vector<int> indices;

    indices.reserve(k + 1);

    for (int i = 0; i < k; ++i) {
        read_arr(arr, indices);
    }
    indices.emplace_back(arr.size());

    merge_sort(arr, indices, 0, k - 1);

    for (int i : arr) {
        cout << i << " ";
    }

    arr.clear();
    indices.clear();

    return 0;
}
