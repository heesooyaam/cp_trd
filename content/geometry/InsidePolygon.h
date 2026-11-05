/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-04-26
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description: Принадлежность p многоугольнику. При strict=true граница исключена. Следить за переполнением произведений.

 * Time: O(n)
 * Usage:
 * vector<P> v = {P{4,4}, P{1,2}, P{2,1}};
 * bool in = inPolygon(v, P{3, 3}, false);
 * Status: stress-tested and tested on kattis:pointinpolygon
 */
#pragma once

#include "Point.h"
#include "OnSegment.h"
#include "SegmentDistance.h"

template <class P>
bool inPolygon(vector<P> &p, P a, bool strict = true) {
    int cnt = 0, n = sz(p);
    for (int i = 0; i < (n); ++i) {
        P q = p[(i + 1) % n];
        if (onSegment(p[i], q, a))
            return !strict;
        // Для double условие выше: segDist(p[i], q, a) <= eps.
        cnt ^=
            ((a.y < p[i].y) - (a.y < q.y)) * a.cross(p[i], q) >
            0;
    }
    return cnt;
}
