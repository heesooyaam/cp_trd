/**
 * Author: Andrew-A-13 (idea), cp_trd
 * Source: Templates/std::hash
 * Description: Hash vector<int> for unordered containers.
 *  Pass as a hasher; do not specialize std::hash<vector<int>>.
 *  Equality still resolves collisions. Not cryptographic.
 * Usage: unordered_map<vi, int, VectorHash> mp;
 * Time: O(N)
 * Status: Container lookup tests, including negative values.
 */
#pragma once
struct vector_hash {
    static uint64_t mix(uint64_t x) {
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }
    size_t operator()(const vi &a) const {
        static const uint64_t seed =
            chrono::steady_clock::now()
                .time_since_epoch()
                .count();
        uint64_t h = mix(seed + a.size());
        for (int x : a) h = mix(h ^ mix(uint64_t(x)));
        return size_t(h);
    }
};
