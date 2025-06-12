/*************************************************************************
                           Classe  -  Measurement
*************************************************************************/

//- Interface de la classe <Measurement> (fichier Measurement.h)
#ifndef MEASUREMENT_H
#define MEASUREMENT_H
//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe Measurement
//
//
//------------------------------------------------------------------------

#include <ctime>
#include <chrono>
using Timestamp = std::chrono::time_point<std::chrono::system_clock>;
#include <string>
#include "Attribute.h"
using namespace std;


class Measurement {
    //----------------------------------------------------------------- PUBLIC
    public:
        //----------------------------------------------------- Méthodes publiques
        float getValue() const;
        // Mode d'emploi :
        // Retourne la valeur de la mesure.
        // Contrat :
        //

        string getSensorID() const;

        Attribute getAttribute() const;
        // Mode d'emploi :
        // Retourne l'attribut associé à la mesure.
        // Contrat :
        //

        Timestamp getTimeStamp() const;
        // Mode d'emploi :
        // Retourne le timestamp de la mesure.
        // Contrat :
        //

        //------------------------------------------------- Surcharge d'opérateurs

        //-------------------------------------------- Constructeurs - destructeur
        Measurement(Timestamp time, float valeur, string capteurID, Attribute attribut);
        // Mode d'emploi :
        // Constructeur de la classe Measurement.
        // Contrat :
        //
        
        Measurement();
        // Mode d'emploi :
        //
        // Contrat :
        //

        ~Measurement();
        // Mode d'emploi :
        //
        // Contrat :
        //

    //------------------------------------------------------------------ PRIVE
    protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
        Timestamp timestamp;
        float value;
        string sensorID;
        Attribute attribute;

};

//-------------------------------- Autres définitions dépendantes de <Measurement>

#endif // MEASUREMENT_H