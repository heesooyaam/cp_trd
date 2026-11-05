/**
 * Author: cp_trd
 * Description: Целые решения ax+by=c: произвольные знаки, нулевые коэффициенты, ограничения и минимум px+qy. Все входные числа по модулю не больше $10^{18}$; промежуточные вычисления и ответы — i128. nullopt в границе означает отсутствие ограничения. count() возвращает nullopt для бесконечного числа решений. minimum(p,q): status=-1 нет решений, 0 минимум не ограничен снизу, 1 найден (x,y). Для максимума вызвать minimum(-p,-q). Ограничения накапливаются; копия объекта позволяет проверить другую область.
 * Time: O(\log(\max(|a|,|b|))) построение, O(1) остальные операции.
 * Status: Exhaustive small coefficients, boxes, objectives; signs, zero and large values.
 */
#pragma once
using i128 = __int128_t;

// В C++ / округляет к нулю. Здесь b!=0, округление вниз/вверх.
i128 floor_div(i128 a, i128 b) {
    i128 q = a / b, r = a % b;
    return q - (r != 0 && ((r < 0) != (b < 0)));
}
i128 ceil_div(i128 a, i128 b) {
    return -floor_div(-a, b);
}
struct integer_interval {
    optional<i128> lo, hi;
    bool empty() const { return lo && hi && *lo > *hi; }
    void lower(i128 x) {
        if (!lo || x > *lo) {
            lo = x;
        }
    }
    void upper(i128 x) {
        if (!hi || x < *hi) {
            hi = x;
        }
    }
    optional<i128> count() const {
        if (empty()) {
            return 0;
        }
        if (!lo || !hi) {
            return nullopt;
        }
        return *hi - *lo + 1;
    }
    // argmin(k*t), вызывать только для непустого интервала.
    // nullopt: функция убывает к минус бесконечности.
    optional<i128> argmin(i128 k) const {
        if (k > 0) {
            return lo;
        }
        if (k < 0) {
            return hi;
        }
        i128 t = 0;
        if (lo) {
            t = max(t, *lo);
        }
        if (hi) {
            t = min(t, *hi);
        }
        return t;
    }
};
struct diophantine {
    // Для линии: (x,y)=(x0,y0)+t*(dx,dy), t целое.
    i128 x0 = 0, y0 = 0, dx = 0, dy = 0;
    bool valid = true, plane = false;
    integer_interval t, xs, ys;
    diophantine(ll a, ll b, ll c) {
        i128 A = a, B = b;
        if (a == 0 && b == 0) {
            valid = c == 0;
            plane = true; // при c=0 любые x,y
            return;
        }
        i128 u = 1, v = 0, s = 0, w = 1;
        i128 g = A < 0 ? -A : A, h = B < 0 ? -B : B;
        while (h != 0) {
            i128 q = g / h;
            tie(g, h) = pair{i128(h), g - q * h};
            tie(u, s) = pair{i128(s), u - q * s};
            tie(v, w) = pair{i128(w), v - q * w};
        }
        valid = c % g == 0;
        x0 = u * (c / g) * (a < 0 ? -1 : 1);
        y0 = v * (c / g) * (b < 0 ? -1 : 1);
        dx = B / g;
        dy = -A / g;
    }
    // Пересечь l <= z+d*t <= r с допустимыми t.
    void restrict_coord(i128 z, i128 d, optional<i128> l,
                        optional<i128> r) {
        if (d == 0) {
            valid &= (!l || *l <= z) && (!r || z <= *r);
            return;
        }
        if (l) {
            if (d > 0) {
                t.lower(ceil_div(*l - z, d));
            } else {
                t.upper(floor_div(*l - z, d));
            }
        }
        if (r) {
            if (d > 0) {
                t.upper(floor_div(*r - z, d));
            } else {
                t.lower(ceil_div(*r - z, d));
            }
        }
    }
    void bounds(optional<i128> lx, optional<i128> rx,
                optional<i128> ly, optional<i128> ry) {
        if (lx) {
            xs.lower(*lx);
        }
        if (rx) {
            xs.upper(*rx);
        }
        if (ly) {
            ys.lower(*ly);
        }
        if (ry) {
            ys.upper(*ry);
        }
        if (!plane) {
            restrict_coord(x0, dx, lx, rx);
            restrict_coord(y0, dy, ly, ry);
        }
    }
    optional<i128> count() const {
        if (!valid || xs.empty() || ys.empty() || t.empty()) {
            return 0;
        }
        if (!plane) {
            return t.count();
        }
        auto x = xs.count(), y = ys.count();
        if (!x || !y) {
            return nullopt;
        }
        return *x * *y;
    }
    struct result {
        int status;
        i128 x = 0, y = 0;
    };
    result minimum(i128 p, i128 q) const {
        if (count() == optional<i128>(0)) {
            return {-1};
        }
        if (plane) {
            auto x = xs.argmin(p), y = ys.argmin(q);
            if (!x || !y) {
                return {0};
            }
            return {1, *x, *y};
        }
        auto k = t.argmin(p * dx + q * dy);
        if (!k) {
            return {0};
        }
        return {1, x0 + *k * dx, y0 + *k * dy};
    }
};
