#include "../utilities/template.h"

bool valid(vi deg) {
	int n = sz(deg);
	sort(all(deg));
	reverse(all(deg));
	int sum = 0;
	for (int i = 0; i < (n); ++i) sum += deg[i];
	if (sum & 1) return 0;
	for (int k = 0; k < (n); ++k) {
		int s = 0, t = 0;
		for (int i = 0; i < (k+1); ++i)
			s += deg[i];
		for (int i = k+1; i < (n); ++i)
			t += min(deg[i], k + 1);
		if (s > k * (k+1) + t) return 0;
	}
	return 1;
}

int main() {
	for (int N = 0; N < (7); ++N) {
		vector<pii> possibleEd;
		for (int i = 0; i < (N); ++i) for (int j = 0; j < (i); ++j) possibleEd.eb(i, j);
		set<vi> valids;
		for (int bi = 0; bi < ((1 << sz(possibleEd))); ++bi) {
			vi deg(N);
			for (int i = 0; i < (sz(possibleEd)); ++i) if (bi & (1 << i)) {
				int a, b;
				tie(a, b) = possibleEd[i];
				deg[a]++;
				deg[b]++;
			}
			assert(valid(deg));
			valids.insert(deg);
		}

		vi de(N);
		function<void(int)> rec = [&](int at) {
			if (at == N) {
				assert(valid(de) == valids.count(de));
			} else {
				for (int a = 0; a < (N); ++a) {
					de[at] = a;
					rec(at + 1);
				}
			}
		};
		rec(0);
	}
	cout << "Tests passed!" << endl;
}
