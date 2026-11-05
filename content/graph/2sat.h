/**
 * Author: Emil Lenngren, Simon Lindholm
 * Date: 2011-11-29
 * License: CC0
 * Source: folklore
 * Description: Находит значения булевых переменных для конъюнкции дизъюнкций по два литерала либо сообщает о несовместности. Отрицание переменной x кодируется побитовым дополнением \texttt{\tilde{}x}.

 * Usage:
 *  TwoSat ts(n);
 *  ts.either(0, \tilde3); // x0 или не x3
 *  ts.setValue(2); // x2 истина
 *  ts.atMostOne({0,\tilde1,2}); // не более одного из x0, не x1, x2
 *  ts.solve(); // true, если решение есть
 *  // ts.values[0..n-1] — найденные значения
 * Time: O(N+E), N — число переменных, E — число дизъюнкций.
 * Status: stress-tested
 */
#pragma once

struct TwoSat {
    int N;
    vector<vi> gr;
    vi values; // 0 = false, 1 = true

    TwoSat(int n = 0) : N(n), gr(2 * n) {}

    int addVar() { // (необязательно)
        gr.eb();
        gr.eb();
        return N++;
    }

    void either(int f, int j) {
        f = max(2 * f, -1 - 2 * f);
        j = max(2 * j, -1 - 2 * j);
        gr[f].eb(j ^ 1);
        gr[j].eb(f ^ 1);
    }
    void setValue(int x) { either(x, x); }

    void atMostOne(const vi &li) { // (необязательно)
        if (sz(li) <= 1)
            return;
        int cur = ~li[0];
        for (int i = 2; i < (sz(li)); ++i) {
            int next = addVar();
            either(cur, ~li[i]);
            either(cur, next);
            either(~li[i], next);
            cur = ~next;
        }
        either(cur, ~li[1]);
    }

    vi val, comp, z;
    int time = 0;
    int dfs(int i) {
        int low = val[i] = ++time, x;
        z.eb(i);
        for (int e : gr[i])
            if (!comp[e])
                low = min(low, val[e] ?: dfs(e));
        if (low == val[i])
            do {
                x = z.back();
                z.pop_back();
                comp[x] = low;
                if (values[x >> 1] == -1)
                    values[x >> 1] = x & 1;
            } while (x != i);
        return val[i] = low;
    }

    bool solve() {
        values.assign(N, -1);
        val.assign(2 * N, 0);
        comp = val;
        for (int i = 0; i < (2 * N); ++i)
            if (!comp[i])
                dfs(i);
        for (int i = 0; i < (N); ++i)
            if (comp[2 * i] == comp[2 * i + 1])
                return 0;
        return 1;
    }
};
