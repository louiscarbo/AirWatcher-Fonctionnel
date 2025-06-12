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
#include "../Services/useCasesManager.h"
#include "../Data/CSVParser.h"


//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
vector<pair<Sensor, double>> UseCasesManager::identifySuspiciousSensors()
// Algorithme :
//  Voir le document de conception pour les détails de l'algorithme.
{
    const int LAST_N = 30;                   // number of most recent readings to consider
    const int RANGE_MIN = 1;                 // ATMO lower bound
    const int RANGE_MAX = 10;                // ATMO upper bound
    const double NEIGHBOR_RADIUS_KM = 5.0;   // km
    const double LOCAL_DIFF_THRESHOLD = 2.0; // ATMO points

    // How many times the average daily change counts as a "spike"
    const double K_SPIKE_MULTIPLIER = 2.0; 

    // Weights for different checks
    const double WEIGHT_RANGE_VIOLATION = 2.0;
    const double WEIGHT_SPIKE_DETECTION = 1.5;
    const double WEIGHT_LOCAL_INCONSISTENCY = 2.0;

    const double MAX_SCORE = 10.0;

    // Initialize the list to hold the suspicious sensor scores
    vector<pair<Sensor, double>> scoredSensors;
    vector<Sensor> allSensors = sensors;

    for (auto& sensor : allSensors) {
        // Retrieve recent ATMO readings to compute the suspicion score
        vector<Timestamp> times = sensor.getMeasurementTimestamps();
        
        // Sort times in descending order and take only LAST_N elements
        sort(times.begin(), times.end(), greater<Timestamp>());
        if (times.size() > LAST_N) {
            times.resize(LAST_N);
        }
        
        // Map each timestamp to its corresponding ATMO index
        vector<double> recentAtmo;
        for (auto& t : times) {
            recentAtmo.push_back(sensor.calculateMeanAtmoIndex(t));
        }

        int N = recentAtmo.size();
        double score;

        if (N == 0) {
            cout << "No recent data available for sensor: " << sensor.getSensorID() << endl;
            // No recent data available, set maximum suspicion score
            score = MAX_SCORE;
        } else {
            // CHECK 1 - Out of range values
            int violations = 0;
            for (auto& atmo : recentAtmo) {
                if (atmo < RANGE_MIN || atmo > RANGE_MAX) {
                    violations++;
                }
            }
            double rateRange = static_cast<double>(violations) / N;

            // CHECK 2 - Spikes
            // a) Compute average daily change in ATMO value
            vector<double> changes;
            double prevAtmo = -1;
            
            for (auto& currentAtmo : recentAtmo) {
                if (prevAtmo >= 0) {  // Check if prevAtmo is valid
                    changes.push_back(abs(currentAtmo - prevAtmo));
                }
                prevAtmo = currentAtmo;
            }
            
            double avgChange = 0.0;
            if (!changes.empty()) {
                avgChange = accumulate(changes.begin(), changes.end(), 0.0) / changes.size();
            }
            
            double spikeThreshold = K_SPIKE_MULTIPLIER * avgChange;
            
            // b) Rate of spikes
            int spikes = 0;
            for (auto& change : changes) {
                if (change > spikeThreshold) {
                    spikes++;
                }
            }
            
            double rateSpike = static_cast<double>(spikes) / max(1, (int)changes.size());

            // CHECK 3 - Local inconsistency (comparison with neighbors)
            vector<double> deviations;
            
            for (auto& time : times) {
                double selfValue = sensor.calculateMeanAtmoIndex(time);
                vector<Sensor> neighbors = findSensorsWithinRadius(*sensor.getCoordinates(), NEIGHBOR_RADIUS_KM);

                vector<double> neighborValues;
                for (auto& neighbor : neighbors) {
                    if (neighbor.hasMeasurementAtTime(time)) {
                        neighborValues.push_back(neighbor.calculateMeanAtmoIndex(time));
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
                // Clamp inconsistency between 0 and 1
                inconsistency = min(max(diffNorm, 0.0), 1.0);
            }

            // Calculate final suspicion score
            double rawScore = WEIGHT_RANGE_VIOLATION * rateRange +
                            WEIGHT_SPIKE_DETECTION * rateSpike +
                            WEIGHT_LOCAL_INCONSISTENCY * inconsistency;
            
            score = min(rawScore, MAX_SCORE);
        }

        // Add the sensor and its suspicion score to the result list
        scoredSensors.push_back(make_pair(sensor, score));
    }

    // Sort by suspicion score (descending)
    sort(scoredSensors.begin(), scoredSensors.end(), 
         [](const pair<Sensor, double>& a, const pair<Sensor, double>& b) {
             return a.second > b.second;
         });
    
    return scoredSensors;
}

vector<Sensor> UseCasesManager::findSensorsWithinRadius(const Coordinates& centerCoords, double R){
    set<Sensor> sensorsWithinRadius;
    for(auto sensor : sensors){
        if ((sensor.getCoordinates()->getLatitude()>=(centerCoords.getLatitude()-R)) && (sensor.getCoordinates()->getLatitude()<=(centerCoords.getLatitude()+R))&&(sensor.getCoordinates()->getLongitude()>=(centerCoords.getLongitude()-R))&&(sensor.getCoordinates()->getLongitude()<=(centerCoords.getLongitude()+R))){
            sensorsWithinRadius.insert(sensor);
        }
    }
    vector<Sensor> liste_finale(sensorsWithinRadius.begin(), sensorsWithinRadius.end());
    return liste_finale;

}

int UseCasesManager::ComputeAtmoIndexInArea(Coordinates centerCoords,float R, Timestamp timestamp){
    // Find all sensors in circle
    vector<Sensor> sensors = findSensorsWithinRadius(centerCoords, R);

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
        cout << "\nChargement des données depuis les fichiers de données." << endl;
    }

    if (verbose) {
        cout << "Chargement des attributs...    ";
    }
    attributes   = parser.loadAttributes();
    if (verbose) {
        cout << "Terminé : " << attributes.size() << " attributs chargés\n";
    }

    if (verbose) {
        cout << "Chargement des capteurs...     ";
    }
    sensors      = parser.loadSensors();
    if (verbose) {
        cout << "Terminé : " << sensors.size() << " capteurs chargés\n";
    }

    if (verbose) {
        cout << "Chargement des mesures...      ";
    }
    measurements = parser.loadMeasurements();
    if (verbose) {
        cout << "Terminé : " << measurements.size() << " mesures chargées\n";
    }

    if (verbose) {
        cout << "Association des mesures aux capteurs... ";
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
        cout << "Terminé\n";
    }

    if (verbose) {
        cout << "Chargement des nettoyeurs...   ";
    }
    cleaners     = parser.loadCleaners();
    if (verbose) {
        cout << "Terminé : " << cleaners.size() << " nettoyeurs chargés\n";
    }

    if (verbose) {
        cout << "Chargement des utilisateurs... ";
    }
    users        = parser.loadPrivateIndividuals();
    if (verbose) {
        cout << "Terminé : " << users.size() << " utilisateurs chargés\n";
    }

    if (verbose) {
        cout << "Chargement des fournisseurs... ";
    }
    providers    = parser.loadAirCleanerProviders();
    if (verbose) {
        cout << "Terminé : " << providers.size() << " fournisseurs chargés\n";
    }

    if (verbose) {
        cout << "Chargement des données terminé." << endl;
    }}

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

