#include "../utilities/template.h"

#include "../../content/graph/SCC.h"

namespace old {
vi orig, low, comp, z;
int no_vertices, no_components;
template<class G> void dfs(int j, G &g) {
	low[j] = orig[j] = no_vertices++;
	comp[j] = -2; z.eb(j);
	for(auto &e:g[j])
		if (comp[e] == -1) {
			dfs(e, g);
			low[j] = min(low[j], low[e]);
		}
		else if (comp[e] == -2)
			low[j] = min(low[j], orig[e]);

	if (orig[j] == low[j]) {
		for (;;) {
			int x = z.back(); z.pop_back();
			comp[x] = no_components;
			if (x == j) break;
		}
		no_components++;
	}
}
template<class G> vi scc(G &g) {
	int n = sz(g);
	orig.assign(n, 0); low = orig;
	no_vertices = no_components = 0;
	comp.assign(n, -1);
	for (int i = 0; i < (n); ++i) if (comp[i] == -1) dfs(i, g);
	return comp;
}
}

int main() {
	unsigned r = 1;
	for (int N = 0; N <= 4; N++) {
		// cout << "N = " << N << endl;
		vector<vi> mat(N, vi(N)), adj(N);
		vi compsize(N), seen(N);
		int count = 0;
		for (int bits = 0; bits < ((1 << (N*N))); ++bits) {
			// if (bits % 10000 == 0) cerr << "." << flush;
			for (int i = 0; i < (N); ++i) for (int j = 0; j < (N); ++j)
				mat[i][j] = bits & 1 << (i*N+j);

			for (int i = 0; i < (N); ++i) {
				adj[i].clear();
				for (int j = 0; j < (N); ++j) if (bits & 1 << (i*N+j)) {
					adj[i].eb(j);
					r *= 12387123; r += 1231;
					if ((r >> 6 & 31) == 3)
						adj[i].eb(j);
				}
			}
			vi comp2 = old::scc(adj);
			scc(adj, [&](vi& v) {
				compsize[ncomps] = sz(v);
			});
			if (comp != comp2) {
				for(auto &x: comp) cout << x << ' ';
				cout << endl;
				for(auto &x: comp2) cout << x << ' ';
				cout << endl;
			}
			for (int i = 0; i < (N); ++i) assert(comp[i] >= 0 && comp[i] < ncomps);
			for (int i = 0; i < (N); ++i) for(auto &j: adj[i]) assert(comp[j] <= comp[i]);
			for (int i = 0; i < (N); ++i) {
				seen.assign(N, 0); seen[i] = 1;
				for (int it = 0; it < (N); ++it) {
					for (int j = 0; j < (N); ++j) if (seen[j]) for(auto &k: adj[j]) seen[k] = 1;
				}
				for (int j = 0; j < (N); ++j) {
					if (seen[j]) assert(comp[j] <= comp[i]);
					else assert(comp[j] != comp[i]);
				}
			}

			count++;
		}
		// cout << "tested " << count << endl;
	}
	cout<<"Tests passed!"<<endl;
	return 0;
}
