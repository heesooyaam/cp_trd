/**
 * Author: Simon Lindholm
 * Date: 2015-03-18
 * License: CC0
 * Source: https://software.intel.com/sites/landingpage/IntrinsicsGuide/
 * Description: Памятка SSE/AVX: арифметика над несколькими числами сразу. Имена операций: \texttt{\_mm...} для 128 бит, \texttt{\_mm256...} для 256 бит; суффиксы epi8/16/32/64, ps, pd задают тип. Требуется поддержка инструкций процессором. loadu/storeu не требуют выравнивания; для выровненной памяти использовать alignas(32) или \texttt{\_mm\_malloc}.
 */
#pragma once

#pragma GCC target("avx2") // либо sse4.1
#include "immintrin.h"     /** keep-include */

typedef __m256i mi;
#define L(x) _mm256_loadu_si256((mi *)&(x))

// Специальные операции:
// load(u)?_si256, store(u)?_si256, setzero_si256, _mm_malloc
// blendv_(epi8|ps|pd) (z?y:x), movemask_epi8 (старшие биты байтов)
// i32gather_epi32(addr, x, 4): addr[] по 32-битным частям x
// sad_epu8: суммы модулей разностей u8, ответ 4xi64
// maddubs_epi16: суммы произведений беззнаковых i7, ответ 16xi15
// madd_epi16: суммы произведений знаковых i16, ответ 8xi32
// extractf128_si256(, i) (256->128), cvtsi128_si32 (128->lo32)
// permute2f128_si256(x,x,1) меняет 128-битные половины
// shuffle_epi32(x, 3*64+2*16+1*4+0) == x для каждой половины
// shuffle_epi8(x, y) takes a vector вместо an imm

// Операции для разных типов (добавить, например, _epi32):
// set1, blend (i8?x:y), add, adds (sat.), mullo, sub, and/or,
// andnot, abs, min, max, sign(1,x), cmp(gt|eq), unpack(lo|hi)

int sumi32(mi m) {
    union {
        int v[8];
        mi m;
    } u;
    u.m = m;
    int ret = 0;
    for (int i = 0; i < (8); ++i)
        ret += u.v[i];
    return ret;
}
mi zero() {
    return _mm256_setzero_si256();
}
mi one() {
    return _mm256_set1_epi32(-1);
}
bool all_zero(mi m) {
    return _mm256_testz_si256(m, m);
}
bool all_one(mi m) {
    return _mm256_testc_si256(m, one());
}

ll example_filteredDotProduct(int n, short *a, short *b) {
    int i = 0;
    ll r = 0;
    mi zero = _mm256_setzero_si256(), acc = zero;
    while (i + 16 <= n) {
        mi va = L(a[i]), vb = L(b[i]);
        i += 16;
        va = _mm256_and_si256(_mm256_cmpgt_epi16(vb, va), va);
        mi vp = _mm256_madd_epi16(va, vb);
        acc = _mm256_add_epi64(
            _mm256_unpacklo_epi32(vp, zero),
            _mm256_add_epi64(acc,
                             _mm256_unpackhi_epi32(vp, zero)));
    }
    union {
        ll v[4];
        mi m;
    } u;
    u.m = acc;
    for (int i = 0; i < (4); ++i)
        r += u.v[i];
    for (; i < n; ++i)
        if (a[i] < b[i])
            r += a[i] * b[i]; // <- эквивалентно
    return r;
}
