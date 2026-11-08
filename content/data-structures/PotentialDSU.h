/**
 * Author: cp_trd
 * License: CC0
 * Description: DSU с потенциалами: хранит ограничения value[b]-value[a]=w.
 *  join(a,b,w) возвращает false при противоречии и не добавляет это
 *  ограничение; true означает, что оно совместимо, даже без слияния.
 *  diff(a,b) возвращает value[b]-value[a] или nullopt, если связи нет.
 *  Все промежуточные суммы и разности должны помещаться в ll.
 *  PotentialDSU<true> вместо разности хранит XOR: value[a] xor value[b]=w.
 *  Для чётностей w=0 означает одинаковый цвет, w=1 -- разный.
 *  Ребро join(a,b,1) проверяет двудольность; после первого false весь
 *  исходный граф уже не двудолен, этот факт сохранять отдельно.
 * Usage: PotentialDSU<> d(3); d.join(0,1,5); d.join(1,2,-2);
 *  auto x = d.diff(0,2); // x.has_value(), *x == 3
 *  // d.join(0,2,4) == false; предыдущие ограничения сохранены
 * Time: $O(\alpha(N))$ амортизированно; память O(N)
 */
#pragma once

template <bool use_xor = false> struct PotentialDSU {
    vector<int> e;
    vector<ll> delta; // value[v]-value[parent[v]] (либо XOR)
    PotentialDSU(int n) : e(n, -1), delta(n) {}
    static ll combine(ll a, ll b) {
        return use_xor ? a ^ b : a + b;
    }
    static ll inverse(ll a) { return use_xor ? a : -a; }
    int find(int v) {
        if (e[v] < 0) {
            return v;
        }
        int p = e[v], root = find(p);
        delta[v] = combine(delta[v], delta[p]);
        return e[v] = root;
    }
    optional<ll> diff(int a, int b) {
        if (find(a) != find(b)) {
            return nullopt;
        }
        return combine(delta[b], inverse(delta[a]));
    }
    bool join(int a, int b, ll w) {
        int ra = find(a), rb = find(b);
        if (ra == rb) {
            return combine(delta[b], inverse(delta[a])) == w;
        }
        // Нужен потенциал корня b относительно корня a.
        w = combine(w, combine(delta[a], inverse(delta[b])));
        if (e[ra] > e[rb]) {
            swap(ra, rb);
            w = inverse(w);
        }
        e[ra] += e[rb];
        e[rb] = ra;
        delta[rb] = w;
        return true;
    }
};
