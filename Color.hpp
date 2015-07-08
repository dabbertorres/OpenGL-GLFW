#ifndef SWIFT_COLOR_HPP
#define SWIFT_COLOR_HPP

namespace swift
{
	using byte = unsigned char;
	
	class Color
	{
		public:
			Color();
			Color(byte b, byte g, byte r, byte a = 255);
			
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
		return {lhs.blue * rhs, lhs.green * rhs, lhs.red * rhs};
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