#include "../utilities/template.h"
#include "../../content/strings/AhoCorasick.h"

#define trav(a, x) for (auto& a : x)

template<class F>
void gen(string& s, int at, int alpha, F f) {
	if (at == sz(s)) f();
	else {
		for (int i = 0; i < (alpha); ++i) {
			s[at] = (char)('A' + i);
			gen(s, at+1, alpha, f);
		}
	}
}

void test(const string& s) {
	vector<string> pats;
	string cur;
	for (int i = 0; i < (sz(s)); ++i) {
		if (s[i] == 'A') {
			pats.eb(cur);
			cur = "";
		}
		else cur += s[i];
	}

	string hay = cur;
	trav(x, pats) if (x.empty()) return;

	AhoCorasick ac(pats);
	vector<vi> positions = ac.findAll(pats, hay);

	vi ord;
	for (int i = 0; i < (sz(hay)); ++i) {
		ord.clear();
		for (int j = 0; j < (sz(pats)); ++j) {
			string& pat = pats[j];
			if (hay.substr(i, pat.size()) == pat) {
				ord.eb(j);
			}
		}
		sort(all(positions[i]));

		if (positions[i] != ord) {
			cerr << "failed!" << endl;
			cerr << hay << endl;
			trav(x, pats) cerr << x << endl;
			cerr << "failed at position " << i << endl;
			cerr << "got:" << endl;
			trav(x, positions[i]) cerr << x << ' ';
			cerr << endl;
			cerr << "expected:" << endl;
			trav(x, ord) cerr << x << ' ';
			cerr << endl;
			abort();
		}
	}
}

int main() {
	// test ~4^10 strings
	for (int n = 0; n < (11); ++n) {
		string s(n, 'x');
		gen(s, 0, 4, [&]() {
			test(s);
		});
	}
	// then ~5^7
	for (int n = 0; n < (8); ++n) {
		string s(n, 'x');
		gen(s, 0, 5, [&]() {
			test(s);
		});
	}
	cout<<"Tests passed!"<<endl;
}
