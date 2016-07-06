#ifndef MATH_VECTOR2_H
#define MATH_VECTOR2_H

#include <iostream>

namespace math { template<class T> class Point2; }
namespace math { template<class T> class Normal2; }

namespace math {

template<class T>
class Vector2 {
	private:
		T m_data[2];

	public:
		inline Vector2();
		inline Vector2(const T& p_x, const T& p_y);
		inline Vector2(const Vector2<T>& p_vector);
		inline Vector2(const Point2<T>& p_point);

		inline Vector2<T>& operator=(const Vector2<T>& p_vector);

		template<class U> inline operator Vector2<U>() const;

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

		inline Vector2<T>& operator+=(const Vector2<T>& p_vector);
		inline Vector2<T>& operator+=(const Normal2<T>& p_normal);
		inline Vector2<T>& operator-=(const Vector2<T>& p_vector);
		inline Vector2<T>& operator*=(const T& p_scalar);
		inline Vector2<T>& operator/=(const T& p_scalar);

		inline T getSquaredMagnitude() const;
		inline T getMagnitude() const;

		inline Vector2<T>& normalize();
		inline Vector2<T> getNormalized() const;

		inline Vector2<T> operator-() const;
		inline T operator*(const Vector2<T>& p_vector) const;
		inline T operator*(const Normal2<T>& p_vector) const;

		inline Vector2<T> getLeftHand() const;
		inline Vector2<T> getRightHand() const;
		inline Normal2<T> getLeftHandNormal() const;
		inline Normal2<T> getRightHandNormal() const;
};

template<class T> inline Vector2<T> operator+(const Vector2<T>& p_v1, const Vector2<T>& p_v2);
template<class T> inline Vector2<T> operator+(const Vector2<T>& p_vector, const Normal2<T>& p_normal);
template<class T> inline Vector2<T> operator+(const Normal2<T>& p_normal, const Vector2<T>& p_vector);
template<class T> inline Vector2<T> operator-(const Vector2<T>& p_v1, const Vector2<T>& p_v2);
template<class T> inline Vector2<T> operator*(const Vector2<T>& p_vector, const T& p_scalar);
template<class T> inline Vector2<T> operator*(const T& p_scalar, const Vector2<T>& p_vector);
template<class T> inline T operator*(const Normal2<T>& p_normal, const Vector2<T>& p_vector);
template<class T> inline Vector2<T> operator/(const Vector2<T>& p_vector, const T& p_scalar);
template<class T> inline std::ostream& operator<<(std::ostream& p_stream, const Vector2<T>& p_vector);

}

#include <cmath>
#include "Point2.h"
#include "Normal2.h"

namespace math {

template<class T>
inline Vector2<T>::Vector2() {
	m_data[0] = 0;
	m_data[1] = 0;
}

template<class T>
inline Vector2<T>::Vector2(const T& p_x, const T& p_y) {
	m_data[0] = p_x;
	m_data[1] = p_y;
}

template<class T>
inline Vector2<T>::Vector2(const Vector2<T>& p_vector) {
	m_data[0] = p_vector.m_data[0];
	m_data[1] = p_vector.m_data[1];
}

template<class T>
inline Vector2<T>::Vector2(const Point2<T>& p_point) {
	m_data[0] = p_point[0];
	m_data[1] = p_point[1];
}

template<class T>
inline Vector2<T>& Vector2<T>::operator=(const Vector2<T>& p_vector) {
	if(this == &p_vector) {
		return *this;
	}

	m_data[0] = p_vector.m_data[0];
	m_data[1] = p_vector.m_data[1];

	return *this;
}

template<class T>
template<class U>
inline Vector2<T>::operator Vector2<U>() const {
	return Vector2<U>(static_cast<U>(m_data[0]), static_cast<U>(m_data[1]));
}

template<class T>
inline const T (&Vector2<T>::getData() const)[2] {
	return m_data;
}

template<class T>
inline T (&Vector2<T>::data())[2] {
	return m_data;
}

template<class T>
inline const T& Vector2<T>::operator[](unsigned int p_index) const {
	return m_data[p_index];
}

template<class T>
inline T& Vector2<T>::operator[](unsigned int p_index) {
	return m_data[p_index];
}

template<class T>
inline const T& Vector2<T>::getX() const {
	return m_data[0];
}

template<class T>
inline const T& Vector2<T>::getY() const {
	return m_data[1];
}

template<class T>
inline void Vector2<T>::setX(const T& p_x) {
	m_data[0] = p_x;
}

template<class T>
inline void Vector2<T>::setY(const T& p_y) {
	m_data[1] = p_y;
}

template<class T>
inline T& Vector2<T>::x() {
	return m_data[0];
}

template<class T>
inline T& Vector2<T>::y() {
	return m_data[1];
}

template<class T>
inline Vector2<T>& Vector2<T>::operator+=(const Vector2<T>& p_vector) {
	m_data[0] += p_vector.m_data[0];
	m_data[1] += p_vector.m_data[1];

	return *this;
}

template<class T>
inline Vector2<T>& Vector2<T>::operator+=(const Normal2<T>& p_normal) {
	m_data[0] += p_normal[0];
	m_data[1] += p_normal[1];

	return *this;
}

template<class T>
inline Vector2<T>& Vector2<T>::operator-=(const Vector2<T>& p_vector) {
	m_data[0] -= p_vector.m_data[0];
	m_data[1] -= p_vector.m_data[1];

	return *this;
}

template<class T>
inline Vector2<T>& Vector2<T>::operator*=(const T& p_scalar) {
	m_data[0] *= p_scalar;
	m_data[1] *= p_scalar;

	return *this;
}

template<class T>
inline Vector2<T>& Vector2<T>::operator/=(const T& p_scalar) {
	m_data[0] /= p_scalar;
	m_data[1] /= p_scalar;

	return *this;
}

template<class T>
inline T Vector2<T>::getSquaredMagnitude() const {
	return m_data[0] * m_data[0] + m_data[1] * m_data[1];
}

template<class T>
inline T Vector2<T>::getMagnitude() const {
	return std::sqrt(getSquaredMagnitude());
}

template<class T>
inline Vector2<T>& Vector2<T>::normalize() {
	*this /= getMagnitude();

	return *this;
}

template<class T>
inline Vector2<T> Vector2<T>::getNormalized() const {
	Vector2<T> res(*this);
	res.normalize();

	return res;
}

template<class T>
inline Vector2<T> Vector2<T>::operator-() const {
	return Vector2<T>(-m_data[0], -m_data[1]);
}

template<class T>
inline T Vector2<T>::operator*(const Vector2<T>& p_vector) const {
	return m_data[0] * p_vector.m_data[0] + m_data[1] * p_vector.m_data[1];
}

template<class T>
inline T Vector2<T>::operator*(const Normal2<T>& p_normal) const {
	return m_data[0] * p_normal[0] + m_data[1] * p_normal[1];
}

template<class T>
inline Vector2<T> Vector2<T>::getLeftHand() const {
	return Vector2<T>(-m_data[1], m_data[0]);
}

template<class T>
inline Vector2<T> Vector2<T>::getRightHand() const {
	return Vector2<T>(m_data[1], -m_data[0]);
}

template<class T>
inline Normal2<T> Vector2<T>::getLeftHandNormal() const {
	return Normal2<T>(getLeftHand()).normalize();
}

template<class T>
inline Normal2<T> Vector2<T>::getRightHandNormal() const {
	return Normal2<T>(getRightHand()).normalize();
}

template<class T>
inline Vector2<T> operator+(const Vector2<T>& p_v1, const Vector2<T>& p_v2) {
	Vector2<T> res(p_v1);
	res += p_v2;

	return res;
}

template<class T>
inline Vector2<T> operator+(const Vector2<T>& p_vector, const Normal2<T>& p_normal) {
	Vector2<T> res(p_vector);
	res += p_normal;

	return res;
}

template<class T>
inline Vector2<T> operator+(const Normal2<T>& p_normal, const Vector2<T>& p_vector) {
	Vector2<T> res(p_vector);
	res += p_normal;

	return res;
}

template<class T>
inline Vector2<T> operator-(const Vector2<T>& p_v1, const Vector2<T>& p_v2) {
	Vector2<T> res(p_v1);
	res -= p_v2;

	return res;
}

template<class T>
inline Vector2<T> operator*(const Vector2<T>& p_vector, const T& p_scalar) {
	Vector2<T> res(p_vector);
	res *= p_scalar;

	return res;
}

template<class T>
inline Vector2<T> operator*(const T& p_scalar, const Vector2<T>& p_vector) {
	Vector2<T> res(p_vector);
	res *= p_scalar;

	return res;
}

template<class T>
inline T operator*(const Normal2<T>& p_normal, const Vector2<T>& p_vector) {
	return p_vector * p_normal;
}

template<class T>
inline Vector2<T> operator/(const Vector2<T>& p_vector, const T& p_scalar) {
	Vector2<T> res(p_vector);
	res /= p_scalar;

	return res;
}

template<class T>
inline std::ostream& operator<<(std::ostream& p_stream, const Vector2<T>& p_vector) {
	p_stream << "(" << p_vector[0] << ", " << p_vector[1] << ")";
	return p_stream;
}

}

#endif
