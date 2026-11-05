/**
 * Author: Johan Sannemo
 * Date: 2016-12-15
 * License: CC0
 * Description: Префикс-функция: pi[i] — длина наибольшего собственного префикса s[0..i], совпадающего с суффиксом. Для abacaba: 0010123. Поиск всех вхождений образца в строку.

 * Time: O(n)
 * Status: Tested on kattis:stringmatching
 */
#pragma once

vector<int> pi(const string &s) {
    vector<int> p(sz(s));
    for (int i = 1; i < (sz(s)); ++i) {
        int g = p[i - 1];
        while (g && s[i] != s[g])
            g = p[g - 1];
        p[i] = g + (s[i] == s[g]);
    }
    return p;
}

vector<int> match(const string &s, const string &pat) {
    vector<int> p = pi(pat + '\0' + s), res;
    for (int i = sz(p) - sz(s); i < (sz(p)); ++i)
        if (p[i] == sz(pat))
            res.eb(i - 2 * sz(pat));
    return res;
}
