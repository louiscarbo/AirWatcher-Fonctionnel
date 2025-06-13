#include <iostream>
#include <string>
using namespace std;

#include "../Tests/Tests_CSVParser.cpp"
#include "../Tests/Tests_useCasesManager.cpp"
#include "../Tests/Tests_Sensor.cpp"
#include "../Tests/Tests_PrivateIndividual.cpp"
#include "../Tests/Tests_Utils.cpp"
#include "../Tests/Tests_AirCleanerProvider.cpp"
#include "../Tests/Tests_Coordinates.cpp"


void runTests()
{
    cout << "\nExécution des tests..." << endl << endl;
    int result = 0;

    result += testCSVParser();
    result += testUtils();
    result += testCoordinates();
    result += testSensor();
    result += testPrivateIndividual();
    result += testAirCleanerProvider();
    result += testuseCasesManager();

    if (result == 0) {
        cout << "All tests passed successfully!" << endl;
    } else {
        cout << result << " test(s) failed." << endl << endl;
    }
}