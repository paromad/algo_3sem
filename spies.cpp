/* Вы — глава агенства, в котором работает N сотрудников — шпионы с кодовыми номерами от 1 до N. Шпионы были посланы в различные страны и получили кусочки важной информации. Ваша задача состоит в следующем:

Организовать встречи между некоторыми шпионами. На каждой такой встрече ровно два шпиона оказываются в одном месте и обмениваются всей информацией, которую получили сами или узнали от других шпионов на предыдущих встречах. Каждую из возможных встреч сложно и затратно организовать, поэтому вам известны все стоимости.
После того, как все встречи состоялись, выбирается группа шпионов, и они посылаются на задание по спасению мира. Для каждого шпиона известно, сколько денег он изведет, если его включить в эту группу. Задание должно быть выполнено, поэтому очень важно, чтобы выбранные шпионы все вместе обладали всей информацией, полученной агенством.
Найдите минимальную цену, за которую можно спасти мир.

Формат ввода
Первая строка содержит натуральное число N — количество шпионов (2 ≤ N ≤ 1000). Каждая из следующих строк содержит N натуральных чисел, не превосходящих 106. Число в k-й строке и m-м столбце обозначает стоимость встречи между шпионами k и m и совпадает с числом в m-й строке и k-м столбце (если k = m, то соответствующее число будет равно 0). Следующая строка содержит n чисел, i-е из них равно стоимости послать i-го шпиона на задание. Все стоимости являются положительными целыми числами.

Формат вывода
Выведите одно число — минимальную стоимость спасения мира. */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstring>
#include <algorithm>

using namespace std;

typedef size_t Vertex;
typedef unsigned long long ull;

struct Edge {
    Vertex from_;
    Vertex to_;
    size_t weight_;

    Edge() = default;

    Edge(Vertex from, Vertex to, size_t weight) : from_(from), to_(to), weight_(weight) {};

    bool operator<(const Edge &other) const {
        return weight_ < other.weight_;
    }
};

template<typename T>
class DSU {
    unordered_map<T, T> prev;
    unordered_map<T, size_t> rank;

    inline T FindSet(T v) {
        T original_v = v;
        while (v != prev[v]) {
            v = prev[v];
        }
        while (original_v != v) {
            prev[original_v] = v;
            original_v = prev[original_v];
        }
        return v;
    };
public:
    DSU() = default;

    DSU(size_t vertex_count) {
        for (size_t i = 1; i <= vertex_count; ++i) {
            prev[i] = i;
            rank[i] = 1;
        }
    }

    inline bool InOneSet(T x, T y) {
        return FindSet(x) == FindSet(y);
    };

    inline void Union(T x, T y) {
        T X = FindSet(x);
        T Y = FindSet(y);
        if (X == Y) {
            exit(-1);
        }
        if (rank[X] < rank[Y]) {
            prev[X] = Y;
            rank[Y] += rank[X];
        } else {
            prev[Y] = X;
            rank[X] += rank[Y];
        }
    };
};


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    size_t vertex_count;

    cin >> vertex_count;

    size_t from, to, weight;

    vector<Edge> edges;

    for (size_t i = 1; i <= vertex_count; ++i) {
        for (size_t j = 1; j <= vertex_count; ++j) {
            size_t cost;
            cin >> cost;
            if (i < j) {
                edges.push_back(Edge(i, j, cost));
            }
        }
    }

    for (size_t i = 1; i <= vertex_count; ++i) {
        size_t cost;
        cin >> cost;
        edges.push_back(Edge(i, vertex_count + 1, cost));
    }

    std::sort(edges.begin(), edges.end());

    DSU<Vertex> dsu(vertex_count + 1);

    vector<Edge> MST;

    for (Edge edge : edges) {
        if (!dsu.InOneSet(edge.from_, edge.to_)) {
            MST.emplace_back(edge);
            dsu.Union(edge.from_, edge.to_);
        }
    }

    size_t MST_weight = 0;

    for (Edge edge : MST) {
        MST_weight += edge.weight_;
    }

    cout << MST_weight;

    return 0;
}
