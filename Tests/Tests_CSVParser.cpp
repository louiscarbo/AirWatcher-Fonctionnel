#include <iostream>
#include <string>
#include <vector>

using namespace std;


#include "../Data/CSVParser.h"
#include "../Model/Sensor.h"
#include "../Model/Measurement.h"
#include "../Model/Cleaner.h"
#include "../Model/PrivateIndividual.h"
#include "../Model/Attribute.h"
#include "../Model/AirCleanerProvider.h"
#include "../Utils.cpp"



int test1_CSVParser()
{
    CSVParser * parser = new CSVParser("Dataset/");

    vector<string> elements = parser->splitLine( "sensor1;O3;2023-10-01 12:00:00;25.5", ';');
    if (elements.at(0) != "sensor1" || elements.at(1) != "O3" || elements.at(2) != "2023-10-01 12:00:00" || elements.at(3) != "25.5") {
        cout << "Test 1 failed: splitLine did not return expected values." << endl;
        cout << "Expected: sensor1;O3;2023-10-01 12:00:00;25.5" << endl;
        cout << "Got: " << elements.at(0) << ";" << elements.at(1) << ";" << elements.at(2) << ";" << elements.at(3) << endl;
        delete parser;
        return 1;
    }
    elements = parser->splitLine( "sensor1;O3;2023-10-01 12:00:00;25.5");
    if (elements.at(0) != "sensor1" || elements.at(1) != "O3" || elements.at(2) != "2023-10-01 12:00:00" || elements.at(3) != "25.5") {
        cout << "Test 1 failed: splitLine did not return expected values." << endl;
        cout << "Expected: sensor1;O3;2023-10-01 12:00:00;25.5" << endl;
        cout << "Got: " << elements.at(0) << ";" << elements.at(1) << ";" << elements.at(2) << ";" << elements.at(3) << endl;
        delete parser;
        return 1;
    }
    delete parser;
    return 0;
}

int test2_CSVParser()
{
    CSVParser * parser = new CSVParser("Dataset/");

    string expectedID[] = {"O3", "SO2", "NO2", "PM10"};
    string expectedUnit[] = {"µg/m3", "µg/m3", "µg/m3", "µg/m3"};
    string expectedDescription[] = {
        "concentration d'ozone",
        "concentration de dioxyde de soufre",
        "concentration de dioxyde d'azote",
        "concentration de particules fines"
    };

    vector<Attribute> attributs = parser->loadAttributes();
    if (attributs.empty()) {
        cout << "Test2 failed: No attributes loaded." << endl;
        delete parser;
        return 1;
    } else {
        for (size_t i = 0; i < attributs.size(); ++i) {
            if (// attributs[i].getAttributeID() != expectedID[i] ||
                attributs[i].getUnit() != expectedUnit[i]
                // ||attributs[i].getDescription() != expectedDescription[i]
                ) {
                cout << "Test2 failed: Attribute mismatch at index " << i << endl;
                cout << "Expected: " << expectedID[i] << ", " << expectedUnit[i] << ", " << expectedDescription[i] << endl;
                cout << "Got: " << "getAttributeID() non implémenté"// << attributs[i].getAttributeID() << ", " 
                     << attributs[i].getUnit() << ", "
                     << "getDescription() non implémenté" // << attributs[i].getDescription()
                     << endl;
                delete parser;
                return 1;
            }
        }
    }

    delete parser;
    return 0;
}

int test3_CSVParser()
{
    CSVParser * parser = new CSVParser("Dataset/");

    vector<Sensor> sensors = parser->loadSensors();
    if (sensors.empty()) {
        cout << "Test3 failed: No sensors loaded." << endl;
        delete parser;
        return 1;
    } else if ( sensors.at(0).getSensorID() != "Sensor0" ||
                sensors.at(0).getCoordinates() == nullptr || 
                sensors.at(0).getCoordinates()->getLatitude() != 44 || 
                sensors.at(0).getCoordinates()->getLongitude() != -1) {
        cout << "Test3 failed: First sensor error" << endl;
        cout << "Expected: Sensor0, Coordinates(44, -1)" << endl;
        cout << "Got: " << sensors.at(0).getSensorID() << ", Coordinates(" 
             << sensors.at(0).getCoordinates()->getLatitude() << ", " 
             << sensors.at(0).getCoordinates()->getLongitude() << ")" << endl;
        delete parser;
        return 1;
    }

    delete parser;
    return 0;
}

/*
int test4_CSVParser()
{
    CSVParser parser("Dataset/");

    vector<Measurement> measurements = parser.loadMeasurements();
    if (measurements.empty()) {
        cout << "Test4 failed: No measurements loaded." << endl;
        return 1;
    } else if (measurements.at(0).getSensorID() != "Sensor0" ||
               measurements.at(0).getAttribute().getAttributeID() != "O3" ||
               measurements.at(0).getValue() != 50.25 ||
               measurements.at(0).getTimeStamp() != parseTimestamp("2019-01-01 12:00:00")) {
        cout << "Test4 failed: First measurement error" << endl;
        cout << "Expected: Sensor0, O3, 50.25, 2019-01-01 12:00:00" << endl;
        cout << "Got: " << measurements.at(0).getSensorID() << ", "
             << measurements.at(0).getAttribute().getAttributeID() << ", "
             << measurements.at(0).getValue() << ", "
             << std::chrono::system_clock::to_time_t(measurements.at(0).getTimeStamp()) << endl;
        return 1;
    }

    return 0;
}
*/

int test5_CSVParser(){
    CSVParser * parser = new CSVParser("Dataset/");

    vector<Cleaner> cleaners = parser->loadCleaners();
    if (cleaners.empty()) {
        cout << "Test5 failed: No cleaners loaded." << endl;
        delete parser;
        return 1;
    }else if (cleaners.at(0).getCoordinates() == nullptr) {
            cout << "Test5 failed: Coordinates is nullptr." << endl;
            return 1;
        
    } else if (// cleaners.at(0).getCleanerID() != "Cleaner0" ||
               cleaners.at(0).getCoordinates()->getLatitude() != 45.333333 ||
               cleaners.at(0).getCoordinates()->getLongitude() != 1.333333 ||
               cleaners.at(0).getTimestamp_start() != parseTimestamp("2019-02-01 12:00:00") ||
               cleaners.at(0).getTimestamp_stop() != parseTimestamp("2019-03-01 00:00:00")) {
        cout << "Test5 failed: First cleaner error" << endl;
        cout << "Expected: Cleaner0, Coordinates(45.333333, 1.333333), 2019-02-01 12:00:00, 2019-03-01 00:00:00" << endl;
        cout << "Got: " << /*cleaners.at(0).getCleanerID()*/ "getCleanerID() non implémenté" << ", Coordinates("
             << cleaners.at(0).getCoordinates()->getLatitude() << ", "
             << cleaners.at(0).getCoordinates()->getLongitude() << "), "
             << std::chrono::system_clock::to_time_t(cleaners.at(0).getTimestamp_start()) << ", "
             << std::chrono::system_clock::to_time_t(cleaners.at(0).getTimestamp_stop()) << endl;
        delete parser;
        return 1;
    }

    delete parser;
    return 0;
}

int test6_CSVParser()
{
    CSVParser * parser = new CSVParser("Dataset/");

    vector<PrivateIndividual> individuals = parser->loadPrivateIndividuals();
    if (individuals.empty()) {
        cout << "Test6 failed: No private individuals loaded." << endl;
        delete parser;
        return 1;
    } else if (//individuals.at(0).getUserName() != "User0" ||
               //individuals.at(0).getSensorsIDs().empty() ||
               //individuals.at(0).getSensorsIDs().at(0) != "Sensor70"
               individuals.at(0).getPoints() != 0 ){
        cout << "Test6 failed: First private individual error" << endl;
        cout << "Expected: User0, Sensor70, 0" << endl;
        cout << "Got: " << /*individuals.at(0).getUserName()*/ "getUserName() pas encore implémenté" << ", "
             << /*(individuals.at(0).getSensorsIDs().empty() ? "No sensors" : individuals.at(0).getSensorsIDs().at(0))*/ "getSensorsIDs() pas encore implémenté" << ","
             << individuals.at(0).getPoints()
             << endl;
        delete parser;
        return 1;
    }

    delete parser;
    return 0;
}

int test7_CSVParser()
{
    CSVParser * parser = new CSVParser("Dataset/");

    vector<AirCleanerProvider> providers = parser->loadAirCleanerProviders();
    if (providers.empty()) {
        cout << "Test7 failed: No air cleaner providers loaded." << endl;
        delete parser;
        return 1;
    } else if (providers.at(0).GetProviderID() != "Provider1" ||
               providers.at(0).getCleanersID().empty() ||
               providers.at(0).getCleanersID().at(0) != "Cleaner1"
               ) {
        cout << "Test7 failed: First air cleaner provider error" << endl;
        cout << "Expected: Provider1, Cleaner1" << endl;
        cout << "Got: " << providers.at(0).GetProviderID() << ", "
             << (providers.at(0).getCleanersID().empty() ? "No cleaners" : providers.at(0).getCleanersID().at(0)) << endl;
        delete parser;
        return 1;
    }

    delete parser;
    return 0;
}

int testCSVParser()
{
    cout << "Running CSVParser tests..." << endl;
    int resultat = 0;
    resultat += test1_CSVParser();
    resultat += test2_CSVParser();
    resultat += test3_CSVParser();
    //resultat += test4(); // Commenté car loadMeasurements() n'est pas fini
    resultat += test5_CSVParser();
    resultat += test6_CSVParser();
    resultat += test7_CSVParser();
    if (resultat == 0) {
        cout << "All tests passed successfully!" << endl << endl;
    } else {
        cout << resultat << " test(s) failed." << endl << endl;
    }

    return resultat;
}