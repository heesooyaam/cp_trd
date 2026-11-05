#include "../utilities/template.h"

#include "../../content/geometry/MinimumEnclosingCircle.h"

int main() {
	srand(2);
	for (int it = 0; it < (1000000); ++it) {
		int N = rand() % 20 + 1;
		// int N = 4;
		vector<P> ps;
		for (int i = 0; i < (N); ++i) {
			ps.eb(rand() % 21 - 10, rand() % 21 - 10);
		}

		pair<P, double> pa = mec(ps);
		P mid = pa.first;
		double rad = pa.second;
		double maxDist = 0;
		for(auto &p: ps) {
			maxDist = max(maxDist, (p - mid).dist());
		}

		assert(abs(maxDist - rad) < 1e-6);

		for (int it2 = 0; it2 < (50); ++it2) {
			P q2 = mid - P(0, 1e-6).rotate(it2);
			for(auto &p: ps) {
				if((p - q2).dist() > rad - 1e-7) goto fail;
			}
			assert(0);
fail:;
		}
	}
	cout<<"Tests passed!"<<endl;
}
