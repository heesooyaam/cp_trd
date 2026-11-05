/**
 * Author: Simon Lindholm
 * Date: 2017-04-17
 * License: CC0
 * Source: folklore
 * Description: Компоненты вершинной двусвязности неориентированного графа. Для рёбер каждой компоненты вызывается обработчик. Внутри компоненты между парой вершин есть два внутренне непересекающихся пути. Вершина может лежать в нескольких компонентах. Рёбра вне компонент — мосты.

 * Usage:
 *  int eid = 0; ed.resize(N);
 *  for (auto [a,b] : edges) {
 *    ed[a].eb(b, eid);
 *    ed[b].eb(a, eid++); }
 *  bicomps([\&](const vector<int>\& edgelist) {...});
 * Time: O(E + V)
 * Status: tested during MIPT ICPC Workshop 2017
 */
#pragma once

vector<int> num, st;
vector<vector<pair<int, int>>> ed;
int Time;
template <class F> int dfs(int at, int par, F &f) {
    int me = num[at] = ++Time, top = me;
    for (auto [y, e] : ed[at])
        if (e != par) {
            if (num[y]) {
                top = min(top, num[y]);
                if (num[y] < me)
                    st.eb(e);
            } else {
                int si = sz(st);
                int up = dfs(y, e, f);
                top = min(top, up);
                if (up == me) {
                    st.eb(e);
                    f(vector<int>(st.begin() + si, st.end()));
                    st.resize(si);
                } else if (up < me)
                    st.eb(e);
                else { /* e — мост */
                }
            }
        }
    return top;
}

template <class F> void bicomps(F f) {
    num.assign(sz(ed), 0);
    for (int i = 0; i < (sz(ed)); ++i)
        if (!num[i])
            dfs(i, -1, f);
}
