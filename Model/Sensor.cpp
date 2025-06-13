#include <string>
#include <ctime>
#include <chrono>
#include <set>
#include <iostream>
#include <vector>
#include "Sensor.h"
using Timestamp = std::chrono::time_point<std::chrono::system_clock>;
#include "../Model/Coordinates.h"
#include "../Model/Measurement.h"
#include <map>
using namespace std;

const Coordinates * Sensor::getCoordinates() const
{
    return &coordinates;
}

int Sensor::calculateMeanAtmoIndex(Timestamp timeStamp)
{
    // Recherche toutes les mesures pour ce timestamp
    vector<Measurement> measurementsAtTime;

    std::time_t target_time_t = std::chrono::system_clock::to_time_t(timeStamp);
    std::tm target_tm = *std::localtime(&target_time_t);
    
    for (const auto& measurement : measurements) {
        std::time_t m_time_t = std::chrono::system_clock::to_time_t(measurement.getTimeStamp());
        std::tm m_tm = *std::localtime(&m_time_t);

        // Si la mesure est du même jour
        if (m_tm.tm_year == target_tm.tm_year &&
            m_tm.tm_mon  == target_tm.tm_mon &&
            m_tm.tm_mday == target_tm.tm_mday) {
            measurementsAtTime.push_back(measurement);
        }
    }
    
    // Si aucune mesure à ce timestamp, retourner 0
    if (measurementsAtTime.empty()) {
        return 0;
    }
        
    // Calculer le sous-indice pour chaque polluant
    map<string, int> subIndices;
    
    for (const auto& measurement : measurementsAtTime) {
        string unit = measurement.getAttribute().getAttributeID();
        float value = measurement.getValue();
        
        // Vérifier si on a les seuils pour ce polluant
        if (dictUnitAtmoMaxValue.find(unit) == dictUnitAtmoMaxValue.end()) {
            cout << "No thresholds defined for pollutant: " << unit << endl;
            continue;
        }
        
        // Calculer le sous-indice pour ce polluant
        int subIndex = 10; // Commencer par le maximum au cas où la valeur dépasse tous les seuils
        const map<int, int>& thresholds = dictUnitAtmoMaxValue.at(unit);
        
        for (int atmo = 1; atmo <= 10; ++atmo) {
            if (thresholds.find(atmo) != thresholds.end()) {
                if (value <= thresholds.at(atmo)) {
                    subIndex = atmo;
                    break;
                }
            }
        }
                
        // Prendre le maximum si on a plusieurs mesures du même polluant
        if (subIndices.find(unit) == subIndices.end() || subIndex > subIndices[unit]) {
            subIndices[unit] = subIndex;
        }
    }
    
    // L'indice ATMO final est le maximum des sous-indices
    int atmoIndex = 1;
    for (const auto& pair : subIndices) {
        atmoIndex = max(atmoIndex, pair.second);
    }

    return atmoIndex;
}
    

/*
bool Sensor::hasMeasurementAtTime(Timestamp timeStamp) const
{
    for (const auto& measurement : measurements) {
        if (measurement.getTimeStamp() == timeStamp) {
            return true;
        }
    }
    return false;
}*/
bool Sensor::hasMeasurementAtTime(Timestamp timeStamp) const
{
    std::time_t target_time_t = std::chrono::system_clock::to_time_t(timeStamp);
    std::tm target_tm = *std::localtime(&target_time_t);

    for (const auto& m : measurements)
    {
        std::time_t m_time_t = std::chrono::system_clock::to_time_t(m.getTimeStamp());
        std::tm m_tm = *std::localtime(&m_time_t);

        if (m_tm.tm_year == target_tm.tm_year &&
            m_tm.tm_mon  == target_tm.tm_mon &&
            m_tm.tm_mday == target_tm.tm_mday)
        {
            return true;
        }
    }

    return false;
}

string Sensor::getSensorID() const
{
#ifdef MAP
    cout << "Appel à getSensorID" << endl;
#endif
    return sensorID;
}

vector<Timestamp> Sensor::getMeasurementTimestamps() const
{
    set<Timestamp> uniqueTimestamps;
    
    for (const auto& measurement : measurements) {
        uniqueTimestamps.insert(measurement.getTimeStamp());
    }
    
    return vector<Timestamp>(uniqueTimestamps.begin(), uniqueTimestamps.end());
}

void Sensor::addMeasurement(Measurement measurement)
{
    measurements.push_back(measurement);
}

Sensor::Sensor()
{
    initDictUnit();
}

Sensor::Sensor(string sensorId, Coordinates coords)
    : sensorID(sensorId)
    , coordinates(coords)
    , privateIndividual(nullptr)
    , measurements()
    , dictUnitAtmoMaxValue()
{
    #ifdef MAP
        cout << "Appel au constructeur de <Sensor>" << endl;
    #endif
    initDictUnit();
}

Sensor::Sensor(const Sensor& other)
    : sensorID(other.sensorID)
    , coordinates(other.coordinates)
    , privateIndividual(other.privateIndividual)
    , measurements(other.measurements)
    , dictUnitAtmoMaxValue(other.dictUnitAtmoMaxValue)
{
    #ifdef MAP
        cout << "Appel au constructeur de copie de <Sensor>" << endl;
    #endif
}

Sensor::Sensor(string sensor_ID, float latitudeInit, float longitudeInit, PrivateIndividual *privateIndiv)
{
    sensorID = sensor_ID;
    coordinates = Coordinates(latitudeInit, longitudeInit);  // Pas de new
    privateIndividual = privateIndiv;
    measurements = list<Measurement>();
    initDictUnit();
}

Sensor::~Sensor()
{
#ifdef MAP
    cout << "Appel au destructeur de <Sensor>" << endl;
#endif
}

void Sensor::initDictUnit()
{
    // O3
    dictUnitAtmoMaxValue["O3"][1] = 29;
    dictUnitAtmoMaxValue["O3"][2] = 54;
    dictUnitAtmoMaxValue["O3"][3] = 79;
    dictUnitAtmoMaxValue["O3"][4] = 104;
    dictUnitAtmoMaxValue["O3"][5] = 129;
    dictUnitAtmoMaxValue["O3"][6] = 149;
    dictUnitAtmoMaxValue["O3"][7] = 179;
    dictUnitAtmoMaxValue["O3"][8] = 209;
    dictUnitAtmoMaxValue["O3"][9] = 239;
    dictUnitAtmoMaxValue["O3"][10] = INT_MAX;

    // SO2
    dictUnitAtmoMaxValue["SO2"][1] = 39;
    dictUnitAtmoMaxValue["SO2"][2] = 79;
    dictUnitAtmoMaxValue["SO2"][3] = 119;
    dictUnitAtmoMaxValue["SO2"][4] = 159;
    dictUnitAtmoMaxValue["SO2"][5] = 199;
    dictUnitAtmoMaxValue["SO2"][6] = 249;
    dictUnitAtmoMaxValue["SO2"][7] = 299;
    dictUnitAtmoMaxValue["SO2"][8] = 399;
    dictUnitAtmoMaxValue["SO2"][9] = 499;
    dictUnitAtmoMaxValue["SO2"][10] = INT_MAX;

    // NO2
    dictUnitAtmoMaxValue["NO2"][1] = 29;
    dictUnitAtmoMaxValue["NO2"][2] = 54;
    dictUnitAtmoMaxValue["NO2"][3] = 84;
    dictUnitAtmoMaxValue["NO2"][4] = 109;
    dictUnitAtmoMaxValue["NO2"][5] = 134;
    dictUnitAtmoMaxValue["NO2"][6] = 164;
    dictUnitAtmoMaxValue["NO2"][7] = 199;
    dictUnitAtmoMaxValue["NO2"][8] = 274;
    dictUnitAtmoMaxValue["NO2"][9] = 399;
    dictUnitAtmoMaxValue["NO2"][10] = INT_MAX;

    // PM10
    dictUnitAtmoMaxValue["PM10"][1] = 6;
    dictUnitAtmoMaxValue["PM10"][2] = 13;
    dictUnitAtmoMaxValue["PM10"][3] = 20;
    dictUnitAtmoMaxValue["PM10"][4] = 27;
    dictUnitAtmoMaxValue["PM10"][5] = 34;
    dictUnitAtmoMaxValue["PM10"][6] = 41;
    dictUnitAtmoMaxValue["PM10"][7] = 49;
    dictUnitAtmoMaxValue["PM10"][8] = 64;
    dictUnitAtmoMaxValue["PM10"][9] = 79;
    dictUnitAtmoMaxValue["PM10"][10] = INT_MAX;
}
