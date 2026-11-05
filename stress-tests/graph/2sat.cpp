#include "../utilities/template.h"
#include "../utilities/random.h"

#include "../../content/graph/2sat.h"

int main1() {
	const int N = 100000, M = 10000000;
	// Random constraints, unsolvable
	{
		TwoSat ts(N);
		for (int i = 0; i < (M); ++i) {
			int r = rand();
			int s = r;
			r >>= 2;
			int a = r % N;
			r >>= 5;
			int b = r % N;
			if (a == b) continue;
			ts.either(a ^ (s&1 ? 0 : -1), b ^ (s&2 ? 0 : -1));
		}
		assert(ts.solve() == 0);
	}
	// Random solvable instance
	{
		vector<bool> v(N);
		for (int i = 0; i < (N); ++i) v[i] = rand() & (1 << 20);
		TwoSat ts(N);
		for (int i = 0; i < (M); ++i) {
			int r = rand();
			int s = r;
			r >>= 2;
			int a = r % N;
			r >>= 5;
			int b = r % N;
			if (a == b) continue;
			ts.either(a ^ (v[a] ? 0 : -1), b ^ (s&1 ? 0 : -1));
		}
		assert(ts.solve() == 1);
	}
	return 0;
}

int main2() {
	int N = 4;
	TwoSat ts(N);
	ts.either(0,1);
	ts.either(0,~1);
	ts.either(~2,~3);
	assert(ts.solve()==1);
	assert(ts.values == vi({1, 1, 0, 0}));
	return 0;
}

// Test at_most_one
int main() {
	main1();
	main2();
	const int N = 100, M = 400;
	for (int it = 0; it < (100); ++it) {
		vector<bool> v(N);
		for (int i = 0; i < (N); ++i) v[i] = rand() & (1 << 20);
		TwoSat ts(N);
		vector<vi> atm;
		vi r;
		for (int i = 0; i < (M); ++i) {
			if (rand()%100 < 5) {
				int r = rand();
				int s = r;
				r >>= 2;
				int a = r % N;
				r >>= 5;
				int b = r % N;
				if (a == b) continue;
				ts.either(v[a] ? a : ~a, (s&1) ? b : ~b);
			} else {
				int k = rand() % 4 + 1;
				r.clear();
				for (int ki = 0; ki < (k-1); ++ki) {
					int a = rand() % N;
					r.eb(v[a] ? ~a : a);
				}
				r.eb(rand() % (2*N) - N);
				shuffle_vec(r);
				ts.atMostOne(r);
				atm.eb(r);
			}
		}
		assert(ts.solve());
		int to = 0;
		for (int i = 0; i < (N); ++i) to += (ts.values[i] == v[i]);
		for(auto &r: atm) {
			int co = 0;
			for(auto &x: r) co += (ts.values[max(x, ~x)] == (x >= 0));
			assert(co <= 1);
		}
	}
	cout<<"Tests passed!"<<endl;
	return 0;
}
