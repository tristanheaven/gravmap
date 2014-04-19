#include <math.h>
#include "core_math.h"
#include "astro_math.h"


void Moon_pos(double Moon[3], double jdate){

    double gm, gm2, gm3, fm, fm2, rasc, decl, atr, djd, t;
    double em, em2, em4, gs, lv, lm, ls, rm, l, plon, plat, rmm, a, b, obliq, r;
    atr = M_PI / 648000;

    djd = jdate - 2451545;

    t = (djd / 36525) + 1;

    gm = r2r(0.374897 + 0.03629164709 * djd);
    gm2 = 2 * gm;
    gm3 = 3 * gm;
    fm = r2r(0.259091 + 0.0367481952 * djd);
    fm2 = 2 * fm;
    em = r2r(0.827362 + 0.03386319198 * djd);
    em2 = 2 * em;
    em4 = 4 * em;
    gs = r2r(0.993126 + 0.0027377785 * djd);
    lv = r2r(0.505498 + 0.00445046867 * djd);
    lm = r2r(0.606434 + 0.03660110129 * djd);
    ls = r2r(0.779072 + 0.00273790931 * djd);
    rm = r2r(0.347343 - 0.00014709391 * djd);


    l = 22640 * sin(gm) - 4586 * sin(gm - em2) + 2370 * sin(em2);
    l = l + 769 * sin(gm2) - 668 * sin(gs) - 412 * sin(fm2);
    l = l - 212 * sin(gm2 - em2) - 206 * sin(gm - em2 + gs);
    l = l + 192 * sin(gm + em2) + 165 * sin(em2 - gs);
    l = l + 148 * sin(gm - gs) - 125 * sin(em) - 110 * sin(gm + gs);
    l = l - 55 * sin(fm2 - em2) - 45 * sin(gm + fm2) + 40 * sin(gm - fm2);
    l = l - 38 * sin(gm - em4) + 36 * sin(gm3) - 31 * sin(gm2 - em4);
    l = l + 28 * sin(gm - em2 - gs) - 24 * sin(em2 + gs) + 19 * sin(gm - em);
    l = l + 18 * sin(em + gs) + 15 * sin(gm + em2 - gs) + 14 * sin(gm2 + em2);
    l = l + 14 * sin(em4) - 13 * sin(gm3 - em2) - 17 * sin(rm);
    l = l - 11 * sin(gm + 16 * ls - 18 * lv) + 10 * sin(gm2 - gs) + 9 * sin(gm - fm2 - em2);
    l = l + 9 * (cos(gm + 16 * ls - 18 * lv) - sin(gm2 - em2 + gs)) - 8 * sin(gm + em);
    l = l + 8 * (sin(2 * (em - gs)) - sin(gm2 + gs)) - 7 * (sin(2 * gs) + sin(gm - 2 * (em - gs)) - sin(rm));
    l = l - 6 * (sin(gm - fm2 + em2) + sin(fm2 + em2)) - 4 * (sin(gm - em4 + gs) - t * cos(gm + 16 * ls - 18 * lv));
    l = l - 4 * (sin(gm2 + fm2) - t * sin(gm + 16 * ls - 18 * lv));
    l = l + 3 * (sin(gm - 3 * em) - sin(gm + em2 + gs) - sin(gm2 - em4 + gs) + sin(gm - 2 * gs) + sin(gm - em2 - 2 * gs));
    l = l - 2 * (sin(gm2 - em2 - gs) + sin(fm2 - em2 + gs) - sin(gm + em4));
    l = l + 2 * (sin(4 * gm) + sin(em4 - gs) + sin(gm2 - em));

    plon = lm + atr * l;


    b = 18461 * sin(fm) + 1010 * sin(gm + fm) + 1000 * sin(gm - fm);
    b = b - 624 * sin(fm - em2) - 199 * sin(gm - fm - em2) - 167 * sin(gm + fm - em2);
    b = b + 117 * sin(fm + em2) + 62 * sin(gm2 + fm) + 33 * sin(gm - fm + em2);
    b = b + 32 * sin(gm2 - fm) - 30 * sin(fm - em2 + gs) - 16 * sin(gm2 - em2 + fm);
    b = b + 15 * sin(gm + fm + em2) + 12 * sin(fm - em2 - gs) - 9 * sin(gm - fm - em2 + gs);
    b = b - 8 * (sin(fm + rm) - sin(fm + em2 - gs)) - 7 * sin(gm + fm - em2 + gs);
    b = b + 7 * (sin(gm + fm - gs) - sin(gm + fm - em4));
    b = b - 6 * (sin(fm + gs) + sin(3 * fm) - sin(gm - fm - gs));
    b = b - 5 * (sin(fm + em) + sin(gm + fm + gs) + sin(gm - fm + gs) - sin(fm - gs) - sin(fm - em));
    b = b + 4 * (sin(gm3 + fm) - sin(fm - em4)) - 3 * (sin(gm - fm - em4) - sin(gm - 3 * fm));
    b = b - 2 * (sin(gm2 - fm - em4) + sin(3 * fm - em2) - sin(gm2 - fm + em2) - sin(gm - fm + em2 - gs));

    plat = atr * (b + 2 * (sin(gm2 - fm - em2) + sin(gm3 - fm)));

    obliq = atr * (84428 - 47 * t + 9 * cos(rm));

    r = 60.36298 - 3.27746 * cos(gm) - .57994 * cos(gm - em2);
    r = r - .46357 * cos(em2) - .08904 * cos(gm2) + .03865 * cos(gm2 - em2);
    r = r - .03237 * cos(em2 - gs) - .02688 * cos(gm + em2) - .02358 * cos(gm - em2 + gs);
    r = r - .0203 * cos(gm - gs) + .01719 * cos(em) + .01671 * cos(gm + gs);
    r = r + .01247 * cos(gm - fm2) + .00704 * cos(gs) + .00529 * cos(em2 + gs);
    r = r - .00524 * cos(gm - em4) + .00398 * cos(gm - em2 - gs) - .00366 * cos(gm3);
    r = r - .00295 * cos(gm2 - em4) - .00263 * cos(em + gs) + .00249 * cos(gm3 - em2);
    r = r - .00221 * cos(gm + em2 - gs) + .00185 * cos(fm2 - em2) - .00161 * cos(2 * (em - gs));
    r = r + 0.00147 * cos(gm + fm2 - em2) - 0.00142 * cos(em4) + 0.00139 * cos(gm2 - em2 + gs);

    rmm = 6378.14 * (r - 0.00118 * cos(gm - em4 + gs) - 0.00116 * cos(gm2 + em2) - 0.0011 * cos(gm2 - gs));

    a = sin(plon) * cos(obliq) - tan(plat) * sin(obliq);
    b = cos(plon);

    rasc = atan3(a, b);

    decl = asin(sin(plat) * cos(obliq) + cos(plat) * sin(obliq) * sin(plon));

    Moon[0] = 1000 * rmm * cos(rasc) * cos(decl);
    Moon[1] = 1000 * rmm * sin(rasc) * cos(decl);
    Moon[2] = 1000 * rmm * sin(decl);
}

void Sun_pos(double Sun[3], double jdate){

    double rasc, decl, atr, djd, t, gs, lm, ls, g2, g4, g5, rm, plon, a, b;
    double obliq, rsm;

    atr = M_PI / 648000;

    djd = jdate - 2451545;

    t = (djd / 36525) + 1;

    gs = r2r(0.993126 + 0.0027377785 * djd);
    lm = r2r(0.606434 + 0.03660110129 * djd);
    ls = r2r(0.779072 + 0.00273790931 * djd);
    g2 = r2r(0.140023 + 0.00445036173 * djd);
    g4 = r2r(0.053856 + 0.00145561327 * djd);
    g5 = r2r(0.056531 + 0.00023080893 * djd);
    rm = r2r(0.347343 - 0.00014709391 * djd);


    plon = 6910 * sin(gs) + 72 * sin(2 * gs) - 17 * t * sin(gs);
    plon = plon - 7 * cos(gs - g5) + 6 * sin(lm - ls) + 5 * sin(4 * gs - 8 * g4 + 3 * g5);
    plon = plon - 5 * cos(2 * (gs - g2)) - 4 * (sin(gs - g2) - cos(4 * gs - 8 * g4 + 3 * g5));
    plon = plon + 3 * (sin(2 * (gs - g2)) - sin(g5) - sin(2 * (gs - g5)));
    plon = ls + atr * (plon - 17 * sin(rm));


    rsm = 149597870.691 * (1.00014 - 0.01675 * cos(gs) - 0.00014 * cos(2 * gs));

    obliq = atr * (84428 - 47 * t + 9 * cos(rm));

    a = sin(plon) * cos(obliq);
    b = cos(plon);

    rasc = atan3(a, b);
    decl = asin(sin(obliq) * sin(plon));

    Sun[0] = 1000 * rsm * cos(rasc) * cos(decl);
    Sun[1] = 1000 * rsm * sin(rasc) * cos(decl);
    Sun[2] = 1000 * rsm * sin(decl);
}
