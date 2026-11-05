#include "../utilities/template.h"

#include "../../content/graph/MinimumVertexCover.h"
#include "../../content/graph/HopcroftKarp.h"

vi coverHK(vector<vi>& g, int n, int m) {
	vi match(m, -1);
	int res = hopcroftKarp(g, match);
	vector<bool> lfound(n, true), seen(m);
	for(auto &it: match) if (it != -1) lfound[it] = false;
	vi q, cover;
	for (int i = 0; i < (n); ++i) if (lfound[i]) q.eb(i);
	while (!q.empty()) {
		int i = q.back(); q.pop_back();
		lfound[i] = 1;
		for(auto &e: g[i]) if (!seen[e] && match[e] != -1) {
			seen[e] = true;
			q.eb(match[e]);
		}
	}
	for (int i = 0; i < (n); ++i) if (!lfound[i]) cover.eb(i);
	for (int i = 0; i < (m); ++i) if (seen[i]) cover.eb(n+i);
	assert(sz(cover) == res);
	return cover;
}

int main() {
	const int MAXN = 20;
	mt19937 rng(17);
	for (int it = 0; it < (300'000); ++it) {
		int N = rand() % MAXN, M = rand() % MAXN;
		vector<vi> gr(N);
		int co = rand() % 128 < 10 ? 2 : 1;
		for (int _ = 0; _ < (co); ++_) {
			int prop = rand();
			if (max(N, M) >= 5 && rand() % 128 < 90) {
				prop /= max(N, M);
				prop *= 2;
			}
			for (int i = 0; i < (N); ++i) for (int j = 0; j < (M); ++j) if (rand() < prop) {
				gr[i].eb(j);
			}
		}
		if (rand() % 128 < 20 && N && M) {
			int paths = rand() % min(N, M);
			vi left(N), right(M);
			for (int i = 0; i < (N); ++i) left[i] = i;
			for (int i = 0; i < (M); ++i) right[i] = i;
			for (int _ = 0; _ < (paths); ++_) {
				shuffle(all(left), rng);
				shuffle(all(right), rng);
				int len = rand() % min(N, M) + 1;
				if (rand() & 128) gr[left[0]].eb(right[0]);
				for (int i = 1; i < (len-1); ++i) {
					gr[left[i]].eb(right[i-1]);
					gr[left[i]].eb(right[i]);
				}
				if (len > 1 && (rand() & 128)) gr[left.back()].eb(right.back());
			}
		}
		for (int i = 0; i < (N); ++i) {
			// Duplicate edges are okay
			// sort(all(gr[i]));
			// gr[i].erase(unique(all(gr[i])), gr[i].end());
			shuffle(all(gr[i]), rng);
		}
		auto verify = [&](vi& cover) {
			vi left(N), right(M);
			for(auto &x: cover) {
				if (x < N) left[x] = 1;
				else right[x - N] = 1;
			}
			for (int i = 0; i < (N); ++i) if (!left[i]) for(auto &j:gr[i]) {
				assert(right[j]);
				/* if (!right[j]) {
					cout << N << ' ' << M << endl;
					for (int i = 0; i < (N); ++i) for(auto &j: gr[i]) cout << i << " - " << j << endl;
					cout << "yields " << sz(cover) << endl;
					for(auto &x: cover) cout << x << endl;
					abort();
				} */
			}
		};
		vi cover1 = cover(gr, N, M);
		vi cover2 = coverHK(gr, N, M);
		assert(sz(cover1) == sz(cover2));
		verify(cover1);
		verify(cover2);
		// cout << '.' << endl;
	}
	cout<<"Tests passed!"<<endl;
}
