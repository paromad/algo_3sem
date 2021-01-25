#include <iostream>
#include <vector>

using namespace std;
using sll = signed long long;

int Partition(vector<sll> &arr, int left, int right) {
    sll pivot = arr[(left + right) / 2];
    int i = left - 1, j = right + 1;
    while (true) {
        do {
            i++;
        } while (arr[i] < pivot);
        do {
            j--;
        } while (pivot < arr[j]);
        if (i >= j) {
            return j;
        }
        std::swap(arr[i], arr[j]);
    }
}

void QuickSort(vector<sll> &arr, int left, int right) {
    if (left < right) {
        int p = Partition(arr, left, right);
        QuickSort(arr, left, p);
        QuickSort(arr, p + 1, right);
    }
}

int main() {
    int n, number;

    cin >> n;

    vector<sll> arr;

    for (int i = 0; i < n; ++i) {
        cin >> number;
        arr.push_back(number);
    }

    QuickSort(arr, 0, n - 1);

    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }

    arr.clear();

    return 0;
}
