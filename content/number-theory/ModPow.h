/**
 * Author: Noam527
 * Date: 2019-04-24
 * License: CC0
 * Source: folklore
 * Description: Бинарное возведение в степень, e>=0. Основание заранее привести к [0,mod); b*b должно помещаться в ll. Для обратного через степень mod-2 модуль простой, основание ненулевое.

 * Time: O(\\log e)
 * Status: tested
 */
#pragma once

const ll mod = 1000000007; // быстрее с const

ll modpow(ll b, ll e) {
    ll ans = 1;
    for (; e; b = b * b % mod, e /= 2)
        if (e & 1)
            ans = ans * b % mod;
    return ans;
}
