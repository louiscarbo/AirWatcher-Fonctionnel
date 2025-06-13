/*************************************************************************
                           Classe  -  UseCasesManager
*************************************************************************/

//- Interface de la classe <UseCasesManager> (fichier UseCasesManager.h) -
#if ! defined ( UseCasesManager_H )
#define UseCasesManager_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

#include <vector>
#include <string>
#include <chrono>
#include "../Model/Sensor.h"
#include "../Model/Measurement.h"
#include "../Model/Attribute.h"
#include "../Model/Coordinates.h"
#include "../Model/PrivateIndividual.h"
#include "../Model/AirCleanerProvider.h"
#include "../Model/Cleaner.h"
#include "../Data/CSVParser.h"
using namespace std;


using Timestamp = std::chrono::time_point<std::chrono::system_clock>;

//------------------------------------------------------------------------
// Rôle de la classe UseCasesManager
//
//
//------------------------------------------------------------------------

class UseCasesManager 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques    
    
    vector<Attribute> getAttributes() const;
    // Mode d'emploi :
    //  Renvoie la liste de tous les attributs.
    // Contrat :

    vector<Sensor> getSensors() const;
    // Mode d'emploi :
    //  Renvoie la liste de tous les capteurs.
    // Contrat :

    vector<Measurement> getMeasurements() const;
    // Mode d'emploi :
    //  Renvoie la liste de toutes les mesures.
    // Contrat :

    vector<Cleaner> getCleaners() const;
    // Mode d'emploi :
    //  Renvoie la liste de tous les cleaners.
    // Contrat :

    vector<PrivateIndividual> getUsers() const;
    // Mode d'emploi :
    //  Renvoie la liste de tous les utilisateurs privés.
    // Contrat :

    vector<AirCleanerProvider> getProviders() const;
    // Mode d'emploi :
    //  Renvoie la liste de tous les fournisseurs de purificateurs d'air.
    // Contrat :

    vector<pair<Sensor, double>> identifySuspiciousSensors();
    // Mode d'emploi :
    //  Appeler cette méthode pour identifier les capteurs suspicieux
    //  (soit des capteurs défectueux, soit des capteurs malicieux).
    //  Elle renvoie une liste de paires (capteur, valeur) où la valeur
    //  est le score de suspicion du capteur.
    // Contrat :
    //  - La liste de capteurs doit être initialisée avant d'appeler cette méthode.

    vector<Sensor> findSensorsWithinRadius(const Coordinates& center, double radius);
    // Mode d'emploi :
    //  Renvoie une liste de capteurs situés dans un rayon donné autour d'un point central.
    //  Le rayon est en kilomètres.
    // Contrat :
    //  - center doit être un objet de type Coordinates valide.

    int ComputeAtmoIndexInArea(Coordinates centerCoords,float R, Timestamp timestamp);
    // Mode d'emploi :
    //  Calcule l'indice ATMO moyen dans une zone circulaire centrée sur
    //  les coordonnées spécifiées, avec un rayon donné.
    //  Le timestamp spécifie le moment pour lequel l'indice doit être calculé.

    
    void loadData(bool verbose = false);
    // Mode d'emploi :
    //  Charge les données à partir des fichiers CSV.

    void setPerformanceTracking(bool enabled);

    bool isPerformanceTrackingEnabled() const;
    
//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    explicit UseCasesManager(const string& dataPath);
    
    UseCasesManager ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~UseCasesManager ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    bool trackPerformance;
    string              dataPath;
    CSVParser                parser;
    vector<Attribute>          attributes;
    vector<Sensor>             sensors;
    vector<Measurement>        measurements;
    vector<Cleaner>            cleaners;
    vector<PrivateIndividual>  users;
    vector<AirCleanerProvider> providers;
};

//-------------------------------- Autres définitions dépendantes de <Xxx>

#endif // UseCasesManager

