/* Шел 2100-й год. Физтех стал огромным ВУЗом, состоящим из большого множества корпусов и гипертонеллей в качестве переходов между ними. Отныне до Тимирязевской (как и от любого другого корпуса) можно добраться за 5 минут от общежития (или любого другого здания университета) с помощью гиперлупов (напрямую или с пересадочными станциями в каждом корпусе).

К сожалению, иногда переходы могут быть обесточены во время проведения ремонтных работ, а значит перемещаться по ним нельзя. Нужно выяснить, сколько гипертоннелей для гиперлупов надо построить, чтобы при неисправности любого из переходов физтех оставался связным.

Учитывая то, что систему разрабатывали самые лучшие ученые страны, в ней нет бессмысленных кратных ребер и петель.

Формат ввода
Первая строка содержит два числа n (3 ≤ n ≤ 5000) — количество зданий на физтехе и m (1 ≤ m ≤ 100000) — количество построенных гипертоннелей. Следующие m строк содержат два числа vi, ui (1 ≤ vi, ui ≤ n) — описание гипертоннелей.

Формат вывода
Выведите минимальное количество гипертоннелей, которые нужно достроить, чтобы при ремонте любого из них физтех оставался связным. */

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_set>

using namespace std;

typedef size_t Vertex;

struct Edge {
    Vertex from_;
    Vertex to_;
    size_t num_;
    Edge() = default;

    Edge(Vertex from, Vertex to, size_t num) : from_(from), to_(to), num_(num) {};
};


template<typename T>
class DSU {
    map<T, T> prev;
    map<T, size_t> rank;
public:
    DSU() = default;

    DSU(size_t vertex_count) {
        for (int i = 1; i <= vertex_count; ++i) {
            prev[i] = i;
            rank[i] = 1;
        }
    }

    T FindSet(T v) {
        if (v == prev[v]) return v;
        return prev[v] = FindSet(prev[v]);
    };

    bool InOneSet(T x, T y) {
        return FindSet(x) == FindSet(y);
    };

    void Union(T x, T y) {
        T X = FindSet(x);
        T Y = FindSet(y);
        if (rank[X] < rank[Y]) {
            prev[X] = Y;
        } else if (rank[X] > rank[Y]) {
            prev[Y] = X;
        } else {
            prev[X] = Y;
            ++rank[Y];
        }
    };
};


class Graph {
protected:
    size_t vertex_count_;
    size_t edge_count_;
    bool is_directed_;
public:
    Graph(size_t vertex_count, size_t edje_count, bool is_directed) : vertex_count_(vertex_count),
                                                                      edge_count_(edje_count),
                                                                      is_directed_(is_directed) {};

    size_t get_vertex_count() const {
        return vertex_count_;
    };

    size_t get_edge_count() const {
        return edge_count_;
    };

    bool is_directed() const {
        return is_directed_;
    }

    virtual void add_edge(const Vertex &start, const Vertex &finish, size_t num) = 0;

    const virtual std::vector<Edge> &get_neighbours(Vertex v) const = 0;
};


class AdjListGraph : public Graph {
    vector<vector<Edge>> adj_list_;
public:
    AdjListGraph(size_t vertex_count, size_t edge_count, bool is_directed) : Graph(vertex_count, edge_count,
                                                                                   is_directed) {
        adj_list_.resize(vertex_count + 1);
    };

    void add_edge(const Vertex &start, const Vertex &finish, size_t num) override {
        adj_list_[start].push_back(Edge(start,finish, num));
        if (!is_directed()) {
            adj_list_[finish].push_back(Edge(finish, start, num));
        }
    }

    const std::vector<Edge> &get_neighbours(Vertex v) const override {
        return adj_list_[v];
    }

    void Components(DSU<Vertex> &dsu, const unordered_set<size_t> &bridges) const {
        for (const auto &it : adj_list_) {
            for (const Edge &e : it) {
                if (bridges.find(e.num_) == bridges.end()) {
                    dsu.Union(e.from_, e.to_);
                }
            }
        }
    }

    size_t NumberOfRoads(DSU<Vertex> &dsu, const unordered_set<size_t> &bridges) {
        map<size_t, size_t> deg;
        for (const auto &it : adj_list_) {
            for (const Edge &e : it) {
                if (bridges.find(e.num_) != bridges.end()) {
                    ++deg[dsu.FindSet(e.from_)];
                    ++deg[dsu.FindSet(e.to_)];
                }
            }
        }
        size_t count = 0;
        for (auto it : deg) {
            if (it.second == 2) {
                ++count;
            }
        }
        return (count + 1) / 2;
    }
};

void DFS(const Graph &graph, const Vertex &v, bool is_root, vector<bool> &used, size_t &time, vector<size_t> &time_in,
         vector<size_t> &time_up, vector<Vertex> &parent, unordered_set<size_t> &bridges) {
    used[v] = true;
    time_in[v] = time_up[v] = ++time;
    for (Edge e : graph.get_neighbours(v)) {
        if (e.to_ != parent[v]) {
            if (used[e.to_]) {
                time_up[v] = std::min(time_up[v], time_in[e.to_]);
            } else {
                parent[e.to_] = v;
                DFS(graph, e.to_, false, used, time, time_in, time_up, parent, bridges);
                time_up[v] = std::min(time_up[v], time_up[e.to_]);
                if (time_in[v] < time_up[e.to_]) {
                    bridges.insert(e.num_);
                }
            }
        }
    }
}


unordered_set<size_t> Bridges(const Graph &graph) {
    unordered_set<size_t> bridges;
    vector<bool> used(graph.get_vertex_count() + 1, false);
    vector<size_t> time_in(graph.get_vertex_count() + 1);
    vector<size_t> time_up(graph.get_vertex_count() + 1);
    vector<Vertex> parent(graph.get_vertex_count() + 1, 0);
    size_t time = 0;
    for (size_t v = 1; v <= graph.get_vertex_count(); ++v) {
        if (!used[v]) {
            DFS(graph, v, true, used, time, time_in, time_up, parent, bridges);
        }
    }
    return bridges;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    size_t vertex_count, edge_count;

    cin >> vertex_count >> edge_count;

    bool is_directed = false;

    AdjListGraph graph(vertex_count, edge_count, is_directed);

    for (size_t i = 1; i <= edge_count; ++i) {
        int first, second;
        cin >> first >> second;
        graph.add_edge(first, second, i);
    }

    unordered_set<size_t> bridges = Bridges(graph);

    DSU<Vertex> dsu(vertex_count);

    graph.Components(dsu, bridges);

    cout << graph.NumberOfRoads(dsu, bridges);

    return 0;
}
