#include <iostream>
#include <vector>
#include <deque>
#include <queue>

using namespace std;

bool DFS(const vector<vector<int>> &graph, const int &v, vector<int> &color, vector<int> &answer) {
    color[v] = 0;
    for (int u : graph[v]) {
        if (color[u] == -1) {
            DFS(graph, u, color, answer);
        }
        if (color[u] == 0) {
            return false;
        }
    }
    color[v] = 1;
    answer.push_back(v);
    return true;
}

bool TopSort (const vector<vector<int>> &graph, vector<int> &color, vector<int> &answer) {
    for (int i = 1; i < graph.size(); ++i) {
        if (color[i] == -1) {
            if (!DFS(graph, i, color, answer)) {
                return false;
            };
        }
    }
    return true;
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

    vector<int> color(n + 1, -1);
    vector<int> answer;

    if (!TopSort(graph, color, answer)) {
        cout << -1;
        return 0;
    }

    for (auto it = answer.rbegin(); it != answer.rend(); ++it) {
        cout << *it << " ";
    }

    return 0;
}
