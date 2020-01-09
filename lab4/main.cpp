#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "Resistor.h"
#include "Rparser.h"
#include "Node.h"
using namespace std;

//Calls 'parser' function of Rparser object
int main()
{
    Rparser parser1;
    parser1.parser();

    return 0;
}
