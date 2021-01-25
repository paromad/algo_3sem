/* Карту местности условно разбили на квадраты, и посчитали среднюю высоту над уровнем моря для каждого квадрата.

Когда идет дождь, вода равномерно выпадает на все квадраты. Если один из четырех соседних с данным квадратом квадратов имеет меньшую высоту над уровнем моря, то вода с текущего квадрата стекает туда (и, если есть возможность, то дальше), если же все соседние квадраты имеют большую высоту, то вода скапливается в этом квадрате.

Разрешается в некоторых квадратах построить водостоки. Когда на каком-то квадрате строят водосток, то вся вода, которая раньше скапливалась в этом квадрате, будет утекать в водосток.

Если есть группа квадратов, имеющих одинаковую высоту и образующих связную область, то если хотя бы рядом с одним из этих квадратов есть квадрат, имеющий меньшую высоту, то вся вода утекает туда, если же такого квадрата нет, то вода стоит во всех этих квадратах. При этом достаточно построить водосток в любом из этих квадратов, и вся вода с них будет утекать в этот водосток.

Требуется определить, какое минимальное количество водостоков нужно построить, чтобы после дождя вся вода утекала в водостоки.

Формат ввода
Во входном файле записаны сначала числа N и M, задающие размеры карты — натуральные числа, не превышающие 100. Далее идет N строк, по M чисел в каждой, задающих высоту квадратов карты над уровнем моря. Высота задается натуральным числом, не превышающим 10000. Считается, что квадраты, расположенные за пределами карты, имеют высоту 10001 (то есть вода никогда не утекает за пределы карты).

Формат вывода
В выходной файл выведите минимальное количество водостоков, которое необходимо построить. */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Cage {
    size_t x_;
    size_t y_;
    size_t high_;

    Cage() : x_(0), y_(0), high_(0) {};

    Cage(size_t x, size_t y, size_t high = 0) : x_(x), y_(y), high_(high) {};

    bool operator<(const Cage &other) const {
        return high_ < other.high_;
    }
};

int cage_hash(const Cage &cage, int size) {
    return cage.x_ * size + cage.y_;
}

Cage back_hash(int number, int size, size_t high) {
    return Cage(number / size, number % size, high);
}

bool check(int x, int y, int n, int m) {
    return (x >= 0 && x < n) && (y >= 0 && y < m);
}

vector<Cage> neighbours(const vector<vector<size_t>> &map, const Cage &vertex, int n, int m) {
    vector<Cage> res;
    for (int i = -1; i <= 1; i += 2) {
        if (check(vertex.x_ + i, vertex.y_, n, m)) {
            if (map[vertex.x_][vertex.y_] <= map[vertex.x_ + i][vertex.y_]) {
                res.emplace_back(Cage(vertex.x_ + i, vertex.y_));
            }
        }
        if (check(vertex.x_, vertex.y_ + i, n, m)) {
            if (map[vertex.x_][vertex.y_] <= map[vertex.x_][vertex.y_ + i]) {
                res.emplace_back(Cage(vertex.x_, vertex.y_ + i));
            }
        }
    }
    return res;
}

void fill_in_graph(vector<vector<Cage>> &graph, const vector<vector<size_t>> &map, int n, int m) {
    for (int i = 0; i < n * m; ++i) {
        Cage vertex = back_hash(i, m, map[i / m][i % m]);
        graph[i] = std::move(neighbours(map, vertex, n, m));
    }
}

void DFS(const vector<vector<Cage>> &graph, const Cage &cage, size_t size, vector<bool> &used) {
    int v = cage_hash(cage, size);
    used[v] = true;
    for (Cage u : graph[v]) {
        if (!used[cage_hash(u, size)]) {
            DFS(graph, u, size, used);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<size_t>> map(n);
    for (int i = 0; i < n; ++i) {
        map[i] = vector<size_t>(m);
    }

    int high;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> high;
            map[i][j] = high;
        }
    }

    vector<vector<Cage>> graph(n * m);
    fill_in_graph(graph, map, n, m);

    vector<Cage> order(n * m);
    for (int i = 0; i < n * m; ++i) {
        order[i] = back_hash(i, m, map[i / m][i % m]);
    }

    std::sort(order.begin(), order.end());

    vector<bool> used(n * m, false);

    size_t count = 0;

    for (Cage cage : order) {
        int v = cage_hash(cage, m);
        if (!used[v]) {
            ++count;
            DFS(graph, cage, m, used);
        }
    }

    cout << count;

    return 0;
}
