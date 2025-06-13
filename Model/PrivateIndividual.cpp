/*************************************************************************
                           PrivateIndividual
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <PrivateIndividual> ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <string>
using namespace std;

//------------------------------------------------------ Include personnel
#include "PrivateIndividual.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC
int PrivateIndividual::nextId = 1;
//----------------------------------------------------- Méthodes publiques

int PrivateIndividual::getPoints() const {
    return points;
}

int PrivateIndividual::getIdUser() const {
    return idUser;
}

string PrivateIndividual::getUserName() const {
    return userName;
}

bool PrivateIndividual::getIsReliable() const {
    return isReliable;
}

vector<string> PrivateIndividual::getSensorsIDs() const {
    return sensorsIDs;
}

void PrivateIndividual::AddPoints(int delta) {
    points += delta;
}

void PrivateIndividual::MarkUnreliable() {
    isReliable = false;
}

void PrivateIndividual::AddSensor (const string& sensorId){
    sensorsIDs.push_back(sensorId);
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
PrivateIndividual::PrivateIndividual (const string& unUserName, bool isReliable, int points):
    idUser(generateNextId()),userName(unUserName),isReliable(isReliable),points(points),sensorsIDs() {}

PrivateIndividual::PrivateIndividual() :
    idUser(generateNextId()),userName(""),isReliable(true),points(0),sensorsIDs() {}

PrivateIndividual::~PrivateIndividual () = default;
//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
int PrivateIndividual::generateNextId(){
    return nextId++;
}