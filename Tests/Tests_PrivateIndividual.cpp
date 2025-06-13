#include "../Model/PrivateIndividual.h"
#include <iostream>
#include <string>
using namespace std;

int test1_PrivateIndividual()
{
    PrivateIndividual user("TestUser", true, 10);
    user.AddPoints(5);
    if (user.getPoints() != 15) {
        cout << "Test AddPoints failed:\nExpected: 15 points\nGot: " << user.getPoints() << " points" << endl;
        return 1;
    }
    user.AddPoints(-3);
    if (user.getPoints() != 12) {
        cout << "Test AddPoints failed after negative delta:\nExpected: 12 points\nGot: " << user.getPoints() << " points" << endl;
        return 1;
    }
    return 0;
}

int test2_PrivateIndividual()
{
    PrivateIndividual user("TestUser", true, 0);
    user.AddSensor("SensorA");
    user.AddSensor("SensorB");
    vector<string> sensors = user.getSensorsIDs();
    if (sensors.size() != 2) {
        cout << "Test AddSensor failed:\nExpected: 2 sensors\nGot: " << sensors.size() << " sensors" << endl;
        return 1;
    }
    if (sensors[0] != "SensorA" || sensors[1] != "SensorB") {
        cout << "Test AddSensor failed: Sensors do not match expected values." << endl;
        cout << "Expected: SensorA, SensorB" << endl;
        cout << "Got: " << sensors[0] << ", " << sensors[1] << endl;
        return 1;
    }
    return 0;
}

int testPrivateIndividual()
{
    cout << "Running PrivateIndividual tests..." << endl;
    int resultat = 0;
    resultat += test1_PrivateIndividual();
    resultat += test2_PrivateIndividual();

    if (resultat == 0) {
        cout << "All tests passed successfully!" << endl << endl;
    } else {
        cout << resultat << " test(s) failed." << endl << endl;
    }

    return resultat;
}