/**
 * Author: chilli, Takanori MAEHARA; адаптация cp_trd
 * Date: 2020-04-03
 * License: CC0
 * Source: https://github.com/spaghetti-source/algorithm/blob/master/graph/gomory_hu_tree.cc#L102
 * Description: Дерево Гомори — Ху для запросов максимального потока
 *  между любыми двумя различными вершинами неориентированного графа.
 *  Вход: n вершин 0..n-1 и рёбра \{u,v,capacity\}, capacity >= 0.
 *  Каждое неориентированное ребро передавать один раз; кратные допустимы.
 *  Выход: n-1 рёбер дерева \{u,v,weight\}. Ответ для пары u,v — минимум
 *  веса на пути в дереве: обход за O(n), либо подъёмы с минимумом за
 *  O(\log n) на запрос. Для разных компонент ответ 0.
 *  Пример: веса пути 8,3,6 дают поток 3. Для одного запроса достаточно Диница.
 * Usage: auto tree = gomory_hu(n, edges);
 * Time: n-1 запусков Диница
 * Status: Сравнение всех пар с независимым потоком на случайных графах.
 */
#pragma once
#include "TeamDinic.h"

using flow_edge = array<ll, 3>;
vector<flow_edge> gomory_hu(int n, const vector<flow_edge> &edges) {
    vector<flow_edge> tree;
    vector<int> parent(n);
    for (int i = 1; i < n; ++i) {
        dinic flow(n);
        for (auto [u, v, cap] : edges) {
            flow.add_edge(int(u), int(v), cap);
            flow.add_edge(int(v), int(u), cap);
        }
        ll value = flow.max_flow(i, parent[i]);
        tree.eb(flow_edge{i, parent[i], value});
        // Последний bfs отмечает сторону i минимального разреза.
        for (int j = i + 1; j < n; ++j) {
            if (parent[j] == parent[i] && flow.level[j] != -1)
                parent[j] = i;
        }
    }
    return tree;
}
