function rjupiter = jupiter (jdate)

% true-of-date heliocentric, ecliptic
% position vector of Jupiter

% input
    
%  jdate = julian day

% output

%  rjupiter = position vector of Jupiter (kilometers)

% Orbital Mechanics with MATLAB

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

atr = pi / 648000;

rjupiter = zeros(3, 1);

% fundamental time arguments

djd = jdate - 2451545;

t = djd / 36525 + 1;

% fundamental trig arguments (radians)

l5 = r2r(0.089608 + 0.00023080893 * djd);
g5 = r2r(0.056531 + 0.00023080893 * djd);
g6 = r2r(0.882987 + 0.00009294371 * djd);
g7 = r2r(0.400589 + 0.00003269438 * djd);

% heliocentric ecliptic longitude (radians)

pl = 19934 * sin(g5) + 5023 * t + 2511 + 1093 * cos(2 * g5 - 5 * g6);
pl = pl + 601 * sin(2 * g5) - 479 * sin(2 * g5 - 5 * g6);
pl = pl - 185 * sin(2 * g5 - 2 * g6) + 137 * sin(3 * g5 - 5 * g6);
pl = pl - 131 * sin(g5 - 2 * g6) + 79 * cos(g5 - g6);
pl = pl - 76 * cos(2 * g5 - 2 * g6) - 74 * t * cos(g5);
pl = pl + 68 * t * sin(g5) + 66 * cos(2 * g5 - 3 * g6);
pl = pl + 63 * cos(3 * g5 - 5 * g6) + 53 * cos(g5 - 5 * g6);
pl = pl + 49 * sin(2 * g5 - 3 * g6) - 43 * t * sin(2 * g5 - 5 * g6);
pl = pl - 37 * cos(g5) + 25 * sin(2 * l5) + 25 * sin(3 * g5);
pl = pl - 23 * sin(g5 - 5 * g6) - 19 * t * cos(2 * g5 - 5 * g6);
pl = pl + 17 * cos(2 * g5 - 4 * g6) + 17 * cos(3 * g5 - 3 * g6);
pl = pl - 14 * sin(g5 - g6) - 13 * sin(3 * g5 - 4 * g6);
pl = pl - 9 * cos(2 * l5) + 9 * cos(g6) - 9 * sin(g6);
pl = pl - 9 * sin(3 * g5 - 2 * g6) + 9 * sin(4 * g5 - 5 * g6);
pl = pl + 9 * sin(2 * g5 - 6 * g6 + 3 * g7) - 8 * cos(4 * g5 - 10 * g6);
pl = pl + 7 * cos(3 * g5 - 4 * g6) - 7 * cos(g5 - 3 * g6);
pl = pl - 7 * sin(4 * g5 - 10 * g6) - 7 * sin(g5 - 3 * g6);
pl = pl + 6 * cos(4 * g5 - 5 * g6) - 6 * sin(3 * g5 - 3 * g6);
pl = pl + 5 * cos(2 * g6) - 4 * sin(4 * g5 - 4 * g6);
pl = pl - 4 * cos(3 * g6) + 4 * cos(2 * g5 - g6);
pl = pl - 4 * cos(3 * g5 - 2 * g6) - 4 * t * cos(2 * g5);
pl = pl + 3 * t * sin(2 * g5) + 3 * cos(5 * g6);
pl = pl + 3 * cos(5 * g5 - 10 * g6) + 3 * sin(2 * g6);
pl = pl - 2 * sin(2 * l5 - g5) + 2 * sin(2 * l5 + g5);
pl = pl - 2 * t * sin(3 * g5 - 5 * g6) - 2 * t * sin(g5 - 5 * g6);
    
plon = l5 + atr * pl;

% heliocentric ecliptic latitude (radians)

plat = -4692 * cos(g5) + 259 * sin(g5) + 227 - 227 * cos(2 * g5);
plat = plat + 30 * t * sin(g5) + 21 * t * cos(g5);
plat = plat + 16 * sin(3 * g5 - 5 * g6) - 13 * sin(g5 - 5 * g6);
plat = plat - 12 * cos(3 * g5) + 12 * sin(2 * g5);
plat = plat + 7 * cos(3 * g5 - 5 * g6) - 5 * cos(g5 - 5 * g6);
   
plat = atr * plat;

% heliocentric distance (kilometers)

r = 5.20883 - 0.25122 * cos(g5) - 0.00604 * cos(2 * g5);
r = r + 0.0026 * cos(2 * g5 - 2 * g6) - 0.0017 * cos(3 * g5 - 5 * g6);
r = r - 0.00106 * sin(2 * g5 - 2 * g6) - 0.00091 * t * sin(g5);
r = r - 0.00084 * t * cos(g5) + .00069 * sin(2 * g5 - 3 * g6);
r = r - 0.00067 * sin(g5 - 5 * g6) + 0.00066 * sin(3 * g5 - 5 * g6);
r = r + 0.00063 * sin(g5 - g6) - 0.00051 * cos(2 * g5 - 3 * g6);
r = r - 0.00046 * sin(g5) - 0.00029 * cos(g5 - 5 * g6);
r = r + 0.00027 * cos(g5 - 2 * g6) - 0.00022 * cos(3 * g5);
r = 149597870.691 * (r - 0.00021 * sin(2 * g5 - 5 * g6));

% heliocentric ecliptic position vector (kilometers)

rjupiter(1) = r * cos(plat) * cos(plon);
rjupiter(2) = r * cos(plat) * sin(plon);
rjupiter(3) = r * sin(plat);


