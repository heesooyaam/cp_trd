/**
 * Author: Simon Lindholm
 * License: CC0
 * Source: http://codeforces.com/blog/entry/8219
 * Description: Для ДП $a_{i,j}=\min_{i<k<j}(a_{i,k}+a_{k,j})+f(i,j)$ оптимальный минимальный k ищется между p[i][j-1] и p[i+1][j], если он монотонен по обеим границам. Достаточно $f(b,c)\le f(a,d)$ и $f(a,c)+f(b,d)\le f(a,d)+f(b,c)$ при $a\le b\le c\le d$. Перебирать отрезки по длине.

 * Time: O(N^2)
 */
