/**
 * Author: Simon Lindholm, chilli
 * Date: 2018-07-23
 * License: CC0
 * Source: http://codeforces.com/blog/entry/60737
 * Description: Хеш-таблица с интерфейсом, близким к unordered\_map. Часто быстрее, расход памяти выше. Начальная ёмкость, если задана, должна быть степенью двойки.
 */
#pragma once

#include <bits/extc++.h> /** keep-include */
// Использовать разные биты хеша, а не только младшие:
struct chash { // C — большое нечётное число
    const uint64_t C = ll(4e18 * acos(0)) | 71;
    ll operator()(ll x) const {
        return __builtin_bswap64(x * C);
    }
};
__gnu_pbds::gp_hash_table<ll, int, chash> h({}, {}, {}, {},
                                            {1 << 16});

/** For CodeForces, or other places where hacking might be a problem:

const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash { // Использовать разные биты хеша, а не только младшие:
	const uint64_t C = ll(4e18 * acos(0)) | 71; // large odd number
	ll operator()(ll x) const { return __builtin_bswap64((x^RANDOM)*C); }
};
__gnu_pbds::gp_hash_table<ll, int, chash> h({},{},{},{}, {1 << 16});
*/
