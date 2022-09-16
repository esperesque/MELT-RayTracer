#include <iostream>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define __STDC_LIB_EXT1__
#include "stb_image_write.h"

#include "Vec3.h"
#include "ColorDBL.h"
#include "Ray.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Polygon.h"

bool hit_sphere(const Point3D& center, double radius, const Ray& r) {
    Vec3 oc = r.get_origin() - center;
    auto a = dot(r.get_direction(), r.get_direction());
    auto b = 2.0 * dot(oc, r.get_direction());
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;
    return (discriminant > 0);
}

ColorDBL ray_color(const Ray& r) {
    // This returns a pixel color that varies depending on height (z)
    if (hit_sphere(Point3D(1, 0.0, 0.0), 0.5, r))
        return ColorDBL(1, 0, 0);
    Vec3 unit_direction = unit_vector(r.get_direction());
    auto t = 0.5 * (unit_direction.get_z() + 1.0);
    return ColorDBL(Vec3((1.0 - t) * Vec3(1, 1, 1) + t * Vec3(0.5, 0.7, 1)));
}

ColorDBL ray_triangle_test(const Ray& r) {

    //Create a list of object containing 100 slots.
    Polygon* object_list[100];

    int index = 0;
    //Add rectangles and triangles to our object to create our world.
    object_list[index++] = new Rectangle{ Point3D(0, -6, 5), Point3D(0, 6, 5), Point3D(10, -6, 5), Point3D(10, 6, 5), ColorDBL{1,0,0}, false };        //Tak-rektangle
    object_list[index++] = new Rectangle{ Point3D(0, -6, -5), Point3D(10, -6, -5), Point3D(0, 6, -5), Point3D(10, 6, -5), ColorDBL{0.5,0.5,0}, false };    //Golv-rektangle
    object_list[index++] = new Rectangle{ Point3D(10, 6, -5), Point3D(13, 0, -5), Point3D(10, 6, 5), Point3D(13, 0, 5), ColorDBL{1,1,1}, true };      //Vägg-HögerFram
    object_list[index++] = new Rectangle{ Point3D(13, 0, -5), Point3D(10, -6, -5), Point3D(13, 0, 5), Point3D(10, -6, 5), ColorDBL{1,1,1}, true };    //Vägg-VänsterFram
    object_list[index++] = new Rectangle{ Point3D(0, 6, -5), Point3D(10, 6, -5), Point3D(0, 6, 5), Point3D(10, 6, 5), ColorDBL{0.5,0.5,0.8}, false };        //Vägg-Höger
    object_list[index++] = new Rectangle{ Point3D(0, -6, -5), Point3D(10, -6, -5), Point3D(0, -6, 5), Point3D(10, -6, 5), ColorDBL{0.3,1,0.5}, false };    //Vägg-Vänster
    object_list[index++] = new Rectangle{ Point3D(-3, 0, -5), Point3D(0, 6, -5), Point3D(-3, 0, 5), Point3D(0, 6, 5), ColorDBL{0.8,0.2, 0.6}, false };        //Vägg-HögerBak
    object_list[index++] = new Rectangle{ Point3D(0, -6, -5), Point3D(-3, 0, -5), Point3D(0, -6, 5), Point3D(-3, 0, 5), ColorDBL{1,0.5,0}, false };      //Vägg-VänsterBak
    object_list[index++] = new Triangle{ Point3D(10, -6, -5), Point3D(13, 0, -5), Point3D(10, 6, -5), ColorDBL{0,1,0}, false };                         //Golv-Triangle
    object_list[index++] = new Triangle{ Point3D(0, -6, -5), Point3D(0, 6, -5), Point3D(-3, 0, -5), ColorDBL{0,0,1}, false };                           //Golv-Triangle2
    object_list[index++] = new Triangle{ Point3D(10, -6, 5), Point3D(10, 6, 5), Point3D(13, 0, 5), ColorDBL{0,1,1}, false };                            //Tak-Triangle
    object_list[index++] = new Triangle{ Point3D(0, -6, 5), Point3D(-3, 0, 5), Point3D(0, 6, 5), ColorDBL{1,1,0}, false };                             //Tak-Triangle2

    //Give the pixel the color of the hit object.
    for (int i = 0; i < index; i++) {
        if (object_list[i]->collision(r)) {
            /*TA BORT KOMMENTARERNA FÖR ATT SÄTTA PÅ SPEGLINGEN*/


            //If the object we hit is a mirror we should send a reflected ray and give the mirror the color of the object the reflected ray hits. 
            /*if (object_list[i]->mirror()) {
                //Calculate the reflected ray.
                //Formula is: d - 2(dot(d,n))n
                Ray reflectedRay(unit_vector(r.at(1)), unit_vector(r.get_direction() - 2 * dot(r.get_direction(), object_list[i]->get_Normalized_normal()) * object_list[i]->get_Normalized_normal()));

                //check if the reflected ray hits an object.
                for (int j = 0; j < index; j++) {

                    if (object_list[j]->collision(reflectedRay)) {
                        ColorDBL myColor = object_list[j]->get_Color();
                        //Return the color of the object our reflected ray hits.
                        return myColor;
                    }
                }
            }*/
            return object_list[i]->get_Color();
        }
    }
    //no object found, pixel should be black
    return ColorDBL(0, 0, 0);
}

int main()
{
    //Define image size and number of color channels.
    const int IMAGE_WIDTH = 800;
    const int IMAGE_HEIGHT = 800;
    const int CHANNEL_NUM = 3;

    uint8_t* pixels = new uint8_t[IMAGE_WIDTH * IMAGE_HEIGHT * CHANNEL_NUM];

    int index = 0;

    // Tests
    /*Vec3 myVec(1, 2, -3);
    std::cout << "My vector has a coordinate, it's " << myVec;
    */

    // viewport stuff - move to Camera Class later!
    Point3D eye_position = Point3D(-1, 0, 0); //Define eye position
    auto viewport_width = 2;
    auto viewport_height = 2;
    auto focal_length = 1;
    auto horizontal = Vec3(0, viewport_width, 0); //Define horizontal direction (y)
    auto vertical = Vec3(0, 0, viewport_height); //Define vertical direction (z)
    auto lower_left_corner = eye_position - horizontal / 2 - vertical / 2 + Vec3(focal_length, 0, 0); //Lower left corner, should return (0, -1, -1)

    //std::cout << "Lower left corner position: " << lower_left_corner << "\n";

    for (int i = IMAGE_HEIGHT - 1; i >= 0; i--) {
        //std::cout << "\rScanlines remaining: " << i << ' ' << std::flush;
        for (int j = 0; j < IMAGE_WIDTH; j++) {
            auto u = double(j) / (IMAGE_WIDTH - 1);
            auto v = double(i) / (IMAGE_HEIGHT - 1);
            Ray r(unit_vector(eye_position), unit_vector(lower_left_corner + u * horizontal + v * vertical - eye_position));
            ColorDBL pixel_color = ray_triangle_test(r);

            pixels[index++] = pixel_color.get_int_r();
            pixels[index++] = pixel_color.get_int_g();
            pixels[index++] = pixel_color.get_int_b();
        }
    }

    stbi_write_png("result.png", IMAGE_WIDTH, IMAGE_HEIGHT, CHANNEL_NUM, pixels, IMAGE_WIDTH * CHANNEL_NUM);

    std::cout << "Render complete.";
}