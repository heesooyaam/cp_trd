/**
 * Author: Noam527
 * Date: 2019-04-24
 * License: CC0
 * Source: folklore
 * Description: Binary exponentiation (binpow), e >= 0.
 *  Normalize b into [0,mod) before calling. b*b must fit ll.
 *  For inverse via exponent mod-2, mod must be prime and b nonzero.
 * Time: O(\\log e)
 * Status: tested
 */
#pragma once

const ll mod = 1000000007; // faster if const

ll modpow(ll b, ll e) {
    ll ans = 1;
    for (; e; b = b * b % mod, e /= 2)
        if (e & 1) ans = ans * b % mod;
    return ans;
}
