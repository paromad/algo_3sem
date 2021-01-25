#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef size_t Vertex;

struct Edge {
    Vertex from_;
    Vertex to_;
    size_t num_;
    Edge() = default;

    Edge(Vertex from, Vertex to, size_t num) : from_(from), to_(to), num_(num) {};
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
};

void DFS(const Graph &graph, const Vertex &v, bool is_root, vector<bool> &used, size_t &time, vector<size_t> &time_in,
         vector<size_t> &time_up, vector<Vertex> &parent, vector<size_t> &bridges) {
    used[v] = true;
    time_in[v] = time_up[v] = ++time;
    bool is_cut_vertex = false;
    for (Edge e : graph.get_neighbours(v)) {
        if (e.to_ != parent[v]) {
            if (used[e.to_]) {
                time_up[v] = std::min(time_up[v], time_in[e.to_]);
            } else {
                parent[e.to_] = v;
                DFS(graph, e.to_, false, used, time, time_in, time_up, parent, bridges);
                time_up[v] = std::min(time_up[v], time_up[e.to_]);
                if (time_in[v] < time_up[e.to_]) {
                    bridges.push_back(e.num_);
                }
            }
        }
    }
}

vector<size_t> Bridges(const Graph &graph) {
    vector<size_t> bridges;
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

    vector<size_t> bridges = Bridges(graph);

    cout << bridges.size() << "\n";

    std::sort(bridges.begin(), bridges.end());

    for (auto it = bridges.begin(); it != bridges.end(); ++it) {
        cout << *it << "\n";
    }

    return 0;
}
