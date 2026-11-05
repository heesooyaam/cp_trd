#include "../utilities/template.h"
#include <valarray>

#include "../../content/numerical/FastFourierTransform.h"

const double eps = 1e-8;
int main() {
	int n = 8;
	vector<C> a(n);
	for (int i = 0; i < (n); ++i) a[i] = C(rand() % 10 - 5, rand() % 10 - 5);
	auto aorig = a;
	fft(a);
	for (int k = 0; k < (n); ++k) {
		C sum{};
		for (int x = 0; x < (n); ++x) {
			sum += aorig[x] * polar(1.0, 2 * M_PI * k * x / n);
		}
		assert(norm(sum - a[k]) < 1e-6);
	}

	vector<double> A(4), B(6);
	for(auto &x: A) x = rand() / (RAND_MAX + 1.0) * 10 - 5;
	for(auto &x: B) x = rand() / (RAND_MAX + 1.0) * 10 - 5;
	vector<double> C = conv(A, B);
	for (int i = 0; i < (sz(A) + sz(B) - 1); ++i) {
		double sum = 0;
		for (int j = 0; j < (sz(A)); ++j) if (i - j >= 0 && i - j < sz(B)) {
			sum += A[j] * B[i - j];
		}
		assert(abs(sum - C[i]) < eps);
	}
	cout<<"Tests passed!"<<endl;
}
