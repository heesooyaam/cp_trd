/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source:
 * Description: Положение p относительно направления s→e: 1 слева, 0 на прямой, -1 справа. С eps ноль означает расстояние до прямой не больше eps. Следить за переполнением произведений.

 * Usage:
 * 	bool left = sideOf(p1,p2,q)==1;
 * Status: tested
 */
#pragma once

#include "Point.h"

template <class P> int sideOf(P s, P e, P p) {
    return sgn(s.cross(e, p));
}

template <class P> int sideOf(P s, P e, P p, double eps) {
    auto a = (e - s).cross(p - s);
    double l = (e - s).dist() * eps;
    return (a > l) - (a < -l);
}
