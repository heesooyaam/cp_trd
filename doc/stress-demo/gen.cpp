#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
#define int ll

int32_t main(int32_t argc, char **argv) {
    if (argc != 2) {
        return 1;
    }
    mt19937 gen(stoull(argv[1]));
    int n = gen() % 8 + 1;
    cout << n << '\n';
    for (int i = 0; i < n; ++i) {
        cout << int(gen() % 21) - 10 << ' ';
    }
    cout << '\n';
}
