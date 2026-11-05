#include "../utilities/template.h"

const ll mod = 5;
ll modpow(ll a, ll e) {
	if (e == 0) return 1;
	ll x = modpow(a * a % mod, e >> 1);
	return e & 1 ? x * a % mod : x;
}

#define mod dummy
#define modpow dummy2
#include "../../content/number-theory/ModPow.h"
#undef mod
#undef modpow

#include "../../content/numerical/BerlekampMassey.h"

template<class F>
void gen(vector<ll>& v, int at, F f) {
	if (at == sz(v)) f();
	else {
		for (int i = 0; i < (mod); ++i) {
			v[at] = i;
			gen(v, at+1, f);
		}
	}
}

int main() {
	for (int n = 1; n < (5); ++n) {
		vector<ll> start(n);
		vector<ll> coef(n), coef2;
		vector<ll> full(2*n);
		gen(start, 0, [&]() {
		gen(coef, 0, [&]() {
			for (int i = 0; i < (n); ++i) full[i] = start[i];
			for (int i = n; i < (2*n); ++i) full[i] = 0;
			for (int i = n; i < (2*n); ++i) for (int j = 0; j < (n); ++j) full[i] = (full[i] + coef[j] * full[i-1 - j]) % mod;
			coef2 = berlekampMassey(full);
// for (int i = 0; i < (2*n); ++i) cerr << full[i] << ' '; cerr << endl;
// for (int i = 0; i < (n); ++i) cerr << coef[i] << ' '; cerr << endl;
// for (int i = 0; i < (sz(coef2)); ++i) cerr << coef2[i] << ' '; cerr << endl;
			if (sz(coef2) == n) assert(coef == coef2);
// for (int i = 0; i < (n); ++i) cerr << full[i] << ' ';
			for (int i = n; i < (2*n); ++i) {
				ll x = 0;
				for (int j = 0; j < (sz(coef2)); ++j) x = (x + coef2[j] * full[i-1 - j]) % mod;
				// cerr << x << ' ';
				assert(x == full[i]);
			}
			// cerr << endl;
// cerr << endl;
		});
		});
	}
	cout<<"Tests passed!"<<endl;
	return 0;
}

int main2() {
	vector<ll> v{0, 1, 1, 3, 5, 11};
	auto v2 = berlekampMassey(v);
	for(auto &x: v2) cout << x << ' ';
	cout << endl;
	return 0;
}
