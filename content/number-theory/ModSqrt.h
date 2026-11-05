/**
 * Author: Simon Lindholm
 * Date: 2016-08-31
 * License: CC0
 * Source: http://eli.thegreenplace.net/2009/03/07/computing-modular-square-roots-in-python/
 * Description: Тонелли — Шенкс: корень $x^2\equiv a\pmod p$ для простого p; второй корень -x по модулю p.

 * Time: O(\log^2 p) в худшем случае, O(\log p) для most $p$
 * Status: Tested for all a,p <= 10000
 */
#pragma once

#include "ModPow.h"

ll sqrt(ll a, ll p) {
    a %= p;
    if (a < 0)
        a += p;
    if (a == 0)
        return 0;
    assert(modpow(a, (p - 1) / 2, p) == 1); // иначе решения нет
    if (p % 4 == 3)
        return modpow(a, (p + 1) / 4, p);
    // a^(n+3)/8 or 2^(n+3)/8 * 2^(n-1)/4 работает при p % 8 == 5
    ll s = p - 1, n = 2;
    int r = 0, m;
    while (s % 2 == 0)
        ++r, s /= 2;
    /// find a non-square mod p
    while (modpow(n, (p - 1) / 2, p) != p - 1)
        ++n;
    ll x = modpow(a, (s + 1) / 2, p);
    ll b = modpow(a, s, p), g = modpow(n, s, p);
    for (;; r = m) {
        ll t = b;
        for (m = 0; m < r && t != 1; ++m)
            t = t * t % p;
        if (m == 0)
            return x;
        ll gs = modpow(g, 1LL << (r - m - 1), p);
        g = gs * gs % p;
        x = x * gs % p;
        b = b * g % p;
    }
}
