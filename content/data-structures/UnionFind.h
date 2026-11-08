/**
 * Author: Lukas Polacek
 * Date: 2009-10-26
 * License: CC0
 * Source: folklore
 * Description: Обычная DSU (СНМ): сжатие путей и объединение по размеру.
 *  find(v) возвращает корень, sameSet(a,b) проверяет связность, size(v)
 *  даёт размер компоненты. join(a,b) возвращает true, только если объединил
 *  разные компоненты. Вершины 0..n-1; откатов нет.
 * Usage: UF dsu(n); dsu.join(0, 1); // dsu.size(0) == 2
 * Time: $O(\alpha(N))$ амортизированно на операцию
 */
#pragma once

struct UF {
    vector<int> e;
    UF(int n) : e(n, -1) {}
    bool sameSet(int a, int b) { return find(a) == find(b); }
    int size(int x) { return -e[find(x)]; }
    int find(int x) {
        if (e[x] < 0) {
            return x;
        }
        return e[x] = find(e[x]);
    }
    bool join(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) {
            return false;
        }
        if (e[a] > e[b]) {
            swap(a, b);
        }
        e[a] += e[b];
        e[b] = a;
        return true;
    }
};
