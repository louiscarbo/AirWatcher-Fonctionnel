#include "Services/UseCasesManager.h"
#include "Presentation/Menu.h"
#include "Tests/Tests.cpp"
#include <string>
#include <iostream>
using namespace std;

int main() {

    // Initialiser les données et les cas d'utilisation
    UseCasesManager manager;
    manager.loadData(true); // Ou une méthode similaire ?

    // Exécuter les tests
    // runTests();
    
    // Initialiser le menu avec le manager
    Menu menu(manager);

    bool profileSelected = false;
    bool applicationRunning = true;

    while(applicationRunning) {

        if (!profileSelected) {
            menu.displayProfileSelectionMenu();
            profileSelected = true;
            cout << "\n\n" << endl;
        }

        // Afficher le menu principal adapté au rôle utilisateur
        menu.displayMainMenu();
        std::string optionStr = menu.getUserInput("Please select an option (1-5) or 'q' to quit: ");
        cout << "\n\n" << endl;

        if (optionStr == "q") {
            applicationRunning = false;
        } else {
            int option = std::stoi(optionStr);
            menu.selectFunctionality(option);
        }

        cout << "\n\n" << endl;
    }

    cout << "Exiting the application. Goodbye!" << endl;

    return 0;
}