#ifndef MATH_POINT2_H
#define MATH_POINT2_H

#include <iostream>

namespace math { template<class T> class Vector2; }

namespace math {

template<class T>
class Point2 {
	private:
		T m_data[2];

	public:
		inline Point2();
		inline Point2(const T& p_x, const T& p_y);
		inline Point2(const Point2<T>& p_point);

		inline Point2<T>& operator=(const Point2<T>& p_point);

		template<class U> inline operator Point2<U>() const;

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

		inline Point2<T>& operator+=(const Vector2<T>& p_vector);
		inline Point2<T>& operator-=(const Vector2<T>& p_vector);

		inline T getSquaredDistance(const Point2<T>& p_point) const;
		inline T getDistance(const Point2<T>& p_point) const;
};

template<class T> inline Point2<T> operator+(const Point2<T>& p_point, const Vector2<T>& p_vector);
template<class T> inline Point2<T> operator-(const Point2<T>& p_point, const Vector2<T>& p_vector);
template<class T> inline Vector2<T> operator-(const Point2<T>& p_p1, const Point2<T>& p_p2);
template<class T> inline std::ostream& operator<<(std::ostream& p_stream, const Point2<T>& p_point);

}

#include <cmath>
#include "Vector2.h"

namespace math {

template<class T>
inline Point2<T>::Point2() {
	m_data[0] = 0;
	m_data[1] = 0;
}

template<class T>
inline Point2<T>::Point2(const T& p_x, const T& p_y) {
	m_data[0] = p_x;
	m_data[1] = p_y;
}

template<class T>
inline Point2<T>::Point2(const Point2<T>& p_point) {
	m_data[0] = p_point.m_data[0];
	m_data[1] = p_point.m_data[1];
}

template<class T>
inline Point2<T>& Point2<T>::operator=(const Point2<T>& p_point) {
	if(this == &p_point) {
		return *this;
	}

	m_data[0] = p_point.m_data[0];
	m_data[1] = p_point.m_data[1];
	return *this;
}

template<class T>
template<class U>
inline Point2<T>::operator Point2<U>() const {
	return Point2<U>(static_cast<U>(m_data[0]), static_cast<U>(m_data[1]));
}

template<class T>
inline const T (&Point2<T>::getData() const)[2] {
	return m_data;
}

template<class T>
inline T (&Point2<T>::data())[2] {
	return m_data;
}

template<class T>
inline const T& Point2<T>::operator[](unsigned int p_index) const {
	return m_data[p_index];
}

template<class T>
inline T& Point2<T>::operator[](unsigned int p_index) {
	return m_data[p_index];
}

template<class T>
inline const T& Point2<T>::getX() const {
	return m_data[0];
}

template<class T>
inline const T& Point2<T>::getY() const {
	return m_data[1];
}

template<class T>
inline void Point2<T>::setX(const T& p_x) {
	m_data[0] = p_x;
}

template<class T>
inline void Point2<T>::setY(const T& p_y) {
	m_data[1] = p_y;
}

template<class T>
inline T& Point2<T>::x() {
	return m_data[0];
}

template<class T>
inline T& Point2<T>::y() {
	return m_data[1];
}

template<class T>
inline Point2<T>& Point2<T>::operator+=(const Vector2<T>& p_vector) {
	m_data[0] += p_vector.getX();
	m_data[1] += p_vector.getY();
	return *this;
}

template<class T>
inline Point2<T>& Point2<T>::operator-=(const Vector2<T>& p_vector) {
	m_data[0] -= p_vector.getX();
	m_data[1] -= p_vector.getY();
	return *this;
}

template<class T>
T Point2<T>::getSquaredDistance(const Point2<T>& p_point) const {
	T xSize = m_data[0] - p_point.m_data[0];
	T ySize = m_data[1] - p_point.m_data[1];
	return xSize * xSize + ySize * ySize;
}

template<class T>
inline T Point2<T>::getDistance(const Point2<T>& p_point) const {
	return std::sqrt(getSquaredDistance(p_point));
}

template<class T>
inline Point2<T> operator+(const Point2<T>& p_point, const Vector2<T>& p_vector) {
	Point2<T> res(p_point);
	res += p_vector;

	return res;
}

template<class T>
inline Point2<T> operator-(const Point2<T>& p_point, const Vector2<T>& p_vector) {
	Point2<T> res(p_point);
	res -= p_vector;

	return res;
}

template<class T>
inline Vector2<T> operator-(const Point2<T>& p_p1, const Point2<T>& p_p2) {
	return Vector2<T>(p_p1.getX() - p_p2.getX(), p_p1.getY() - p_p2.getY());
}

template<class T>
inline std::ostream& operator<<(std::ostream& p_stream, const Point2<T>& p_point) {
	p_stream << "(" << p_point[0] << ", " << p_point[1] << ")";
	return p_stream;
}

}

#endif
