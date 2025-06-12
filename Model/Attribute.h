/*************************************************************************
                           Classe  -  Attribute
*************************************************************************/

//- Interface de la classe <Attribute> (fichier Attribute.h)
#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H
//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe Attribute
//
//
//------------------------------------------------------------------------
#include <string>
using namespace std;

class Attribute {
    //----------------------------------------------------------------- PUBLIC
    public:
        //----------------------------------------------------- Méthodes publiques
        string getUnit() const;
        // Mode d'emploi :
        // Retourne l'unité de l'attribut.
        // Contrat :
        //

        string getAttributeID() const;

        //------------------------------------------------- Surcharge d'opérateurs

        //-------------------------------------------- Constructeurs - destructeur

        Attribute(string attributeID, string unit, string description);
        // Mode d'emploi :
        //
        // Contrat :
        //

        Attribute();
        // Mode d'emploi :
        //
        // Contrat :
        //

        
        
        ~Attribute();
        // Mode d'emploi :
        // Destructeur de la classe Attribute.
        // Contrat :
        //

        //------------------------------------------------------------------ PRIVE
    protected:
        //----------------------------------------------------- Méthodes protégées

        //----------------------------------------------------- Attributs protégés
        string attributeID;
        string unit;
        string description;

};

//-------------------------------- Autres définitions dépendantes de <Attribute>

#endif // ATTRIBUTE_H