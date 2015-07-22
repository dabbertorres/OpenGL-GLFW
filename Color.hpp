#ifndef SWIFT_COLOR_HPP
#define SWIFT_COLOR_HPP

#include <array>

namespace swift
{
	using byte = unsigned char;
}

namespace priv
{
	std::array<swift::byte, 4> normalize(int b, int g, int r, int a);
}

namespace swift
{
	class Color
	{
		public:
			Color();
			Color(byte b, byte g, byte r, byte a = 255);
			Color(const std::array<byte, 3>& arr);
			Color(const std::array<byte, 4>& arr);
			
			byte blue;
			byte green;
			byte red;
			byte alpha;
	};

	bool operator==(const Color& lhs, const Color& rhs);
	bool operator!=(const Color& lhs, const Color& rhs);
	bool operator<=(const Color& lhs, const Color& rhs);
	bool operator>=(const Color& lhs, const Color& rhs);
	bool operator<(const Color& lhs, const Color& rhs);
	bool operator>(const Color& lhs, const Color& rhs);

	Color operator+(const Color& lhs, const Color& rhs);
	Color operator-(const Color& lhs, const Color& rhs);
	Color operator*(const Color& lhs, const Color& rhs);

	Color& operator+=(Color& lhs, const Color& rhs);
	Color& operator-=(Color& lhs, const Color& rhs);
	Color& operator*=(Color& lhs, const Color& rhs);

	template<typename T>
	Color operator*(const Color& lhs, T rhs)
	{
		auto arr = normalize(static_cast<int>(lhs.blue) * rhs,
							static_cast<int>(lhs.green) * rhs,
							static_cast<int>(lhs.red) * rhs,
							static_cast<int>(lhs.alpha) * rhs);

		return {arr[0], arr[1], arr[2], arr[3]};
	}

	template<typename T>
	Color operator*(T lhs, const Color& rhs)
	{
		return rhs * lhs;
	}

	template<typename T>
	Color& operator*=(Color& lhs, T rhs)
	{
		lhs = lhs * rhs;
		return lhs;
	}
}

#endif
