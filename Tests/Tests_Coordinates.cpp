#include "../Model/Coordinates.h"
#include <string>
#include <cmath>
#include <iostream>
using namespace std;

int test1_Coordinates()
{
    string coordStr = "44.0,-1.0";
    Coordinates coords = Coordinates::parseCoordinates(coordStr);
    if (coords.getLatitude() != 44.0 || coords.getLongitude() != -1.0) {
        cout << "Test1 failed: Coordinates do not match expected values." << endl;
        cout << "Expected: 44.0, -1.0" << endl;
        cout << "Got: " << coords.getLatitude() << ", " << coords.getLongitude() << endl;
        return 1;
    }

    return 0;
}

int test2_Coordinates()
{
    Coordinates c1(44.0, -1.0);
    Coordinates c2(54.0, 9.0);
    float dist = Coordinates::distance(c1, c2);
    if (abs(dist - 14.14) >= 0.1) {
        cout << "Test2 failed: Distance calculation is incorrect." << endl;
        cout << "Expected: 14.14 km\nGot: " << dist << " km" << endl;
        return 1;
    }

    return 0;
}

int testCoordinates()
{
    cout << "Running coordinates tests..." << endl;
    int resultat = 0;
    resultat += test1_Coordinates();
    resultat += test2_Coordinates();
    
    if (resultat == 0) {
        cout << "All tests passed successfully!" << endl << endl;
    } else {
        cout << resultat << " test(s) failed." << endl << endl;
    }

    return resultat;
}