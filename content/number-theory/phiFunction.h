/**
 * Author: Håkan Terelius
 * Date: 2009-09-25
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Euler's_totient_function
 * Description: Функция Эйлера: число положительных чисел до n, взаимно простых с n. $\phi(1)=1$, $\phi(p^k)=(p-1)p^{k-1}$ для простого p. Мультипликативна: $\phi(mn)=\phi(m)\phi(n)$ при gcd(m,n)=1. $\phi(n)=n\prod_{p\mid n}(1-1/p)$; $\sum_{d\mid n}\phi(d)=n$. При n>1 сумма взаимно простых с n чисел от 1 до n равна $n\phi(n)/2$. Теорема Эйлера: $a^{\phi(n)}\equiv1\pmod n$ при gcd(a,n)=1. Малая теорема Ферма: $a^{p-1}\equiv1\pmod p$, если p простое и p не делит a.

 * Status: Tested
 */
#pragma once

const int LIM = 5000000;
int phi[LIM];

void calculatePhi() {
    for (int i = 0; i < (LIM); ++i)
        phi[i] = i & 1 ? i : i / 2;
    for (int i = 3; i < LIM; i += 2)
        if (phi[i] == i)
            for (int j = i; j < LIM; j += i)
                phi[j] -= phi[j] / i;
}
