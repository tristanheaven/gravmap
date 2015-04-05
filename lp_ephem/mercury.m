function rmercury = mercury (jdate)

% true-of-date heliocentric, ecliptic
% position vector of Mercury

% input
    
%  jdate = julian date

% output

%  rmercury = position vector of Mercury (kilometers)

% Orbital Mechanics with MATLAB

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

atr = pi / 648000;

rmercury = zeros(3, 1);

% fundamental time arguments

djd = jdate - 2451545;

tjd = djd / 36525 + 1;

% fundamental trig arguments (radians)

l1 = r2r(0.700695 + 0.011367714 * djd);
g1 = r2r(0.485541 + 0.01136759566 * djd);
f1 = r2r(0.566441 + 0.01136762384 * djd);
g2 = r2r(0.140023 + 0.00445036173 * djd);

% heliocentric ecliptic longitude (radians)

pl = 84378 * sin(g1) + 10733 * sin(2 * g1);
pl = pl + 1892 * sin(3 * g1) - 646 * sin(2 * f1);
pl = pl + 381 * sin(4 * g1) - 306 * sin(g1 - 2 * f1);
pl = pl - 274 * sin(g1 + 2 * f1) - 92 * sin(2 * g1 + 2 * f1);
pl = pl + 83 * sin(5 * g1) - 28 * sin(3 * g1 + 2 * f1);
pl = pl + 25 * sin(2 * g1 - 2 * f1) + 19 * sin(6 * g1);
pl = pl - 9 * sin(4 * g1 + 2 * f1) + 8 * tjd * sin(g1);
pl = pl + 7 * cos(2 * g1 - 5 * g2);
   
plon = l1 + atr * pl;

% heliocentric ecliptic latitude (radians)

pb = 24134 * sin(f1) + 5180 * sin(g1 - f1);
pb = pb + 4910 * sin(g1 + f1) + 1124 * sin(2 * g1 + f1);
pb = pb + 271 * sin(3 * g1 + f1) + 132 * sin(2 * g1 - f1);
pb = pb + 67 * sin(4 * g1 + f1) + 18 * sin(3 * g1 - f1);
pb = pb + 17 * sin(5 * g1 + f1) - 10 * sin(3 * f1);
pb = pb - 9 * sin(g1 - 3 * f1);

plat = atr * pb;

% heliocentric distance (kilometers)

pr = 0.39528 - 0.07834 * cos(g1) - 0.00795 * cos(2 * g1);
pr = pr - 0.00121 * cos(3 * g1) - 0.00022 * cos(4 * g1);

r = 149597870.691 * pr;

% heliocentric ecliptic position vector (kilometers)

rmercury(1) = r * cos(plat) * cos(plon);
rmercury(2) = r * cos(plat) * sin(plon);
rmercury(3) = r * sin(plat);
