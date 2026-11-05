/**
 * Author: Simon Lindholm
 * Date: 2018-07-06
 * License: CC0
 * Description: Кодирование перестановки целым числом без сохранения лексикографического порядка. Для обратного преобразования можно построить таблицу.

 * Time: O(n)
 */
#pragma once

int permToInt(vector<int> &v) {
    int use = 0, i = 0, r = 0;
    for (int x : v)
        r = r * ++i + __builtin_popcount(use & -(1 << x)),
        use |= 1 << x; // (именно минус, не ~!)
    return r;
}
