#include "../utilities/template.h"

typedef vector<double> vd;
const double eps = 1e-12;

enum { YES, NO, MULT };
int solve_linear(vector<vd>& A, vd& b, vd& x) {
	int n = sz(A), m = sz(x), br = -1, bc = -1;
	vi col(m); iota(all(col), 0);

	for (int i = 0; i < (n); ++i) {
		double v, bv = -1;
		for (int r = i; r < (n); ++r) for (int c = i; c < (m); ++c)
			if ((v = fabs(A[r][c])) > bv)
				br = r, bc = c, bv = v;
		if (bv <= eps) {
			for (int j = i; j < (n); ++j) if (fabs(b[j]) > eps) return NO;
			if (i == m) break;
			return MULT;
		}
		swap(A[i], A[br]);
		swap(b[i], b[br]);
		swap(col[i], col[bc]);
		for (int j = 0; j < (n); ++j) swap(A[j][i], A[j][bc]);
		bv = 1/A[i][i];
		for (int j = i+1; j < (n); ++j) {
			double fac = A[j][i] * bv;
			b[j] -= fac * b[i];
			for (int k = i+1; k < (m); ++k) A[j][k] -= fac*A[i][k];
		}
	}
	if (n < m) return MULT;

	for (int i = m; i--;) {
		x[col[i]] = (b[i] /= A[i][i]);
		for (int j = 0; j < (i); ++j)
			b[j] -= A[j][i] * b[i];
	}
	return YES;
}

int main() {
	const int n = 1000;
	vector<vd> A(n, vd(n));
	for (int i = 0; i < (n); ++i) for (int j = 0; j < (n); ++j) A[i][j] = rand() * 1000.0 / RAND_MAX;
	vd x(n), b(n);
	for (int i = 0; i < (n); ++i) b[i] = rand() * 1000.0 / RAND_MAX;
	int r = solve_linear(A, b, x);
	assert(r == 0);
	cout<<"Tests passed!"<<endl;
	// cout << r << endl;
	// for (int i = 0; i < (n); ++i) cout << x[i] << ' ';
	// cout << endl;
}
