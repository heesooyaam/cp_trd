/**
 * Author: heesooyaam, adapted for cp_trd
 * Description: Binary gcd of unsigned 64-bit integers, including zero.
 *  lcm requires the result to fit in uint64\_t.
 * Source: AlgoTemplates/Math/FastGcdLcm.cpp (see doc/team-sources.md)
 * Time: O(\log(\max(a,b)))
 * Status: Tested against std::gcd and 128-bit lcm.
 */
#pragma once
uint64_t binary_gcd(uint64_t a, uint64_t b) {
    if (!a || !b) return a | b;
    int s = __builtin_ctzll(a | b);
    a >>= __builtin_ctzll(a);
    do {
        b >>= __builtin_ctzll(b);
        if (a > b) swap(a, b);
        b -= a;
    } while (b);
    return a << s;
}
uint64_t binary_lcm(uint64_t a, uint64_t b) {
    return a && b ? a / binary_gcd(a, b) * b : 0;
}
