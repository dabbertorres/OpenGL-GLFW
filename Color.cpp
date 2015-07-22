#include "Color.hpp"

namespace priv
{
	std::array<swift::byte, 4> normalize(int b, int g, int r, int a)
	{
		return {static_cast<swift::byte>(b > 255 ? 255 : b < 0 ? 0 : b),
				static_cast<swift::byte>(g > 255 ? 255 : g < 0 ? 0 : g),
				static_cast<swift::byte>(r > 255 ? 255 : r < 0 ? 0 : r),
				static_cast<swift::byte>(a > 255 ? 255 : a < 0 ? 0 : a)};
	}
}

namespace swift
{
	using namespace priv;
	
	Color::Color()
	:	Color(0, 0, 0, 0)
	{}

	Color::Color(byte b, byte g, byte r, byte a)
	:	blue(b),
		green(g),
		red(r),
		alpha(a)
	{}
	
	Color::Color(const std::array<byte, 3>& arr)
	:	blue(arr[0]),
		green(arr[1]),
		red(arr[2]),
		alpha(255)
	{}
	
	Color::Color(const std::array<byte, 4>& arr)
	:	blue(arr[0]),
		green(arr[1]),
		red(arr[2]),
		alpha(arr[3])
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
		auto arr = normalize(static_cast<int>(lhs.blue) + static_cast<int>(rhs.blue),
							static_cast<int>(lhs.green) + static_cast<int>(rhs.green),
							static_cast<int>(lhs.red) + static_cast<int>(rhs.red),
							static_cast<int>(lhs.alpha) + static_cast<int>(rhs.alpha));

		return {arr[0], arr[1], arr[2], arr[3]};
	}

	Color operator-(const Color& lhs, const Color& rhs)
	{
		auto arr = normalize(static_cast<int>(lhs.blue) - static_cast<int>(rhs.blue),
							static_cast<int>(lhs.green) - static_cast<int>(rhs.green),
							static_cast<int>(lhs.red) - static_cast<int>(rhs.red),
							static_cast<int>(lhs.alpha) - static_cast<int>(rhs.alpha));

		return {arr[0], arr[1], arr[2], arr[3]};
	}

	Color operator*(const Color& lhs, const Color& rhs)
	{
		auto arr = normalize(static_cast<int>(lhs.blue) * static_cast<int>(rhs.blue),
							static_cast<int>(lhs.green) * static_cast<int>(rhs.green),
							static_cast<int>(lhs.red) * static_cast<int>(rhs.red),
							static_cast<int>(lhs.alpha) * static_cast<int>(rhs.alpha));

		return {arr[0], arr[1], arr[2], arr[3]};
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
