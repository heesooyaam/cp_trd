/**
 * Author: cp_trd
 * License: CC0
 * Description: XOR-базис 64-битных беззнаковых чисел. Хранит все XOR
 *  подмножеств; пустое подмножество даёт 0. add(x) возвращает true,
 *  если x независим и увеличил rank; contains(x) проверяет представимость.
 *  max\_xor(x) даёт максимум x xor s по представимым s (по умолчанию x=0).
 *  Различных XOR ровно $2^{rank}$; после n добавлений каждый из них
 *  получается $2^{n-rank}$ подмножествами. Непустое подмножество с XOR=0
 *  существует тогда и только тогда, когда n>rank. Для rank=64 не писать
 *  1ULL<<rank: считать количество через unsigned \_\_int128 или по модулю.
 * Usage: XorBasis b; b.add(3); b.add(5); // b.max_xor() == 6
 * Time: O(64) на операцию; merge O(64^2)
 */
#pragma once

struct XorBasis {
    uint64_t basis[64]{}; // basis[i]: старший бит i
    int rank = 0;
    uint64_t reduce(uint64_t x) const {
        for (int i = 63; i >= 0; --i) {
            x = min(x, x ^ basis[i]);
        }
        return x;
    }
    bool contains(uint64_t x) const { return reduce(x) == 0; }
    bool add(uint64_t x) {
        x = reduce(x);
        if (!x) {
            return false;
        }
        basis[bit_width(x) - 1] = x;
        ++rank;
        return true;
    }
    uint64_t max_xor(uint64_t x = 0) const {
        for (int i = 63; i >= 0; --i) {
            x = max(x, x ^ basis[i]);
        }
        return x;
    }
    void merge(const XorBasis &other) {
        for (uint64_t x : other.basis) {
            add(x);
        }
    }
};
