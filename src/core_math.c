#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "core_math.h"
#include "astro_math.h"

#define G 6.67384e-11
#define Moon_mass (7.34767e22)
#define Sun_mass (1.99e30)
#define Earth_rad (6371000.0)

void ectoeq(double cord[3], double obliq){

    cord[0] = cord[0];
    cord[1] = cord[1]*cos(obliq) - cord[2]*sin(obliq);
    cord[2] = cord[1]*sin(obliq) + cord[2]*cos(obliq);
}


double r2r(double x){
    double y;
    y = 2.0 * M_PI * (x - trunc(x));
    return y;
}


double atan3(double a, double b){

    double epsilon, pidiv2, c, y;
    epsilon = 0.0000000001;
    c = 0;

    pidiv2 = 0.5 * M_PI;

    if (abs(a) < epsilon){
       y = (1 - sign(b)) * pidiv2;
    }
    else{
       c = (2 - sign(a)) * pidiv2;
    }

    if (abs(b) < epsilon){
       y = c;
    }
    else{
       y = c + sign(a) * sign(b) * (abs(atan(a / b)) - pidiv2);
    }
    return y;
}


double sign(double x){
    double y;
    if(x > 0){
        y = 1;
    }
    if(x == 0){
        y = 0;
    }
    if(x < 0){
        y = -1;
    }
    return y;
}


double anomcalc(double surface_cart[3], double Moon[3], double Sun[3]){
    double anom_m, anom_m1, anom_m2, anom_s, anom_s1, anom_s2, anom_net, Moon_dist[3], Sun_dist[3];
    double  surface_polar[2];
    int row;



    for(row = 0; row < 3; row = row +1){
        Moon_dist[row] = surface_cart[row] + Moon[row];
        Sun_dist[row] = surface_cart[row] + Sun[row];
    }

    anom_m1 = ((G * Moon_mass)/(modu(Moon)*modu(Moon)));
    anom_m2 = ((G * Moon_mass)/(modu(Moon_dist)*modu(Moon_dist)));
    anom_s1 = ((G * Sun_mass)/(modu(Sun)*modu(Sun)));
    anom_s2 = ((G * Sun_mass)/((modu(Sun_dist))*(modu(Sun_dist))));


    anom_m =  (anom_m1 - anom_m2);
    anom_s =  (anom_s1 - anom_s2);

    anom_net = anom_m + anom_s;

    return anom_net;
}


double modu(double vec[3]){
    double mod, premod;
    premod = (vec[0] * vec[0]) + (vec[1] * vec[1]) + (vec[2] * vec[2]);

    mod = sqrt(premod);

    return mod;
}


void polar_to_cart(double surface_polar[2], double surface_cart[3]){
    surface_cart[0] = Earth_rad * sin(surface_polar[0]) * cos(surface_polar[1]);
    surface_cart[1] = Earth_rad * sin(surface_polar[0]) * sin(surface_polar[1]);
    surface_cart[2] = Earth_rad * cos(surface_polar[0]);
}


void colour(struct rgb img_data[256][256], int x, int y, int z, double jdate){
    double heat, anom, surface_cart[3], Moon[3];
    double Sun[3], surface_polar[2], obliq, rowd, cold;
    int row, col, n;

    obliq = 23.4;
    obliq = obliq * 0.017453;
    n = pow(2, z);

    Moon_pos(Moon, jdate);
    Sun_pos(Sun, jdate);

    ectoeq(Moon, obliq);
    ectoeq(Sun, obliq);

    for(row = 0; row < 256; row = row + 1){
        for(col = 0; col < 256; col = col + 1){
            rowd = row;
            cold = col;

            // Testing swap to fix projection error
            surface_polar[0] = 0.017453 * (((x + cold/256) / n) * 360.0 - 180.0);
            surface_polar[1] = atan(sinh(M_PI * (1 - 2 * (y + rowd/256) / n)));

            polar_to_cart(surface_polar, surface_cart);

            anom = anomcalc(surface_cart, Moon, Sun);

            heat = (anom)/(1.87e-6);

            if(heat < 0){
                heat = 0;
            }
            if(heat > 1){
                heat = 1;
            }

            hue_assign(img_data, heat, row, col);
        }
    }
}


double gregorian_calendar_to_jd(int h, int d, int m, int y){
    double jdate, dd, hd, dadj;
    y+=8000;
    if(m<3) { y--; m+=12; }
    hd = h;
    return (y*365) +(y/4) -(y/100) +(y/400) -1200820 +(m*153+3)/5-92 +d-1 + (hd-12)/24;
}


void hue_assign(struct rgb img_data[256][256], double heat, int row, int col){
    if(heat <= 0.2){
        img_data[row][col].r = 250;
        img_data[row][col].g = 1225 * heat + 5;
        img_data[row][col].b = 5;
    }
    if((heat > 0.2)&&(heat <= 0.4)){
        img_data[row][col].r = -1225 * heat + 495;
        img_data[row][col].g = 250;
        img_data[row][col].b = 5;
    }
    if((heat > 0.4)&&(heat <= 0.6)){
        img_data[row][col].r = 5;
        img_data[row][col].g = 250;
        img_data[row][col].b = 1225 * heat - 485;
    }
    if((heat > 0.6)&&(heat <= 0.8)){
        img_data[row][col].r = 5;
        img_data[row][col].g = -1225 * heat + 985;
        img_data[row][col].b = 250;
    }
    if((heat > 0.8)&&(heat <= 1)){
        img_data[row][col].r = 1225 * heat -975;
        img_data[row][col].g = 5;
        img_data[row][col].b = 250;
    }
}
