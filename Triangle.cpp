#include "Triangle.hpp"

Triangle::Triangle()
{
	points.fill({});
}

Triangle::Triangle(Point one, Point two, Point three)
{
	points[0] = one;
	points[1] = two;
	points[2] = three;
}
