/*************************************************************************
                           Classe : AirCleanerProvider
                             -------------------
    début                : 
    copyright            : B3232 B3235
    e-mail               : 
*************************************************************************/

//---------- Interface de la classe <useCasesManager> (fichier AirCleanerProvider.h) ----------------
#if ! defined ( AIRCLEANERPROVIDER_H )
#define AIRCLEANERPROVIDER_H

#include <string>
#include <vector>
using namespace std;

//--------------------------------------------------- Interfaces utilisées
#include "Cleaner.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <AirCleanerProvider>
//
//
//------------------------------------------------------------------------

class AirCleanerProvider
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    const string& GetProviderID() const;
    void AddCleanerID(const string& cleaner);
    const vector<string>& getCleanersID() const;

//-------------------------------------------- Constructeurs - destructeur
    explicit AirCleanerProvider(const std::string& providerID);
    ~AirCleanerProvider();

private:
//----------------------------------------------------- Méthodes protégées
//----------------------------------------------------- Attributs protégés
    string providerID;
    vector<string>  cleanersID; //stocker que les ID
};

//-------------------------------- Autres définitions dépendantes de <Xxx>

#endif // AIRCLEANERPROVIDER_H
