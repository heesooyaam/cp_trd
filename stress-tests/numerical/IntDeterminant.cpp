#include "../utilities/template.h"

const int mod = 7; // 4

typedef vector<vector<ll>> vvll;
ll det(vvll& a) { // integer determinant
	int n = sz(a); ll ans = 1;
	for (int i = 0; i < (n); ++i) {
		for (int j = i+1; j < (n); ++j) {
			while (a[j][i] != 0) { // gcd step
				ll t = a[i][i] / a[j][i];
				for (int k = i; k < (n); ++k)
					a[i][k] = (a[i][k] - a[j][k] * t) % mod;
				swap(a[i], a[j]);
				ans *= -1;
			}
		}
		if (!a[i][i]) return 0;
		ans = ans * a[i][i] % mod;
	}
	if (ans < 0) ans += mod;
	return ans;
}

ll idet(vvll& a) { // integer determinant
	int n = sz(a); ll ans = 1;
	for (int i = 0; i < (n); ++i) {
		for (int j = i+1; j < (n); ++j) {
			while (a[j][i] != 0) { // gcd step
				ll t = a[i][i] / a[j][i]; // can take mod-inv if mod p
				for (int k = i; k < (n); ++k) a[i][k] -= a[j][k] * t;
				swap(a[i], a[j]);
				ans *= -1;
			}
		}
		if (!a[i][i]) return 0;
		ans *= a[i][i];
	}
	return ans;
}

double det(vector<vector<double>>& a) {
	int n = sz(a); double res = 1;
	for (int i = 0; i < (n); ++i) {
		int b = i;
		for (int j = i+1; j < (n); ++j) if (fabs(a[j][i]) > fabs(a[b][i])) b = j;
		if (i != b) swap(a[i], a[b]), res *= -1;
		res *= a[i][i];
		if (res == 0) return 0;
		for (int j = i+1; j < (n); ++j) {
			double v = a[j][i] / a[i][i];
			if (v != 0) for (int k = i+1; k < (n); ++k) a[j][k] -= v * a[i][k];
		}
	}
	return res;
}

template<class F>
void rec(int i, int j, vvll& A, F f) {
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
void rec2(int i, vector<ll>& A, F f) {
	if (i == sz(A)) f();
	else {
		for (int v = 0; v < (mod); ++v) {
			A[i] = v;
			rec2(i+1, A, f);
		}
	}
}

int main() {
	for (int n = 0; n < (4); ++n) {
		vvll mat(n, vector<ll>(n, 0)), mat2;
		vector<vector<double>> mat3(n, vector<double>(n, 0));
		rec(0,0,mat,[&]() {
			for (int i = 0; i < (n); ++i) for (int j = 0; j < (n); ++j) mat3[i][j] = (double)mat[i][j];
			// mat2 = mat; ll a = det(mat2);
			int a = (int)round(det(mat3)) % mod;
			mat2 = mat; ll b = idet(mat2) % mod;
			if (a < 0) a += mod;
			if (b < 0) b += mod;
			if (a != b) {
				for (int i = 0; i < (n); ++i) {
					for (int j = 0; j < (n); ++j) cout << mat[i][j];
					cout << endl;
				}
				cout << a << ' ' << b << endl;
				assert(a == b);
			}
		});
	}
	cout<<"Tests passed!"<<endl;
}
