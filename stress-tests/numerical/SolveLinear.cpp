#include "../utilities/template.h"

const int mod = 3;
const int nmax = 4, mmax = 4, nmmax = 10;

const int lut[9] = {-4,-2,-3,-1,-100,1,3,2,4};

int modinv(int x) {
	assert(x);
	return x;
	// return lut[x+4];
}

typedef vector<int> vd;

int solveLinear(vector<vd>& A, vd& b, vd& x) {
	int n = sz(A), m = sz(x), rank = 0, br, bc;
	if (n) assert(sz(A[0]) == m);
	vi col(m); iota(all(col), 0);

	for (int i = 0; i < (n); ++i) {
		int v, bv = -1;
		for (int r = i; r < (n); ++r) for (int c = i; c < (m); ++c)
			if ((v = A[r][c])) {
				br = r, bc = c, bv = v;
				goto found;
			}
		for (int j = i; j < (n); ++j) if (b[j]) return -1;
		break;
found:
		swap(A[i], A[br]);
		swap(b[i], b[br]);
		swap(col[i], col[bc]);
		for (int j = 0; j < (n); ++j) swap(A[j][i], A[j][bc]);
		bv = modinv(A[i][i]);
		for (int j = i+1; j < (n); ++j) {
			int fac = A[j][i] * bv % mod;
			b[j] = (b[j] - fac * b[i]) % mod;
			for (int k = i+1; k < (m); ++k) A[j][k] = (A[j][k] - fac*A[i][k]) % mod;
		}
		rank++;
	}

	x.assign(m, 0);
	for (int i = rank; i--;) {
		b[i] = ((b[i] * modinv(A[i][i]) % mod) + mod) % mod;
		x[col[i]] = b[i];
		for (int j = 0; j < (i); ++j)
			b[j] = (b[j] - A[j][i] * b[i]);
	}
	return rank;
}

template<class F>
void rec(int i, int j, vector<vd>& A, F f) {
	if (i == sz(A)) {
		f();
	}
	else if (j == sz(A[i])) {
		rec(i+1, 0, A, f);
	}
	else {
		for (int v = 0; v < (mod); ++v) {
			A[i][j] = v;
			rec(i, j+1, A, f);
		}
	}
}

template<class F>
void rec2(int i, vd& A, F f) {
	if (i == sz(A)) f();
	else {
		for (int v = 0; v < (mod); ++v) {
			A[i] = v;
			rec2(i+1, A, f);
		}
	}
}

int main() {
	for (int n = 0; n < (nmax+1); ++n) for (int m = 0; m < (mmax+1); ++m) {
		int nm = n*m;
		if (nm > nmmax) continue;
		vector<vd> A(n, vd(m));
		vd b(n), x(m), theX(m);
		rec(0, 0, A, [&]() {
			rec2(0, b, [&]() {
				int sols = 0;
				rec2(0, x, [&]() {
					for (int i = 0; i < (n); ++i) {
						int v = 0;
						for (int j = 0; j < (m); ++j) v += A[i][j] * x[j];
						if (v % mod != b[i]) return;
					}
					sols++;
					if (sols == 1) theX = x;
				});
				vector<vd> A2 = A;
				vd x2 = x, b2 = b;
				int r = solveLinear(A2, b2, x2);
				if (sols == 0) assert(r == -1);
				else if (sols == 1) assert(r == m);
				else assert(r < m);
				if (sols == 1) assert(x2 == theX);
			});
		});
	}
	cout<<"Tests passed!"<<endl;
}
