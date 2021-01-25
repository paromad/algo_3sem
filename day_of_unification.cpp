/* В Байтландии есть целых n городов, но нет ни одной дороги. Король страны, Вальдемар де Беар, решил исправить эту ситуацию и соединить некоторые города дорогами так, чтобы по этим дорогам можно было добраться от любого города до любого другого. Когда строительство будет завершено, король планирует отпраздновать День Объединения. К сожалению, казна Байтландии почти пуста, поэтому король требует сэкономить деньги, минимизировав суммарную длину всех построенных дорог.

Формат ввода
Первая строка входного файла содержит натуральное число n (1 ≤ n ≤ 5000) — количество городов в Байтландии.

Каждая из следующих n строк содержит по два целых числа xi, yi — координаты i-го города (-10000 ≤ xi, yi ≤ 10000). Никакие два города не расположены в одной точке.

Формат вывода
Первая строка выходного файла должна содержать минимальную суммарную длину дорог. Выведите число с точностью не менее 10-6. */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

typedef size_t Vertex;
typedef long long sll;

struct Cage {
    sll x_;
    sll y_;

    Cage() = default;

    Cage(sll x, sll y) : x_(x), y_(y) {};

    friend sll dist(const Cage &a, const Cage &b) {
        return (a.x_ - b.x_) * (a.x_ - b.x_) + (a.y_ - b.y_) * (a.y_ - b.y_);
    }
};


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    size_t vertex_count;

    cin >> vertex_count;

    vector<Cage> cages;

    int x, y;

    for (size_t i = 0; i < vertex_count; ++i) {
        cin >> x >> y;
        cages.emplace_back(Cage(x, y));
    }

    vector<bool> used(vertex_count, false);
    used[0] = true;

    vector<sll> min_edje(vertex_count, 0);

    for (size_t i = 1; i < vertex_count; ++i) {
        min_edje[i] = dist(cages[0], cages[i]);
    }

    long double MST_weight = 0;

    for (size_t i = 1; i < vertex_count; ++i) {
        int v = -1;
        for (size_t j = 0; j < vertex_count; ++j) {
            if (!used[j] && (v == -1 || min_edje[j] < min_edje[v])) {
                v = j;
            }
        }
        used[v] = true;
        MST_weight += sqrt(min_edje[v]);
        for (size_t j = 1; j < vertex_count; ++j) {
            if (dist(cages[j], cages[v]) < min_edje[j]) {
                min_edje[j] = dist(cages[j], cages[v]);
            }
        }
    }

    cout.precision(7);
    cout << MST_weight;

    return 0;
}
