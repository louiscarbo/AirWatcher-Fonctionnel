/*************************************************************************
                           Classe : Attribute
*************************************************************************/

// Réalisation de la classe <Attribute> (fichier Attribute.cpp)

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <string>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Attribute.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

string Attribute::getUnit() const {
    return unit;
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

Attribute::Attribute(string attributeID, string unit, string description){
    this->attributeID = attributeID;
    this->unit = unit;
    this->description = description;
}
Attribute::Attribute(){
    attributeID = "";
    unit = "";
    description = "";
}

Attribute::~Attribute ( ){
#ifdef MAP
    cout << "Appel au destructeur de <Attribute>" << endl;
#endif
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées