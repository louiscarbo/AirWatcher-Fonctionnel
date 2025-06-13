#include "../Utils.cpp"
using Timestamp = std::chrono::time_point<std::chrono::system_clock>;
#include <string>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <ctime>
#include <iostream>
using namespace std;

int test_Utils()
{
    string dateStr = "2023-10-01 12:00:00";
    Timestamp timestamp = parseTimestamp(dateStr);
    
    if (timestamp.time_since_epoch().count() == 0) {
        cout << "Test parseTimestamp failed: Timestamp parsing error." << endl;
        return 1;
    } else if (std::chrono::system_clock::to_time_t(timestamp) != 1696158000) { // Expected timestamp for 2023-10-01 12:00:00
        cout << "Test parseTimestamp failed: Timestamp does not match expected value." << endl;
        cout << "Expected: 1738396800\nGot: " << std::chrono::system_clock::to_time_t(timestamp) << endl;
        return 1;
    }
    
    return 0;
}

int testUtils()
{
    cout << "Running Utils tests..." << endl;
    int resultat = 0;
    resultat += test_Utils();
    
    if (resultat == 0) {
        cout << "All tests passed successfully!" << endl << endl;
    } else {
        cout << resultat << " test(s) failed." << endl << endl;
    }

    return resultat;
}