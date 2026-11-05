/**
 * Author: heesooyaam, refactored for cp_trd
 * Source: AlgoTemplates/Other/circles_to_tree_scanline.cpp
 * Description: Лес вложенности окружностей положительного радиуса. Границы попарно не пересекаются, не касаются и не совпадают. Индексы от 0; parent=-1 у внешних окружностей, children — дети. Используется long double: зазоры должны превосходить ошибку округления. Не включать fast-math. Пояснение: doc/circle-tree.md.

 * Time: O(n \log n) время, O(n) память.
 * Status: Random laminar families vs quadratic containment.
 */
#pragma once
struct circle_tree {
    struct circle {
        long double x, y, r;
    };
    vector<circle> circles;
    vector<int> parent, roots;
    vector<vector<int>> children;
    circle_tree(vector<circle> data)
        : circles(std::move(data)), parent(circles.size(), -1),
          children(circles.size()) {
        using arc = pair<int, int>; // id, 0=нижняя дуга, 1=верхняя
        vector<tuple<long double, int, int>> events;
        for (int i = 0; i < int(circles.size()); ++i) {
            auto [x, y, r] = circles[i];
            assert(r > 0);
            events.eb(x - r, 1, i); // вход
            events.eb(x + r, 0, i); // выход обрабатывается первым
        }
        sort(all(events));
        long double scan_x = 0;
        auto height = [&](arc a) {
            auto [x, y, r] = circles[a.first];
            long double dx = x - scan_x;
            auto dy = sqrtl(max(0.L, (r - dx) * (r + dx)));
            return y + (a.second ? dy : -dy);
        };
        auto cmp = [&](arc a, arc b) {
            if (a.first == b.first)
                return a.second < b.second;
            auto y1 = height(a), y2 = height(b);
            return y1 != y2 ? y1 < y2 : a < b;
        };
        set<arc, decltype(cmp)> active(cmp);
        using iterator = decltype(active)::iterator;
        vector<array<iterator, 2>> where(circles.size());
        for (auto [x, enter, id] : events) {
            scan_x = x;
            if (!enter) {
                active.erase(where[id][0]);
                active.erase(where[id][1]);
                continue;
            }
            auto it = active.lower_bound({id, 0});
            if (it != active.end()) {
                auto [next, upper] = *it;
                parent[id] = upper ? next : parent[next];
            }
            if (parent[id] == -1)
                roots.eb(id);
            else
                children[parent[id]].eb(id);
            where[id][0] = active.emplace(id, 0).first;
            where[id][1] = active.emplace(id, 1).first;
        }
    }
};
