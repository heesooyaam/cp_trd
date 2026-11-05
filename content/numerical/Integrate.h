/**
 * Author: Simon Lindholm
 * Date: 2015-02-11
 * License: CC0
 * Source: Wikipedia
 * Description: Интегрирование по формуле Симпсона. Ошибка порядка $h^4$; проверить устойчивость ответа при уменьшении шага.

 * Status: mostly untested
 */
#pragma once

template <class F>
double quad(double a, double b, F f, const int n = 1000) {
    double h = (b - a) / 2 / n, v = f(a) + f(b);
    for (int i = 1; i < (n * 2); ++i)
        v += f(a + i * h) * (i & 1 ? 4 : 2);
    return v * h / 3;
}
