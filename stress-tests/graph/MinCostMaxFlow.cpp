#include "../utilities/template.h"

// #include "mcmf3.h"
// #include "mcmf4.h"
// #include "mcmfold.h"
// #include "mcmfnew.h"
#include <bits/extc++.h>
#define setpi dummy(){} bool setpi
#undef assert
#define assert(x) return x
#include "../../content/graph/MinCostMaxFlow.h"
#undef assert
#undef setpi
#include <cassert>
#include "MinCostMaxFlow2.h"

struct MCMF2 {
	vector<vector<FlowEdge>> g;
	MCMF2(int n) : g(n) {}
	void addEdge(int s, int t, Flow c, Flow cost = 0) {
		flow_add_edge(g, s, t, c, cost);
	}
	pair<ll, ll> maxflow(int s, int t) {
		return min_cost_max_flow(g, s, t);
	}
	void setpi(int s) {}
};

// typedef MCMF2 MCMF;

#if 1
static size_t i;
#else
static char buf[450 << 20];
static size_t i = sizeof buf;
void* operator new(size_t s) {
	assert(s < i);
	return (void*)&buf[i -= s];
}
void operator delete(void*) noexcept {}
#endif

typedef vector<ll> vd;
bool zero(ll x) { return x == 0; }
ll MinCostMatching(const vector<vd>& cost, vi& L, vi& R) {
	int n = sz(cost), mated = 0;
	vd dist(n), u(n), v(n);
	vi dad(n), seen(n);

	/// construct dual feasible solution
	for (int i = 0; i < (n); ++i) {
		u[i] = cost[i][0];
		for (int j = 1; j < (n); ++j) u[i] = min(u[i], cost[i][j]);
	}
	for (int j = 0; j < (n); ++j) {
		v[j] = cost[0][j] - u[0];
		for (int i = 1; i < (n); ++i) v[j] = min(v[j], cost[i][j] - u[i]);
	}

	/// find primal solution satisfying complementary slackness
	L = vi(n, -1);
	R = vi(n, -1);
	for (int i = 0; i < (n); ++i) for (int j = 0; j < (n); ++j) {
		if (R[j] != -1) continue;
		if (zero(cost[i][j] - u[i] - v[j])) {
			L[i] = j;
			R[j] = i;
			mated++;
			break;
		}
	}

	for (; mated < n; mated++) { // until solution is feasible
		int s = 0;
		while (L[s] != -1) s++;
		fill(all(dad), -1);
		fill(all(seen), 0);
		for (int k = 0; k < (n); ++k)
			dist[k] = cost[s][k] - u[s] - v[k];

		int j = 0;
		for (;;) { /// find closest
			j = -1;
			for (int k = 0; k < (n); ++k){
				if (seen[k]) continue;
				if (j == -1 || dist[k] < dist[j]) j = k;
			}
			seen[j] = 1;
			int i = R[j];
			if (i == -1) break;
			for (int k = 0; k < (n); ++k) { /// relax neighbors
				if (seen[k]) continue;
				auto new_dist = dist[j] + cost[i][k] - u[i] - v[k];
				if (dist[k] > new_dist) {
					dist[k] = new_dist;
					dad[k] = j;
				}
			}
		}

		/// update dual variables
		for (int k = 0; k < (n); ++k) {
			if (k == j || !seen[k]) continue;
			auto w = dist[k] - dist[j];
			v[k] += w, u[R[k]] -= w;
		}
		u[s] += dist[j];

		/// augment along path
		while (dad[j] >= 0) {
			int d = dad[j];
			R[j] = R[d];
			L[R[j]] = j;
			j = d;
		}
		R[j] = s;
		L[s] = j;
	}

	auto value = vd(1)[0];
	for (int i = 0; i < (n); ++i) value += cost[i][L[i]];
	return value;
}

void testPerf() {
	srand(2);
	int N = 500, E = 10000, CAPS = 100, COSTS = 100000;
	MCMF mcmf(N);
	int s = 0, t = 1;
	for (int i = 0; i < (E); ++i) {
		int a = rand() % N;
		int b = rand() % N;
		int cap = rand() % CAPS;
		int cost = rand() % COSTS;
		if (a == b) continue;
		mcmf.addEdge(a, b, cap, cost);
		// ::cap[a][b] = cap;
		// ::cost[a][b] = cost;
	}
	auto pa = mcmf.maxflow(s, t);
	cout << pa.first << ' ' << pa.second << endl;
}

void testMatching() {
	for (int it = 0; it < (100000); ++it) {
		size_t last = ::i;
		int N = rand() % 10, M = rand() % 10;
		int NM = max(N, M);
		vector<vd> co(NM, vd(NM));
		for (int i = 0; i < (N); ++i) for (int j = 0; j < (M); ++j) co[i][j] = (rand() % 10) + 2;
		vi L, R;
		ll v = MinCostMatching(co, L, R);
		int S = N+M, T = N+M+1;
		MCMF mcmf(N+M+2);
		for (int i = 0; i < (N); ++i) mcmf.addEdge(S, i, 1, 0);
		for (int i = 0; i < (M); ++i) mcmf.addEdge(N+i, T, 1, 0);
		for (int i = 0; i < (N); ++i) for (int j = 0; j < (M); ++j) mcmf.addEdge(i, N+j, 1, co[i][j] - 2);
		mcmf.setpi(S);
		auto pa = mcmf.maxflow(S, T);
		assert(pa.first == min(N, M));
		assert(pa.second == v - 2 * pa.first);
		::i = last;
	}
}

void testNeg() {
	const int ITS = 1000000;
	int ed[100][100];
	int negs = 0;
	for (int it = 0; it < (ITS); ++it) {
		size_t lasti = ::i;
		int N = rand() % 7 + 2;
		int M = rand() % 17;
		int S = 0, T = 1;
		MCMF mcmf(N);
		MCMF2 mcmf2(N);
		for (int i = 0; i < (N); ++i) for (int j = 0; j < (N); ++j) ed[i][j] = 0;
		bool anyneg = false;
		for (int eid = 0; eid < (M); ++eid) {
			int i = rand() % N, j = rand() % N;
			if (i != j && !ed[i][j]) {
				ed[i][j] = 1;
				int fl = rand() % 50;
				int co = rand() % 11 - 3;
				mcmf.addEdge(i, j, fl, co);
				mcmf2.addEdge(i, j, fl, co);
				if (co < 0) anyneg = true;
			}
		}
		negs += anyneg;
		if (anyneg || rand() % 3 == 0) {
			if (!mcmf.setpi(S))  // has negative loops
				continue;
		}
		auto pa = mcmf.maxflow(S, T);
		auto pa2 = mcmf2.maxflow(S, T);
		assert(pa == pa2);
		::i = lasti;
	}
	// cerr << negs << "/" << ITS << " graphs with negative edge costs" << endl;
	cout<<"Tests passed!"<<endl;
}

int main() {
	testMatching();
	testNeg();
}
