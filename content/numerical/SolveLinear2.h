/**
 * Author: Simon Lindholm
 * Date: 2016-09-06
 * License: CC0
 * Source: me
 * Description: Изменения в SolveLinear для получения всех однозначно определённых координат решения x.

 * Status: tested on kattis:equationsolverplus, stress-tested
 */
#pragma once

#include "SolveLinear.h"

for (int j = 0; j < (n); ++j)
    if (j != i) // вместо for (int j = i+1; j < (n); ++j)
        // ... затем в конце:
        x.assign(m, undefined);
for (int i = 0; i < (rank); ++i) {
    for (int j = rank; j < (m); ++j)
        if (fabs(A[i][j]) > eps)
            goto fail;
    x[col[i]] = b[i] / A[i][i];
fail:;
}
