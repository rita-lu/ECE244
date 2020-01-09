#include "Resistor.h"
#include <iomanip>

//Constructor
Resistor::Resistor()
{
    resistance = 0;
    name = "";
    endpointNodeIDs[0] = 0;
    endpointNodeIDs[1] = 0;
}

//Second constructor that sets the values of member variables
Resistor::Resistor(string name_,double resistance_,int endpoints_[2], Resistor* next_) {
    name = name_;
    resistance = resistance_;
    endpointNodeIDs[0]=endpoints_[0];
    endpointNodeIDs[1]=endpoints_[1];
    next = next_;
}

//returns first node that resistor is connected to.
int Resistor::getEndpoint1(){
    return endpointNodeIDs[0];
}

//returns second node that resistor is connected to.
int Resistor::getEndpoint2(){
    return endpointNodeIDs[1];
}

//returns the next pointer of the resistor
Resistor* Resistor::getNext(){
    return next;
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

//Destructor
Resistor::~Resistor() {
}
