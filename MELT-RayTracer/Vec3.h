#pragma once

#include <iostream>
#include <cmath>

using std::sqrt;
using std::pow;

class Vec3 {
public:
	//Default construtor
	Vec3() : x(0), y(0), z(0) {}

	//Construtor
	Vec3(float x0, float y0, float z0) : x(x0), y(y0), z(z0) {}

	//Default destructor
	~Vec3() = default;

	//Return the x-value
	float get_x() const {
		return x;
	}

	//Return the y-value
	float get_y() const {
		return y;
	}

	//Return the z-value
	float get_z() const {
		return z;
	}

	//Some random shit operator.
	Vec3 operator-() const {
		return Vec3(-x, -y, -z);
	}
	
	//Operator for addition
	Vec3& operator+=(const Vec3& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	//Operator for multiplication
	Vec3& operator*=(const float t) {
		x *= t;
		y *= t;
		z *= t;
		return *this;
	}

	//Operator for division.
	Vec3& operator/=(const float t) {
		return *this *= 1 / t;
	}

	//used for normalizing. Return the denominator.
	float length() const {
		return sqrt((pow(x, 2) + pow(y, 2) + pow(z, 2)));
	}

	// Utility functions

	//Used for printing to console.
	inline friend std::ostream& operator<<(std::ostream& out, const Vec3& v) {
		return out << v.x << ' ' << v.y << ' ' << v.z;
	}

	inline friend Vec3 operator+(const Vec3& u, const Vec3& v) {
		return Vec3(u.x + v.x, u.y + v.y, u.z + v.z);
	}

	inline friend Vec3 operator-(const Vec3& u, const Vec3& v) {
		return Vec3(u.x - v.x, u.y - v.y, u.z - v.z);
	}

	inline friend Vec3 operator*(const Vec3& u, const Vec3& v) {
		return Vec3(u.x * v.x, u.y * v.y, u.z * v.z);
	}

	inline friend Vec3 operator*(float t, const Vec3& v) {
		return Vec3(t * v.x, t * v.y, t * v.z);
	}

	inline friend Vec3 operator*(const Vec3& v, float t) {
		return t * v;
	}

	inline friend Vec3 operator/(Vec3 v, float t) {
		return (1 / t) * v;
	}

	//Calculate the dot product.
	inline friend float dot(const Vec3& u, const Vec3& v) {
		return u.x * v.x + u.y * v.y + u.z * v.z;
	}

	//Calculate the cross product.
	inline friend Vec3 cross(const Vec3& u, const Vec3& v) {
		return Vec3(u.y * v.z - u.z * v.y, 
					u.z * v.x - u.x * v.z, 
					u.x * v.y - u.y * v.x);
	}

	//Normalize the vector
	inline friend Vec3 unit_vector(Vec3 v) {
		return v / v.length();
	}

private:
	float x;
	float y;
	float z;
};

//Type alias
using Point3D = Vec3;


