/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source:
 * Description: Отсекает часть многоугольника слева от ориентированной прямой s→e, возвращает вершины оставшейся части.

 * Usage:
 * 	vector<P> p = ...;
 * 	p = polygonCut(p, P(0,0), P(1,0));
 * Status: tested but not extensively
 */
#pragma once

#include "Point.h"

typedef Point<double> P;
vector<P> polygonCut(const vector<P> &poly, P s, P e) {
    vector<P> res;
    for (int i = 0; i < (sz(poly)); ++i) {
        P cur = poly[i], prev = i ? poly[i - 1] : poly.back();
        auto a = s.cross(e, cur), b = s.cross(e, prev);
        if ((a < 0) != (b < 0))
            res.eb(cur + (prev - cur) * (a / (a - b)));
        if (a < 0)
            res.eb(cur);
    }
    return res;
}
