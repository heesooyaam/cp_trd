#include "../utilities/template.h"

#include "../../content/graph/MaximalCliques.h"

template<class F>
void fastCliques(vector<B>& eds, F f) {
	B R{}, P = ~B(), X{};
	vi deg(sz(eds));
	for (int i = 0; i < (sz(eds)); ++i) deg[i] = sz(eds[i]);
	for (int j = 0; j < (sz(eds)); ++j) {
		int i = (int)(min_element(all(deg)) - deg.begin());
		R[i] = 1;
		rec(eds, R, P & eds[i], X & eds[i], f);
		R[i] = P[i] = 0; X[i] = 1;
		for (int k = 0; k < (sz(eds)); ++k) if (eds[i][k]) deg[k]--;
		deg[i] = 1000000;
	}
}

int main1() {
	for (int n = 1; n < (11); ++n) for (int m = 0; m < (200); ++m) {
		vector<B> ed(n);
		for (int i = 0; i < (m); ++i) {
			int a = rand() % n, b = rand() % n;
			if (a == b) continue;
			ed[a][b] = 1;
			ed[b][a] = 1;
		}
		unordered_set<B> cl;
		int co = 0;
		cliques(ed, [&](B x) {
			co++;
			cl.insert(x);
		});
		assert(sz(cl) == co); // no duplicates
		auto isClique = [&](B c) {
			for (int i = 0; i < (n); ++i) if (c[i])
			for (int j = i+1; j < (n); ++j) if (c[j]) {
				if (!ed[i][j]) return false; // not a clique
			}
			for (int i = 0; i < (n); ++i) if (!c[i]) {
				bool all = true;
				for (int j = 0; j < (n); ++j) if (c[j]) all &= ed[i][j];
				if (all) return false; // not maximal
			}
			return true;
		};
		for(auto &c: cl) {
			assert(isClique(c));
		}

		int realCo = 0;
		for (int bi = 0; bi < ((1 << n)); ++bi) {
			B c{};
			for (int i = 0; i < (n); ++i) c[i] = !!(bi & (1 << i));
			if (isClique(c)) realCo++;
		}
		assert(co == realCo);
	}
	cout<<"Tests passed!"<<endl;
	return 0;
}

int main2() {
	for (int it = 0; it < (20); ++it) {
		const int n = 128, m = 4000;
		vector<B> ed(n);
		for (int i = 0; i < (m); ++i) {
			int a = rand() % n, b = rand() % n;
			if (a == b) continue;
			ed[a][b] = 1;
			ed[b][a] = 1;
		}
		int co = 0, sum = 0;
		cliques(ed, [&](B x) { co++; sum += (int)x.count(); });
		cout << co << ' ' << (double)sum / co << endl;
	}
	return 0;
}

#ifndef target
#define target main1
#endif
int main() { target(); }
