#include "../utilities/template.h"
#include "../utilities/random.h"

#include "../../content/data-structures/LazySegmentTree.h"

int main() {
	int N = 10;
	vi v(N);
	iota(all(v), 0);
	shuffle_vec(v);
	Node* tr = new Node(v,0,N);
	for (int i = 0; i < (N); ++i) for (int j = 0; j < (N); ++j) if (i <= j) {
		int ma = -inf;
		for (int k = i; k < (j); ++k) ma = max(ma, v[k]);
		assert(ma == tr->query(i,j));
	}
	for (int it = 0; it < (1000000); ++it) {
		int i = rand() % (N+1), j = rand() % (N+1);
		if (i > j) swap(i, j);
		int x = (rand() % 10) - 5;

		int r = rand() % 100;
		if (r < 30) {
			int res = tr->query(i, j);
			int ma = -inf;
			for (int k = i; k < (j); ++k) ma = max(ma, v[k]);
			assert(ma == res);
		}
		else if (r < 70) {
			tr->add(i, j, x);
			for (int k = i; k < (j); ++k) v[k] += x;
		}
		else {
			tr->set(i, j, x);
			for (int k = i; k < (j); ++k) v[k] = x;
		}
	}
	cout<<"Tests passed!"<<endl;
}
