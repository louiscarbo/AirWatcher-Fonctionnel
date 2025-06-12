/*************************************************************************
                           AirCleanerProvider
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <AirCleanerProvider> (fichier AirCleanerProvider.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "AirCleanerProvider.h"


//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
const string& AirCleanerProvider::GetProviderID() const {
    return providerID;
}

void AirCleanerProvider::AddCleanerID(const string& cleanerID) {
    cleanersID.push_back(cleanerID);
}

const vector<string>& AirCleanerProvider::getCleanersID() const {
    return cleanersID;
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
AirCleanerProvider::AirCleanerProvider(const string& providerID) : providerID(providerID)
{
    #ifdef MAP
    cout << "Appel constructeur <AirCleanerProvider>" << endl;
    #endif
 }

AirCleanerProvider::~AirCleanerProvider() = default;
//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

