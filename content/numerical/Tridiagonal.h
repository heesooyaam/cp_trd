/**
 * Author: Ulf Lundstrom, Simon Lindholm
 * Date: 2009-08-15
 * License: CC0
 * Source: https://en.wikipedia.org/wiki/Tridiagonal_matrix_algorithm
 * Description: Решает трёхдиагональную систему Ax=b: d — главная диагональ, p — над ней, q — под ней (длины n, n-1, n-1). Решение должно быть единственным. Для строгого диагонального преобладания или положительной определённости алгоритм устойчив; тогда перестановки tr и проверку нулевой диагонали можно убрать.

 * Time: O(N)
 * Status: Brute-force tested mod 5 and 7 and stress-tested for real matrices obeying the criteria above.
 */
#pragma once

typedef double T;
vector<T> tridiagonal(vector<T> diag, const vector<T> &super,
                      const vector<T> &sub, vector<T> b) {
    int n = sz(b);
    vi tr(n);
    for (int i = 0; i < (n - 1); ++i) {
        if (abs(diag[i]) <
            1e-9 * abs(super[i])) { // diag[i] == 0
            b[i + 1] -= b[i] * diag[i + 1] / super[i];
            if (i + 2 < n)
                b[i + 2] -= b[i] * sub[i + 1] / super[i];
            diag[i + 1] = sub[i];
            tr[++i] = 1;
        } else {
            diag[i + 1] -= super[i] * sub[i] / diag[i];
            b[i + 1] -= b[i] * sub[i] / diag[i];
        }
    }
    for (int i = n; i--;) {
        if (tr[i]) {
            swap(b[i], b[i - 1]);
            diag[i - 1] = diag[i];
            b[i] /= super[i - 1];
        } else {
            b[i] /= diag[i];
            if (i)
                b[i - 1] -= b[i] * super[i - 1];
        }
    }
    return b;
}
