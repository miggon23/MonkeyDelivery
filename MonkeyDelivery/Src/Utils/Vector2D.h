#ifndef VECTOR2D_H_
#define VECTOR2D_H_

#include <iostream>
#include <math.h>

// needed for visual studio
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

template <typename T>
class Vector2D {
    T x;  // first coordinate
    T y;  // second coordinate
public:
    Vector2D();
    Vector2D(const Vector2D &v);
    Vector2D(T x, T y);
    virtual ~Vector2D() {};
    T getX() const;
    T getY() const;
    void setX(T x);
    void setY(T y);
    void set(const Vector2D<T> &v);
    void set(T x, T y);
    double magnitude() const;
    //void rotate(double degrees);
    //double angle(const Vector2D& v) const;
    void normalize();
    Vector2D<T> getInverse() const;

    bool operator==(const Vector2D<T>& v) const;
    bool operator!=(const Vector2D<T>& v) const;
    Vector2D operator-(const Vector2D<T>& v) const;
    Vector2D operator+(const Vector2D<T>& v) const;
    Vector2D operator*(double d) const;
    double operator*(const Vector2D<T>& d) const;
    Vector2D operator/(double d) const;
};

template <typename T>
using Point2D = Vector2D<T>;


template <typename T>
Vector2D<T>::Vector2D() : x(0), y(0) {}

template <typename T>
Vector2D<T>::Vector2D(const Vector2D& v) : x(v.x), y(v.y) {}

template <typename T>
Vector2D<T>::Vector2D(T x, T y) : x(x), y(y) {}

template <typename T>
T Vector2D<T>::getX() const {
    return x;
}

template <typename T>
T Vector2D<T>::getY() const {
    return y;
}

template <typename T>
void Vector2D<T>::setX(T x_) {
    x = x_;
}

template <typename T>
void Vector2D<T>::setY(T y_) {
    y = y_;
}

template <typename T>
void Vector2D<T>::set(const Vector2D<T>& v) {
    x = v.x;
    y = v.y;
}

template <typename T>
void Vector2D<T>::set(T x_, T y_) {
    x = x_;
    y = y_;
}

template <typename T>
double Vector2D<T>::magnitude() const {
    return sqrt(pow(x, 2) + pow(y, 2));
}

/*
void Vector2D::rotate(double degrees) {
	degrees = fmod(degrees, 360);
	if (degrees > 180) {
		degrees = degrees - 360;
	} else if (degrees <= -180) {
		degrees = 360 + degrees;
	}

	assert(degrees >= -180 && degrees <= 180);

	double angle = degrees * M_PI / 180;
	double sine = sin(angle);
	double cosine = cos(angle);

	//rotation matix
	double matrix[2][2] = { { cosine, -sine }, { sine, cosine } };

	double x = x;
	double y = y;

	x = matrix[0][0] * x + matrix[0][1] * y;
	y = matrix[1][0] * x + matrix[1][1] * y;

}

double Vector2D::angle(const Vector2D& v) const {

	double a2 = atan2(v.getX(), v.getY());
	double a1 = atan2(x, y);
	double sign = a1 > a2 ? 1 : -1;
	double angle = a1 - a2;
	double K = -sign * M_PI * 2;
	angle = (abs(K + angle) < abs(angle)) ? K + angle : angle;
	return angle * 180. / M_PI;
}
*/

template <typename T>
Vector2D<T> Vector2D<T>::getInverse() const {
    return Vector2D<T>(-x, -y);
}


template <typename T>
bool Vector2D<T>::operator==(const Vector2D<T>& v) const {
    return (x == v.x && y == v.y);
}

template <typename T>
bool Vector2D<T>::operator!=(const Vector2D<T>& v) const {
    return !(*this == v);
}

template <typename T>
void Vector2D<T>::normalize() {
    double mag = magnitude();
    if (mag > 0.0) {
        x = x / mag;
        y = y / mag;
    }
}

template <typename T>
Vector2D<T> Vector2D<T>::operator-(const Vector2D<T>& v) const {
    Vector2D<T> r;
    r.x = x - v.x;
    r.y = y - v.y;
    return r;
}

template <typename T>
Vector2D<T> Vector2D<T>::operator+(const Vector2D<T>& v) const {
    Vector2D<T> r;
    r.x = x + v.x;
    r.y = y + v.y;
    return r;
}

template <typename T>
Vector2D<T> Vector2D<T>::operator*(double d) const {
    Vector2D<T> r;
    r.x = x * d;
    r.y = y * d;
    return r;
}

template <typename T>
double Vector2D<T>::operator*(const Vector2D<T>& d) const {
    return d.x * x + d.y * y;
}

template <typename T>
Vector2D<T> Vector2D<T>::operator/(double d) const {
    Vector2D<T> r;
    r.x = x / d;
    r.y = y / d;
    return r;
}

#endif /* VECTOR2D_H_ */