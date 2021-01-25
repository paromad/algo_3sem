#include <iostream>
#include <random>
#include <vector>
#include <string>

class Hash {
    int a_;
    int b_;
    const static size_t p_ = 1e9 + 7;
public:
    Hash() : a_(0), b_(0) {};

    Hash(std::mt19937 &rnd) : a_(rnd()), b_(rnd()) {}

    Hash(const Hash &other) = default;

    size_t operator()(const std::string &x) const {
        size_t hash = 0;
        for (const char &symbol : x) {
            hash *= a_;
            hash += symbol - 'a' + 1;
            hash %= p_;
        }
        return (static_cast<size_t>(a_) * hash + b_) % p_;
    }
};

class StaticHashTable {
    std::vector<std::vector<std::string>> table_;
    std::vector<Hash> inside_hash_;
    Hash outside_hash_;

    static void fill_table_(const Hash &hash, std::vector<std::vector<std::string>> &table,
                            std::vector<std::string> &values) {
        for (std::string &str : values) {
            size_t hash_value = hash(str);
            table[hash_value % table.size()].push_back(std::move(str));
        }
    }

    static void fill_table_(const Hash &hash, std::vector<std::string> &table, std::vector<std::string> &values) {
        for (std::string &str : values) {
            size_t hash_value = hash(str);
            table[hash_value % table.size()] = std::move(str);
        }
    }

    template<typename ConditionType>
    static Hash generate_hash(std::mt19937 &rnd, const std::vector<std::string> &values, size_t table_size,
                              ConditionType condition) {
        while (true) {
            std::vector<int> table(table_size);
            Hash hash(rnd);
            for (const auto &str : values) {
                table[hash(str) % table_size]++;
            }
            if (condition(table)) {
                return hash;
            }
        }
    }

    static bool outside_condition(const std::vector<int> &table) {
        int square_sum = 0;
        for (const int &cnt : table) {
            square_sum += cnt * cnt;
        }
        return square_sum <= 4 * table.size();
    }

    static bool inside_condition(const std::vector<int> &table) {
        for (const int &cnt : table) {
            if (cnt > 1) {
                return false;
            }
        }
        return true;
    }

public:
    explicit StaticHashTable(std::vector<std::string> &&values) : table_(values.size()), inside_hash_(values.size()) {
        std::mt19937 rnd{};

        outside_hash_ = generate_hash(rnd, values, values.size(), outside_condition);
        fill_table_(outside_hash_, table_, values);

        for (size_t i = 0; i < table_.size(); ++i) {
            std::vector<std::string> values_i = std::move(table_[i]);
            size_t ni = values_i.size();
            inside_hash_[i] = generate_hash(rnd, values_i, ni * ni, inside_condition);
            table_[i].resize(ni * ni);
            fill_table_(inside_hash_[i], table_[i], values_i);
        }
    }

    bool find(const std::string &str) {
        size_t first_idx = outside_hash_(str) % table_.size();
        if (table_[first_idx].empty()) {
            return false;
        }
        size_t second_idx = inside_hash_[first_idx](str) % table_[first_idx].size();
        return table_[first_idx][second_idx] == str;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int n;
    std::cin >> n;

    std::vector<std::string> in(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> in[i];
    }

    StaticHashTable ht(std::move(in));

    int k;
    std::cin >> k;

    for (int i = 0; i < k; ++i) {
        std::string str;
        std::cin >> str;
        std::cout << (ht.find(str) ? "YES\n" : "NO\n");
    }

    return 0;
}
