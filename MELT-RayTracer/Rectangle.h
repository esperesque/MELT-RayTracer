#pragma once
#include "Triangle.h"
#include "Polygon.h"

class Rectangle : public Polygon {
public:

	//Default constructor
	Rectangle() = default;

	//Constructor
	Rectangle(Point3D vertex0, Point3D vertex1, Point3D vertex2, Point3D vertex3, ColorDBL c, bool mirror)
		: v0{ vertex0 }, v1{ vertex1 }, v2{ vertex2 }, v3{ vertex3 }, color{ c }, isMirror{ mirror } {
		t1= {v0,v1,v2, color, isMirror};
		t2= {v1,v2,v3, color, isMirror};

		normalized_normal = t1.get_Normalized_normal();
	}

	//Default constructor
	~Rectangle() = default;

	bool collision(const Ray& ray) const override {
		if (t1.collision(ray) || t2.collision(ray))
			return true;
		
		return false;
	}

	//overrided bool to check if object is a mirror or not.
	bool mirror() const override {
		return isMirror;
	}

	//Return the normalized normal.
	Vec3 get_Normalized_normal() override {
		return normalized_normal;
	}

	//Return the color of our object.
	ColorDBL get_Color() override {
		return color;
	}

private:
	Point3D v0, v1, v2, v3;
	Triangle t1, t2;
	bool isMirror = false; //If we define an object as mirror it should reflect rays.
	ColorDBL color;
	Vec3 normalized_normal;
};