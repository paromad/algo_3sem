/* В Физтех-школе Прикладной Математики и Информатики студенты изучают теорию графов. К сожалению, студент Демид не очень хорош в ней с математической точки зрения, но знает огромное множество алгоритмов в этой области. Поэтому многие теоремы он доказывает результатами работы некоторого алгоритма и их последующей обработкой. Но однажды ему задали непосильную задачу, помочь решить которую он просит вас. Перейдем к самой задаче.

Дан неориентированный связный граф без петель и кратных ребер на N вершинах, которые занумеровали от 1 до N. Затем на каждое ребро выписали сумму номеров вершин, которое оно соединяет, а изначальную нумерацию вершин стерли.

Для удобства работы с графом, вершины уже занумеровали от 1 до N каким-то образом, то есть формально надо найти такую перестановку p[], что если p[i] = k, то i-я вершина во входных данных имела номер k в исходном графе.

Формат ввода
На первой строке дано два натуральных числа N, M (1 ≤ N, M ≤ 106) — количество вершин и ребер в графе. Далее на M строках идут описания ребер в виде трех чисел u, v, c (1 ≤ u, v ≤ N, u ≠ v, 3 ≤ c ≤ 2N - 1 ) — ребро между вершинами с номерами u, v с написанным на нем числом c.

Формат вывода
Выведите массив из N чисел через пробел — искомая перестановка. Гарантируется, что ответ есть. */

#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    int From, To, Num;

    Edge(int u, int v, int c) : From(u), To(v), Num(c) {}
};

struct Equation {
    int Num = 0;
    int Sign = 0;

    Equation(int num, int sign) : Num(num), Sign(sign) {}

    Equation() = default;

    bool operator<(const Equation &other) const {
        return Num < other.Num;
    }
};

void DFS(const vector<vector<Edge>> &graph, int u, vector<bool> &used, vector<Equation> &eq, int &solv_num, bool &solved) {
    used[u] = true;
    for (const Edge &e : graph[u]) {
        Equation neq(e.Num - eq[u].Num, -eq[u].Sign);
        int v = e.To;
        if (!used[v]) {
            eq[v] = neq;
            DFS(graph, v, used, eq, solv_num, solved);
        } else if (eq[v].Sign != neq.Sign) {
            solved = true;
            solv_num = (neq.Num - eq[v].Num) / (eq[v].Sign - neq.Sign);
        }
    }
}

void Print(int n, int sol, const vector<Equation> &eq) {
    vector<char> used(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        int r = eq[i].Sign * sol + eq[i].Num;
        if (r < 1 || r > n || used[r]) {
            return;
        }
        used[r] = true;
    }
    for (int i = 0; i < n; ++i) {
        cout << eq[i].Sign * sol + eq[i].Num << " ";
    }
}

int CalcBipart(const vector<int> &part, const vector<Equation> &eq) {
    if (!part.size()) return 1;
    Equation m = eq[part[0]];
    for (int i : part) {
        m = min(m, eq[i]);
    }
    return (1 - m.Num) / m.Sign;
}

void SolveBipart(int n, const vector<Equation> &eq) {
    vector<int> part1, part2;
    for (int i = 0; i < n; ++i) {
        if (eq[i].Sign == 1) {
            part1.push_back(i);
        } else {
            part2.push_back(i);
        }
    }
    Print(n, CalcBipart(part1, eq), eq);
    Print(n, CalcBipart(part2, eq), eq);
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<Edge>> graph(n);
    for (int i = 0; i < m; ++i) {
        int u, v, c;
        cin >> u >> v >> c;
        --u;
        --v;
        graph[u].emplace_back(u, v, c);
        graph[v].emplace_back(v, u, c);
    }

    vector<bool> used(n, false);
    vector<Equation> eq(n);

    eq[0].Sign = 1;
    eq[0].Num = 0;

    int solv_num = 0;
    bool solved = false;

    DFS(graph, 0, used, eq, solv_num, solved);

    if (solved) {
        Print(n, solv_num, eq);
    } else {
        SolveBipart(n, eq);
    }

    return 0;
}
