/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-04-27
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description: Пересечение отрезков: пустой массив, одна точка или два конца общего отрезка. Для нецелого пересечения нужен вещественный тип P. Промежуточные выражения содержат произведения трёх координат.

 * Usage:
 * vector<P> inter = segInter(s1,e1,s2,e2);
 * if (sz(inter)==1)
 *   cout << "segments intersect at " << inter[0] << endl;
 * Status: stress-tested, tested on kattis:intersection
 */
#pragma once

#include "Point.h"
#include "OnSegment.h"

template <class P> vector<P> segInter(P a, P b, P c, P d) {
    auto oa = c.cross(d, a), ob = c.cross(d, b),
         oc = a.cross(b, c), od = a.cross(b, d);
    // Пересечение во внутренних точках обоих отрезков.
    if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
        return {(a * ob - b * oa) / (ob - oa)};
    set<P> s;
    if (onSegment(c, d, a))
        s.emplace(a);
    if (onSegment(c, d, b))
        s.emplace(b);
    if (onSegment(a, b, c))
        s.emplace(c);
    if (onSegment(a, b, d))
        s.emplace(d);
    return {all(s)};
}
