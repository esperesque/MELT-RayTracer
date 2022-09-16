#pragma once
#include "Vec3.h"

class ColorDBL {
public:
	//Default constructor
	ColorDBL() : r(0), g(0), b(0) {}

	//Constructor
	ColorDBL(const double &r0, const double &g0, const double &b0) : r(r0), g(g0), b(b0) {}

	//Constructor from Vec3 to RGB
	ColorDBL(const Vec3& v) : r(v.get_x()), g(v.get_y()), b(v.get_z()) {
	}

	//Default destructor
	~ColorDBL() = default;

	void friend write_color(const ColorDBL &pixel_color) {
		std::cout << "\nRed: " << pixel_color.r;
		std::cout << "\nGreen: " << pixel_color.g;
		std::cout << "\nBlue: " << pixel_color.b;
	}

	//Return the red color channel
	int get_int_r(){
		return (int)255 * r;
	}

	//Return the green color channel
	int get_int_g() {
		return (int)255 * g;
	}

	//Return the blue color channel
	int get_int_b() {
		return (int)255 * b;
	}

private:
	double r;
	double g;
	double b;
};

