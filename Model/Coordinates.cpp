/*************************************************************************
                           Classe : Coordinates
*************************************************************************/

// Réalisation de la classe <Coordinates> (fichier Coordinates.cpp)

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include "Coordinates.h"
#include <string>
#include <stdexcept>
#include <cmath>
#include <iostream>
using namespace std;

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

double Coordinates::getLatitude() const {
    return latitude;
}

double Coordinates::getLongitude() const {
    return longitude;
}

Coordinates Coordinates::parseCoordinates(const std::string &input) {
    size_t commaPos = input.find(',');
    if (commaPos == std::string::npos) {
        throw std::invalid_argument("Invalid coordinate format. Use 'latitude,longitude'.");
    }
    
    double lat = std::stod(input.substr(0, commaPos));
    double lon = std::stod(input.substr(commaPos + 1));
    
    return Coordinates(lat, lon);
}

float Coordinates::distance(const Coordinates &c1, const Coordinates &c2) {
    double latDiff = c1.latitude - c2.latitude;
    double lonDiff = c1.longitude - c2.longitude;
    return static_cast<float>(sqrt(latDiff * latDiff + lonDiff * lonDiff));
}

//------------------------------------------------- Surcharge d'opérateurs

Coordinates& Coordinates::operator=(const Coordinates& other) {
    #ifdef MAP
        cout << "Appel à l'opérateur d'assignation de <Coordinates>" << endl;
    #endif
    if (this != &other) {
        this->latitude = other.latitude;
        this->longitude = other.longitude;
    }
    return *this;
}

//-------------------------------------------- Constructeurs - destructeur

Coordinates::Coordinates() {
    #ifdef MAP
        cout << "Appel au constructeur par défault de <Coordinates>" << endl;
    #endif
    this->latitude = 0.0;
    this->longitude = 0.0;
}

Coordinates::Coordinates(double uneLatitude, double uneLongitude) {
    #ifdef MAP
        cout << "Appel au constructeur de <Coordinates>" << endl;
    #endif
    this->latitude = uneLatitude;
    this->longitude = uneLongitude;
}

Coordinates::~Coordinates() {
    #ifdef MAP
        cout << "Appel au destructeur de <Coordinates>" << endl;
    #endif
}

Coordinates::Coordinates(const Coordinates& other) {
    #ifdef MAP
        cout << "Appel au constructeur de copie de <Coordinates>" << endl;
    #endif
    this->latitude = other.latitude;
    this->longitude = other.longitude;
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées