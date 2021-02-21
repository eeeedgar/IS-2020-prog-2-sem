#include "geometry.h"
#include <iostream>
#include <cassert>

using namespace std;


int main()
{
    Point *a = new Point[3]{Point(0, 0), Point(0, 3), Point(4, 0)};
    ClosedPolygonalChain c(3, a);
    ClosedPolygonalChain p(c);
    Triangle t(3, a);

    assert(equalsf(p.perimeter(), 12));
    assert(t.hasRightAngle());
}