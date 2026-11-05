/**
 * Author: heesooyaam (source), adapted for cp_trd
 * Source: AlgoTemplates/Math/fast_mint.cpp; Montgomery reduction
 * Description: Быстрый mint Монтгомери: нечётный модуль времени компиляции $1<M<2^{30}$. Деление/inverse требует gcd(value,M)=1. get() возвращает [0,M). Модуль по умолчанию 998244353.

 * Time: O(1) арифметика, O(\log M) обратный.
 * Status: Randomized arithmetic tests, prime and composite moduli.
 */
#pragma once
template <uint32_t M> struct LazyMontgomeryModInt {
    using mint = LazyMontgomeryModInt;
    using u32 = uint32_t;
    using u64 = uint64_t;
    static_assert(M > 1 && M < (1u << 30) && (M & 1));
    static constexpr u32 get_r() {
        u32 x = M;
        for (int i = 0; i < 4; ++i)
            x *= 2 - M * x;
        return x;
    }
    static constexpr u32 r = get_r(), n2 = -u64(M) % M;
    u32 a = 0;
    static constexpr u32 reduce(u64 b) {
        return u32((b + u64(u32(b) * u32(-r)) * M) >> 32);
    }
    constexpr LazyMontgomeryModInt() = default;
    constexpr LazyMontgomeryModInt(ll b)
        : a(reduce(u64(b % M + M) * n2)) {}
    u32 get() const {
        u32 x = reduce(a);
        return x >= M ? x - M : x;
    }
    static constexpr u32 get_mod() { return M; }
    mint &operator+=(mint b) {
        if (int32_t(a += b.a - 2 * M) < 0)
            a += 2 * M;
        return *this;
    }
    mint &operator-=(mint b) {
        if (int32_t(a -= b.a) < 0)
            a += 2 * M;
        return *this;
    }
    mint &operator*=(mint b) {
        a = reduce(u64(a) * b.a);
        return *this;
    }
    mint &operator/=(mint b) { return *this *= b.inverse(); }
    mint operator+(mint b) const { return mint(*this) += b; }
    mint operator-(mint b) const { return mint(*this) -= b; }
    mint operator*(mint b) const { return mint(*this) *= b; }
    mint operator/(mint b) const { return mint(*this) /= b; }
    mint operator-() const { return mint() - *this; }
    bool operator==(mint b) const { return get() == b.get(); }
    bool operator!=(mint b) const { return !(*this == b); }
    mint pow(u64 e) const {
        mint res = 1, b = *this;
        for (; e; e >>= 1, b *= b)
            if (e & 1)
                res *= b;
        return res;
    }
    mint inverse() const {
        ll x = get(), y = M, u = 1, v = 0;
        while (y) {
            ll t = x / y;
            x -= t * y;
            swap(x, y);
            u -= t * v;
            swap(u, v);
        }
        assert(x == 1);
        return u;
    }
    friend ostream &operator<<(ostream &os, mint b) {
        return os << b.get();
    }
    friend istream &operator>>(istream &is, mint &b) {
        ll x;
        is >> x;
        b = mint(x);
        return is;
    }
};
using mint = LazyMontgomeryModInt<998244353>;
