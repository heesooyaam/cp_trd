/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source: tinyKACTL
 * Description: Удвоенная знаковая площадь многоугольника; обход по часовой стрелке даёт отрицательную. Следить за переполнением.

 * Status: Stress-tested and tested on kattis:polygonarea
 */
#pragma once

#include "Point.h"

template <class T> T polygonArea2(vector<Point<T>> &v) {
    T a = v.back().cross(v[0]);
    for (int i = 0; i < (sz(v) - 1); ++i)
        a += v[i].cross(v[i + 1]);
    return a;
}
