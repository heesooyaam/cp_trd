#include "../utilities/template.h"

#include "../../content/strings/Hashing.h"

#include <sys/time.h>
int main() {
	assert((H(1)*2+1-3).get() == 0);

	for (int it = 0; it < (10000); ++it) {
		int n = rand() % 10;
		int alpha = rand() % 10 + 1;
		string s;
		for (int i = 0; i < (n); ++i) s += (char)('a' + rand() % alpha);
		HashInterval hi(s);
		set<string> strs;
		set<ull> hashes;

		// HashInterval
		for (int i = 0; i < (n+1); ++i) for (int j = i; j < (n+1); ++j) {
			string sub = s.substr(i, j - i);
			ull hash = hashString(sub).get();
			assert(hi.hashInterval(i, j).get() == hash);
			hashes.insert(hash);
			strs.insert(sub);
		}

		// getHashes
		for (int le = 1; le < (n+1); ++le) {
			auto ve = getHashes(s, le);
			assert(sz(ve) == n-le+1);
			for (int i = 0; i < (n-le+1); ++i) {
				assert(ve[i].get() == hi.hashInterval(i, i + le).get());
			}
		}

		// No collisions
		assert(sz(strs) == sz(hashes));
	}
	cout<<"Tests passed!"<<endl;
}
