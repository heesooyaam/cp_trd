/**
 * Author: Andrew-A-13, generalized for cp_trd
 * Source: Templates/Garbage/Отжиг
 * Description: Minimize cost over permutations using random swaps.
 *  Returns the best visited state, not the last state.
 *  Tune temperatures to cost differences, try independent restarts.
 *  cost must be finite; there is no guarantee of the optimum.
 * Time: O(steps * (cost evaluation + occasional state copy)).
 * Status: Permutation and best-state invariants tested.
 */
#pragma once
template <class Cost>
pair<double, vector<int>>
anneal(vector<int> p, Cost cost, int steps, double start_temp,
       double end_temp, mt19937 &rng) {
    assert(steps >= 0 && start_temp > 0 && end_temp > 0);
    double cur = cost(p), best_cost = cur;
    vector<int> best = p;
    int n = int(p.size());
    if (n < 2) return {best_cost, best};
    uniform_int_distribution<int> index(0, n - 1);
    uniform_real_distribution<double> real(0, 1);
    for (int step = 0; step < steps; ++step) {
        double t = double(step) / max(1, steps - 1);
        double temp =
            exp(log(start_temp) * (1 - t) + log(end_temp) * t);
        int i = index(rng), j = index(rng);
        swap(p[i], p[j]);
        double next = cost(p);
        if (next <= cur ||
            real(rng) < exp((cur - next) / temp))
            cur = next;
        else
            swap(p[i], p[j]);
        if (cur < best_cost) best_cost = cur, best = p;
    }
    return {best_cost, best};
}
