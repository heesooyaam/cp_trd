/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-10-31
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description: Общие внешние касательные; для внутренних передать отрицательный r2. Возвращает 0,1 или 2 пары точек касания на первой и второй окружности. При единственной касательной точки совпадают, прямая перпендикулярна линии центров. Для касательных из точки задать r2=0.

 * Status: tested
 */
#pragma once

#include "Point.h"

template <class P>
vector<pair<P, P>> tangents(P c1, double r1, P c2, double r2) {
    P d = c2 - c1;
    double dr = r1 - r2, d2 = d.dist2(), h2 = d2 - dr * dr;
    if (d2 == 0 || h2 < 0)
        return {};
    vector<pair<P, P>> out;
    for (double sign : {-1, 1}) {
        P v = (d * dr + d.perp() * sqrt(h2) * sign) / d2;
        out.eb(c1 + v * r1, c2 + v * r2);
    }
    if (h2 == 0)
        out.pop_back();
    return out;
}
