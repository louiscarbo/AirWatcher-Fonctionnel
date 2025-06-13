/*************************************************************************
                           Menu
*************************************************************************/

//---------- Réalisation de la classe <Menu> (fichier Menu.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <string>
#include <ctime>
#include <chrono>

//------------------------------------------------------ Include personnel
#include "Menu.h"
#include "../Model/Coordinates.h"
#include "../Utils.cpp"
using Timestamp = std::chrono::time_point<std::chrono::system_clock>;


//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Menu::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

void Menu::displayProfileSelectionMenu()
{
    #ifdef MAP
        cout << "Appel à displayProfileSelectionMenu" << endl;
    #endif
    cout << "--- Profile Selection ---" << endl;
    cout << "1. Private Individual" << endl;
    cout << "2. Government Agency" << endl;
    cout << "3. Air Cleaner Provider" << endl;
    cout << "Please select a profile (1-3): ";

    int choice;
    bool validChoice = false;
    
    while (!validChoice)
    {
        cin >> choice;
        
        if (choice < 1 || choice > 3)
        {
            cin.clear();
            cout << "Invalid choice. Please select a valid profile (1-3): ";
        } else {
            validChoice = true;
            selectedProfile = choice;
            cout << "Profile selected." << endl;
        }
    }
}

void Menu::displayMainMenu()
{
    #ifdef MAP
        cout << "Appel à displayMainMenu" << endl;
    #endif
    
    cout << "--- Menu ---" << endl;
    
    cout << "1. Calculate Air Quality at a Precise Moment and Geography" << endl;
    cout << "2. Calculate the Average Air Quality in a Given Area" << endl;
    cout << "3. Identify Areas with Similar Air Quality" << endl;
    cout << "4. Observe Impact of the Cleaners on Air Quality" << endl;

    if (selectedProfile == 1) // Private Individual
    {
        cout << "5. Consult your Awarded Points" << endl;
    }

    if (selectedProfile == 2) // Government Agency
    {
        cout << "5. Identify malfunctioning or malicious sensors" << endl;
    }

    cout << "6. Turn on/off performance tracking" << endl;
}

std::string Menu::getUserInput(const std::string &prompt)
{
    #ifdef MAP
        cout << "Appel à getUserInput avec prompt: " << prompt << endl;
    #endif
    
    cout << prompt;
    std::string input;
    cin >> input;
    return input;
}

//------------------------------------------------- Surcharge d'opérateurs
//-------------------------------------------- Constructeurs - destructeur
Menu::Menu(UseCasesManager &useCasesManager)
    : manager(useCasesManager)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Menu>" << endl;
#endif
} //----- Fin de Menu

Menu::~Menu()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Menu>" << endl;
#endif
} //----- Fin de ~Menu

//------------------------------------------------------------------ PRIVE

void Menu::selectFunctionality(int option)
{
    #ifdef MAP
        cout << "Appel à selectFunctionality avec option: " << option << endl;
    #endif
    
    switch (option)
    {
        case 1:
            calculateAirQualityAtMoment();
            break;
        case 2:
            calculateMeanAirQualityArea();
            break;
        case 3:
            identifyAreasWithSimilarAirQuality();
            break;
        case 4:
            observeCleanerImpact();
            break;
        case 5:
            if (selectedProfile == 1) // Utilisateur
            {
                consultUserPoints();
            } else if (selectedProfile == 2) {
                identifyMalfunctioningSensors();
            } else {
                cout << "Invalid Option. Please try again." << endl;
            }
            break;
        case 6:
        {
            bool currentState = manager.isPerformanceTrackingEnabled();
            manager.setPerformanceTracking(!currentState);
            cout << "Performance tracking is now " << (currentState ? "disabled." : "enabled.") << endl;
            break;
        }
        default:
            cout << "Invalid Option. Please try again." << endl;
            break;
    }
}

void Menu::calculateAirQualityAtMoment()
{
    #ifdef MAP
        cout << "Appel à calculateAirQualityAtMoment" << endl;
    #endif
    
    cout << "--- Calculate Air Quality at a Precise Moment and Geography ---" << endl;
    cout << "Not Implemented." << endl;
}

void Menu::calculateMeanAirQualityArea()
{
    #ifdef MAP
        std::cout << "Appel à calculateMeanAirQualityArea" << std::endl;
    #endif
    
    std::cout << "\n--- Calculate the Average Air Quality in a Given Area ---\n";

    // Lecture des coordonnées
    std::string coordInput = getUserInput("Enter center coordinates (lat,lon): ");
    Coordinates center = Coordinates::parseCoordinates(coordInput);

    std::string radiusInput = getUserInput("Enter radius (km): ");
    float radius = std::stof(radiusInput);

    // Lecture de l'instant souhaité
    std::string tsInput = getUserInput("Enter timestamp (YYYY-MM-DD HH:MM:SS): ");
    Timestamp ts = parseTimestamp(tsInput);

    std::time_t tt = std::chrono::system_clock::to_time_t(ts);
    std::cout << "Parsed timestamp : " << std::ctime(&tt);

    // Calcul avec le Manager
    int result = manager.ComputeAtmoIndexInArea(center, radius, ts);

    // Affichage du résultat
    if (result < 0) {
        std::cout << "No data available at that time or within that area.\n";
    } else {
        std::cout << "Mean ATMO index over the area: " << result << "\n";
    }
}

void Menu::identifyAreasWithSimilarAirQuality()
{
    #ifdef MAP
        cout << "Appel à identifyAreasWithSimilarAirQuality" << endl;
    #endif
    
    cout << "--- Identify Areas with Similar Air Quality ---" << endl;
    cout << "Not Implemented." << endl;
}

void Menu::identifyMalfunctioningSensors()
{
    #ifdef MAP
        std::cout << "Appel à identifyMalfunctioningSensors" << std::endl;
    #endif
    
    std::cout << "\n--- Identify Malfunctioning or Malicious Sensors ---\n";

    
    auto scored = manager.identifySuspiciousSensors();

    if (scored.empty()) {
        std::cout << "No sensors found.\n";
        return;
    }

    std::cout << "\nSensor ID     | Suspicion Score\n";
    std::cout << "--------------+----------------\n";
    for (auto &p : scored) {
        const Sensor &s = p.first;
        double score   = p.second;
        std::cout 
            << s.getSensorID() 
            << std::string(14 - s.getSensorID().size(), ' ')
            << "| " 
            << score 
            << "\n";
    }
    std::cout << std::endl;
}

void Menu::observeCleanerImpact()
{
    #ifdef MAP
        cout << "Appel à observeCleanerImpact" << endl;
    #endif
    
    cout << "--- Observe Impact of the Cleaners on Air Quality ---" << endl;
    cout << "Not Implemented." << endl;
}

void Menu::consultUserPoints()
{
    #ifdef MAP
        cout << "Appel à consultUserPoints" << endl;
    #endif
    
    cout << "--- Consult User Points ---" << endl;
    cout << "Not Implemented." << endl;
}

//----------------------------------------------------- Méthodes protégées
