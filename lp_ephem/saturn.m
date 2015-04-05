function rsaturn = saturn (jdate)

% true-of-date heliocentric, ecliptic
% position vector of Saturn

% input
    
%  jdate = julian day

% output

%  rsaturn = position vector of Saturn (kilometers)

% Orbital Mechanics with MATLAB

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

atr = pi / 648000;

rsaturn = zeros(3, 1);

% fundamental time arguments

djd = jdate - 2451545;

t = djd / 36525 + 1;

% fundamental trig arguments (radians)

g5 = r2r(0.056531 + 0.00023080893 * djd);
l6 = r2r(0.133295 + 0.00009294371 * djd);
g6 = r2r(0.882987 + 0.00009294371 * djd);
g7 = r2r(0.400589 + 0.00003269438 * djd);

% heliocentric ecliptic longitude (radians)

pl = 23045 * sin(g6) + 5014 * t - 2689 * cos(2 * g5 - 5 * g6) + 2507;
pl = pl + 1177 * sin(2 * g5 - 5 * g6) - 826 * cos(2 * g5 - 4 * g6);
pl = pl + 802 * sin(2 * g6) + 425 * sin(g5 - 2 * g6);
pl = pl - 229 * t * cos(g6) - 153 * cos(2 * g5 - 6 * g6);
pl = pl - 142 * t * sin(g6) - 114 * cos(g6);
pl = pl + 101 * t * sin(2 * g5 - 5 * g6) - 70 * cos(2 * l6);
pl = pl + 67 * sin(2 * l6) + 66 * sin(2 * g5 - 6 * g6);
pl = pl + 60 * t * cos(2 * g5 - 5 * g6) + 41 * sin(g5 - 3 * g6);
pl = pl + 39 * sin(3 * g6) + 31 * sin(g5 - g6);
pl = pl + 31 * sin(2 * g5 - 2 * g6) - 29 * cos(2 * g5 - 3 * g6);
pl = pl - 28 * sin(2 * g5 - 6 * g6 + 3 * g7) + 28 * cos(g5 - 3 * g6);
pl = pl + 22 * t * sin(2 * g5 - 4 * g6) - 22 * sin(g6 - 3 * g7);
pl = pl + 20 * sin(2 * g5 - 3 * g6) + 20 * cos(4 * g5 - 10 * g6);
pl = pl + 19 * cos(2 * g6 - 3 * g7) + 19 * sin(4 * g5 - 10 * g6);
pl = pl - 17 * t * cos(2 * g6) - 16 * cos(g6 - 3 * g7);
pl = pl - 12 * sin(2 * g5 - 4 * g6) + 12 * cos(g5);
pl = pl - 12 * sin(2 * g6 - 2 * g7) - 11 * t * sin(2 * g6);
pl = pl - 11 * cos(2 * g5 - 7 * g6) + 10 * sin(2 * g6 - 3 * g7);
pl = pl + 10 * cos(2 * g5 - 2 * g6) + 9 * sin(4 * g5 - 9 * g6);
pl = pl - 8 * sin(g6 - 2 * g7) - 8 * cos(2 * l6 + g6);
pl = pl + 8 * cos(2 * l6 - g6) + 8 * cos(g6 - g7);
pl = pl - 8 * sin(2 * l6 - g6) + 7 * sin(2 * l6 + g6);
pl = pl - 7 * cos(g5 - 2 * g6) - 7 * cos(2 * g6);
pl = pl - 6 * t * sin(4 * g5 - 10 * g6) + 6 * cos(4 * g5 - 10 * g6) * t;
pl = pl + 6 * t * sin(2 * g5 - 6 * g6) - 5 * sin(3 * g5 - 7 * g6);
pl = pl - 5 * cos(3 * g5 - 3 * g6) - 5 * cos(2 * g6 - 2 * g7);
pl = pl + 5 * sin(3 * g5 - 4 * g6) + 5 * sin(2 * g5 - 7 * g6);
pl = pl + 4 * sin(3 * g5 - 3 * g6) + 4 * sin(3 * g5 - 5 * g6);
pl = pl + 4 * cos(g5 - 2 * g6) * t + 3 * t * cos(2 * g5 - 4 * g6);
pl = pl + 3 * cos(2 * g5 - 6 * g6 + 3 * g7) - 3 * t * sin(2 * l6);
pl = pl + 3 * cos(2 * g5 - 6 * g6) * t - 3 * t * cos(2 * l6);
pl = pl + 3 * cos(3 * g5 - 7 * g6) + 3 * cos(4 * g5 - 9 * g6);
pl = pl + 3 * sin(3 * g5 - 6 * g6) + 3 * sin(2 * g5 - g6);
pl = pl + 3 * sin(g5 - 4 * g6) + 2 * cos(3 * g6 - 3 * g7);
pl = pl + 2 * t * sin(g5 - 2 * g6) + 2 * sin(4 * g6);
pl = pl - 2 * cos(3 * g5 - 4 * g6) - 2 * cos(2 * g5 - g6);
pl = pl - 2 * sin(2 * g5 - 7 * g6 + 3 * g7) + 2 * cos(g5 - 4 * g6);
pl = pl + 2 * cos(4 * g5 - 11 * g6) - 2 * sin(g6 - g7);
 
plon = l6 + atr * pl;
 
% heliocentric ecliptic latitude (radians)

plat = 8297 * sin(g6) - 3346 * cos(g6) + 462 * sin(2 * g6);
plat = plat - 189 * cos(2 * g6) + 185 + 79 * t * cos(g6);
plat = plat - 71 * cos(2 * g5 - 4 * g6) + 46 * sin(2 * g5 - 6 * g6);
plat = plat - 45 * cos(2 * g5 - 6 * g6) + 29 * sin(3 * g6);
plat = plat - 20 * cos(2 * g5 - 3 * g6) + 18 * t * sin(g6);
plat = plat - 14 * cos(2 * g5 - 5 * g6) - 11 * cos(3 * g6) - 10 * t;
plat = plat + 9 * sin(g5 - 3 * g6) + 8 * sin(g5 - g6);
plat = plat - 6 * sin(2 * g5 - 3 * g6) + 5 * sin(2 * g5 - 7 * g6);
plat = plat - 5 * cos(2 * g5 - 7 * g6) + 4 * sin(2 * g5 - 5 * g6);
plat = plat - 4 * sin(2 * g6) * t - 3 * cos(g5 - g6);
plat = plat + 3 * cos(g5 - 3 * g6) + 3 * t * sin(2 * g5 - 4 * g6);
plat = plat + 3 * sin(g5 - 2 * g6) + 2 * sin(4 * g6);
plat = plat - 2 * cos(2 * g5 - 2 * g6);
  
plat = atr * plat;

% heliocentric distance (kilometers)

r = 9.55774 - 0.53252 * cos(g6) - 0.01878 * sin(2 * g5 - 4 * g6);
r = r - 0.01482 * cos(2 * g6) + 0.00817 * sin(g5 - g6);
r = r - 0.00539 * cos(g5 - 2 * g6) - 0.00524 * t * sin(g6);
r = r + 0.00349 * sin(2 * g5 - 5 * g6) + 0.00347 * sin(2 * g5 - 6 * g6);
r = r + 0.00328 * t * cos(g6) - 0.00225 * sin(g6);
r = r + 0.00149 * cos(2 * g5 - 6 * g6) - 0.00126 * cos(2 * g5 - 2 * g6);
r = r + 0.00104 * cos(g5 - g6) + 0.00101 * cos(2 * g5 - 5 * g6);
r = r + 0.00098 * cos(g5 - 3 * g6) - 0.00073 * cos(2 * g5 - 3 * g6);
r = r - 0.00062 * cos(3 * g6) + 0.00042 * sin(2 * g6 - 3 * g7);
r = r + 0.00041 * sin(2 * g5 - 2 * g6) - 0.0004 * sin(g5 - 3 * g6);
r = r + 0.0004 * cos(2 * g5 - 4 * g6) - 0.00028 * t - 0.00023 * sin(g5);
r = 149597870.691 * (r + 0.0002 * sin(2 * g5 - 7 * g6));
   
% heliocentric ecliptic position vector (kilometers)

rsaturn(1) = r * cos(plat) * cos(plon);
rsaturn(2) = r * cos(plat) * sin(plon);
rsaturn(3) = r * sin(plat);
 
