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

int ectoeq(double cord[3], double obliq){

    cord[0] = cord[0];
    cord[1] = cord[1]*cos(obliq) - cord[2]*sin(obliq);
    cord[2] = cord[1]*sin(obliq) + cord[2]*cos(obliq);

    return 0;
}


double r2r(double x){
    double y;
    y = 2.0 * M_PI * (x - trunc(x));
    return y;
}


double atan3(double a, double b){

    double epsilon, pidiv2, c, y;
    epsilon = 0.0000000001;

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
    double m_sep, s_sep, surface_polar[2];
    int row;

    surface_polar[0] = atan(surface_cart[1]/surface_cart[0]);
    surface_polar[1] = acos(surface_cart[2]/Earth_rad);


    for(row = 0; row < 3; row = row +1){
        Moon_dist[row] = surface_cart[row] + Moon[row];
        Sun_dist[row] = surface_cart[row] + Sun[row];
    }

    anom_m1 = ((G * Moon_mass)/(modu(Moon)*modu(Moon)));
    anom_m2 = ((G * Moon_mass)/(modu(Moon_dist)*modu(Moon_dist)));
    anom_s1 = ((G * Sun_mass)/(modu(Sun)*modu(Sun)));
    anom_s2 = ((G * Sun_mass)/((modu(Sun_dist))*(modu(Sun_dist))));


/*
    printf("cos m = %lf",cos(m_sep));
    printf("cos s = %lf", cos(s_sep));
*/
    anom_m = /*cos(m_sep)*/  (anom_m1 - anom_m2);
    anom_s = /*cos(s_sep)*/  (anom_s1 - anom_s2);

    anom_net = anom_m + anom_s;

    return anom_net;
}


double modu(double vec[3]){
    double mod, premod;
    premod = (vec[0] * vec[0]) + (vec[1] * vec[1]) + (vec[2] * vec[2]);

    mod = sqrt(premod);

    return mod;
}



int polar_to_cart(double surface_polar[2], double surface_cart[3]){
    surface_cart[0] = Earth_rad * sin(surface_polar[0]) * cos(surface_polar[1]);
    surface_cart[1] = Earth_rad * sin(surface_polar[0]) * sin(surface_polar[1]);
    surface_cart[2] = Earth_rad * cos(surface_polar[0]);

    return 0;
}

int colour(struct rgb img_data[256][256], int x, int y, int z, double jdate){
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

            surface_polar[1] = 0.017453 * (((x + cold/256) / n) * 360.0 - 180.0);
            surface_polar[0] = atan(sinh(M_PI * (1 - 2 * (y + rowd/256) / n)));

            polar_to_cart(surface_polar, surface_cart);

            anom = anomcalc(surface_cart, Moon, Sun);

            heat = (anom + 1.8e-6)/(3.6e-6);

            if(heat < 0.5){
                double Db, Dg;
                Db = (-512.0 * heat + 256.0);
                Dg = 512.0 * heat;

                img_data[row][col].b = (Db<0)?0:(Db>255)?255:(uint8_t)(Db);
                img_data[row][col].g = (Dg<0)?0:(Dg>255)?255:(uint8_t)(Dg);
                img_data[row][col].r = 0;
            }
            else{
                double Dg, Dr;
                Dg = (-512.0 * heat + 512.0);
                Dr = (512.0 * heat - 256.0);

                img_data[row][col].b = 0;
                img_data[row][col].g = (Dg<0)?0:(Dg>255)?255:(uint8_t)(Dg);
                img_data[row][col].r = (Dr<0)?0:(Dr>255)?255:(uint8_t)(Dr);
            }

        }
    }

    return 0;

}


/*
int geoidcolour(struct rgb img_data[256][256], int x, int y, int z){
    double heat, anom, surface_cart[3], lat_rad;
    double surface_polar[2], rowd, cold;
    int row, col, n;

    n = 2 ^ z;

    for(row = 0; row < 256; row = row + 1){
        for(col = 0; col < 256; col = col + 1){
            rowd = row;
            cold = col;

            surface_polar[1] = 0.017453 * (((x + cold/256) / n) * 360.0 - 180.0);
            surface_polar[0] = atan(sinh(M_PI * (1 - 2 * (y + rowd/256) / n)));

            polar_to_cart(surface_polar, surface_cart);

            anom = geoidcalc(surface_polar);

            heat = (anom + 1.65e-6)/(3.3e-6);

            if(heat < 0.5){
                img_data[row][col].b = -512 * heat + 256;
                img_data[row][col].g = 512 * heat;
                img_data[row][col].r = 0;
            }
            else{
                img_data[row][col].b = 0;
                img_data[row][col].g = -512 * heat + 512;
                img_data[row][col].r = 512 * heat - 256;
            }
        }
    }

    return 0;

}



double anglesep(double vector[3], double surface_polar[2]){
    double thetav, phiv, A, delt_theta;



    surface_polar[0] = 0.017453 * surface_polar[0];
    surface_polar[1] = 0.017453 * surface_polar[1];

    thetav = acos(vector[2]/sqrt(vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2]));
    phiv = atan(vector[1]/vector[0]);

    delt_theta = thetav - surface_polar[1];

    A = acos(sin(phiv) * sin(surface_polar[0]) + cos(phiv) * cos(surface_polar[0]) * cos(delt_theta));

    return A;
}
*/
