/* В аудитории есть N парт, расположенных вдоль прямой. Необходимо рассадить за них K студентов. Но, так как социальную дистанцию никто не отменял, необходимо максимизировать минимальное расстояние между студентами.

Формат ввода
В первой строке идут числа N (3 ≤ N ≤ 104) — количество парт и K (1 < K < N) — количество студентов. На следующей строке через пробел идут N натуральных чисел в порядке возрастания — координаты парт на прямой, не превосходящие 10^9. */

#include <iostream>
#include <vector>

using namespace std;

bool check(vector<int> &arr, int k, int x) {
    int i = 1, n = arr.size(), pos = 0;
    --k;
    while (i < n && k > 0) {
        if (arr[i] - arr[pos] >= x) {
            pos = i;
            --k;
        }
        ++i;
    }
    return k == 0;
}

int main() {
    int n, k;

    vector<int> arr;

    cin >> n >> k;

    arr.reserve(n);

    int number;
    for (size_t i = 0; i < n; ++i) {
        cin >> number;
        arr.emplace_back(number);
    }

    int l = 0;
    int r = arr[n - 1] - arr[0];

    while (r - l > 1) {
        int mid = (l + r) / 2;
        if (check(arr, k, mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }

    if (check(arr, k, r)) {
        cout << r;
    } else {
        cout << l;
    }

    arr.clear();

    return 0;
}
