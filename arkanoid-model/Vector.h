#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>

template<class T>
class Vector
{
	private:
	T _x;
	T _y;

	public:
	Vector(T x, T y);
	virtual ~Vector();

	T getX() const;
	T getY() const;
	T getNorm() const;

	void setX(T x);
	void setY(T y);

	bool operator==(const Vector &pos) const;
	Vector<T>& operator/=(const T& value);
	Vector<T>& operator*=(const T &v);
	Vector<T>& operator+=(const Vector <T> &v);
	Vector<T>& operator-=(const Vector <T> &v);
	Vector<T>& operator*=(const Vector <T> &v);
	Vector<T>& operator/=(const Vector <T> &v);
	Vector<T> operator-()const;

	void normalize();
	T dot(const Vector& v) const;
};

template <class T>
Vector<T> operator+(const Vector<T> &v, const Vector<T> &v2);

template <class T>
Vector<T> operator-(const Vector<T> &v, const Vector<T> &v2);

template <class T>
Vector<T> operator*(const Vector<T> &v, const Vector<T> &v2);

template <class T>
Vector<T> operator*(const Vector<T> &v, const T &val);

template <class T>
Vector<T> operator*(const T &val, const Vector<T> &v);

template <class T>
Vector<T> operator/(const Vector<T> &v, const Vector<T> &v2);

template <class T>
Vector<T> operator/(const Vector<T> &v, const T &val);

#include "Vector.cxx"

typedef Vector < float > VectorF;

#endif