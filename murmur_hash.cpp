#include <iostream>
#include <cstring>
#include <unordered_set>
#include <random>

using namespace std;

#define BIG_CONSTANT(x) (x)

uint64_t MurmurHash64A(const void *key, int len, uint64_t seed) {
    const uint64_t m = BIG_CONSTANT(0xc6a4a7935bd1e995);
    const int r = 47;

    uint64_t h = seed ^(len * m);

    const uint64_t *data = (const uint64_t *) key;
    const uint64_t *end = data + (len / 8);

    while (data != end) {
        uint64_t k = *data++;

        k *= m;
        k ^= k >> r;
        k *= m;

        h ^= k;
        h *= m;
    }

    const unsigned char *data2 = (const unsigned char *) data;

    switch (len & 7) {
        case 7:
            h ^= uint64_t(data2[6]) << 48;
        case 6:
            h ^= uint64_t(data2[5]) << 40;
        case 5:
            h ^= uint64_t(data2[4]) << 32;
        case 4:
            h ^= uint64_t(data2[3]) << 24;
        case 3:
            h ^= uint64_t(data2[2]) << 16;
        case 2:
            h ^= uint64_t(data2[1]) << 8;
        case 1:
            h ^= uint64_t(data2[0]);
            h *= m;
    };

    h ^= h >> r;
    h *= m;
    h ^= h >> r;

    return h;
}

class murmur_hash {
    uint64_t seed_;
public:
    murmur_hash() {
        std::mt19937 rnd{};
        seed_ = rnd();
    }

    murmur_hash(const murmur_hash &other) = default;

    size_t operator()(const char *x) const {
        return MurmurHash64A(x, strlen(x), seed_);
    }
};

class hash_table {
    std::unordered_set<const char *, murmur_hash> set_;
public:
    void insert(const char *x) {
        set_.insert(x);
    }

    void erase(const char *x) {
        set_.erase(x);
    }

    bool find(const char *x) {
        return (set_.find(x) != set_.end());
    }
};

int main() {
    char command;
    char *string = new char[11];

    hash_table table;

    cin >> command;
    while (command != '#') {
        cin >> string;

        switch (command) {
            case '+' :
                table.insert(string);
                break;
            case '-' :
                table.erase(string);
                break;
            case '?' :
                cout << (table.find(string) ? "YES\n" : "NO\n");
                break;
        }

        cin >> command;
    }

    return 0;
}
