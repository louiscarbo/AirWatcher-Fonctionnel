#include "../Model/Sensor.h"
#include "../Model/Measurement.h"
#include "../Model/Attribute.h"
#include "../Utils.cpp"
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
using namespace std;


int test1_Sensor()
{
    Sensor sensor("S1", Coordinates(44.0, -1.0));
    string dateStr = "2023-10-01 12:00:00";
    Timestamp timestamp = parseTimestamp(dateStr);
    Measurement m(timestamp, 50.0, "capteur1", Attribute("attributeID", "unit", "description"));
    sensor.addMeasurement(m);

    auto measurements = sensor.getMeasurements();
    if (measurements.size() != 1) {
        cout << "Test 1 failed: Expected: 1 measurement\nGot: " << measurements.size() << " measurement" << endl;
        return 1;
    }
    if (measurements.front().getValue() != 50.0) {
        cout << "Test 1 failed: Value mismatch." << endl;
        cout << "Expected: 50.0\nGot: " << measurements.front().getValue() << endl;
        return 1;
    }
    return 0;
}

int test2_Sensor()
{
    Sensor sensor("S2", Coordinates(44.0, -1.0));
    string dateStr = "2023-10-01 12:00:00";
    Timestamp timestamp = parseTimestamp(dateStr);
    string dateStr2 = "2024-11-11 13:00:00";
    Timestamp timestamp2 = parseTimestamp(dateStr2);
    Measurement m1(timestamp, 30.0, "capteur1", Attribute("attributeID", "unit", "description"));
    sensor.addMeasurement(m1);

    if (!sensor.hasMeasurementAtTime(timestamp)) {
        cout << "Test 2 failed: Should have measurement at timestamp." << endl;
        return 1;
    }
    if (sensor.hasMeasurementAtTime(timestamp2)) {
        cout << "Test 2 failed: Should not have measurement at timestamp2." << endl;
        return 1;
    }
    return 0;
}

int test3_Sensor()
{
    Sensor sensor("S3", Coordinates(44.0, -1.0));
    string dateStr = "2023-10-01 12:00:00";
    Timestamp timestamp = parseTimestamp(dateStr);
    sensor.addMeasurement(Measurement(timestamp, 30.0, "capteur1", Attribute("O3", "µg/m3", "concentration d'ozone")));
    sensor.addMeasurement(Measurement(timestamp, 40.0, "capteur1", Attribute("NO2", "µg/m3", "concentration de dioxyde d'azote")));
    sensor.addMeasurement(Measurement(timestamp, 50.0, "capteur1", Attribute("O3", "µg/m3", "concentration d'ozone")));

    int meanAtmo = sensor.calculateMeanAtmoIndex(timestamp);
    if (meanAtmo < 0) {
        cout << "Test 3 failed: Mean ATMO index is negative (invalid)." << endl;
        return 1;
    }

    string dateStr2 = "2024-11-11 13:00:00";
    Timestamp timestamp2 = parseTimestamp(dateStr2);
    int meanAtmo2 = sensor.calculateMeanAtmoIndex(timestamp2);
    if (meanAtmo2 == meanAtmo) {
        cout << "Test 3 failed: Should not return same value for empty timestamp." << endl;
        return 1;
    }
    return 0;
}

int testSensor()
{
    cout << "Running Sensor tests..." << endl;
    int resultat = 0;
    resultat += test1_Sensor();
    resultat += test2_Sensor();
    resultat += test3_Sensor();

    if (resultat == 0) {
        cout << "All tests passed successfully!" << endl << endl;
    } else {
        cout << resultat << " test(s) failed." << endl << endl;
    }
    return resultat;
}