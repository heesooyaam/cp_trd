#include "../utilities/template.h"

ll det(vector<vector<ll>>& a) {
	int n = sz(a); ll ans = 1;
	for (int i = 0; i < (n); ++i) {
		for (int j = i+1; j < (n); ++j) {
			while (a[j][i] != 0) { // gcd step
				ll t = a[i][i] / a[j][i];
				if (t) for (int k = i; k < (n); ++k)
					a[i][k] = (a[i][k] - a[j][k] * t);
				swap(a[i], a[j]);
				ans *= -1;
			}
		}
		ans = ans * a[i][i];
		if (!ans) return 0;
	}
	return ans;
}

ll rec(vector<vi>& ed, int active, int finished) {
	int N = sz(ed);
	if (finished == (1 << N) - 1) return 1;
	int chosen = -1;
	for (int i = 0; i < (N); ++i) if (!(finished & (1 << i)) && (active & (1 << i))) {
		chosen = i;
		break;
	}
	if (chosen == -1) return 0; // missing nodes from tree
	int si = sz(ed[chosen]);
	ll res = 0;
	for (int bi = 0; bi < ((1 << si)); ++bi) {
		int edto = 0;
		for (int i = 0; i < (si); ++i) {
			if (bi & (1 << i)) {
				if (edto & (1 << ed[chosen][i])) goto fail;
				edto |= 1 << ed[chosen][i];
			}
		}
		if (active & edto) continue;
		res += rec(ed, active | edto, finished | (1 << chosen));
fail:;
	}
	return res;
}

ll countTrees(vector<vi>& ed, int root) {
	return rec(ed, 1 << root, 0);
}

int main() {
	for (int it = 0; it < (100); ++it) {
		int N = rand() % 7 + 1;
		int M = rand() % 10;
		int root = rand() % N;
		vector<vi> ed(N);
		vector<vector<ll>> mat(N, vector<ll>(N));
		for (int i = 0; i < (M); ++i) {
			int a = rand() % N;
			int b = rand() % N;
			ed[a].eb(b);
			mat[b][b]++;
			mat[a][b]--;
		}
		ll numTrees = countTrees(ed, root);

		mat.erase(mat.begin() + root);
		for (int i = 0; i < (N-1); ++i) mat[i].erase(mat[i].begin() + root);

		ll numTrees2 = det(mat);
		assert(numTrees == numTrees2);
	}
	cout << "Tests passed!" << endl;
}
