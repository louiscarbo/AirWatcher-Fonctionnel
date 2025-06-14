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
    if(useCasesManager->getAttributes().empty()) {
        cout << "Test1 failed: No attributes loaded." << endl;
        delete useCasesManager;
        return 1;
    } else if (useCasesManager->getCleaners().empty()) {
        cout << "Test1 failed: No cleaners loaded." << endl;
        delete useCasesManager;
        return 1;
    } else if (useCasesManager->getSensors().empty()) {
        cout << "Test1 failed: No sensors loaded." << endl;
        delete useCasesManager;
        return 1;
    } else if (useCasesManager->getMeasurements().empty()) {
        cout << "Test1 failed: No measurements loaded." << endl;
        delete useCasesManager;
        return 1;
    } else if (useCasesManager->getUsers().empty()) {
        cout << "Test1 failed: No private individuals loaded." << endl;
        delete useCasesManager;
        return 1;
    } else if (useCasesManager->getProviders().empty()) {
        cout << "Test1 failed: No air cleaner providers loaded." << endl;
        delete useCasesManager;
        return 1;
    }

    delete useCasesManager;
    return 0;
}

int test2_useCasesManager()
{
    UseCasesManager * useCasesManager = new UseCasesManager();
    useCasesManager->loadData();

    Coordinates centerCoords(44.0, -1.0);
    float R = 0.8; // 800 m radius
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
    
    if (suspiciousSensors.empty()) {
        cout << "Test4 failed: No suspicious sensors were found." << endl;
        delete useCasesManager;
        return 1;
    }
    
    if (suspiciousSensors[0].first.getSensorID() != "Sensor36") {
        cout << "Test4 failed: First suspicious sensor is not Sensor36." << endl;
        cout << "Expected: Sensor36" << endl;
        cout << "Got: " << suspiciousSensors[0].first.getSensorID() << endl;
        cout << "All suspicious sensors found:" << endl;
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