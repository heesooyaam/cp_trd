#include <random>
#include "../utilities/template.h"
#include "../utilities/genGraph.h"
#include "../utilities/random.h"

#include "../../content/graph/EdgeColoring.h"

void test(int n, const vector<pii>& ed) {
	vi deg(n);
	for (pii e : ed) ++deg[e.first], ++deg[e.second];
	int maxdeg = n == 0 ? 0 : *max_element(all(deg));
	vi cols = edgeColoring(n, ed);
	assert(sz(cols) == sz(ed));
	vector<vector<bool>> usedCols(n, vector<bool>(maxdeg+1));
	for (int i = 0; i < (sz(cols)); ++i) {
		int col = cols[i];
		assert(cols[i] <= maxdeg);
		for (int x : {ed[i].first, ed[i].second}) {
			assert(!usedCols[x][col]);
			usedCols[x][col] = 1;
		}
	}
}

void testCorrect() {
	for (int n = 0; n < (7); ++n) {
		for (int edbits = 0; edbits < ((1 << (n*(n-1)/2))); ++edbits) {
			vector<pii> ed;
			int it = 0;
			for (int i = 0; i < (n); ++i) for (int j = i+1; j < (n); ++j) {
				if (edbits & 1 << (it++)) {
					ed.push_back({i, j});
				}
			}
			if (n <= 4 || n + sz(ed) <= 9) {
				// test all k!*2^k input orders
				sort(all(ed));
				if (n != 0) do {
					for (int bi = 0; bi < ((1 << sz(ed))); ++bi) {
						if (bi) {
							int ind = __builtin_ctz(bi);
							swap(ed[ind].first, ed[ind].second);
						}
						test(n, ed);
					}
				} while (next_permutation(all(ed)));
			} else {
				int its = n == 5 ? 10 : 5;
				for (int it = 0; it < (its); ++it) {
					shuffle_vec(ed);
					for (auto& e : ed) if (randBool()) swap(e.first, e.second);
					test(n, ed);
				}
			}
		}
	}
	for (int n = 10; n < (30); ++n) for (int it = 0; it < (200); ++it) {
		int m = randIncl(n * (n-1) / 2);
		vector<pii> ed = randomSimpleGraphAsEdgeList(n, m);
		test(n, ed);
	}
	for (int n = 1; n <= 1000000; n *= 2) {
		int m = (int) min(1000000LL / n, (ll)n * (n-1) / 2);
		auto ed = randomSimpleGraphAsEdgeList(n, m);
		test(n, ed);
	}
	cout << "Tests passed!" << endl;
}

void testPerfRandom() {
	for (int i = 0; i < (100); ++i) {
		int n = 1000;
		int m = 20000;
		auto ed = randomSimpleGraphAsEdgeList(n, m);
		edgeColoring(n, ed);
	}
}

void testPerfRegular() {
	int n = 3000;
	int k = 30;
	// m = 45000
	vector<pii> ed = randomRegularGraphAsEdgeList(n, k);
	for (int i = 0; i < (100); ++i) edgeColoring(n, ed);
}

int main(int argc, char** argv) {
	srand(2);
	string arg = argc == 1 ? "" : argv[1];
	if (arg == "random") testPerfRandom();
	else if (arg == "regular") testPerfRegular();
	else {
		assert(argc == 1);
		testCorrect();
	}
}
