#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
#define int ll

int32_t main() {
    int n;
    cin >> n;
    int ans =
        0; // Намеренная ошибка: а если все числа отрицательные?
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        ans = max(ans, x);
    }
    cout << ans << '\n';
}
