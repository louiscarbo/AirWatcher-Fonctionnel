/*************************************************************************
                           Classe : PrivateIndividual
                             -------------------
    début                : 
    copyright            : B3232 B3235
    e-mail               : 
*************************************************************************/

//---------- Interface de la classe <PrivateIndividual> ----------------
#if ! defined ( PRIVATEINDIVIDUAL_H )
#define PRIVATEINDIVIDUAL_H

#include <string>
#include <vector>

//--------------------------------------------------- Interfaces utilisées
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <PrivateIndividual>
//
//
//------------------------------------------------------------------------

class PrivateIndividual {
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void AddPoints(int delta);
    // met à jour le nombre de points de l'utilisateur à chaque utilisation de ses données

    void MarkUnreliable();
    // par défaut, user reliable, cette méthode le rend non fiable

    int getPoints() const;

    int getIdUser() const;

    std::string getUserName() const;

    bool getIsReliable() const;

    std::vector<std::string> getSensorsIDs() const;

    void AddSensor(const string& sensorId);
//-------------------------------------------- Constructeurs - destructeur

    PrivateIndividual (const string &unUserName, bool isReliable, int points);
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    PrivateIndividual ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~PrivateIndividual ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

private:
    static int nextId; //compteur pour générer les id auto
    int idUser;
    std::string userName;
    bool isReliable;
    int points;
    std::vector<std::string> sensorsIDs;
//----------------------------------------------------- Méthodes protégées
    static int generateNextId();

};

#endif
