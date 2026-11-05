/**
 * Author: Benjamin Qi, Oleksandr Kulkov, chilli
 * Date: 2020-01-12
 * License: CC0
 * Source: https://codeforces.com/blog/entry/53170, https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Trees%20(10)/HLD%20(10.3).h
 * Description: Разбиение дерева на тяжёлые пути; до корня не больше O(\log n) лёгких рёбер. Реализованы прибавление и максимум на пути/поддереве; подходят другие коммутативные операции ДО. Вход — полный список смежности, корень 0. VALS\_EDGES=true хранит значения на рёбрах, иначе на вершинах. Начальные значения задаёт ДО.

 * Time: O((\log N)^2)
 * Status: stress-tested against old HLD
 */
#pragma once

#include "../data-structures/LazySegmentTree.h"

template <bool VALS_EDGES> struct HLD {
    int N, tim = 0;
    vector<vi> adj;
    vi par, siz, rt, pos;
    Node *tree;
    HLD(vector<vi> adj_)
        : N(sz(adj_)), adj(adj_), par(N, -1), siz(N, 1), rt(N),
          pos(N), tree(new Node(0, N)) {
        dfsSz(0);
        dfsHld(0);
    }
    void dfsSz(int v) {
        for (int &u : adj[v]) {
            adj[u].erase(find(all(adj[u]), v));
            par[u] = v;
            dfsSz(u);
            siz[v] += siz[u];
            if (siz[u] > siz[adj[v][0]])
                swap(u, adj[v][0]);
        }
    }
    void dfsHld(int v) {
        pos[v] = tim++;
        for (int u : adj[v]) {
            rt[u] = (u == adj[v][0] ? rt[v] : u);
            dfsHld(u);
        }
    }
    template <class B> void process(int u, int v, B op) {
        for (;; v = par[rt[v]]) {
            if (pos[u] > pos[v])
                swap(u, v);
            if (rt[u] == rt[v])
                break;
            op(pos[rt[v]], pos[v] + 1);
        }
        op(pos[u] + VALS_EDGES, pos[v] + 1);
    }
    void modifyPath(int u, int v, int val) {
        process(u, v,
                [&](int l, int r) { tree->add(l, r, val); });
    }
    int queryPath(int u, int v) { // изменить под задачу
        int res = -1e9;
        process(u, v, [&](int l, int r) {
            res = max(res, tree->query(l, r));
        });
        return res;
    }
    int querySubtree(int v) { // modifySubtree аналогично
        return tree->query(pos[v] + VALS_EDGES,
                           pos[v] + siz[v]);
    }
};
