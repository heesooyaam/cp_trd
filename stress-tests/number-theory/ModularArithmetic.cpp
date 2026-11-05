#include "../utilities/template.h"

#include "../../content/number-theory/ModularArithmetic.h"

int main() {
	for (int a = 0; a < (mod); ++a) for (int b = 1; b < (mod); ++b) {
		Mod ma(a);
		Mod mb(b);
		Mod mc = ma / mb;
		assert((mc * mb).x == a);
	}
	Mod a = 2;
	ll cur=1;
	for (int i = 0; i < (17); ++i) {
		assert((a ^ i).x == cur);
		cur = (cur * 2) % mod;
		// cout << i << ": " << (a ^ i).x << endl;
	}
	cout<<"Tests passed!"<<endl;
}
