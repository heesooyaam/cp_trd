// g++ -std=c++20 -O2 -DCP_BITSET_MODE=0 bitset.cpp
// Modes: 0 baseline, 1 popcnt, 2 O3+avx2+popcnt, 3 +unroll.
// Run only on x86 CPUs supporting the requested instructions.
#ifndef CP_BITSET_MODE
#define CP_BITSET_MODE 0
#endif
#if CP_BITSET_MODE == 1
#pragma GCC target("popcnt")
#elif CP_BITSET_MODE >= 2
#pragma GCC optimize("O3")
#pragma GCC target("avx2,popcnt")
#if CP_BITSET_MODE == 3
#pragma GCC optimize("unroll-loops")
#endif
#endif
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char** argv) {
    int rounds = argc > 1 ? stoi(argv[1]) : 100000;
    mt19937_64 rng(337);
    bitset<16384> a, b, c;
    for (int i = 0; i < 16384; ++i) {
        a[i] = rng() & 1; b[i] = rng() & 1;
    }
    uint64_t checksum = 0;
    auto start = chrono::steady_clock::now();
    for (int i = 0; i < rounds; ++i) {
        a.flip(rng() % a.size());
        c = (a & b) ^ (a >> 13);
        checksum += c.count();
    }
    cout << checksum << '\n';
    cerr << chrono::duration<double>(
        chrono::steady_clock::now() - start).count() << " s\n";
}
