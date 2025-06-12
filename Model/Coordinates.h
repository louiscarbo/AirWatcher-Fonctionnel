/*************************************************************************
                           Classe  -  Coordinates
*************************************************************************/

//- Interface de la classe <Coordinates> (fichier Coordinates.h) -
#if ! defined ( Coordinates_H )
#define Coordinates_H

//--------------------------------------------------- Interfaces utilisées
#include <string>

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe Coordinates
//
//
//------------------------------------------------------------------------

class Coordinates 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques    

    double getLatitude() const;

    double getLongitude() const;

    static Coordinates parseCoordinates(const std::string &input);

    static float distance(const Coordinates &c1, const Coordinates &c2);
    // Mode d'emploi :
    //   Renvoie la distance entre deux coordonnées en kilomètres.

//------------------------------------------------- Surcharge d'opérateurs

    Coordinates& operator=(const Coordinates& other);

//-------------------------------------------- Constructeurs - destructeur
    Coordinates ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    Coordinates (double uneLatitude, double uneLongitude);
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Coordinates ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    Coordinates(const Coordinates& other);

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    double latitude;
    double longitude;
};

//-------------------------------- Autres définitions dépendantes de <Xxx>

#endif // Coordinates
