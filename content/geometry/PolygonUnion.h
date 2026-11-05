/**
 * Author: black_horse2014, chilli
 * Date: 2019-10-29
 * License: Unknown
 * Source: https://codeforces.com/gym/101673/submission/50481926
 * Description: Calculates the area of the union of $n$ polygons (not necessarily
 * convex). The points within each polygon must be given in CCW order.
 * (Epsilon checks may optionally be added to sideOf/sgn, but shouldn't be needed.)
 * Time: $O(N^2)$, where $N$ is the total number of points
 * Status: stress-tested, Submitted on ECNA 2017 Problem A
 */
#pragma once

#include "Point.h"
#include "sideOf.h"

typedef Point<double> P;
double rat(P a, P b) {
    return sgn(b.x) ? a.x / b.x : a.y / b.y;
}
double polyUnion(vector<vector<P>> &poly) {
    double ret = 0;
    for (int i = 0; i < (sz(poly)); ++i)
        for (int v = 0; v < (sz(poly[i])); ++v) {
            P A = poly[i][v],
              B = poly[i][(v + 1) % sz(poly[i])];
            vector<pair<double, int>> segs = {{0, 0}, {1, 0}};
            for (int j = 0; j < (sz(poly)); ++j)
                if (i != j) {
                    for (int u = 0; u < (sz(poly[j])); ++u) {
                        P C = poly[j][u],
                          D = poly[j][(u + 1) % sz(poly[j])];
                        int sc = sideOf(A, B, C),
                            sd = sideOf(A, B, D);
                        if (sc != sd) {
                            double sa = C.cross(D, A),
                                   sb = C.cross(D, B);
                            if (min(sc, sd) < 0)
                                segs.eb(sa /
                                                      (sa - sb),
                                                  sgn(sc - sd));
                        } else if (!sc && !sd && j < i &&
                                   sgn((B - A).dot(D - C)) >
                                       0) {
                            segs.eb(rat(C - A, B - A),
                                              1);
                            segs.eb(rat(D - A, B - A),
                                              -1);
                        }
                    }
                }
            sort(all(segs));
            for (auto &s : segs)
                s.first = min(max(s.first, 0.0), 1.0);
            double sum = 0;
            int cnt = segs[0].second;
            for (int j = 1; j < (sz(segs)); ++j) {
                if (!cnt)
                    sum += segs[j].first - segs[j - 1].first;
                cnt += segs[j].second;
            }
            ret += A.cross(B) * sum;
        }
    return ret / 2;
}
