#pragma once
#include "Vec3.h"

class Ray {
public:
	//Default constructor
	Ray() = default;

	//Constructor
	Ray(const Point3D &orig, const Vec3 &dir) : origin(orig), direction(dir) {}

	//Default destructor
	~Ray() = default; 

	//Return the ray origin
	Point3D get_origin() const {
		return origin;
	}

	//Reuturn the ray direction
	Vec3 get_direction() const {
		return direction;
	}

	//Linear interpolation, P(t) = A + tb where A is origin of the ray and b is the ray direction.
	Point3D at(double t) const {
		return origin + t * direction;
	}

private:
	Vec3 direction;
	Point3D origin;
};