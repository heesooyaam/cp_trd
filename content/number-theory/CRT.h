/**
 * Author: Simon Lindholm
 * Date: 2019-05-22
 * License: CC0
 * Description: КТО: crt(a,m,b,n) находит $x\equiv a\pmod m$, $x\equiv b\pmod n$. При |a|<m, |b|<n ответ в [0,lcm(m,n)). Требуется $mn<2^{62}$; совместность проверяется assert.

 * Time: $\log(n)$
 * Status: Works
 */
#pragma once

#include "euclid.h"

ll crt(ll a, ll m, ll b, ll n) {
    if (n > m)
        swap(a, b), swap(m, n);
    ll x, y, g = euclid(m, n, x, y);
    assert((a - b) % g == 0); // иначе решения нет
    x = (b - a) % n * x % n / g * m + a;
    return x < 0 ? x + m * n / g : x;
}
