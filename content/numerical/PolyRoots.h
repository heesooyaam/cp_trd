/**
 * Author: Per Austrin
 * Date: 2004-02-08
 * License: CC0
 * Description: Поиск вещественных корней полинома.

 * Usage: polyRoots({{2,-3,1}},-1e9,1e9) // решить x^2-3x+2 = 0
 * Time: O(n^2 \log(1/\epsilon))
 */
#pragma once

#include "Polynomial.h"

vector<double> polyRoots(Poly p, double xmin, double xmax) {
    if (sz(p.a) == 2) {
        return {-p.a[0] / p.a[1]};
    }
    vector<double> ret;
    Poly der = p;
    der.diff();
    auto dr = polyRoots(der, xmin, xmax);
    dr.eb(xmin - 1);
    dr.eb(xmax + 1);
    sort(all(dr));
    for (int i = 0; i < (sz(dr) - 1); ++i) {
        double l = dr[i], h = dr[i + 1];
        bool sign = p(l) > 0;
        if (sign ^ (p(h) > 0)) {
            for (int it = 0; it < (60);
                 ++it) { // while (h - l > 1e-8)
                double m = (l + h) / 2, f = p(m);
                if ((f <= 0) ^ sign)
                    l = m;
                else
                    h = m;
            }
            ret.eb((l + h) / 2);
        }
    }
    return ret;
}
