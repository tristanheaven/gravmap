% demo_lpe       July 10, 2013

% this script demonstrates how to use
% the low-precision ephemeris functions

% Orbital Mechanics with MATLAB

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

clear all;

% define target body name vector

pdata = ['Mercury              '; ...
    'Venus                '; ...
    'Earth                '; ...
    'Mars                 '; ...
    'Jupiter              '; ...
    'Saturn               '; ...
    'Uranus               '; ...
    'Neptune              '; ...
    'Pluto                '; ...
    'Moon                 '; ...
    'Sun                  '];

tname = cellstr(pdata);

% conversion factor - radians to degrees

rtd = 180.0 / pi;

clc; home;

fprintf('\ndemo_lpe - demonstrates how to use the low-precision ephemeris functions\n');

% request calendar date

[month, day, year] = getdate;

jdutc = julian(month, day, year);

% select target body

fprintf('\n    celestial body menu\n');

fprintf('\n  <1> Mercury');
fprintf('\n  <2> Venus');
fprintf('\n  <3> Earth');
fprintf('\n  <4> Mars');
fprintf('\n  <5> Jupiter');
fprintf('\n  <6> Saturn');
fprintf('\n  <7> Uranus');
fprintf('\n  <8> Neptune');
fprintf('\n  <9> Pluto');
fprintf('\n  <10> Moon');
fprintf('\n  <11> Sun');

for ity = 1:1:5
    
    fprintf('\n\nplease select the celestial body\n');
    
    ibody = input('? ');
    
    if (ibody >= 1 && ibody <= 11)
        break;
    end
    
end

% evaluate ephemeris

switch ibody
    
    case 1
        
        % mercury
        
        rhelio = mercury (jdutc);
        
    case 2
        
        % venus
        
        rhelio = venus (jdutc);
        
    case 3
        
        % earth
        
        rhelio = earth (jdutc);
        
    case 4
        
        % mars
        
        rhelio = mars (jdutc);
        
    case 5
        
        % jupiter
        
        rhelio = jupiter (jdutc);
        
    case 6
        
        % saturn
        
        rhelio = saturn (jdutc);
        
    case 7
        
        % uranus
        
        rhelio = uranus (jdutc);
        
    case 8
        
        % neptune
        
        rhelio = neptune (jdutc);
        
    case 9
        
        % pluto
        
        rhelio = pluto (jdutc);
        
    case 10
        
        % moon
        
        [rasc, decl, rgeo] = moon (jdutc);
        
    case 11
        
        % sun
        
        [rasc, decl, rgeo] = sun1 (jdutc);
end

% print results

fprintf('\n\nprogram demo_lpe\n');

fprintf('\ncelestial body    ');

disp(tname(ibody));

[cdstr, utstr] = jd2str(jdutc);

fprintf('\nUTC calendar date       ');

disp(cdstr);

fprintf('\nUTC Julian date         %12.6f \n', jdutc);

if (ibody >= 1 && ibody <= 9)
    
    fprintf('\nheliocentric, ecliptic position vector and magnitude\n');
    
    fprintf ('\n        rx (km)                 ry (km)                rz (km)                rmag (km)');
    
    fprintf ('\n %+16.14e  %+16.14e  %+16.14e  %+16.14e  \n', rhelio(1), rhelio(2), rhelio(3), norm(rhelio));
    
    fprintf('\n');
    
end

if (ibody > 9)
    
    fprintf('\ngeocentric declination       %12.6f degrees\n', rtd * decl);
    
    fprintf('\ngeocentric right ascension   %12.6f degrees\n', rtd * rasc);
    
    fprintf('\ngeocentric, equatorial position vector and magnitude\n');
    
    fprintf ('\n        rx (km)                 ry (km)                rz (km)                rmag (km)');
    
    fprintf ('\n %+16.14e  %+16.14e  %+16.14e  %+16.14e  \n', rgeo(1), rgeo(2), rgeo(3), norm(rgeo));
    
    fprintf('\n');
    
end



