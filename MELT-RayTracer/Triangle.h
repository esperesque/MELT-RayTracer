#pragma once
#include "Ray.h"
#include "Polygon.h"

class Triangle : public Polygon {
public:
	Triangle() = default;

	Triangle(Point3D v0, Point3D v1, Point3D v2, ColorDBL c, bool mirror) : vertex0{ v0 }, vertex1{ v1 }, vertex2{ v2 }, isMirror{ mirror }, color{ c } {
		//Calculate two edges and the normal
		edge1 = calculate_Edge(vertex0, vertex1); 
		edge2 = calculate_Edge(vertex0, vertex2);
		normal = calculate_Normal(edge1, edge2);
		normalized_normal = unit_vector(normal); //Normalize normal.
	}

	//Default destructor.
	~Triangle() = default;

	bool collision(const Ray& ray) const override {
		const float EPSILON = 1e-9; //a very small value used to check if determinant is close to 0.

		Vec3 P = cross(ray.get_direction(), edge2); //Get the vector that is orthogonal to the ray-direction and one of the edges.
		float determinant = dot(edge1, P);

		if (determinant > -EPSILON && determinant < EPSILON)
			return false; //This ray is parallell to the triangle. 

		Point3D startPoint = ray.get_origin() - vertex0;
		float invDet = 1 / determinant; //Inverse determinant. 
		float u = dot(startPoint, P) * invDet; //Create world coordinate u.
		if (u < 0 || u > 1)
			return false;

		Vec3 q = cross(startPoint, edge1);
		float v = invDet * dot(ray.get_direction(), q); //Create world coordinate v.
		if (v < 0 || u + v > 1)
			return false;

		//Compute t to find where the intersection point is on the line. 
		const float t = invDet * dot(edge2, q) ;
		if (t > EPSILON) { //ray intersection
			return true;
		}
		//This means there is a line intersection but not a ray intersection.
		return false;
	
	}

	//overrided bool to check if object is a mirror or not.
	bool mirror() const override {
		return isMirror;
	}

	//Used to calculate an edge from two vertices.
	Vec3 calculate_Edge(const Vec3& v1, const Vec3& v2) {
		return Vec3(v2 - v1);
	}

	//Used to calculate the normal from two edges.
	Vec3 calculate_Normal(const Vec3& e1, const Vec3& e2) {
		return cross(e1, e2);
	}

	//Return the normalized normal.
	Vec3 get_Normalized_normal() override{
		return normalized_normal;
	}

	//Return the first edge.
	Vec3 get_Edge1() {
		return edge1;
	}

	//Return the second edge.
	Vec3 get_Edge2() {
		return edge2;
	}

	//Return the color of our object.
	ColorDBL get_Color() override {
		return color;
	}

private:
	Point3D vertex0, vertex1, vertex2;
	Vec3 edge1, edge2;
	Vec3 normal, normalized_normal{ 0,0,0 }; 
	ColorDBL color{0,0,0};
	bool isMirror = false; //If we define an object as mirror it should reflect rays.
};
