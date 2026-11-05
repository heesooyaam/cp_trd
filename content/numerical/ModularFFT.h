/**
 * Author: Andrew-A-13, adapted for cp_trd
 * Source: Templates/FFT/modular (doc/team-sources.md)
 * Description: NTT modulo 998244353; w=31 has order $2^{23}$.
 *  fft uses a nonempty power-of-two length <= $2^{23}$ and
 *  coefficients in [0,mod). multiply accepts signed int
 *  coefficients, returns exactly a.size()+b.size()-1 terms;
 *  an empty input gives {}. No floating-point rounding.
 * Time: O(N \log N), memory O(N).
 * Status: Stress-tested against quadratic convolution.
 */
#pragma once
struct modular_fft {
    static constexpr int mod = 998244353, max_log = 23;
    static int power(int a, int e) {
        int r = 1;
        for (; e; e >>= 1, a = int(ll(a) * a % mod))
            if (e & 1) r = int(ll(r) * a % mod);
        return r;
    }
    static void fft(vector<int> &a, bool inverse = false) {
        int n = int(a.size());
        assert(n && !(n & (n - 1)) && n <= (1 << max_log));
        for (int i = 1, j = 0; i < n; ++i) {
            int b = n >> 1;
            for (; j & b; b >>= 1) j ^= b;
            j ^= b;
            if (i < j) swap(a[i], a[j]);
        }
        for (int len = 2; len <= n; len *= 2) {
            int w = power(31, (1 << max_log) / len);
            if (inverse) w = power(w, mod - 2);
            for (int i = 0; i < n; i += len) {
                int z = 1;
                for (int j = 0; j < len / 2; ++j) {
                    int x = a[i + j];
                    int y =
                        int(ll(a[i + j + len / 2]) * z % mod);
                    a[i + j] =
                        x + y < mod ? x + y : x + y - mod;
                    a[i + j + len / 2] =
                        x - y < 0 ? x - y + mod : x - y;
                    z = int(ll(z) * w % mod);
                }
            }
        }
        if (inverse) {
            int inv = power(n, mod - 2);
            for (int &x : a) x = int(ll(x) * inv % mod);
        }
    }
    static vector<int> multiply(vector<int> a, vector<int> b) {
        if (a.empty() || b.empty()) return {};
        int s = int(a.size()) + int(b.size()) - 1, n = 1;
        assert(s <= (1 << max_log));
        while (n < s) n *= 2;
        for (vector<int> *v : {&a, &b}) {
            for (int &x : *v) {
                x %= mod;
                if (x < 0) x += mod;
            }
            v->resize(n);
            fft(*v);
        }
        for (int i = 0; i < n; ++i)
            a[i] = int(ll(a[i]) * b[i] % mod);
        fft(a, true);
        a.resize(s);
        return a;
    }
};
