//This program allows to user to insert, modify, delete and print a resistor
//Allows the printing node resistors and solving of node voltages that are not set to a certain voltage.
// delete a resistor by making use of classes, objects, and arrays.
#include "Node.h"
#include "Resistor.h"
#include "NodeList.h"
#include "Rparser.h"
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;


Rparser:: Rparser(){
}

int Rparser:: parser() {
    //declaration of variables
    string line;
    string command;
    bool moreLines = true;
  
    //gets a line from a user, if 'eof', end file
    cout << "> ";
    getline(cin, line);
    if (cin.eof())
       moreLines = false;  
    
    //while the user hasn't exited, run this code
    while (moreLines) {   
        stringstream myOwnStringStream(line); //get string stream from user

        myOwnStringStream >> command; 
        if ((command != "insertR") && (command != "modifyR") && (command != "printR") && (command != "printNode") 
                && (command != "deleteR") && (command != "setV") && (command != "unsetV") && (command != "solve")){
            cout << "Error: invalid command" << endl;
        }
        else {
            // If the command is to insert a resistor
            if (command == "insertR"){
                insertR (myOwnStringStream);
            }
            // If the command is to modify a resistor value
            else if (command == "modifyR"){
                modifyR (myOwnStringStream);
            }
            //If the command is to print a resistor.
            else if (command == "printR"){
                printR (myOwnStringStream);
            }
            // If the command is to print a node.
            else if (command == "printNode"){
                printNode (myOwnStringStream);
            }
            //If the command is to delete a resistor
            else if (command == "deleteR"){
                deleteR (myOwnStringStream);
            }
            //If the command is to set a node voltage
            else if (command == "setV"){
                setV (myOwnStringStream);
            }
            //If the command is to unset a node voltage
            else if (command == "unsetV"){
                unsetV (myOwnStringStream);
            }
            //If the command is to solve for unknown node voltages
            else if (command == "solve"){
                solve ();
            }
        }
        // when the line has been processed and an output is given, receive next line from user.
        cout << "> ";
        getline(cin, line);
        
        // if the user ends the file, the program exits and memory is deleted. Otherwise, processes another line.
        if (cin.eof()){
            moreLines = false;
        }
        else
           moreLines = true;
        }
        
        //deletes all resistors connected to all nodes and then deletes all nodes
        nlist.deleteAllNodes();
        return 0;
    }

//Function to insert a resistor
void Rparser::insertR (stringstream& myOwnStringStream){
    string resistorName;
    double resistance;
    int nodeid1, nodeid2;
    myOwnStringStream >> resistorName >> resistance >> nodeid1 >> nodeid2;
 
    int endpointNodes[2]; //create array that stores the 2 endpoint nodes
    endpointNodes[0]=nodeid1;
    endpointNodes[1]=nodeid2; 
    
    //tries to find a resistor in node list and if the resistor doesn't exist, insert it into the 2 nodes.
    Resistor* temp = nlist.FindResistor(resistorName);
    if(temp==NULL){  
        //returns pointers to the first node and second node if found, otherwise create a new nodes
        Node* n1 = nlist.FindOrInsertNode (nodeid1);
        Node* n2 = nlist.FindOrInsertNode (nodeid2);
        //adds new resistor to both nodes
        n1->addResistor(resistorName, resistance, endpointNodes);
        n2->addResistor(resistorName, resistance, endpointNodes);
        cout << "Inserted: resistor " << resistorName << " " << fixed << setprecision(2) << resistance << " Ohms " <<
        nodeid1 << " -> " << nodeid2 <<endl;      
    }
    else
       cout << "Error: resistor " << resistorName << " already exists" << endl;
    
    myOwnStringStream.clear();
    myOwnStringStream.ignore(1000,'\n');
}

//Function to modify a resistor value
void Rparser:: modifyR (stringstream& myOwnStringStream){
    string resistorName;
    double resistance;
    myOwnStringStream >> resistorName >> resistance;
    
    //modifies resistance of resistor if resistor exists, and returns old resistor value. Otherwise, return -1 if doesn't exist
    double oldresistance = nlist.modifyResistance(resistorName, resistance);
    if (oldresistance==-1)
        cout << "Error: resistor " << resistorName << " not found" << endl;
    else cout << "Modified: resistor " << resistorName << " from " << oldresistance << " Ohms to " << resistance << " Ohms" << endl;
  
    myOwnStringStream.clear();
    myOwnStringStream.ignore(1000,'\n');
}
 
//Function to print a resistor or all resistors.
void Rparser:: printR(stringstream& myOwnStringStream){
    string resistorName;
    myOwnStringStream >> resistorName;
    
    //prints resistor if found
    Resistor* temp;
    temp=nlist.FindResistor(resistorName);
    if (temp==NULL) cout << "Error: resistor " << resistorName << " not found" << endl;
    else{
        cout << "Print:" << endl;
        temp->print();
    }
       
    myOwnStringStream.clear();
    myOwnStringStream.ignore(1000,'\n');
}


//Function to print a node or all nodes
void Rparser::printNode (stringstream& myOwnStringStream){
    string selection;
    int nodeid1;
    char ch;
    //use peek to see if the first character of the second argument is an 'a' or a number.
    myOwnStringStream.ignore (1000,' ');
    ch=myOwnStringStream.peek();
    
    //if the character is an 'a' store argument in a string and check if the argument is 'all'. If yes, print all nodes and node resistors
    if (ch=='a'){
        myOwnStringStream >> selection;
        if (selection=="all"){
            cout << "Print:" << endl;   
            nlist.printAllNodes();
        }
    }
    //if printing one node info, looks for node and prints all resistor values connected to that node
    else{
       myOwnStringStream >> nodeid1;
       Node* temp = nlist.FindNode(nodeid1);
       if (temp==NULL) cout << "Error: " << nodeid1 << " is not found";
       else{
            cout << "Print:" << endl;
            nlist.FindNode(nodeid1)->print();
       }
    }    
    myOwnStringStream.clear();
    myOwnStringStream.ignore(1000,'\n');
}

//Function to delete all resistors
void Rparser::deleteR (stringstream& myOwnStringStream){
    string selection;
    myOwnStringStream >> selection;
    
    //delete all nodes and resistors
    if (selection =="all"){
        cout << "Deleted: all resistors"<< endl;  
        nlist.deleteAllNodes();
    }
    
    //delete one resistor
    else {
        bool deletedR = nlist.deleteOneResistor(selection);
        if (deletedR) cout << "Deleted: resistor " << selection << endl;
        else cout << "Error: resistor " << selection << " not found" << endl;       
    }
}  

//set a node voltage if the node exists
void Rparser::setV (stringstream& myOwnStringStream){
    int nodeid;
    double voltage;
    myOwnStringStream >> nodeid >> voltage;
    
    Node* temp = nlist.FindNode(nodeid);
    if (temp==NULL) cout << "Error: node " << nodeid << " not found" << endl;
    else {
        temp->setV(voltage); 
        cout << "Set: node " << nodeid << " to " << voltage << " Volts" << endl; 
    }
}

//unset a node voltage if the node exists
void Rparser::unsetV (stringstream& myOwnStringStream){
    int nodeid;
    double voltage;
    myOwnStringStream >> nodeid >> voltage;
    
    Node* temp = nlist.FindNode(nodeid);
    if (temp==NULL) cout << "Error: node " << nodeid << " not found" << endl;
    else {
        temp->unsetV(); 
        cout << "Unset: the solver will determine the voltage of node " << nodeid << endl;
    }
}

//solves unknown node voltages if at least one node has its voltage set
void Rparser::solve (){
    if (!nlist.isAnyVoltageSet()) cout << "Error: no nodes have their voltage set" << endl;
    else{
        cout << "Solve:" << endl;
        nlist.solve(); 
    }
}