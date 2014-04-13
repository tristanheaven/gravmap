
#ifndef GRAVITY_MAP__CORE_MATH_H
#define GRAVITY_MAP__CORE_MATH_H
#include <stdint.h>
struct rgb{
    uint8_t r, g, b;
};
int colour(struct rgb img_data[256][256], int x, int y, int z, double jdate);
double r2r(double x);
double atan3(double a, double b);
double sign(double x);
int ectoeq(double cord[3], double obliq);
double modu(double vec[3]);
int polar_to_cart(double surface_polar[2], double surface_cart[3]);
double anomcalc(double surface_cart[3], double Moon[3], double Sun[3]);



#endif // GRAVITY_MAP__CORE_MATH_H
