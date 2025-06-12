/*************************************************************************
                                Menu
*************************************************************************/

//---------- Interface de la classe <Menu> (fichier Menu.h) ----------------
#include "../Services/UseCasesManager.h"
#if ! defined ( Menu_H )
#define Menu_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Menu>
//  Afficher le menu principal de l'application AirWatcher
//------------------------------------------------------------------------

class Menu
{
//----------------------------------------------------------------- PUBLIC
UseCasesManager &manager;
int selectedProfile;

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //

    void displayProfileSelectionMenu();
    // Mode d'emploi :
    //  Affiche le menu de sélection de profil utilisateur.

    void displayMainMenu();
    // Mode d'emploi :
    //  Affiche le menu principal adapté au rôle utilisateur sélectionné.

    std::string getUserInput(const std::string &prompt);
    // Mode d'emploi :
    //  Affiche un message de prompt et lit l'entrée de l'utilisateur.

    void selectFunctionality(int option);
    // Mode d'emploi :
    //  Sélectionne la fonctionnalité à exécuter en fonction de l'option
    //  choisie.


//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    Menu ( UseCasesManager &useCasesManager );
    // Mode d'emploi :
    //  Constructeur par défaut de la classe Menu.
    // Contrat :
    //  - useCasesManager doit être un objet de type UseCasesManager valide

    virtual ~Menu ( );
    // Mode d'emploi :
    //  Destructeur de la classe Menu.

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
    void calculateAirQualityAtMoment();
    // Mode d'emploi :
    //  Affiche le menu correspondant au calcul de la qualité de l'air à un
    //  moment donné et appelle la méthode appropriée du UseCasesManager.

    void calculateMeanAirQualityArea();
    // Mode d'emploi :
    //  Affiche le menu correspondant au calcul de la qualité de l'air moyenne
    //  dans une zone et appelle la méthode appropriée du UseCasesManager.

    void identifyAreasWithSimilarAirQuality();
    // Mode d'emploi :
    //  Affiche le menu correspondant à l'identification des zones avec une
    //  qualité de l'air similaire et appelle la méthode appropriée du
    //  UseCasesManager.

    void identifyMalfunctioningSensors();
    // Mode d'emploi :
    //  Affiche le menu correspondant à l'identification des capteurs
    //  défectueux et appelle la méthode appropriée du UseCasesManager.

    void observeCleanerImpact();
    // Mode d'emploi :
    //  Affiche le menu correspondant à l'observation de l'impact des
    //  nettoyeurs sur la qualité de l'air et appelle la méthode appropriée
    //  du UseCasesManager.

    void consultUserPoints();
    // Mode d'emploi :
    //  Affiche le menu correspondant à la consultation des points
    //  attribués à l'utilisateur et appelle la méthode appropriée du
    //  UseCasesManager.


//----------------------------------------------------- Attributs protégés

};

//-------------------------------- Autres définitions dépendantes de <Menu>

#endif // Menu_H

