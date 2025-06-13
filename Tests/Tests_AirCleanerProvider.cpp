#include "../Model/AirCleanerProvider.h"
#include <stdio.h>  
using Timestamp = std::chrono::time_point<std::chrono::system_clock>;
#include <string>
#include <iostream>
using namespace std;

int test_AddCleanerID()
{
    AirCleanerProvider provider("Provider1");
    provider.AddCleanerID("Cleaner1");
    provider.AddCleanerID("Cleaner2");

    const vector<string>& cleaners = provider.getCleanersID();
    if (cleaners.size() != 2) {
        cout << "Test AddCleanerID failed:\nExpected: 2 cleaners\nGot: " << cleaners.size() << " cleaners" << endl;
        return 1;
    }

    if (cleaners[0] != "Cleaner1" || cleaners[1] != "Cleaner2") {
        cout << "Test AddCleanerID failed: Cleaners do not match expected values." << endl;
        cout << "Expected: Cleaner1, Cleaner2" << endl;
        cout << "Got: " << cleaners[0] << ", " << cleaners[1] << endl;
        return 1;
    }

    return 0;
}


int testAirCleanerProvider()
{
    cout << "Running AircleanerProviders tests..." << endl;
    int resultat = 0;
    resultat += test_AddCleanerID();
    
    if (resultat == 0) {
        cout << "All tests passed successfully!" << endl << endl;
    } else {
        cout << resultat << " test(s) failed." << endl << endl;
    }

    return resultat;
}