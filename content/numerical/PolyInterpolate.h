/**
 * Author: Simon Lindholm
 * Date: 2017-05-10
 * License: CC0
 * Source: Wikipedia
 * Description: По n точкам (x[i],y[i]) строит полином степени не выше n-1: $p(x)=\sum a_i x^i$. Для устойчивости выбирать узлы Чебышёва $x_k=c\cos(k\pi/(n-1))$.

 * Time: O(n^2)
 */
#pragma once

typedef vector<double> vd;
vd interpolate(vd x, vd y, int n) {
    vd res(n), temp(n);
    for (int k = 0; k < (n - 1); ++k)
        for (int i = k + 1; i < (n); ++i)
            y[i] = (y[i] - y[k]) / (x[i] - x[k]);
    double last = 0;
    temp[0] = 1;
    for (int k = 0; k < (n); ++k)
        for (int i = 0; i < (n); ++i) {
            res[i] += y[k] * temp[i];
            swap(last, temp[i]);
            temp[i] -= last * x[k];
        }
    return res;
}
