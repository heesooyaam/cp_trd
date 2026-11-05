/**
 * Author: Andrew-A-13, adapted to heesooyaam's style
 * Source: Templates/Строковые алгоритмы/Суффиксный массив
 * Description: Suffix array by cyclic shifts + counting sort.
 *  Supports all byte values, including zero; input is unchanged.
 *  lcp[i] = LCP(sa[i],sa[i+1]); empty input gives empty arrays.
 * Time: Build O(n \log n), LCP O(n), memory O(n).
 * Status: Stress-tested against sorted suffixes and naive LCP.
 */
#pragma once
vector<int> suffix_array(string_view s) {
    int n = int(s.size()) + 1;
    vector<int> a(n), p(n), c(n), pn(n), cn(n);
    vector<int> cnt(max(n, 257));
    for (int i = 0; i < n - 1; ++i) {
        a[i] = (unsigned char)s[i] + 1;
    }
    for (int x : a) ++cnt[x];
    partial_sum(cnt.begin(), cnt.end(), cnt.begin());
    for (int i = n - 1; i >= 0; --i) p[--cnt[a[i]]] = i;
    for (int i = 1; i < n; ++i) {
        c[p[i]] = c[p[i - 1]] + (a[p[i]] != a[p[i - 1]]);
    }
    for (int len = 1; len < n; len *= 2) {
        for (int i = 0; i < n; ++i) {
            pn[i] = (p[i] - len + n) % n;
        }
        cnt.assign(n, 0);
        for (int x : c) ++cnt[x];
        partial_sum(cnt.begin(), cnt.end(), cnt.begin());
        for (int i = n - 1; i >= 0; --i) {
            p[--cnt[c[pn[i]]]] = pn[i];
        }
        cn[p[0]] = 0;
        for (int i = 1; i < n; ++i) {
            pair<int, int> cur{c[p[i]], c[(p[i] + len) % n]};
            pair<int, int> prev{c[p[i - 1]],
                                c[(p[i - 1] + len) % n]};
            cn[p[i]] = cn[p[i - 1]] + (cur != prev);
        }
        c.swap(cn);
    }
    p.erase(p.begin());
    return p;
}
vector<int> suffix_lcp(string_view s, const vector<int> &sa) {
    int n = int(s.size()), k = 0;
    vector<int> pos(n), lcp(max(0, n - 1));
    for (int i = 0; i < n; ++i) pos[sa[i]] = i;
    for (int i = 0; i < n; ++i) {
        if (pos[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = sa[pos[i] + 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k])
            ++k;
        lcp[pos[i]] = k;
        if (k) --k;
    }
    return lcp;
}
