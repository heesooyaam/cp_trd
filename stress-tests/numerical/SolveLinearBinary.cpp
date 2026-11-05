#include "../utilities/template.h"

const int nmax = 5, mmax = 5, nmmax = 16;

typedef bitset<5> bs;

int solveLinear(vector<bs>& A, vi& b, bs& x, int m) {
	int n = sz(A), rank = 0, br;
	assert(m <= sz(x));
	vi col(m); iota(all(col), 0);
	for (int i = 0; i < (n); ++i) {
		for (br=i; br<n; ++br) if (A[br].any()) break;
		if (br == n) {
			for (int j = i; j < (n); ++j) if(b[j]) return -1;
			break;
		}
		int bc = (int)A[br]._Find_next(i-1);
		swap(A[i], A[br]);
		swap(b[i], b[br]);
		swap(col[i], col[bc]);
		for (int j = 0; j < (n); ++j) if (A[j][i] != A[j][bc]) {
			A[j].flip(i); A[j].flip(bc);
		}
		for (int j = i+1; j < (n); ++j) if (A[j][i]) {
			b[j] ^= b[i];
			A[j] ^= A[i];
		}
		rank++;
	}

	x = bs();
	for (int i = rank; i--;) {
		if (!b[i]) continue;
		x[col[i]] = 1;
		for (int j = 0; j < (i); ++j) b[j] ^= A[j][i];
	}
	return rank; // (multiple solutions if rank < m)
}

template<class F>
void rec(int i, int j, vector<bs>& A, int m, F f) {
	if (i == sz(A)) {
		f();
	}
	else if (j == m) {
		rec(i+1, 0, A, m, f);
	}
	else {
		for (int v = 0; v < (2); ++v) {
			A[i][j] = v;
			rec(i, j+1, A, m, f);
		}
	}
}

template<class F>
void rec2(int i, bs& A, int m, F f) {
	if (i == m) f();
	else {
		for (int v = 0; v < (2); ++v) {
			A[i] = v;
			rec2(i+1, A, m, f);
		}
	}
}

int main() {
	int ct = 0;
	for (int n = 0; n < (nmax+1); ++n) for (int m = 0; m < (mmax+1); ++m) {
		int nm = n*m;
		if (nm > nmmax) continue;
		vector<bs> A(n, bs(m));
		bs b, x, theX;
		vi b2(n);
		rec(0, 0, A, m, [&]() {
			rec2(0, b, n, [&]() {
				int sols = 0;
				rec2(0, x, m, [&]() {
					for (int i = 0; i < (n); ++i) {
						int v = 0;
						for (int j = 0; j < (m); ++j) v ^= A[i][j] & x[j];
						if (v != b[i]) return;
					}
					sols++;
					if (sols == 1) theX = x;
				});
				vector<bs> A2 = A;
				bs x2 = x; for (int i = 0; i < (n); ++i) b2[i] = b[i];
				int r = solveLinear(A2, b2, x2, m);
				if (sols == 0) assert(r == -1);
				else if (sols == 1) assert(r == m);
				else assert(r < m);
				if (sols == 1) assert(x2 == theX);
				ct++;
			});
		});
	}
	cout<<"Tests passed!"<<endl;
}
