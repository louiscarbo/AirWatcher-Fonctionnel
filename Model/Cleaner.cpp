/*************************************************************************
                           Classe : Cleaner
*************************************************************************/

// Réalisation de la classe <Cleaner> (fichier Cleaner.cpp)

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include <string>
#include <ctime>
#include <chrono>
using Timestamp = std::chrono::time_point<std::chrono::system_clock>;
using namespace std;
#include "Cleaner.h"
#include "Coordinates.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

Timestamp Cleaner::getTimestamp_start() const {
    return timestamp_start;
}

Timestamp Cleaner::getTimestamp_stop() const {
    return timestamp_stop;
}

Coordinates * Cleaner::getCoordinates() const {
    return coordinates;
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

Cleaner::Cleaner() {
    #ifdef MAP
        cout << "Appel au constructeur par défaut de <Cleaner>" << endl;
    #endif
    this->cleanerID = "";
    this->timestamp_start = chrono::system_clock::now();
    this->timestamp_stop = chrono::system_clock::now();
    this->coordinates = new Coordinates();
}

Cleaner::Cleaner(const Cleaner& other) {
    #ifdef MAP
        cout << "Appel au constructeur de copie de <Cleaner>" << endl;
    #endif
    this->cleanerID = other.cleanerID;
    this->timestamp_start = other.timestamp_start;
    this->timestamp_stop = other.timestamp_stop;
    // COPIE PROFONDE du pointeur :
    this->coordinates = new Coordinates(other.coordinates->getLatitude(), other.coordinates->getLongitude());
}

Cleaner::Cleaner(string cleanerID, Timestamp timestamp_start, Timestamp timestamp_stop, Coordinates coordinates) {
    #ifdef MAP
        cout << "Appel au constructeur de <Cleaner>" << endl;
    #endif
    this->cleanerID = cleanerID;
    this->timestamp_start = timestamp_start;
    this->timestamp_stop = timestamp_stop;
    this->coordinates = new Coordinates(coordinates.getLatitude(), coordinates.getLongitude());
}

Cleaner::Cleaner(string cleanerID, Timestamp timestamp_start, Timestamp timestamp_stop, double uneLatitude, double uneLongitude) {
    #ifdef MAP
        cout << "Appel au constructeur de <Cleaner>" << endl;
    #endif
    this->cleanerID = cleanerID;
    this->timestamp_start = timestamp_start;
    this->timestamp_stop = timestamp_stop;
    this->coordinates = new Coordinates(uneLatitude, uneLongitude);
}

Cleaner::~Cleaner() {
    #ifdef MAP
        cout << "Appel au destructeur de <Cleaner>" << endl;
    #endif
    delete coordinates;
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées