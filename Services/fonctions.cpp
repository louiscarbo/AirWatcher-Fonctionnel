#include "../Model/Coordinates.h"
#include <cmath>
#include <stdio.h>  
using namespace std;


float distance(Coordinates c1, Coordinates c2){
    return sqrt(pow(c1.getLatitude()-c2.getLatitude(),2)+pow(c1.getLongitude()-c2.getLongitude(),2));
}