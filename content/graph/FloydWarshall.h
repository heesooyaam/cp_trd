/**
 * Author: Simon Lindholm
 * Date: 2016-12-15
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Floyd–Warshall_algorithm
 * Description: Кратчайшие пути между всеми парами, отрицательные рёбра допустимы. Вход m — матрица расстояний; отсутствующее ребро равно inf. Выход: кратчайшие расстояния, inf при недостижимости, -inf при пути через отрицательный цикл. На диагонали изначально 0.

 * Time: O(N^3)
 * Status: slightly tested
 */
#pragma once

const ll inf = 1LL << 62;
void floydWarshall(vector<vector<ll>> &m) {
    int n = sz(m);
    for (int i = 0; i < (n); ++i)
        m[i][i] = min<ll>(m[i][i], 0);
    for (int k = 0; k < (n); ++k)
        for (int i = 0; i < (n); ++i)
            for (int j = 0; j < (n); ++j)
                if (m[i][k] != inf && m[k][j] != inf) {
                    auto newDist = max(m[i][k] + m[k][j], -inf);
                    m[i][j] = min(m[i][j], newDist);
                }
    for (int k = 0; k < (n); ++k)
        if (m[k][k] < 0)
            for (int i = 0; i < (n); ++i)
                for (int j = 0; j < (n); ++j)
                    if (m[i][k] != inf && m[k][j] != inf)
                        m[i][j] = -inf;
}
