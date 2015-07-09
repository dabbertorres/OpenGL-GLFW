#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <array>
#include <cmath>
#include <initializer_list>

template<typename T, int D>
class Vector
{
	public:
		Vector();
		Vector(std::initializer_list<T>);
		Vector(const std::array<T, D>&);
		
		~Vector() = default;

		T& operator[](unsigned int);
		const T& operator[](unsigned int) const;
		
		T magnitude() const;
		Vector unit() const;

	private:
		std::array<T, D> dims;
};

// arithmetic functions
template<typename T, int D>
Vector<T, D> operator +(const Vector<T, D>&, const Vector<T, D>&);

template<typename T, int D>
Vector<T, D> operator -(const Vector<T, D>&, const Vector<T, D>&);

// dot product
template<typename T, int D>
T operator *(const Vector<T, D>&, const Vector<T, D>&);

template<typename T, int D>
Vector<T, D> operator *(const Vector<T, D>&, T);

template<typename T, int D>
Vector<T, D> operator *(T, const Vector<T, D>&);

// cross product
template<typename T, int D>
Vector<T, D> operator /(const Vector<T, D>&, T);

// assignment arithmetic functions
template<typename T, int D>
Vector<T, D>& operator +=(Vector<T, D>&, const Vector<T, D>&);

template<typename T, int D>
Vector<T, D>& operator -=(Vector<T, D>&, const Vector<T, D>&);

template<typename T, int D>
Vector<T, D>& operator *=(Vector<T, D>&, T);

template<typename T, int D>
Vector<T, D>& operator /=(Vector<T, D>&, T);

// comparison functions
template<typename T, int D>
bool operator ==(const Vector<T, D>&, const Vector<T, D>&);

template<typename T, int D>
bool operator !=(const Vector<T, D>&, const Vector<T, D>&);

template<typename T, int D>
Vector<T, D>::Vector()
{
	dims.fill(0);
}

template<typename T, int D>
Vector<T, D>::Vector(std::initializer_list<T> list)
{
	// gcc is being funny with constructing std::array from an initializer_list...
	for(auto it = list.begin(); it - list.begin() < D && it != list.end(); ++it)
	{
		dims[it - list.begin()] = *it;
	}
}

template<typename T, int D>
Vector<T, D>::Vector(const std::array<T, D>& arr)
:	dims(arr)
{}

template<typename T, int D>
T& Vector<T, D>::operator[](unsigned int i)
{
	return dims[i];
}

template<typename T, int D>
const T& Vector<T, D>::operator[](unsigned int i) const
{
	return dims[i];
}

template<typename T, int D>
T Vector<T, D>::magnitude() const
{
	T total = 0;
	
	for(auto i = 0u; i < D; ++i)
		total += dims[i] * dims[i];
	
	return std::sqrt(total);
}

template<typename T, int D>
Vector<T, D> Vector<T, D>::unit() const
{
	T mag = magnitude();
	
	if(!mag)
		return {0, 0};
	
	return *this / mag;
}

template<typename T, int D>
Vector<T, D> operator +(const Vector<T, D>& lhs, const Vector<T, D>& rhs)
{
	std::array<T, D> arr;
	
	for(auto i = 0u; i < arr.size(); ++i)
		arr[i] = lhs[i] + rhs[i];
	
	return {arr};
}

template<typename T, int D>
Vector<T, D> operator -(const Vector<T, D>& lhs, const Vector<T, D>& rhs)
{
	std::array<T, D> arr;
	
	for(auto i = 0u; i < arr.size(); ++i)
		arr[i] = lhs[i] - rhs[i];
	
	return {arr};
}

// dot product
template<typename T, int D>
T operator *(const Vector<T, D>& lhs, const Vector<T, D>& rhs)
{
	T total = 0;
	
	for(auto i = 0u; i < D; ++i)
		total += lhs[i] * rhs[i];
	
	return total;
}

template<typename T, int D>
Vector<T, D> operator *(const Vector<T, D>& lhs, T rhs)
{
	std::array<T, D> arr;
	
	for(auto i = 0u; i < arr.size(); ++i)
		arr[i] = lhs[i] * rhs;
	
	return {arr};
}

template<typename T, int D>
Vector<T, D> operator *(T lhs, const Vector<T, D>& rhs)
{
	std::array<T, D> arr;
	
	for(auto i = 0u; i < arr.size(); ++i)
		arr[i] = lhs * rhs[i];
	
	return {arr};
}

template<typename T, int D>
Vector<T, D> operator /(const Vector<T, D>& lhs, T rhs)
{
	std::array<T, D> arr;
	
	for(auto i = 0u; i < arr.size(); ++i)
		arr[i] = lhs[i] / rhs;
	
	return {arr};
}

// assignment arithmetic functions
template<typename T, int D>
Vector<T, D>& operator +=(Vector<T, D>& lhs, const Vector<T, D>& rhs)
{
	for(auto i = 0u; i < D; ++i)
		lhs[i] += rhs[i];
	
	return lhs;
}

template<typename T, int D>
Vector<T, D>& operator -=(Vector<T, D>& lhs, const Vector<T, D>& rhs)
{
	for(auto i = 0u; i < D; ++i)
		lhs[i] -= rhs[i];
	
	return lhs;
}

template<typename T, int D>
Vector<T, D>& operator *=(Vector<T, D>& lhs, T rhs)
{
	for(auto i = 0u; i < D; ++i)
		lhs[i] += rhs;
	
	return lhs;
}

template<typename T, int D>
Vector<T, D>& operator /=(Vector<T, D>& lhs, T rhs)
{
	for(auto i = 0u; i < D; ++i)
		lhs[i] /= rhs;
	
	return lhs;
}

// comparison functions
template<typename T, int D>
bool operator ==(const Vector<T, D>& lhs, const Vector<T, D>& rhs)
{
	for(auto i = 0u; i < D; ++i)
	{
		if(lhs[i] == rhs[i])
			continue;
		else
			return false;
	}
	
	return true;
}

template<typename T, int D>
bool operator !=(const Vector<T, D>& lhs, const Vector<T, D>& rhs)
{
	return !(lhs == rhs);
}

#endif
