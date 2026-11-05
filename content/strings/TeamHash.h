/**
 * Author: heesooyaam, adapted for cp_trd (C++20)
 * Source: AlgoTemplates/Strings/hash.cpp
 * Description: Два полиномиальных хеша, при необходимости в обе стороны. Запросы по [l,r] с индексацией от 1, даже при cur\_ind=false (вход от 0). Пустой отрезок [l,l-1]. rev — схема Горнера, dir — возрастающие степени. Сравнение объектов требует одинаковых параметров шаблона; длины тоже сравниваются. Возможны коллизии; на враждебных тестах выбирать случайные основания. Элементы сравниваются по остаткам.

 * Usage: string_hasher h(s, true, false); h.is_palindrome(1,n);
 * Time: Построение O(n), запросы O(1), память O(n).
 * Status: Random substrings, palindromes, signed arrays, empty input.
 */
#pragma once
template <class container_t, array mod, array base>
struct hasher {
    static constexpr int pts = int(mod.size());
    static_assert(mod.size() == base.size());
    using hash_t = array<ll, mod.size()>;
    inline static vector<hash_t> powers = [] {
        hash_t one;
        one.fill(1);
        return vector<hash_t>{one};
    }();
    struct hash_value {
        int length, shift;
        hash_t h{};
        bool operator==(const hash_value &other) const {
            if (length != other.length)
                return false;
            int delta = abs(shift - other.shift);
            const auto &a = shift < other.shift ? h : other.h;
            const auto &b = shift < other.shift ? other.h : h;
            for (int j = 0; j < pts; ++j) {
                if (a[j] * powers[delta][j] % mod[j] != b[j])
                    return false;
            }
            return true;
        }
    };
    int n;
    vector<hash_t> rev, dir;
    hasher(const container_t &data, bool both = false,
           bool cur_ind = true)
        : n(int(data.size()) - int(cur_ind)),
          rev(max(0, n) + 1), dir(both ? max(0, n) + 1 : 0) {
        assert(n >= 0);
        while (int(powers.size()) <= n) {
            auto next = powers.back();
            for (int j = 0; j < pts; ++j)
                next[j] = next[j] * base[j] % mod[j];
            powers.eb(next);
        }
        for (int i = 1; i <= n; ++i) {
            ll value = data[i - !cur_ind];
            if constexpr (is_same_v<
                              typename container_t::value_type,
                              char>) {
                value = (unsigned char)value;
            }
            for (int j = 0; j < pts; ++j) {
                ll x = (value % mod[j] + mod[j]) % mod[j];
                rev[i][j] =
                    (rev[i - 1][j] * base[j] + x) % mod[j];
                if (both)
                    dir[i][j] =
                        (dir[i - 1][j] + x * powers[i - 1][j]) %
                        mod[j];
            }
        }
    }
    hash_value get_rev_hash(int l, int r) const {
        hash_value h{r - l + 1, 0, {}};
        for (int j = 0; j < pts; ++j)
            h.h[j] =
                (rev[r][j] -
                 rev[l - 1][j] * powers[r - l + 1][j] % mod[j] +
                 mod[j]) %
                mod[j];
        return h;
    }
    hash_value get_dir_hash(int l, int r) const {
        assert(!dir.empty());
        hash_value h{r - l + 1, l - 1, {}};
        for (int j = 0; j < pts; ++j)
            h.h[j] =
                (dir[r][j] - dir[l - 1][j] + mod[j]) % mod[j];
        return h;
    }
    bool is_palindrome(int l, int r) const {
        return get_dir_hash(l, r) == get_rev_hash(l, r);
    }
};
using string_hasher =
    hasher<string, array{1000000007, 1000000023},
           array{237, 192}>;
template <class T>
using arr_hasher =
    hasher<vector<T>, array{1000000007, 1000000023},
           array{200005, 300023}>;
