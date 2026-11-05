/**
 * Author: Stanford
 * Source: Stanford Notebook
 * License: MIT
 * Description: Максимизирует $c^Tx$ при $Ax\le b$, $x\ge0$. Возвращает -inf, если решений нет; inf, если максимум не ограничен; иначе оптимум. В x записывается решение (при неограниченности — допустимое). Численная устойчивость не гарантируется. Лучше выбирать переменные так, чтобы x=0 было допустимо.

 * Usage:
 * vvd A = {{1,-1}, {-1,1}, {-1,-2}};
 * vd b = {1,1,-4}, c = {-1,-1}, x;
 * T val = LPSolver(A, b, c).solve(x);
 * Time: O(NM) на поворот; в общем случае экспоненциальное число поворотов.
 * Status: seems to work?
 */
#pragma once

typedef double T; // long double, Rational, double + mod<P>...
typedef vector<T> vd;
typedef vector<vd> vvd;

const T eps = 1e-8, inf = 1 / .0;
#define MP make_pair
#define ltj(X)                                                 \
    if (s == -1 || MP(X[j], N[j]) < MP(X[s], N[s]))            \
    s = j

struct LPSolver {
    int m, n;
    vi N, B;
    vvd D;

    LPSolver(const vvd &A, const vd &b, const vd &c)
        : m(sz(b)), n(sz(c)), N(n + 1), B(m),
          D(m + 2, vd(n + 2)) {
        for (int i = 0; i < (m); ++i)
            for (int j = 0; j < (n); ++j)
                D[i][j] = A[i][j];
        for (int i = 0; i < (m); ++i) {
            B[i] = n + i;
            D[i][n] = -1;
            D[i][n + 1] = b[i];
        }
        for (int j = 0; j < (n); ++j) {
            N[j] = j;
            D[m][j] = -c[j];
        }
        N[n] = -1;
        D[m + 1][n] = 1;
    }

    void pivot(int r, int s) {
        T *a = D[r].data(), inv = 1 / a[s];
        for (int i = 0; i < (m + 2); ++i)
            if (i != r && abs(D[i][s]) > eps) {
                T *b = D[i].data(), inv2 = b[s] * inv;
                for (int j = 0; j < (n + 2); ++j)
                    b[j] -= a[j] * inv2;
                b[s] = a[s] * inv2;
            }
        for (int j = 0; j < (n + 2); ++j)
            if (j != s)
                D[r][j] *= inv;
        for (int i = 0; i < (m + 2); ++i)
            if (i != r)
                D[i][s] *= -inv;
        D[r][s] = inv;
        swap(B[r], N[s]);
    }

    bool simplex(int phase) {
        int x = m + phase - 1;
        for (;;) {
            int s = -1;
            for (int j = 0; j < (n + 1); ++j)
                if (N[j] != -phase)
                    ltj(D[x]);
            if (D[x][s] >= -eps)
                return true;
            int r = -1;
            for (int i = 0; i < (m); ++i) {
                if (D[i][s] <= eps)
                    continue;
                if (r == -1 ||
                    MP(D[i][n + 1] / D[i][s], B[i]) <
                        MP(D[r][n + 1] / D[r][s], B[r]))
                    r = i;
            }
            if (r == -1)
                return false;
            pivot(r, s);
        }
    }

    T solve(vd &x) {
        int r = 0;
        for (int i = 1; i < (m); ++i)
            if (D[i][n + 1] < D[r][n + 1])
                r = i;
        if (D[r][n + 1] < -eps) {
            pivot(r, n);
            if (!simplex(2) || D[m + 1][n + 1] < -eps)
                return -inf;
            for (int i = 0; i < (m); ++i)
                if (B[i] == -1) {
                    int s = 0;
                    for (int j = 1; j < (n + 1); ++j)
                        ltj(D[i]);
                    pivot(i, s);
                }
        }
        bool ok = simplex(1);
        x = vd(n);
        for (int i = 0; i < (m); ++i)
            if (B[i] < n)
                x[B[i]] = D[i][n + 1];
        return ok ? D[m][n + 1] : inf;
    }
};
