/* Вам задан ориентированный граф с N вершинами и M ребрами (1 ≤ N ≤ 20000, 1 ≤ M ≤ 200000). Найдите компоненты сильной связности заданного графа и топологически отсортируйте его конденсацию.

Формат ввода
Граф задан во входном файле следующим образом: первая строка содержит числа N и M. Каждая из следующих M строк содержит описание ребра — два целых числа из диапазона от 1 до N — номера начала и конца ребра.

Формат вывода
На первой строке выведите число K — количество компонент сильной связности в заданном графе. На следующей строке выведите N чисел — для каждой вершины выведите номер компоненты сильной связности, которой принадлежит эта вершина. Компоненты сильной связности должны быть занумерованы таким образом, чтобы для любого ребра номер компоненты сильной связности его начала не превышал номера компоненты сильной связности его конца. */

#include <iostream>
#include <vector>
#include <deque>

using namespace std;

vector<vector<int>> Reverse(const vector<vector<int>> &graph) {
    vector<vector<int>> new_graph(graph.size());
    for (int i = 0; i < graph.size(); ++i) {
        for (int j : graph[i]) {
            new_graph[j].push_back(i);
        }
    }
    return new_graph;
}

void DFS(const vector<vector<int>> &graph, const int &v, vector<bool> &used, deque<int> &answer) {
    used[v] = true;
    for (int u : graph[v]) {
        if (!used[u]) {
            DFS(graph, u, used, answer);
        }
    }
    answer.push_front(v);
}

void TopSort (const vector<vector<int>> &graph, vector<bool> &used, deque<int> &answer) {
    for (int i = 0; i < graph.size(); ++i) {
        if (!used[i]) {
            DFS(graph, i, used, answer);
        }
    }
}

void DFS(const vector<vector<int>> &graph, const int &v, vector<bool> &used, vector<int> &number, size_t counter) {
    used[v] = true;
    number[v] = counter;
    for (int u : graph[v]) {
        if (!used[u]) {
            DFS(graph, u, used, number, counter);
        }
    }
}

vector<int> Casaraju(const vector<vector<int>> &graph, vector<bool> &used, size_t &counter) {
    deque<int> order;
    TopSort(graph, used, order);
    vector<vector<int>> transposed_graph = Reverse(graph);
    used = vector<bool>(graph.size() + 1, false);
    vector<int> number_of_component(graph.size());
    for (int i : order) {
        if (!used[i]) {
            ++counter;
            DFS(transposed_graph, i, used, number_of_component, counter);
        }
    }
    return number_of_component;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n);

    for (int i = 0; i < m; ++i) {
        int first, second;
        cin >> first >> second;
        graph[first - 1].push_back(second - 1);
    }

    vector<bool> used(n, false);

    size_t counter = 0;

    vector<int> res = Casaraju(graph, used, counter);

    cout << counter << "\n";

    for (int i : res) {
        cout << i << " ";
    }

    return 0;
}
