#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void read_arr(vector<int> &arr) {
    size_t n;
    cin >> n;
    int number;
    for (size_t i = 0; i < n; ++i) {
        cin >> number;
        arr.push_back(number);
    }
}

void inplace_merge(vector<int> &arr, int left, int mid, int right) {
    if (left == mid || mid == right) {
        return;
    }
    if (left + 1 == mid && mid + 1 == right) {
        if (arr[left] > arr[mid]) {
            std::swap(arr[left], arr[mid]);
        }
        return;
    }
    auto it = arr.begin();
    if (mid - left < right - mid) {
        std::rotate(it + left, it + mid, it + right);
        mid = right + left - mid;
    }
    int m_first = left + (mid - left) / 2;
    int m_second = lower_bound(it + mid, it + right, arr[m_first]) - it;
    std::rotate(it + m_first, it + mid, it + m_second);
    int new_mid = m_first + m_second - mid;
    inplace_merge(arr, left, m_first, new_mid);
    inplace_merge(arr, new_mid, m_second, right);
}

int main() {
    vector<int> arr;
    int n, m;
    cin >> n;
    int number;
    for (int i = 0; i < n; ++i) {
        cin >> number;
        arr.push_back(number);
    }
    cin >> m;
    for (int i = 0; i < m; ++i) {
        cin >> number;
        arr.push_back(number);
    }

    inplace_merge(arr, 0, n, n + m);

    for (int i : arr) {
        cout << i << " ";
    }
    
    arr.clear();

    return 0;
}
