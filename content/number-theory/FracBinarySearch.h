/**
 * Author: Lucian Bicsi, Simon Lindholm
 * Date: 2017-10-31
 * License: CC0
 * Description: Минимальная дробь p/q в [0,1] с p,q<=N, удовлетворяющая монотонному предикату f. Если f обнаруживает точное решение, можно завершить поиск исключением и отказаться от ограничения N.

 * Usage: fracBS([](Frac f) { return f.p>=3*f.q; }, 10); // {1,3}
 * Time: O(\log(N))
 * Status: stress-tested for n <= 300
 */

struct Frac {
    ll p, q;
};

template <class F> Frac fracBS(F f, ll N) {
    bool dir = 1, A = 1, B = 1;
    Frac lo{0, 1}, hi{1, 1}; // Для поиска на (0,N] задать hi=1/0
    if (f(lo))
        return lo;
    assert(f(hi));
    while (A || B) {
        ll adv = 0, step = 1; // двигать hi при dir, иначе lo
        for (int si = 0; step; (step *= 2) >>= si) {
            adv += step;
            Frac mid{lo.p * adv + hi.p, lo.q * adv + hi.q};
            if (abs(mid.p) > N || mid.q > N || dir == !f(mid)) {
                adv -= step;
                si = 2;
            }
        }
        hi.p += lo.p * adv;
        hi.q += lo.q * adv;
        dir = !dir;
        swap(lo, hi);
        A = B;
        B = !!adv;
    }
    return dir ? hi : lo;
}
