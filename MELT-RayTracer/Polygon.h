#pragma once
#include "ColorDBL.h"
#include "Vec3.h"

class Polygon {
public:

	virtual bool collision(const Ray& ray) const {
		return false;
	}

	virtual bool mirror() const {
		return false;
	}

	virtual ColorDBL get_Color() {
		return ColorDBL{ 0,0,0 };
	}
	
	virtual Vec3 get_Normalized_normal() {
		return Vec3{ 0,0,0 };
	}

private:
};
