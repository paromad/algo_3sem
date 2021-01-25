/* У Васи есть N свинок-копилок, свинки занумерованы числами от 1 до N. Каждая копилка может быть открыта единственным соответствующим ей ключом или разбита.

Вася положил ключи в некоторые из копилок (он помнит, какой ключ лежит в какой из копилок). Теперь Вася собрался купить машину, а для этого ему нужно достать деньги из всех копилок. При этом он хочет разбить как можно меньшее количество копилок (ведь ему еще нужно копить деньги на квартиру, дачу, вертолет...). Помогите Васе определить, какое минимальное количество копилок нужно разбить.

Формат ввода
В первой строке содержится число N — количество свинок-копилок (1 ≤ N ≤ 100). Далее идет N строк с описанием того, где лежит ключ от какой копилки: в i-ой из этих строк записан номер копилки, в которой находится ключ от i-ой копилки.

Формат вывода
Выведите единственное число: минимальное количество копилок, которые необходимо разбить. */

#include <iostream>
#include <vector>

using namespace std;

void color_DFS(const vector<vector<int>> &graph, const int &v, vector<int> &color) {
    color[v] = 0;
    for (int u : graph[v]) {
        if (color[u] == -1) {
            color_DFS(graph, u, color);
        }
    }
    color[v] = 1;
}

void DFS(const vector<vector<int>> &graph, const int &v, vector<int> &tmp_color, vector<int> &color, size_t &count) {
    tmp_color[v] = 0;
    for (int u : graph[v]) {
        if (tmp_color[u] == -1) {
            DFS(graph, u, tmp_color, color, count);
        }
        if (tmp_color[u] == 0) {
            ++count;
            color_DFS(graph, u, color);
            tmp_color = color;
        }
    }
    tmp_color[v] = 1;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    int n;
    cin >> n;

    vector<vector<int>> graph(n);

    int vertex;

    for (int i = 0; i < n; ++i) {
        cin >> vertex;
        graph[vertex - 1].push_back(i);
    }

    vector<int> color(n, -1);
    vector<int> tmp_color(n, -1);

    size_t count = 0;

    for (int i = 0; i < n; ++i) {
        if (color[i] == -1) {
            DFS(graph, i, tmp_color, color, count);
        }
    }

    cout << count;

    return 0;
}
