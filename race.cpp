/* а день рождения юному технику Мише подарили машинку с радиоуправлением. Мише быстро наскучило гонять машинку туда-сюда по комнате, и он соорудил специальную трассу. Для этого он разбил комнату на квадратные ячейки, некоторые из них оставив пустыми, а в некоторые поставив препятствия. Целую неделю Миша каждый день улучшал свой рекорд по прохождению трассы. Но каково же было разочарование Миши, когда к нему в гости пришел Тима со своей машинкой и побил его рекорд. Стало понятно, что машинку необходимо модернизировать.

На пробных испытаниях, которые были произведены через день, Миша обнаружил, что машинка действительно ездит лучше, однако ее поведение несколько изменилось. На пульте теперь функционируют только четыре кнопки: вперед, назад, вправо, влево. При нажатии на них машинка едет по направлению к соответствующей стене комнаты, являющейся одновременно границей трассы, точно перпендикулярно ей. Машинка разгоняется до такой скорости, что перестает реагировать на другие команды, врезается в ближайшее препятствие или стену и отскакивает от нее на половину пройденного расстояния, то есть если между машинкой и стеной было x пустых клеток, то после отскока она остановится на клетке, от которой  клеток до стены.

Теперь Мише интересно, какое минимальное количество раз необходимо нажать на кнопку пульта, чтобы машинка, начав в клетке старта, остановилась в клетке финиша.

Формат ввода
Первая строка входного файла содержит два целых числа n и m — размеры трассы (2 ≤ m, n ≤ 20). Следующие n строк содержат по m символов каждая: символ «.» соответствует пустой клетке, «#» — препятствию, а «S» и «T» — клетке старта и клетке финиша соответственно.

Формат вывода
В выходной файл выведите минимальное количество нажатий на кнопки пульта для проведения машинки по трассе от старта до финиша.

Если доехать от старта до финиша невозможно, выведите -1. */

#include<iostream>
#include<queue>
#include <vector>

using namespace std;

struct Cage {
    int x_;
    int y_;

    Cage() : x_(0), y_(0) {};

    Cage(int x, int y) : x_(x), y_(y) {};
};

int cage_hash(const Cage &cage, int size) {
    return cage.x_ * size + cage.y_;
}

Cage back_hash(int number, int size) {
    return Cage(number / size, number % size);
}

vector<Cage> neighbours(const vector<vector<char>> &track, const Cage &vertex, int n, int m) {
    vector<Cage> res;
    int x = vertex.x_, y = vertex.y_, i, j;

    for (i = x; (i >= 0) && (track[i][y] != '#'); --i);
    if (x - i > 1) res.push_back(Cage((x + i + 1) / 2, y));

    for (i = x; (i < n) && (track[i][y] != '#'); ++i);
    if (i - x > 1) res.push_back(Cage((x + i) / 2, y));

    for (j = y; (j >= 0) && (track[x][j] != '#'); --j);
    if (y - j > 1) res.push_back(Cage(x, (y + j + 1) / 2));

    for (j = y; (j < m) && (track[x][j] != '#'); ++j);
    if (j - y > 1) res.push_back(Cage(x, (y + j) / 2));

    return res;
}

void fill_in_graph(vector<vector<Cage>> &graph, const vector<vector<char>> &track, int n, int m) {
    for (int i = 0; i < n * m; ++i) {
        Cage vertex = back_hash(i, m);
        if (track[vertex.x_][vertex.y_] != '#') {
            graph[i] = std::move(neighbours(track, vertex, n, m));
        }
    }
}

void BFS(const vector<vector<Cage>> &graph, const Cage &start, int m, vector<int> &distances) {
    queue<Cage> que;
    que.push(start);
    distances[cage_hash(start, m)] = 0;
    while (!que.empty()) {
        Cage v = que.front();
        que.pop();
        for (Cage u : graph[cage_hash(v, m)]) {
            if (distances[cage_hash(u, m)] == -1 || distances[cage_hash(u, m)] > distances[cage_hash(v, m)] + 1) {
                distances[cage_hash(u, m)] = distances[cage_hash(v, m)] + 1;
                que.push(u);
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    char symbol;

    Cage start, finish;

    vector<vector<char>> track(n);
    for (int i = 0; i < n; ++i) {
        track[i] = vector<char>(m);
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> symbol;
            track[i][j] = symbol;
            if (symbol == 'S') {
                start = Cage(i, j);
            }
            if (symbol == 'T') {
                finish = Cage(i, j);
            }
        }
    }

    vector<vector<Cage>> graph(n * m);
    fill_in_graph(graph, track, n, m);

    vector<int> distances(n * m, -1);

    BFS(graph, start, m, distances);

    cout << distances[cage_hash(finish, m)];

    return 0;
}
