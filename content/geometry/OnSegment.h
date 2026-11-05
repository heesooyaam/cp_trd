/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-04-26
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description: Принадлежность точки p отрезку [s,e]. Для вещественных координат использовать segDist(s,e,p)<=eps.

 * Status:
 */
#pragma once

#include "Point.h"

template <class P> bool onSegment(P s, P e, P p) {
    return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}
