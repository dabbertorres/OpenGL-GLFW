#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <array>

#include "Vector.hpp"

class Triangle
{
	public:
		using Point = Vector<float, 2>;

		Triangle();
		Triangle(Point, Point, Point);
		~Triangle() = default;

	private:
		std::array<Point, 3> points;
};

#endif
