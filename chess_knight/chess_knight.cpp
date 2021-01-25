/* На шахматной доске N × N в клетке (x1, y1) стоит голодный шахматный конь. Он хочет попасть в клетку (x2, y2), где растет вкусная шахматная трава. Какое наименьшее количество ходов он должен для этого сделать?

Формат ввода
На вход программы поступает пять чисел: N, x1, y1, x2, y2 (5 ≤ N ≤ 20, 1 ≤ x1, y1, x2, y2 ≤ N). Левая верхняя клетка доски имеет координаты (1, 1), правая нижняя — (N, N).

Формат вывода
В первой строке выведите единственное число K — наименьшее необходимое число ходов коня. В каждой из следующих K+1 строк должно быть записано 2 числа — координаты очередной клетки в пути коня. */

#include<iostream>
#include<queue>
#include <vector>

using namespace std;

struct Cage {
    int x_;
    int y_;

    Cage() : x_(0), y_(0) {};

    Cage(int x, int y) : x_(x), y_(y) {};

    bool operator==(const Cage &other) const {
        return x_ == other.x_ && y_ == other.y_;
    }

    friend ostream &operator<<(ostream &os, const Cage &cage) {
        os << cage.x_ + 1 << " " << cage.y_ + 1 << "\n";
        return os;
    }
};

int cage_hash(const Cage &cage, int size) {
    return cage.x_ * size + cage.y_;
}

Cage back_hash(int number, int size) {
    return Cage(number / size, number % size);
}

bool check(int x, int y, int size) {
    return (x >= 0 && x < size) && (y >= 0 && y < size);
}

vector<Cage> neighbours(const Cage &vertex, int size) {
    vector<Cage> res;
    for (int i = -1; i <= 1; i += 2) {
        for (int j = -2; j <= 2; j += 4) {
            if (check(vertex.x_ + i, vertex.y_ + j, size)) res.push_back(Cage(vertex.x_ + i, vertex.y_ + j));
            if (check(vertex.x_ + j, vertex.y_ + i, size)) res.push_back(Cage(vertex.x_ + j, vertex.y_ + i));
        }
    }
    return res;
}

void fill_in_graph(vector<vector<Cage>> &graph, int size) {
    for (int i = 0; i < size * size; ++i) {
        Cage vertex = back_hash(i, size);
        graph[i] = std::move(neighbours(vertex, size));
    }
}

void
BFS(const vector<vector<Cage>> &graph, int size, const Cage &start, vector<int> &distances, vector<Cage> &parents) {
    queue<Cage> que;
    que.push(start);
    distances[cage_hash(start, size)] = 0;
    while (!que.empty()) {
        Cage v = que.front();
        que.pop();
        for (Cage u : graph[cage_hash(v, size)]) {
            if (distances[cage_hash(u, size)] > distances[cage_hash(v, size)] + 1) {
                distances[cage_hash(u, size)] = distances[cage_hash(v, size)] + 1;
                parents[cage_hash(u, size)] = v;
                que.push(u);
            }
        }
    }
}

int main() {
    int n, x, y;
    cin >> n;

    cin >> x >> y;
    Cage start{x - 1, y - 1};

    cin >> x >> y;
    Cage finish{x - 1, y - 1};

    vector<vector<Cage>> graph(n * n);
    fill_in_graph(graph, n);

    vector<int> distances(n * n, n * n + 1);
    vector<Cage> parents(n * n);

    BFS(graph, n, start, distances, parents);

    int dist = distances[cage_hash(finish, n)];

    cout << dist << "\n";

    vector<Cage> res(dist + 1);

    res[dist--] = finish;

    while (dist >= 0) {
        finish = parents[cage_hash(finish, n)];
        res[dist--] = finish;
    }

    for (Cage i : res) {
        cout << i;
    }

    return 0;
}
