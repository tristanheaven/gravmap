function rvenus = venus (jdate)

% true-of-date heliocentric, ecliptic
% position vector of venus

% input

%  jdate = julian day

% output

%  rvenus = position vector of venus (kilometers)

% Orbital Mechanics with MATLAB

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

atr = pi / 648000;

rvenus = zeros(3, 1);

% fundamental time arguments

djd = jdate - 2451545;

t = djd / 36525 + 1;

% fundamental trig arguments (radians)

gs = r2r(0.993126 + 0.0027377785 * djd);
l2 = r2r(0.505498 + 0.00445046867 * djd);
g2 = r2r(0.140023 + 0.00445036173 * djd);
f2 = r2r(0.292498 + 0.00445040017 * djd);

% heliocentric ecliptic longitude (radians)

pl = 2814 * sin(g2) - 181 * sin(2 * f2);
pl = pl - 20 * t * sin(g2) + 12 * sin(2 * g2);
pl = pl - 10 * cos(2 * gs - 2 * g2) + 7 * cos(3 * gs - 3 * g2);

plon = l2 + atr * pl;

% heliocentric ecliptic latitude (radians)

plat = 12215 * sin(f2) + 83 * sin(g2 + f2) + 83 * sin(g2 - f2);
plat = atr * plat;

% heliocentric distance (kilometers)

r = 149597870.691 * (0.72335 - 0.00493 * cos(g2));

% heliocentric ecliptic position vector (kilometers)

rvenus(1) = r * cos(plat) * cos(plon);
rvenus(2) = r * cos(plat) * sin(plon);
rvenus(3) = r * sin(plat);


