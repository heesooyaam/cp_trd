#include "../utilities/template.h"

#include "../../content/data-structures/FenwickTree.h"

int main() {
	for (int it = 0; it < (100000); ++it) {
		int N = rand() % 10;
		FT fw(N);
		vi t(N);
		for (int i = 0; i < (N); ++i) {
			int v = rand() % 3;
			fw.update(i, v);
			t[i] += v;
		}
		int q = rand() % 20;
		int ind = fw.lower_bound(q);
		int res = -1, sum = 0;
		for (int i = 0; i < (N+1); ++i) {
			if (sum < q) res = i;
			if (i != N) sum += t[i];
		}
		assert(res == ind);
	}
	cout<<"Tests passed!"<<endl;
}
