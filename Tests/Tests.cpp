#include <iostream>
#include <string>
using namespace std;

#include "../Tests/Tests_CSVParser.cpp"
#include "../Tests/Tests_useCasesManager.cpp"


void runTests()
{
    cout << "\nExécution des tests..." << endl << endl;
    int result = 0;

    result += testCSVParser();
    result += testuseCasesManager();

    if (result == 0) {
        cout << "All tests passed successfully!" << endl;
    } else {
        cout << result << " test(s) failed." << endl << endl;
    }
}