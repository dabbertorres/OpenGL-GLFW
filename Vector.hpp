#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <array>
#include <initializer_list>

template<typename T, int D>
class Vector
{
	public:
		Vector();
		Vector(std::initializer_list<T>);
		~Vector() = default;

		T& operator[](unsigned int);
		const T& operator[](unsigned int) const;

	private:
		std::array<T, D> dims;
};

template<typename T, int D>
Vector<T, D>::Vector()
{
	dims.fill(0);
}

template<typename T, int D>
Vector<T, D>::Vector(std::initializer_list<T> list)
:	dims(list)
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

#endif
