/* Вам нужно распространить новость о посвяте среди всех первокурсников. Известно, что первокурсники общаются друг с другом через чаты, при этом если новость вброшена в чат, то гарантируется что все его участники прочтут новость (эх, было бы так не только в условии этой задачи).

Так как у вас уже и так очень много своих чатов, вы хотите вступить в как можно меньшее их количество, чтобы все первокурсники узнали, что посвят уже скоро. При этом вам неизвестны составы чатов, но до вас дошли сведения, что некоторые пары первокурсников гарантированно сидят в одном чате. Более того, если студент сидит в чате и видит новость, то он пересылает сообщение с важной информации во все остальные чаты, где он есть.

Формат ввода
Во входном файле записано два числа N — число первокурсников и M — число известных вам пар первокурсников, сидящих в одном чате (1 ≤ N ≤ 100000, 0 ≤ M ≤ 100000). В следующих M строках записаны по два числа i и j (1 ≤ i, j ≤ N), которые означают, что первокурсники с номерами i и j в одном чате.

Формат вывода
В первой строчке выходного файла выведите количество чатов, куда вам надо вступить. Далее выведите группы студентов, которые узнают о новости для каждого вступления в чат: в первой строке количество студентов в такой группе в компоненте, во второй — номера студентов в произвольном порядке. */

#include <iostream>
#include <vector>

using namespace std;

void DFS(const vector<vector<int>> &graph, const int &v, vector<int> &color, vector<int> &res) {
    color[v] = 0;
    for (int u : graph[v]) {
        if (color[u] == -1) {
            DFS(graph, u, color, res);
        }
    }
    color[v] = 1;
    res.push_back(v);
}

void Components (const vector<vector<int>> &graph, vector<int> &color, vector<vector<int>> &answer) {
    for (int i = 1; i < graph.size(); ++i) {
        if (color[i] == -1) {
            vector<int> res;
            DFS(graph, i, color, res);
            answer.push_back(res);
        }
    }
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
        graph[second].push_back(first);
    }

    vector<int> color(n + 1, -1);
    vector<vector<int>> answer;

    Components(graph, color, answer);

    cout << answer.size() << "\n";
    for (auto vect : answer) {
        cout << vect.size() << "\n";
        for (int i : vect) {
            cout << i << " ";
        }
        cout << "\n";
    }

    return 0;
}
