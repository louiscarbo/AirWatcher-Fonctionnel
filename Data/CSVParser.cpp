/*************************************************************************
                           CSVParser
*************************************************************************/

//---------- Réalisation de la classe <CSVParser> (fichier CSVParser.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>

//------------------------------------------------------ Include personnel
#include "CSVParser.h"
#include "../Utils.cpp"

using Timestamp = std::chrono::time_point<std::chrono::system_clock>;

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
 vector<string> CSVParser::splitLine ( const string & ligne, char delimiter) {
    vector <string> elements;
    stringstream ss(ligne);
    string car;

    while (getline(ss,car,delimiter)) {
        elements.push_back(car);
    }
    return elements;
 }

vector<Attribute> CSVParser::loadAttributes (){
    vector<Attribute> attributs;
    ifstream file(path + "/attributes.csv");

    if (!file) {
        cerr <<"Erreur ouverture du fichier contenant les attributs";
        return attributs;   
    }

    string line;
    getline(file,line); //pour éliminer la première ligne du tableau avec les titres des colonnes 

    while (getline(file,line)){
        if (line.empty()) continue;
        auto cols = splitLine(line);

        if (cols.size() <3) continue; //car 3 colonnes 
        attributs.emplace_back( cols[0],cols[1],cols[2]);
    }
    return attributs; 
}

vector<Sensor> CSVParser::loadSensors (){
    vector<Sensor> sensors;
    ifstream file(path + "/sensors.csv");

    if (!file) {
        cerr <<"Erreur ouverture du fichier contenant les capteurs (sensors)";
        return sensors;   
    }

    string line;

    while (getline(file,line)){
        if (line.empty()) continue;
        auto cols = splitLine(line);

        if (cols.size() <3) continue;
        Sensor s(
                cols[0],
                Coordinates {
                    stod(cols[1]),
                    stod(cols[2])
                }
            );
        sensors.push_back(move(s));
    }
    return sensors; 
}

vector<Measurement> CSVParser::loadMeasurements (){
    vector<Measurement> mesures;
    ifstream file(path + "/measurements.csv");

    if (!file) {
        cerr <<"Erreur ouverture du fichier contenant les mesures (measurements)";
        return mesures;   
    }

    string line;

    while (getline(file,line)){
        if (line.empty()) continue;
        auto cols = splitLine(line);

        if (cols.size() <4) continue; //4 car 4 colonnes

        mesures.emplace_back(
            parseTimestamp(cols[0]),  //                          !!!!!! A REVOIR !!!!!! 
            stof(cols[3]),
            cols[1],
            Attribute{cols[2],"",""}
        );
    }
    return mesures; 
}

vector<Cleaner> CSVParser::loadCleaners (){
    vector<Cleaner> cleaners;
    ifstream file(path + "/cleaners.csv");

    if (!file) {
        cerr <<"Erreur ouverture du fichier contenant les cleaners";
        return cleaners;   
    }

    string line;

    while (getline(file,line)){
        if (line.empty()) continue;
        auto cols = splitLine(line);

        if (cols.size() <5) continue;

        Cleaner c(
            cols[0],
            parseTimestamp(cols[3]),
            parseTimestamp(cols[4]),
            stod(cols[1]),
            stod(cols[2])
        );
        cleaners.push_back(move(c));
    }
    return cleaners; 
}

vector<PrivateIndividual> CSVParser::loadPrivateIndividuals() {
    std::ifstream file(path + "/users.csv");
    if (!file) {
        cerr << "Erreur d'ouverture de /users.csv";
        return {};
    }

    unordered_map<std::string, PrivateIndividual> mapUsers;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        auto cols = splitLine(line);

        // on s'attend à : userName;sensorID
        if (cols.size() < 2) continue;

        const std::string& userName = cols[0];
        const std::string& sensorID = cols[1];

        // crée le PrivateIndividual une seule fois
        auto it = mapUsers.find(userName);
        if (it == mapUsers.end()) {
            auto [ins, pairIt] = mapUsers.emplace(
                userName,
                PrivateIndividual(userName, true, 0)  //par défaut il est reliable 
            );
            it = ins;
        }
        // ajoute le capteur à cet utilisateur
        it->second.AddSensor(sensorID);
    }

    // convertit la map en vector à retourner
    std::vector<PrivateIndividual> users;
    users.reserve(mapUsers.size());
    for (auto& kv : mapUsers) {
        users.push_back(std::move(kv.second));
    }
    return users;
}

vector<AirCleanerProvider> CSVParser::loadAirCleanerProviders(){
    std::ifstream file(path + "/providers.csv");
    if (!file) {
        std::cerr << "Erreur d'ouverture fichier providers.csv\n";
        return {};
    }

    // map temporaire : providerID → AirCleanerProvider
    unordered_map<string, AirCleanerProvider> mapProv;
    string line;

    while (getline(file, line)) {
        if (line.empty()) continue;
        auto cols = splitLine(line);
        
        if (cols.size() < 2) continue;

        const string& providerID = cols[0];
        const string& cleanerID  = cols[1];

        // Si le provider n’existe pas encore, on le crée
        auto it = mapProv.find(providerID);
        if (it == mapProv.end()) {
            auto ins = mapProv.emplace(
                providerID,
                AirCleanerProvider(providerID)
            );
            it = ins.first;
        }
        // On ajoute l’ID du cleaner à ce provider
        it->second.AddCleanerID(cleanerID);
    }

    // Conversion en vector<AirCleanerProvider>
    vector<AirCleanerProvider> providers;
    providers.reserve(mapProv.size());
    for (auto& kv : mapProv) {
        providers.push_back(std::move(kv.second));
    }
    return providers;
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
CSVParser::CSVParser ( const std::string & unpath ): path(unpath){
    #ifdef MAP
    cout << "Appel constructeur <CSVParser>" << endl;
    #endif
}

CSVParser::CSVParser ( ){
    #ifdef MAP
    cout << "Appel constructeur par défaut <CSVParser>" << endl;
    #endif
    path = ""; // Initialiser le chemin à vide
}


CSVParser::~CSVParser ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <CSVParser>" << endl;
#endif
} //----- Fin de ~CSVParser


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

