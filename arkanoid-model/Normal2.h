#ifndef MATH_NORMAL2_H
#define MATH_NORMAL2_H

#include <iostream>

namespace math { template<class T> class Vector2; }

namespace math {

template<class T>
class Normal2 {
	private:
		T m_data[2];

	public:
		inline Normal2();
		inline Normal2(const T& p_x, const T& p_y);
		inline Normal2(const Normal2<T>& p_normal);
		inline Normal2(const Vector2<T>& p_vector);

		inline Normal2<T>& operator=(const Normal2<T>& p_normal);

		template<class U> inline operator Normal2<U>() const;
		inline operator Vector2<T>() const;

		inline const T (&getData() const)[2];
		inline T (&data())[2];

		inline const T& operator[](unsigned int p_index) const;
		inline T& operator[](unsigned int p_index);

		inline const T& getX() const;
		inline const T& getY() const;
		inline void setX(const T& p_x);
		inline void setY(const T& p_y);
		inline T& x();
		inline T& y();

		inline Normal2<T>& operator+=(const Normal2<T>& p_normal);
		inline Normal2<T>& operator*=(const T& p_scalar);
		inline Normal2<T>& operator/=(const T& p_scalar);

		inline T getSquaredMagnitude() const;
		inline T getMagnitude() const;

		inline Normal2<T>& normalize();

		inline Normal2<T> operator-() const;
};

template<class T> inline Normal2<T> operator+(const Normal2<T>& p_n1, const Normal2<T>& p_n2);
template<class T> inline Normal2<T> operator*(const Normal2<T>& p_normal, const T& p_scalar);
template<class T> inline Normal2<T> operator*(const T& p_scalar, const Normal2<T>& p_normal);
template<class T> inline Normal2<T> operator/(const Normal2<T>& p_normal, const T& p_scalar);
template<class T> inline std::ostream& operator<<(std::ostream& p_stream, const Normal2<T>& p_normal);

}

#include <cmath>
#include "Vector2.h"

namespace math {

template<class T>
inline Normal2<T>::Normal2() {
	m_data[0] = 0;
	m_data[1] = 0;
}

template<class T>
inline Normal2<T>::Normal2(const T& p_x, const T& p_y) {
	m_data[0] = p_x;
	m_data[1] = p_y;
}

template<class T>
inline Normal2<T>::Normal2(const Normal2<T>& p_normal) {
	m_data[0] = p_normal.m_data[0];
	m_data[1] = p_normal.m_data[1];
}

template<class T>
inline Normal2<T>::Normal2(const Vector2<T>& p_vector) {
	m_data[0] = p_vector[0];
	m_data[1] = p_vector[1];
}

template<class T>
inline Normal2<T>& Normal2<T>::operator=(const Normal2<T>& p_normal) {
	if(this == &p_normal) {
		return *this;
	}

	m_data[0] = p_normal.m_data[0];
	m_data[1] = p_normal.m_data[1];

	return *this;
}

template<class T>
template<class U>
inline Normal2<T>::operator Normal2<U>() const {
	return Normal2<U>(static_cast<U>(m_data[0]), static_cast<U>(m_data[1]));
}

template<class T>
inline Normal2<T>::operator Vector2<T>() const {
	return Vector2<T>(m_data[0], m_data[1]);
}

template<class T>
inline const T (&Normal2<T>::getData() const)[2] {
	return m_data;
}

template<class T>
inline T (&Normal2<T>::data())[2] {
	return m_data;
}

template<class T>
inline const T& Normal2<T>::operator[](unsigned int p_index) const {
	return m_data[p_index];
}

template<class T>
inline T& Normal2<T>::operator[](unsigned int p_index) {
	return m_data[p_index];
}

template<class T>
inline const T& Normal2<T>::getX() const {
	return m_data[0];
}

template<class T>
inline const T& Normal2<T>::getY() const {
	return m_data[1];
}

template<class T>
inline void Normal2<T>::setX(const T& p_x) {
	m_data[0] = p_x;
}

template<class T>
inline void Normal2<T>::setY(const T& p_y) {
	m_data[1] = p_y;
}

template<class T>
inline T& Normal2<T>::x() {
	return m_data[0];
}

template<class T>
inline T& Normal2<T>::y() {
	return m_data[1];
}

template<class T>
inline Normal2<T>& Normal2<T>::operator+=(const Normal2<T>& p_normal) {
	m_data[0] += p_normal.m_data[0];
	m_data[1] += p_normal.m_data[1];

	return *this;
}

template<class T>
inline Normal2<T>& Normal2<T>::operator*=(const T& p_scalar) {
	m_data[0] *= p_scalar;
	m_data[1] *= p_scalar;

	return *this;
}

template<class T>
inline Normal2<T>& Normal2<T>::operator/=(const T& p_scalar) {
	m_data[0] /= p_scalar;
	m_data[1] /= p_scalar;

	return *this;
}

template<class T>
inline T Normal2<T>::getSquaredMagnitude() const {
	return m_data[0] * m_data[0] + m_data[1] * m_data[1];
}

template<class T>
inline T Normal2<T>::getMagnitude() const {
	return std::sqrt(getSquaredMagnitude());
}

template<class T>
inline Normal2<T>& Normal2<T>::normalize() {
	*this /= getMagnitude();

	return *this;
}

template<class T>
inline Normal2<T> Normal2<T>::operator-() const {
	return Normal2<T>(-m_data[0], -m_data[1]);
}

template<class T>
inline Normal2<T> operator*(const Normal2<T>& p_normal, const T& p_scalar) {
	Normal2<T> res(p_normal);
	res *= p_scalar;

	return res;
}

template<class T>
inline Normal2<T> operator*(const T& p_scalar, const Normal2<T>& p_normal) {
	Normal2<T> res(p_normal);
	res *= p_scalar;

	return res;
}

template<class T>
inline Normal2<T> operator/(const Normal2<T>& p_normal, const T& p_scalar) {
	Normal2<T> res(p_normal);
	res /= p_scalar;

	return res;
}

template<class T>
inline Normal2<T> operator+(const Normal2<T>& p_n1, const Normal2<T>& p_n2) {
	Normal2<T> res(p_n1);
	res += p_n2;

	return res;
}

template<class T>
inline std::ostream& operator<<(std::ostream& p_stream, const Normal2<T>& p_normal) {
	p_stream << "(" << p_normal[0] << ", " << p_normal[1] << ")";
	return p_stream;
}

}

#endif
