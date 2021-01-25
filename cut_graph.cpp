/* Дан неориентированный граф. Над ним в заданном порядке производят операции следующих двух типов:

cut — разрезать граф, то есть удалить из него ребро;

ask — проверить, лежат ли две вершины графа в одной компоненте связности.

Известно, что после выполнения всех операций типа cut рёбер в графе не осталось. Найдите результат выполнения каждой из операций типа ask.

Формат ввода
Первая строка входного файла содержит три целых числа, разделённые пробелами — количество вершин графа n, количество рёбер m и количество операций k (1 ≤ n ≤ 50000 , 0 ≤ m ≤ 100000 , m ≤ k ≤ 150000).

Следующие m строк задают рёбра графа; i-ая из этих строк содержит два числа ui и vi (1 ≤ ui ≤ vi ≤ n), разделённые пробелами — номера концов i-го ребра. Вершины нумеруются с единицы; граф не содержит петель и кратных рёбер.

Далее следуют k строк, описывающих операции.

Операция типа cut задаётся строкой cut u v (1 ≤ u ≤ v ≤ n), которая означает, что из графа удаляют ребро между вершинами u и v.

Операция типа ask задаётся строкой ask u v (1 ≤ u ≤ v ≤ n), которая означает, что необходимо узнать, лежат ли в данный момент вершины u и v в одной компоненте связности.

Гарантируется, что каждое ребро графа встретится в операциях типа cut ровно один раз.

Формат вывода
Для каждой операции ask во входном файле выведите на отдельной строке слово «YES», если две указанные вершины лежат в одной компоненте связности, и «NO» в противном случае. Порядок ответов должен соответствовать порядку операций ask во входном файле. */

#include <iostream>
#include <vector>
#include <map>
#include <cstring>

using namespace std;

struct Command {
    size_t comm_;
    int x_;
    int y_;
    Command() = default;
    Command(size_t comm, size_t x = 0, size_t y = 0) : comm_(comm), x_(x), y_(y) {};
};

template<typename T>
class DSU {
    map<T, T> prev;
    map<T, size_t> rank;

    T FindSet(T v) {
        if (v == prev[v]) return v;
        return prev[v] = FindSet(prev[v]);
    };
public:
    DSU() = default;

    DSU(size_t vertex_count) {
        for (int i = 1; i <= vertex_count; ++i) {
            prev[i] = i;
            rank[i] = 1;
        }
    }

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


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    size_t vertex_count, edge_count, operation_count;

    cin >> vertex_count >> edge_count >> operation_count;

    vector<Command> operation(operation_count);

    for (size_t i = 0; i < edge_count; ++i) {
        size_t first, second;
        cin >> first >> second;
    }

    for (size_t i = 0; i < operation_count; ++i) {
        char command[4];
        size_t comm, first, second;
        cin >> command >> first >> second;
        if (!strcmp(command, "cut")) {
            comm = 1;
        } else {
            comm = 2;
        }
        operation[i] = (Command(comm, first, second));
    }

    DSU<size_t> dsu(vertex_count);

    vector<bool> answer;

    while (operation_count > 0) {
        Command command = operation[operation_count - 1];
        switch (command.comm_) {
            case 1:
                dsu.Union(command.x_, command.y_);
                break;
            case 2:
                answer.push_back(dsu.InOneSet(command.x_, command.y_) ? true : false);
                break;
        }
        --operation_count;
    }

    for (auto it = answer.crbegin(); it != answer.crend(); ++it) {
        cout << (*it ? "YES\n" : "NO\n");
    }

    return 0;
}
