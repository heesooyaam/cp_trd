#include "../utilities/template.h"
#include "../utilities/random.h"

#include "../../content/data-structures/RMQ.h"

int main() {
	srand(2);
	for (int N = 0; N < (100); ++N) {
		vi v(N);
		for (int i = 0; i < (N); ++i) v[i] = i;
		shuffle_vec(v);
		RMQ<int> rmq(v);
		for (int i = 0; i < (N); ++i) for (int j = i+1; j < (N+1); ++j) {
			int m = rmq.query(i,j);
			int n = 1 << 29;
			for (int k = i; k < (j); ++k) n = min(n, v[k]);
			assert(n == m);
		}
	}
	cout<<"Tests passed!"<<endl;
}
