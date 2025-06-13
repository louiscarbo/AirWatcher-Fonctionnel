/*************************************************************************
                           Classe : useCasesManager
*************************************************************************/

// Réalisation de la classe <UseCasesManager> (fichier UseCasesManager.cpp)

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>  // For sort, min, max
#include <numeric>    // For accumulate
#include <cmath>      // For abs
#include <chrono>
using namespace std;

//------------------------------------------------------ Include personnel
#include "../Services/UseCasesManager.h"
#include "../Data/CSVParser.h"
#include <unordered_map>


//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
vector<pair<Sensor, double>> UseCasesManager::identifySuspiciousSensors()
{
    auto start = chrono::high_resolution_clock::now();

    const int LAST_N = 30;                   
    const int RANGE_MIN = 0;                 
    const int RANGE_MAX = 100;                
    const double NEIGHBOR_RADIUS_KM = 0.8;   
    const double LOCAL_DIFF_THRESHOLD = 2.0; 
    const double SPIKE_THRESHOLD = 2.0;

    const double WEIGHT_RANGE_VIOLATION = 1000.0;
    const double WEIGHT_SPIKE_DETECTION = 1.5;
    const double WEIGHT_LOCAL_INCONSISTENCY = 2.0;
    
    const double MAX_SCORE = 10.0;

    vector<pair<Sensor, double>> scoredSensors;
    vector<Sensor> allSensors = sensors;

    cout << "Identifying suspicious sensors..." << endl;

    // OPTIMIZATION 1: Pre-compute all neighbors for all sensors
    unordered_map<string, vector<string>> neighborMap;
    for (int i = 0; i < allSensors.size(); i++) {
        for (int j = 0; j < allSensors.size(); j++) {
            if (i != j) {
                const Coordinates* coord1 = allSensors[i].getCoordinates();
                const Coordinates* coord2 = allSensors[j].getCoordinates();
                
                double distance = Coordinates::distance(*coord1, *coord2);
                
                if (distance <= NEIGHBOR_RADIUS_KM) {
                    neighborMap[allSensors[i].getSensorID()].push_back(allSensors[j].getSensorID());
                }
            }
        }
    }

    // OPTIMIZATION 2: Create sensor lookup map
    unordered_map<string, Sensor*> sensorLookup;
    for (auto& sensor : allSensors) {
        sensorLookup[sensor.getSensorID()] = &sensor;
    }

    int currentSensor = 0;
    for (auto& sensor : allSensors) {
        currentSensor++;
        cout << "\rProgress: " << sensor.getSensorID() << " " << currentSensor << "/" << allSensors.size() 
             << " (" << (currentSensor * 100 / allSensors.size()) << "%)" << flush;

        vector<Timestamp> times = sensor.getMeasurementTimestamps();
        
        // OPTIMIZATION 3: Cache ATMO calculations
        unordered_map<string, double> atmoCache;
        vector<double> recentAtmo;
        
        for (auto& t : times) {
            string timeKey = to_string(chrono::duration_cast<chrono::seconds>(t.time_since_epoch()).count());
            double atmo = sensor.calculateMeanAtmoIndex(t);
            atmoCache[timeKey] = atmo;
            recentAtmo.push_back(atmo);
        }

        int N = recentAtmo.size();
        double score;

        if (N == 0) {
            score = MAX_SCORE;
        } else {
            // CHECK 1 - Out of range measurement values
            int violations = 0;
            int totalMeasurements = 0;
            
            for (const auto& time : times) {
                for (const auto& measurement : measurements) {
                    if (measurement.getSensorID() == sensor.getSensorID() && 
                        measurement.getTimeStamp() == time) {
                        
                        double value = measurement.getValue();
                        totalMeasurements++;
                        if (value < RANGE_MIN || value > RANGE_MAX) {
                            violations++;
                        }
                    }
                }
            }
            
            double rateRange = totalMeasurements > 0 ? static_cast<double>(violations) / totalMeasurements : 0.0;

            // CHECK 2 - Spikes
            vector<double> changes;
            double prevAtmo = -1;
            
            for (auto& currentAtmo : recentAtmo) {
                if (prevAtmo >= 0) {
                    changes.push_back(abs(currentAtmo - prevAtmo));
                }
                prevAtmo = currentAtmo;
            }

            int spikes = 0;
            for (auto& change : changes) {
                if (change > SPIKE_THRESHOLD) {
                    spikes++;
                }
            }
            double rateSpike = static_cast<double>(spikes) / max(1, (int)changes.size());

            // CHECK 3 - OPTIMIZED Local inconsistency
            vector<double> deviations;
            const vector<string>& neighborIds = neighborMap[sensor.getSensorID()];
            
            for (int i = 0; i < times.size(); i++) {
                const auto& time = times[i];
                double selfValue = recentAtmo[i];
                
                vector<double> neighborValues;
                for (const string& neighborId : neighborIds) {
                    Sensor* neighbor = sensorLookup[neighborId];
                    if (neighbor->hasMeasurementAtTime(time)) {
                        neighborValues.push_back(neighbor->calculateMeanAtmoIndex(time));
                    }
                }

                if (!neighborValues.empty()) {
                    double averageNeighborValues = accumulate(neighborValues.begin(), neighborValues.end(), 0.0) / neighborValues.size();
                    deviations.push_back(abs(selfValue - averageNeighborValues));
                }
            }
            
            double inconsistency = 0.0;
            if (!deviations.empty()) {
                double meanDev = accumulate(deviations.begin(), deviations.end(), 0.0) / deviations.size();
                double diffNorm = meanDev / LOCAL_DIFF_THRESHOLD;
                inconsistency = min(max(diffNorm, 0.0), 1.0);
            }

            double rawScore = WEIGHT_RANGE_VIOLATION * rateRange +
                            WEIGHT_SPIKE_DETECTION * rateSpike +
                            WEIGHT_LOCAL_INCONSISTENCY * inconsistency;
            
            // DEBUG
            // cout << "\nSensor ID: " << sensor.getSensorID() 
            //      << ", Range Violations: " << violations 
            //      << ", Spikes: " << spikes 
            //      << ", Local Inconsistency: " << inconsistency 
            //      << ", Raw Score: " << rawScore;
            // cout << "\nScore Details:"
            //      << " (Range: " << rateRange 
            //      << ", Spikes: " << rateSpike 
            //      << ", Inconsistency: " << inconsistency << ")" << endl;
            // END DEBUG
            
            score = min(rawScore, MAX_SCORE);
        }

        scoredSensors.push_back(make_pair(sensor, score));
    }

    cout << endl;
    
    sort(scoredSensors.begin(), scoredSensors.end(), 
         [](const pair<Sensor, double>& a, const pair<Sensor, double>& b) {
             return a.second > b.second;
         });


    // Track performance if enabled
    if (trackPerformance) {
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
        cout << "[PERFORMANCE] identifySuspiciousSensors executed in " << duration.count() << " ms" << endl;
    }

    
    return scoredSensors;
}

vector<Sensor> UseCasesManager::findSensorsWithinRadius(const Coordinates& centerCoords, double R)
{    
    vector<Sensor> sensorsWithinRadius;
    
    for(const auto& sensor : sensors) {
        double distance = Coordinates::distance(centerCoords, *sensor.getCoordinates());
        if (distance <= R) {
            sensorsWithinRadius.push_back(sensor);
        }
    }
    
    return sensorsWithinRadius;
}

int UseCasesManager::ComputeAtmoIndexInArea(Coordinates centerCoords,float R, Timestamp timestamp){
    auto start = chrono::high_resolution_clock::now();

    // Find all sensors in circle
    vector<Sensor> sensors = findSensorsWithinRadius(centerCoords, R);
    cout << "Sensors found within radius " << R << " km of center (" 
         << centerCoords.getLatitude() << ", " << centerCoords.getLongitude() << "):" << endl;
    for (const auto& sensor : sensors) {
        cout << sensor.getSensorID() << " ";
    }
    cout << endl;

    if (sensors.empty()){
        printf("No data available\n");
        return -1; // No sensors found in the specified area
    }
    // Accumulate weighted ATMO values
    float weightedSum = 0.0;
    float totalWeight = 0.0;
    float weight;
    int atmo;
    float d;
    for (auto sensor: sensors){
        if(sensor.hasMeasurementAtTime(timestamp)){
            atmo = sensor.calculateMeanAtmoIndex(timestamp);
            d = Coordinates::distance(centerCoords, *sensor.getCoordinates());
            weight = max((float)0, (R-d)/R);
            weightedSum += (weight*atmo);
            totalWeight += weight;
        }
    }

    // Track performance if enabled
    if (trackPerformance) {
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
        cout << "[PERFORMANCE] findSensorsWithinRadius executed in " << duration.count() << " ms" << endl;
    }

    // Return weighted average
    if(totalWeight==0){
        printf("No data at timestamp\n");
        return -1; // No valid measurements found at the specified timestamp
    }else{
        return weightedSum/totalWeight;
    }
}


void UseCasesManager::loadData(bool verbose) {

    if (verbose) {
        cout << "\nLoading data from CSV files." << endl;
    }

    if (verbose) {
        cout << "Loading attributes...    ";
    }
    attributes   = parser.loadAttributes();
    if (verbose) {
        cout << "Finished: " << attributes.size() << " attributes loaded\n";
    }

    if (verbose) {
        cout << "Loading sensors...       ";
    }
    sensors      = parser.loadSensors();
    if (verbose) {
        cout << "Finished: " << sensors.size() << " sensors loaded\n";
    }

    if (verbose) {
        cout << "Loading measurements...  ";
    }
    measurements = parser.loadMeasurements();
    if (verbose) {
        cout << "Finished: " << measurements.size() << " measurements loaded\n";
    }

    // Associating measurements with sensors
    if (verbose) {
        cout << "Associating measurements with sensors... ";
    }
    for (const auto& measurement : measurements) {
        for (auto& sensor : sensors) {
            if (sensor.getSensorID() == measurement.getSensorID()) {
                sensor.addMeasurement(measurement);
                break;
            }
        }
    }
    if (verbose) {
        cout << "Done\n";
    }

    if (verbose) {
        cout << "Loading cleaners...      ";
    }
    cleaners     = parser.loadCleaners();
    if (verbose) {
        cout << "Finished: " << cleaners.size() << " cleaners loaded\n";
    }

    if (verbose) {
        cout << "Loading users...         ";
    }
    users        = parser.loadPrivateIndividuals();
    if (verbose) {
        cout << "Finished: " << users.size() << " users loaded\n";
    }

    if (verbose) {
        cout << "Loading providers...     ";
    }
    providers    = parser.loadAirCleanerProviders();
    if (verbose) {
        cout << "Finished: " << providers.size() << " providers loaded\n";
    }

    if (verbose) {
        cout << "Loading data completed.\n" << endl;
    }
}

void UseCasesManager::setPerformanceTracking(bool enabled) {
    trackPerformance = enabled;
}

bool UseCasesManager::isPerformanceTrackingEnabled() const {
    return trackPerformance;
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

UseCasesManager::UseCasesManager(const string& dataPath)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <UseCasesManager>" << endl;
#endif
    this->dataPath = dataPath;
    this->parser = CSVParser(dataPath);
    this->trackPerformance = false; // Default value, can be set later if needed
}

UseCasesManager::UseCasesManager()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <UseCasesManager>" << endl;
#endif
    this->dataPath = "Dataset/";
    this->parser = CSVParser(this->dataPath);
    this->trackPerformance = false;
} //----- Fin de UseCasesManager


UseCasesManager::~UseCasesManager()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <UseCasesManager>" << endl;
#endif
} //----- Fin de ~UseCasesManager


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

