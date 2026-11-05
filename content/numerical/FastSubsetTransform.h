/**
 * Author: Lucian Bicsi
 * Date: 2015-06-25
 * License: GNU Free Documentation License 1.2
 * Source: csacademy
 * Description: Преобразование для свёрток $c_z=\sum_{z=x\oplus y}a_xb_y$, где $\oplus$ — AND, OR или XOR. Размер массива — степень двойки.

 * Time: O(N \log N)
 * Status: stress-tested
 */
#pragma once

void FST(vi &a, bool inv) {
    for (int n = sz(a), step = 1; step < n; step *= 2) {
        for (int i = 0; i < n; i += 2 * step)
            for (int j = i; j < (i + step); ++j) {
                int &u = a[j], &v = a[j + step];
                tie(u, v) =
                    inv ? pii(v - u, u) : pii(v, u + v); // AND
                // inv ? pii(v, u - v) : pii(u + v, u); // OR /// include-line
                // pii(u + v, u - v);                   // XOR /// include-line
            }
    }
    // if (inv) // только XOR /// include-line
    //     for (int &x : a) /// include-line
    //         x /= sz(a); /// include-line
}
vi conv(vi a, vi b) {
    FST(a, 0);
    FST(b, 0);
    for (int i = 0; i < (sz(a)); ++i)
        a[i] *= b[i];
    FST(a, 1);
    return a;
}
