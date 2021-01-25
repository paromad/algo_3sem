/* Дан ориентированный невзвешенный граф. Необходимо определить есть ли в нём циклы, и если есть, то вывести любой из них.

Формат ввода
В первой строке входного файла находятся два натуральных числа N и M (1 ≤ N ≤ 100000, M ≤ 100000) — количество вершин и рёбер в графе соответственно. Далее в M строках перечислены рёбра графа. Каждое ребро задаётся парой чисел — номерами начальной и конечной вершин соответственно.

Формат вывода
Если в графе нет цикла, то вывести NO, иначе — YES и затем перечислить все вершины в порядке обхода цикла. */

#include <iostream>
#include <vector>
#include <deque>
#include <queue>

using namespace std;

void DFS(const vector<vector<int>> &graph, const int &v, vector<int> &parent, vector<int> &color, pair<int, int> &cycle) {
    color[v] = 0;
    for (int u : graph[v]) {
        if (color[u] == -1) {
            parent[u] = v;
            DFS(graph, u, parent, color, cycle);
        }
        if (color[u] == 0) {
            cycle = make_pair(u, v);
        }
    }
    color[v] = 1;
}

int main() {
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n + 1);
    for (int i = 0; i < m; ++i) {
        int first, second;
        cin >> first >> second;
        graph[first].push_back(second);
    }

    vector<int> parent(n + 1, -1);
    vector<int> color(n + 1, -1);

    pair<int, int> cycle = make_pair(0, 0);

    for (int i = 1; i <= n; ++i) {
        if (color[i] == -1) {
            DFS(graph, i, parent, color, cycle);
        }
    }

    if (cycle == make_pair(0, 0)) {
        cout << "NO";
    } else {
        cout << "YES\n";
        vector<int> res;
        res.push_back(cycle.second);
        while (parent[cycle.second] != cycle.first) {
            cycle.second = parent[cycle.second];
            res.push_back(cycle.second);
        }
        res.push_back(cycle.first);
        for (auto it = res.rbegin(); it != res.rend(); ++it) {
            cout << *it << " ";
        }
    }
}
