#include "../utilities/template.h"

#include "../../content/graph/LinkCutTree.h"
#include "../../content/data-structures/UnionFind.h"

int main() {
	srand(2);
	LinkCut lczero(0);
	for (int it = 0; it < (10000); ++it) {
		int N = rand() % 20 + 1;
		LinkCut lc(N);
		UF uf(N);
		vector<pii> edges;
		for (int it2 = 0; it2 < (1000); ++it2) {
			int v = (rand() >> 4) & 3;
			if (v == 0 && !edges.empty()) { // remove
				int r = (rand() >> 4) % sz(edges);
				pii ed = edges[r];
				swap(edges[r], edges.back());
				edges.pop_back();
				if (rand() & 16)
					lc.cut(ed.first, ed.second);
				else
					lc.cut(ed.second, ed.first);
			} else {
				int a = (rand() >> 4) % N;
				int b = (rand() >> 4) % N;
				uf.e.assign(N, -1);
				for(auto &ed: edges) uf.join(ed.first, ed.second);
				bool c = uf.sameSet(a, b);
				if (!c && v != 1) {
					lc.link(a, b);
					edges.eb(a, b);
				} else {
					assert(lc.connected(a, b) == c);
				}
			}
		}
	}
	cout<<"Tests passed!"<<endl;
}
