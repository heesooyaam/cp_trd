/**
 * Author: Jeremy Lim, Joshua Andersson
 * Date: 2026-07-09
 * License: CC0
 * Source: https://github.com/scipy/scipy/blob/main/scipy/optimize/rectangular_lsap/rectangular_lsap.cpp
 * Description: Венгерский алгоритм: назначает каждой левой вершине различную правую с минимумом суммы стоимостей. Вход cost[N][M], требуется N<=M. Выход (стоимость,match), где пара L[i] — R[match[i]]. Для максимума поменять знак стоимостей.

 * Time: O(N^2M)
 * Status: Tested on kattis:cordonbleu, kattis:engaging, stress-tested
 */
#pragma once

template <class T>
pair<T, vi> weightedMatching(vector<vector<T>> &C) {
    int i = sz(C), m = i ? sz(C[0]) : 0, c, s, r;
    vector<T> dist(m), pot(m);
    vi match(i), rev(m, -1), cols(m), prev(m);
    T d = 0, nd, cost = 0;
    while (i--) {
        for (int c = 0; c < (m); ++c)
            dist[c] = C[i][c], cols[c] = c, prev[c] = i;
        for (s = 0;;) {
            for (int j = s; j < (m); ++j) {
                c = cols[j], nd = dist[c] - pot[c];
                if (j == s || d > nd)
                    d = nd, swap(cols[s], cols[j]);
            }
            if ((r = rev[c = cols[s++]]) == -1)
                break;
            for (int j = 0; j < (m); ++j)
                if (dist[j] >
                    (nd = C[r][j] - C[r][c] + dist[c]))
                    dist[j] = nd, prev[j] = r;
        }
        cost += dist[c];
        while (s--)
            pot[cols[s]] = dist[cols[s]] - d;
        for (; r != i; swap(c, match[r]))
            r = rev[c] = prev[c];
    }
    return {cost, match};
}
