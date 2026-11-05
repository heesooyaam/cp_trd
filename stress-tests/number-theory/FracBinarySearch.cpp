#include "../utilities/template.h"

#include "../../content/number-theory/FracBinarySearch.h"

int main() {
	for (int n = 1; n < (300); ++n) {
		vector<pair<double, pii>> v;
		for (int i = 0; i < (n+1); ++i) for (int j = 1; j < (n+1); ++j) if (__gcd(i,j) == 1) {
			double r = (double)i / j;
			v.eb(r, pii(i,j));
		}
		v.eb(1e9, pii(0,0));
		sort(all(v));
		map<double, pii> actual(all(v));

		for (int iter = 0; iter < (100000); ++iter) {
			double x = rand() / (RAND_MAX + 1.0);
			// x *= min(n, 10); // if testing with search range (0, n)
			auto fn = [&](Frac f) { return (double)f.p >= x * (double)f.q; };
			Frac f = fracBS(fn, n);
			auto best = actual.lower_bound(x)->second;
			assert(best.first == f.p);
			assert(best.second == f.q);
		}
	}
	cout<<"Tests passed!"<<endl;
	return 0;
}
