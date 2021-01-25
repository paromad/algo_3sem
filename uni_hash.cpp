/* Реализовать универсальное семейство хеш функций для целых чисел от 0 до 109. Воспользоваться реализованным семейством и std::unordered_set для решения следующей задачи.

Нужно реализовать структуру данных множество, способную быстро выполнять следующие операции:

«+ N» — добавить число N в множество. Не гарантируется, что N отсутствует в множестве.
«- N» — удалить число N из множества. Не гарантируется, что N имеется в множестве.
«? N» — узнать, есть ли число N в множестве. */

#include <iostream>
#include <random>
#include <unordered_set>

class hash {
    int a_;
    int b_;
    const static size_t p_ = 1e9 + 7;
public:
    hash() {
        std::mt19937 rnd{};
        a_ = rnd();
        b_ = rnd();
    }

    hash(const hash &other) = default;

    size_t operator()(int x) const {
        return (static_cast<size_t>(a_) * x + b_) % p_;
    }
};

class hash_table {
    std::unordered_set<int, hash> set_;
public:
    void insert(unsigned x) {
        set_.insert(x);
    }

    void erase(unsigned x) {
        set_.erase(x);
    }

    bool find(unsigned x) {
        return (set_.find(x) != set_.end());
    }
};

int main() {
    int n;
    std::cin >> n;

    char command;
    unsigned num;

    hash_table table;

    for (int i = 0; i < n; ++i) {
        std::cin >> command >> num;
        switch (command) {
            case '+':
                table.insert(num);
                break;
            case '-':
                table.erase(num);
                break;
            case '?':
                std::cout << (table.find(num) ? "YES\n" : "NO\n");
                break;
        }
    }

    return 0;
}
