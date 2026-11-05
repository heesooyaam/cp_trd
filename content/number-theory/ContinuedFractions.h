/**
 * Author: Simon Lindholm
 * Date: 2018-07-15
 * License: CC0
 * Source: Wikipedia
 * Description: Для x>=0 ищет ближайшее приближение p/q с p,q<=N. Соседние подходящие дроби удовлетворяют $p_{k+1}q_k-q_{k+1}p_k=(-1)^k$ и лежат по разные стороны x. Для рационального x переменная y достигает бесконечности; для квадратичной иррациональности коэффициенты периодичны с некоторого места.

 * Time: O(\log N)
 * Status: stress-tested for n <= 300
 */

typedef double d; // для N ~ 1e7; long double для N ~ 1e9
pair<ll, ll> approximate(d x, ll N) {
    ll LP = 0, LQ = 1, P = 1, Q = 0, inf = LLONG_MAX;
    d y = x;
    for (;;) {
        ll lim = min(P ? (N - LP) / P : inf,
                     Q ? (N - LQ) / Q : inf),
           a = (ll)floor(y), b = min(a, lim), NP = b * P + LP,
           NQ = b * Q + LQ;
        if (a > b) {
            // При b > a/2 промежуточная дробь даёт лучшее
            // приближение; при b = a/2 это возможно, но не обязательно.
            // Для обычной подходящей дроби вернуть здесь {P,Q}.
            return (abs(x - (d)NP / (d)NQ) <
                    abs(x - (d)P / (d)Q))
                       ? make_pair(NP, NQ)
                       : make_pair(P, Q);
        }
        if (abs(y = 1 / (y - (d)a)) > 3 * N) {
            return {NP, NQ};
        }
        LP = P;
        P = NP;
        LQ = Q;
        Q = NQ;
    }
}
