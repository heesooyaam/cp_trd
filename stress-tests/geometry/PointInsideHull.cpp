#include "../utilities/template.h"

#include "../../content/geometry/ConvexHull.h"
namespace ignore {
	#include "../../content/geometry/SegmentDistance.h"
}
#include "../../content/geometry/PointInsideHull.h"
#include "../../content/geometry/InsidePolygon.h"

int main() {
	for (int it = 0; it < (100000); ++it) {
		int N = rand() % 15;
		vector<P> ps;
		for (int i = 0; i < (N); ++i) ps.eb(rand() % 20 - 10, rand() % 20 - 10);
		vector<P> ps2 = convexHull(ps);
		if (ps2.empty()) continue;
		for (int it2 = 0; it2 < (20); ++it2) {
			int x = rand() % 22 - 11;
			int y = rand() % 22 - 11;
			P p{x,y};
			assert(inPolygon(ps2, p, true) == (inHull(ps2, p, true)));
			assert(inPolygon(ps2, p, false) == (inHull(ps2, p, false)));
		}
	}
	cout<<"Tests passed!"<<endl;
}
