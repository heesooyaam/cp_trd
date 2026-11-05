/**
 * Author: Simon Lindholm
 * Date: 2015-02-23
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Bellman-Ford_algorithm
 * Description: Кратчайшие пути из s, допустимы отрицательные веса. Недостижимые вершины имеют dist=inf; достижимые через отрицательный цикл — dist=-inf. Требуется $V^2\max|w_i|<2^{63}$ с запасом от переполнения.

 * Time: O(VE)
 * Status: Tested on kattis:shortestpath3
 */
#pragma once

const ll inf = LLONG_MAX;
struct Ed {
    int a, b, w, s() { return a < b ? a : -a; }
};
struct Node {
    ll dist = inf;
    int prev = -1;
};

void bellmanFord(vector<Node> &nodes, vector<Ed> &eds, int s) {
    nodes[s].dist = 0;
    sort(all(eds), [](Ed a, Ed b) { return a.s() < b.s(); });

    int lim =
        sz(nodes) / 2 + 2; // /3+100 при случайном порядке вершин
    for (int i = 0; i < (lim); ++i)
        for (Ed ed : eds) {
            Node cur = nodes[ed.a], &dest = nodes[ed.b];
            if (abs(cur.dist) == inf)
                continue;
            ll d = cur.dist + ed.w;
            if (d < dest.dist) {
                dest.prev = ed.a;
                dest.dist = (i < lim - 1 ? d : -inf);
            }
        }
    for (int i = 0; i < (lim); ++i)
        for (Ed e : eds) {
            if (nodes[e.a].dist == -inf)
                nodes[e.b].dist = -inf;
        }
}
