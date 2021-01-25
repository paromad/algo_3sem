#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Enrollee {
    std::string surname_;
    std::string name_;
    int points_;

    Enrollee() = default;

    Enrollee(const std::string &surname, const std::string &name, int inf_point, int math_points, int rus_points)
            : surname_(surname), name_(name), points_(inf_point + math_points + rus_points) {};

    bool operator<(const Enrollee &other) const {
        return points_ < other.points_;
    }

    friend ostream &operator<<(ostream &os, const Enrollee &enrollee) {
        os << enrollee.surname_ << " " << enrollee.name_;
        return os;
    }
};

void read_arr(vector<Enrollee> &arr) {
    size_t n;
    cin >> n;
    arr.reserve(n);
    std::string name, surname;
    int inf_points, math_points, rus_points;
    for (size_t i = 0; i < n; ++i) {
        cin >> surname >> name >> inf_points >> math_points >> rus_points;
        arr.emplace_back(Enrollee(surname, name, inf_points, math_points, rus_points));
    }
}

void inplace_merge(vector<Enrollee> &arr, int left, int mid, int right) {
    if (left == mid || mid == right) {
        return;
    }
    if (left + 1 == mid && mid + 1 == right) {
        if (arr[left] < arr[mid]) {
            std::swap(arr[left], arr[mid]);
        }
        return;
    }
    auto it = arr.begin();
    int m_first, m_second;
    auto comp = [](const Enrollee& x, const Enrollee& y) {return y < x;};
    if (mid - left > right - mid) {
        m_first = left + (mid - left) / 2;
        m_second = lower_bound(it + mid, it + right, arr[m_first], comp) - it;
    } else {
        m_second = mid + (right - mid) / 2;
        m_first = upper_bound(it + left, it + mid, arr[m_second], comp) - it;
    }
    std::rotate(it + m_first, it + mid, it + m_second);
    int new_mid = m_first + m_second - mid;
    inplace_merge(arr, left, m_first, new_mid);
    inplace_merge(arr, new_mid, m_second, right);

}

void merge_sort(vector<Enrollee> &arr, size_t left, size_t right) {
    if (left + 1 < right) {
        size_t mid = (left + right) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid, right);
        inplace_merge(arr, left, mid, right);
    }
}

int main() {
    vector<Enrollee> arr;
    read_arr(arr);

    merge_sort(arr, 0, arr.size());

    for (size_t i = 0; i < arr.size(); ++i) {
        cout << arr[i] << "\n";
    }

    arr.clear();

    return 0;
}
