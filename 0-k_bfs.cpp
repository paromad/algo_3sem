/* Дан ориентированный взвешенный граф. Найдите кратчайшее расстояние от одной заданной вершины до другой.

Формат ввода
В первой строке входного файла два числа: N и M (1 ≤ N ≤ 50 ⋅ 103, 1 ≤ M ≤ 3 ⋅ 106), где N — количество вершин графа, а M — количество ребер.

В следующей строке заданы числа S и F — начальная и конечная вершины.

Далее следует M троек чисел Ai, Bi, Ti (1 ≤ Ti ≤ 30) — номера вершин соединенных ребром и вес данного ребра.

Формат вывода
Вывести искомое расстояние или -1, если пути между указанными вершинами не существует. */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void BFS(const vector<vector<pair<int, int>>> &graph, const int &start, const int &k, vector<int> &distances) {
    vector<queue<int>> queues(k);
    queues[0].push(start);
    distances[start] = 0;
    for (size_t i = 0; i < graph.size() * k; ++i) {
        while (!queues[i % k].empty()) {
            int v = queues[i % k].front();
            queues[i % k].pop();
            for (auto u : graph[v]) {
                if (distances[u.first] == -1 || distances[u.first] > distances[v] + u.second) {
                    distances[u.first] = distances[v] + u.second;
                    queues[(i + u.second) % k].push(u.first);
                }
            }
        }
    }
}

int main() {
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(false);

    int n, m, start, finish;
    cin >> n >> m >> start >> finish;

    int max_size = 0;

    vector<vector<pair<int, int>>> graph(n + 1);
    for (int i = 0; i < m; ++i) {
        int first, second, weight;
        cin >> first >> second >> weight;
        if (weight > max_size) max_size = weight;
        graph[first].push_back(make_pair(second, weight));
    }

    vector<int> distances(n + 1, -1);

    BFS(graph, start, max_size + 1, distances);

    cout << distances[finish];

    return 0;
}
