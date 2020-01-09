#include "Node.h"
#include "Resistor.h"
#include <iostream>

//default constructor that sets the number of resistors connect to the node to 0 initially.
Node::Node() {
    voltage=0;
    vAlreadySet=false;
}

//constructor that assigns a node id and next node pointer
Node::Node(int nodeid, Node* nextNode) {
    nodeID = nodeid;
    next = nextNode; 
}

//returns the nodeID
int Node::getNodeID(){
    return nodeID;
}

//sets a node voltage 
void Node::setV(double voltage_){
    voltage=voltage_;
    vAlreadySet=true;
}

//returns node voltage
double Node::getV(){
    return voltage;
}

//assigns a node voltage to nodes with unknown voltages, used in the solver
void Node:: tempSetV(double voltage_){
    voltage=voltage_;
}

//unsets a node voltage
void Node::unsetV(){
    voltage=0;
    vAlreadySet=false;
}

//adds a resistor to the node by calling 'addResistor' function of the resistor list
void Node::addResistor (string name, double resistance, int endpoints[]){
    rlist.addResistor(name, resistance, endpoints);
}

//prints resistor connections at a node by calling 'printAll' function of the resistor list
void Node::print(){
    if(rlist.getNumRes()!=0){
        cout << "Connections at node " << nodeID << ": " << rlist.getNumRes() << " resistor(s)" << endl;
        rlist.printAll();
    }
}

//destructor
Node::~Node() {
}