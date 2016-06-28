template<class T>
Vector<T>::Vector(T x, T y)
	: _x(x)
	, _y(y)
{
}

template<class T>
Vector<T>::~Vector()
{
}

template<class T>
T
Vector<T>::getX() const
{
	return _x;
}

template<class T>
T
Vector<T>::getY() const
{
	return _y;
}

template<class T>
void
Vector<T>::setX(T x)
{
	_x = x;
}

template<class T>
void
Vector<T>::setY(T y)
{
	_y = y;
}

template<class T>
bool
Vector<T>::operator==(const Vector &pos) const
{
	return pos._x == _x && pos._y == _y;
}


template<class T>
Vector<T>&
Vector<T>::operator+=(const Vector <T> &v)
{
	_x += v.getX();
	_y += v.getY();
	return *this;
}

template<class T>
Vector<T>&
Vector<T>::operator-=(const Vector <T> &v)
{
	_x -= v.getX();
	_y -= v.getY();
	return *this;
}

template<class T>
Vector<T>& Vector<T>::operator/=(const T& value)
{
	_x /= value;
	_y /= value;
	return *this;
}

template<class T>
Vector<T>& Vector<T>::operator*=(const T& value)
{
	_x *= value;
	_y *= value;
	return *this;
}

template<class T>
Vector<T>& Vector<T>::operator*=(const Vector<T>& v)
{
	_x *= v._x;
	_y *= v._y;
	return *this;
}

template<class T>
Vector<T>& Vector<T>::operator/=(const Vector <T> &v)
{
	_x /= v._x;
	_y /= v._y;
	return *this;
}



template<class T>
T
Vector<T>::getNorm() const
{
	return std::sqrt(_x*_x + _y*_y);
}

template<class T>
void
Vector<T>::normalize()
{
	*this /= getNorm();
}

template<class T>
T
Vector<T>::dot(const Vector& v) const
{
	return _x * v._x + _y * v._y;
}

template<class T>
Vector<T>
Vector<T>::operator-() const
{
	Vector<T> t(-_x, -_y);
	return t;
}

template <class T>
Vector<T> operator+(const Vector<T> &v, const Vector<T> &v2)
{
	Vector<T> ret(v);
	return ret += v2;
}

template <class T>
Vector<T> operator-(const Vector<T> &v, const Vector<T> &v2)
{
	Vector<T> ret(v);
	return ret -= v2;
}

template <class T>
Vector<T> operator*(const Vector<T> &v, const Vector<T> &v2)
{
	Vector<T> ret(v);
	return ret *= v2;
}

template <class T>
Vector<T> operator/(const Vector<T> &v, const Vector<T> &v2)
{
	Vector<T> ret(v);
	return ret /= v2;
}

template <class T>
Vector<T> operator*(const Vector<T> &v, const T &val)
{
	Vector<T> ret(v);
	return ret *= val;
}

template <class T>
Vector<T> operator*(const T &val, const Vector<T> &v)
{
	return v * val;
}

template <class T>
Vector<T> operator/(const Vector<T> &v, const T &val)
{
	Vector<T> ret(v);
	return ret /= val;
}