#include "Color.hpp"

namespace swift
{
	Color::Color()
	:	Color(0, 0, 0, 0)
	{}

	Color::Color(byte b, byte g, byte r, byte a)
	:	blue(b),
		green(g),
		red(r),
		alpha(a)
	{}

	bool operator==(const Color& lhs, const Color& rhs)
	{
		return lhs.blue == rhs.blue && lhs.green == rhs.green && lhs.red == rhs.red && lhs.alpha == rhs.alpha;
	}

	bool operator!=(const Color& lhs, const Color& rhs)
	{
		return !(lhs == rhs);
	}

	bool operator<=(const Color& lhs, const Color& rhs)
	{
		return lhs.blue <= rhs.blue && lhs.green <= rhs.green && lhs.red <= rhs.red && lhs.alpha <= rhs.alpha;
	}

	bool operator>=(const Color& lhs, const Color& rhs)
	{
		return lhs.blue >= rhs.blue && lhs.green >= rhs.green && lhs.red >= rhs.red && lhs.alpha >= rhs.alpha;
	}

	bool operator<(const Color& lhs, const Color& rhs)
	{
		return lhs.blue < rhs.blue && lhs.green < rhs.green && lhs.red < rhs.red && lhs.alpha < rhs.alpha;
	}

	bool operator>(const Color& lhs, const Color& rhs)
	{
		return lhs.blue > rhs.blue && lhs.green > rhs.green && lhs.red > rhs.red && lhs.alpha > rhs.alpha;
	}

	Color operator+(const Color& lhs, const Color& rhs)
	{
		int blue = static_cast<int>(lhs.blue) + static_cast<int>(rhs.blue);
		int green = static_cast<int>(lhs.green) + static_cast<int>(rhs.green);
		int red = static_cast<int>(lhs.red) + static_cast<int>(rhs.red);
		int alpha = static_cast<int>(lhs.alpha) + static_cast<int>(rhs.alpha);

		byte b = blue > 255 ? 255 : blue < 0 ? 0 : blue;
		byte g = green > 255 ? 255 : green < 0 ? 0 : green;
		byte r = red > 255 ? 255 : red < 0 ? 0 : red;
		byte a = alpha > 255 ? 255 : alpha < 0 ? 0 : alpha;

		return {b, g, r, a};
	}

	Color operator-(const Color& lhs, const Color& rhs)
	{
		int blue = static_cast<int>(lhs.blue) - static_cast<int>(rhs.blue);
		int green = static_cast<int>(lhs.green) - static_cast<int>(rhs.green);
		int red = static_cast<int>(lhs.red) - static_cast<int>(rhs.red);
		int alpha = static_cast<int>(lhs.alpha) - static_cast<int>(rhs.alpha);

		byte b = blue > 255 ? 255 : blue < 0 ? 0 : blue;
		byte g = green > 255 ? 255 : green < 0 ? 0 : green;
		byte r = red > 255 ? 255 : red < 0 ? 0 : red;
		byte a = alpha > 255 ? 255 : alpha < 0 ? 0 : alpha;

		return {b, g, r, a};
	}

	Color operator*(const Color& lhs, const Color& rhs)
	{
		int blue = static_cast<int>(lhs.blue) * static_cast<int>(rhs.blue);
		int green = static_cast<int>(lhs.green) * static_cast<int>(rhs.green);
		int red = static_cast<int>(lhs.red) * static_cast<int>(rhs.red);
		int alpha = static_cast<int>(lhs.alpha) * static_cast<int>(rhs.alpha);

		byte b = blue > 255 ? 255 : blue < 0 ? 0 : blue;
		byte g = green > 255 ? 255 : green < 0 ? 0 : green;
		byte r = red > 255 ? 255 : red < 0 ? 0 : red;
		byte a = alpha > 255 ? 255 : alpha < 0 ? 0 : alpha;

		return {b, g, r, a};
	}

	Color& operator+=(Color& lhs, const Color& rhs)
	{
		lhs = lhs + rhs;
		return lhs;
	}

	Color& operator-=(Color& lhs, const Color& rhs)
	{
		lhs = lhs - rhs;
		return lhs;
	}

	Color& operator*=(Color& lhs, const Color& rhs)
	{
		lhs = lhs * rhs;
		return lhs;
	}
}
