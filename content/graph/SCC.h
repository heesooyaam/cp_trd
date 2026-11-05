/**
 * Author: Lukas Polacek
 * Date: 2009-10-28
 * License: CC0
 * Source: Czech graph algorithms book, by Demel. (Tarjan's algorithm)
 * Description: Компоненты сильной связности ориентированного графа: любые две вершины одной компоненты взаимно достижимы.

 * Usage: scc(graph, [\&](vi\& v) { ... }) обрабатывает все компоненты
 * in reverse topological order. comp[i] holds the component
 * index of a node (a component only has edges to components with
 * lower index). ncomps will contain the number of components.
 * Time: O(E + V)
 * Status: Bruteforce-tested for N <= 5
 */
#pragma once

vi val, comp, z, cont;
int Time, ncomps;
template <class G, class F> int dfs(int j, G &g, F &f) {
    int low = val[j] = ++Time, x;
    z.eb(j);
    for (auto e : g[j])
        if (comp[e] < 0)
            low = min(low, val[e] ?: dfs(e, g, f));

    if (low == val[j]) {
        do {
            x = z.back();
            z.pop_back();
            comp[x] = ncomps;
            cont.eb(x);
        } while (x != j);
        f(cont);
        cont.clear();
        ncomps++;
    }
    return val[j] = low;
}
template <class G, class F> void scc(G &g, F f) {
    int n = sz(g);
    val.assign(n, 0);
    comp.assign(n, -1);
    Time = ncomps = 0;
    for (int i = 0; i < (n); ++i)
        if (comp[i] < 0)
            dfs(i, g, f);
}
