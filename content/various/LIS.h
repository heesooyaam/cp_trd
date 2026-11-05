/**
 * Author: Johan Sannemo
 * License: CC0
 * Description: Compute indices for the longest increasing subsequence.
 * Time: $O(N \log N)$
 * Status: Tested on kattis:longincsubseq, stress-tested
 */
#pragma once

template <class I> vector<int> lis(const vector<I> &S) {
    if (S.empty())
        return {};
    vector<int> prev(sz(S));
    typedef pair<I, int> p;
    vector<p> res;
    for (int i = 0; i < (sz(S)); ++i) {
        // change 0 -> i for longest non-decreasing subsequence
        auto it = lower_bound(all(res), p{S[i], 0});
        if (it == res.end())
            res.eb(), it = res.end() - 1;
        *it = {S[i], i};
        prev[i] = it == res.begin() ? 0 : (it - 1)->second;
    }
    int L = sz(res), cur = res.back().second;
    vector<int> ans(L);
    while (L--)
        ans[L] = cur, cur = prev[cur];
    return ans;
}
