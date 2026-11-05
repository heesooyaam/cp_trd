/**
 * Author: Ulf Lundstrom
 * Date: 2009-04-11
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Circumcircle
 * Description: Описанная окружность треугольника ABC: ccRadius — радиус, ccCenter — центр. Точки не должны лежать на одной прямой.

 * Status: tested
 */
#pragma once

#include "Point.h"

typedef Point<double> P;
double ccRadius(P A, P B, P C) {
    return (B - A).dist() * (C - B).dist() * (A - C).dist() /
           abs((B - A).cross(C - A)) / 2;
}
P ccCenter(P A, P B, P C) {
    P b = C - A, c = B - A;
    return A + (b * c.dist2() - c * b.dist2()).perp() /
                   b.cross(c) / 2;
}
