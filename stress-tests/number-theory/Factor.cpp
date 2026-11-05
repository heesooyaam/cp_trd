#include "../utilities/template.h"

#include "../../content/number-theory/Factor.h"

mt19937_64 uni(time(0));
void assertValid(ull N, vector<ull> prFac){
	ull cur=1;
	for (auto i: prFac){
		if (!isPrime(i)){
			cout<<N<<endl;
			cout<<i<<endl;
			assert(isPrime(i));
		}
		cur *= i;
	}
	if (cur!= N)
		cout<<cur<<' '<<N<<endl;
	assert(cur == N);
}
int main() {
	assert(factor(1).empty());
	assert(factor(2) == vector<ull>{2});
	assert((factor(2299) == vector<ull>{11, 19, 11}));
	for (int n = 2; n < (1e5); ++n) {
		auto res = factor(n);
		assertValid(n, res);
		res = factor(n*ll(n));
		assertValid(n*ll(n), res);
	}
	for (int i = 2; i < (1e5); ++i) {
		ull n = 1 + (uni()%(3ul<<61));
		auto res = factor(n);
		assertValid(n, res);
	}
	for (int i = 0; i < (1e5); ++i) {
		// max number that modmul can handle
		ull n = 7268172458553106874 - i;
		auto res = factor(n);
		assertValid(n, res);
	}
	cout<<"Tests passed!"<<endl;
}
