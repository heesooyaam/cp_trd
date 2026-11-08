#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
#define int ll
#define all(x) begin(x), end(x)

int32_t main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &x : a) {
        cin >> x;
    }
    // Простой эталон: сортировка, затем последний элемент.
    sort(all(a));
    cout << a.back() << '\n';
}
