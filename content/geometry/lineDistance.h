/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source: Basic math
 * Description: Знаковое расстояние от p до прямой ab: положительно слева по направлению a→b, отрицательно справа. При a=b не определено. В промежуточных произведениях возможно переполнение. Для Point3D брать длину векторного произведения, расстояние неотрицательно.

 * Status: tested
 */
#pragma once

#include "Point.h"

template <class P> double lineDist(P a, P b, P p) {
    return (double)(b - a).cross(p - a) / (b - a).dist();
}
