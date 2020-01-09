#include "Node.h"
#include "Resistor.h"
#include <iostream>

extern Resistor** resistorArray; //allows the use of the pointer to resistor array from Rparser.cpp

//Function that returns true if there is still space in the node for a resistor to be added.
bool Node::canAddResistor(int rIndex){
    if (numRes<MAX_RESISTORS_PER_NODE)
        return true;
    else
        return false;
}

//Function that adds resistor index to the array inside of the node object that stores a maximum of 5 resistors and advance index of the array.
void Node::addResistor(int rIndex){
    resIDArray[numRes] = rIndex; 
    numRes++;
}

//prints all the connections at a node by looping through the number of resistors connected to that node 
//which gives the index of resistors. Uses that index to access the resistor information in the resistor array.
void Node::print(int nodeIndex){
    cout << "Connections at node " <<  nodeIndex << ": " << numRes << " resistor(s)" << endl;
    for (int i=0; i<numRes; i++){
        cout << "  ";
        resistorArray[resIDArray[i]]->print();
    }
}

//Constructor that sets the number of resistors connect to the node to 0 initially.
Node::Node() {
    numRes =0;
}

//Destructor
Node::~Node() {
}