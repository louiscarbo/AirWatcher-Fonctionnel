#include <iostream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

#include "../Model/Sensor.h"
#include "../Model/Measurement.h"
#include "../Model/Attribute.h"
#include "../Model/Coordinates.h"
#include "../Model/PrivateIndividual.h"
#include "../Model/AirCleanerProvider.h"
#include "../Model/Cleaner.h"
#include "../Data/CSVParser.h"
#include "../Services/UseCasesManager.h"
#include "../Utils.cpp"



int test1_useCasesManager()
{
    UseCasesManager * useCasesManager = new UseCasesManager();
    useCasesManager->loadData();
    delete useCasesManager;

    return 0;
}

int test2_useCasesManager()
{
    UseCasesManager * useCasesManager = new UseCasesManager();
    useCasesManager->loadData();

    Coordinates centerCoords(44.0, -1.0);
    float R = 5.0; // 5 km radius
    Timestamp timestamp = parseTimestamp("2019-01-01 12:00:00");

    int atmoIndex = useCasesManager->ComputeAtmoIndexInArea(centerCoords, R, timestamp);
    
    if (atmoIndex < 0) {
        cout << "Test2 failed: ComputeAtmoIndexInArea returned an error." << endl;
        delete useCasesManager;
        return 1;
    }

    delete useCasesManager;
    return 0;
}

int test3_useCasesManager()
{
    UseCasesManager * useCasesManager = new UseCasesManager();
    useCasesManager->loadData();

    Coordinates centerCoords(44.0, -1.0);
    float R = 0.1; // 5 km radius

    vector<Sensor> sensors = useCasesManager->findSensorsWithinRadius(centerCoords, R);
    
    if (sensors.empty()) {
        cout << "Test3 failed: No sensors found within the specified radius." << endl;
        delete useCasesManager;
        return 1;
    } else if (sensors.at(0).getSensorID() != "Sensor0" || 
               sensors.at(0).getCoordinates() == nullptr || 
               sensors.at(0).getCoordinates()->getLatitude() != 44.0 || 
               sensors.at(0).getCoordinates()->getLongitude() != -1.0) {
        cout << "Test3 failed: First sensor does not match expected values." << endl;
        cout << "Expected: Sensor0, Coordinates(44.0, -1.0)" << endl;
        cout << "Got: " << sensors.at(0).getSensorID() << ", Coordinates(" 
             << sensors.at(0).getCoordinates()->getLatitude() << ", " 
             << sensors.at(0).getCoordinates()->getLongitude() << ")" << endl;
        delete useCasesManager;
        return 1;
    }

    delete useCasesManager;
    return 0;
}

int test4_useCasesManager()
{
    UseCasesManager * useCasesManager = new UseCasesManager();
    useCasesManager->loadData();

    vector<pair<Sensor, double>> suspiciousSensors = useCasesManager->identifySuspiciousSensors();
    
    if (!suspiciousSensors.empty()) {
        cout << "Test4 failed: Suspicious sensors were found when there should be none." << endl;
        cout << "Suspicious Sensors:" << endl;
        for (const auto& pair : suspiciousSensors) {
            cout << "Sensor ID: " << pair.first.getSensorID() 
                 << ", Suspicion Score: " << pair.second << endl;
        }
        delete useCasesManager;
        return 1;
    }

    delete useCasesManager;
    return 0;
}
    
int testuseCasesManager()
{
    cout << "Running useCasesManager tests..." << endl;
    int resultat = 0;
    resultat += test1_useCasesManager();
    resultat += test2_useCasesManager();
    resultat += test3_useCasesManager();
    resultat += test4_useCasesManager();
    
    if (resultat == 0) {
        cout << "All tests passed successfully!" << endl << endl;
    } else {
        cout << resultat << " test(s) failed." << endl << endl;
    }

    return resultat;
}