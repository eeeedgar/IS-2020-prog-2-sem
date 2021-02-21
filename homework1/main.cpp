#include "geometry.h"
#include <iostream>
#include <cassert>

using namespace std;


int main()
{
    Point *a = new Point[3]{Point(0, 0), Point(0, 3), Point(4, 0)};
    ClosedPolygonalChain b(3, a);
    ClosedPolygonalChain p(b);
    assert(equalsf(p.perimeter(), 12));
}