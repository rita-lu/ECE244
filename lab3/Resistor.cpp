#include "Resistor.h"
#include <iomanip>

//Constructor that sets all objects to be 0 or empty string initially.
Resistor::Resistor()
{
    resistance = 0;
    name = "";
    endpointNodeIDs[0] = 0;
    endpointNodeIDs[1] = 0;
}

//Second constructor that sets the variables of the object to values that are passed in to the function
Resistor::Resistor(int rIndex_,string name_,double resistance_,int endpoints_[2]) {
    name = name_;
    resistance = resistance_;
    endpointNodeIDs[0]=endpoints_[0];
    endpointNodeIDs[1]=endpoints_[1];
}

//Destructor
Resistor::~Resistor() {
}

//Returns name of resistor
string Resistor::getName() const{
    return (name);
}

//Returns resistance value of a resistor
double Resistor::getResistance() const{
    return (resistance);
}
//Sets resistance of resistor
void Resistor:: setResistance (double resistance_){
    resistance = resistance_;
}

//Prints resistor information
void Resistor:: print (){
    cout << setw(20) << left << name << " " << setw(8) << right << resistance << " Ohms " << endpointNodeIDs[0] << " -> " << endpointNodeIDs[1] << endl;
}