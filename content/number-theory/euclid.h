/**
 * Author: Unknown
 * Date: 2002-09-15
 * Source: predates tinyKACTL
 * Description: Расширенный Евклид: $ax+by=\gcd(a,b)$. Для одного НОД использовать std::gcd. При взаимно простых a,b число x — обратное к a по модулю b.
 */
#pragma once

ll euclid(ll a, ll b, ll &x, ll &y) {
    if (!b)
        return x = 1, y = 0, a;
    ll d = euclid(b, a % b, y, x);
    return y -= a / b * x, d;
}
