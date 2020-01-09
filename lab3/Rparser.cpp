//This program allows to user to insert, modify, print a resistor, print a node value
// delete a resistor by making use of classes, objects, and arrays.
#include "Node.h"
#include "Resistor.h"
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

//declaring variables and pointer to array of objects for resistors and nodes
int resIndex=0;
Node* nodeArray;
Resistor** resistorArray;
int maxNodeNumber, maxResistors;

//declaring global functions
bool resistorNotFound(string);
void deleteMemory();

int Rparser() {
    //declaration of variables
    string line;
    string command;
    bool moreLines = true;
   
    //declaration of functions that deal with the different commands
    void insertR (stringstream&);
    void modifyR (stringstream&);
    void printR (stringstream&);
    void printNode (stringstream&);
    void deleteR (stringstream&);
    void maxVal (stringstream&);
  
    //gets a line from a user, if 'eof', end file
    cout << "> ";
    getline(cin, line);
    stringstream myOwnStringStream(line);
    
    //stores the different arguments of maxval line into different variables
    myOwnStringStream >> command >> maxNodeNumber >> maxResistors;
    
    //checks to see if the arguments are valid
    while (maxNodeNumber <= 0 || maxResistors <= 0){
        cout << "Error: maxVal arguments must be greater than 0" <<endl;
        cout << "> ";
        getline(cin, line);
        stringstream myOwnStringStream(line);
         myOwnStringStream >> command >> maxNodeNumber >> maxResistors;
    }
    cout << "New network: max node number is " << maxNodeNumber << "; max resistors is " << maxResistors <<endl;
    
    //dynamically allocate 2 arrays of objects according to size given by arguments
    nodeArray = new Node [maxNodeNumber+1];
    resistorArray = new Resistor* [maxResistors];
    
    //gets the second line from user. If EOF, delete dynamically allocated memory.
    cout << "> ";
    getline(cin, line);
    if (cin.eof()) {
       moreLines = false;
       deleteMemory();   
    }
   
    //while the user hasn't exited, run this code
    while (moreLines) {   
        stringstream myOwnStringStream(line); //get string stream from user

        myOwnStringStream >> command; 
        if ((command != "insertR") && (command != "modifyR") && (command != "printR") && (command != "printNode") 
                && (command != "deleteR") && (command != "maxVal")){
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
            // If the command is to reallocate new node and resistor arrays of a different size
            else if (command == "maxVal"){
                maxVal(myOwnStringStream);
            }
            //If the command is to delete a resistor
            else if (command == "deleteR"){
                deleteR (myOwnStringStream);
            }
        }
        // when the line has been processed and an output is given, receive next line from user.
        cout << "> ";
        getline(cin, line);
        
        // if the user ends the file, the program exits and memory is deleted. Otherwise, processes another line.
        if (cin.eof()){
            moreLines = false;
            deleteMemory();
        }
        else
           moreLines = true;
        }
        return 0;
    }

//Function to insert a resistor
void insertR (stringstream& myOwnStringStream){
    string resistorName;
    double resistance;
    int nodeid1, nodeid2;
    bool doubleRes=false; //variable that tells if there is already another  resistor of the same name that exists
    myOwnStringStream >> resistorName >> resistance >> nodeid1 >> nodeid2;
    
    //loops through the resistor array to see if there is another resistor of the same name already.
    //if the same resistor already exists, doubleRes is set to true.
    for (int i =0; i<resIndex; i++)
        if (resistorArray[i]->getName()==resistorName)
            doubleRes=true;    
    
    if (nodeid2<0 || nodeid2>maxNodeNumber) //if the node is out of range of 0 to the max node number.
        cout << "Error: node " << nodeid2<< " is out of permitted range 0-" << maxNodeNumber << endl;
    //if the index of the resistor array is over the amount of maximum resistors number, resistor array is full.
    else if(resIndex>=maxResistors) 
        cout << "Error: resistor array is full" << endl;
    //if node array is full as indicated by the Node class function called 'canAddResistor'
    else if (!nodeArray[nodeid1].canAddResistor(resIndex) || !nodeArray[nodeid2].canAddResistor(resIndex)) //
        cout << "Error: node is full" << endl;
    //if there is already a resistor of the same name that exists, as indicated by the boolean 'doubleRes' variable.
    else if (doubleRes)
        cout << "Error: resistor " << resistorName << " already exists" << endl; 
    //if you are inserting a resistor that connects to the same node, outputs an error
    else if (nodeid2==nodeid1)
        cout << "Error: both terminals of resistor connect to node " << nodeid2 <<endl;
    //if no errors, insert the resistor
    else{
        cout << "Inserted: resistor " << resistorName << " " << fixed << setprecision(2) << resistance << " Ohms " <<
        nodeid1 << " -> " << nodeid2 <<endl;
        
        int endpointNodes[2]; //create array that stores the 2 endpoint nodes
        endpointNodes[0]=nodeid1;
        endpointNodes[1]=nodeid2; 
        
        //creating objects in the indices of the resistor and node arrays
        resistorArray[resIndex]= new Resistor(resIndex,resistorName, resistance, endpointNodes);  
        nodeArray[nodeid1].addResistor(resIndex);
        nodeArray[nodeid2].addResistor(resIndex);
        resIndex++;
    }
    myOwnStringStream.clear();
    myOwnStringStream.ignore(1000,'\n');
}

//Function to modify a resistor value
void modifyR (stringstream& myOwnStringStream){
    string resistorName;
    double resistance;
 
    myOwnStringStream >> resistorName >> resistance;
    
    //if the resistor the user is trying to modify is not found in the resistor array, output error.
    //otherwise, look for the resistor in the resistor array and set it its resistance to the new resistance.
    if (resistorNotFound(resistorName)){
        cout << "Error: resistor " << resistorName << "not found" << endl;
    }
    else{
        for (int i =0; i<resIndex; i++){
            if(resistorArray[i]->getName()==resistorName){
                cout << "Modified: resistor " << resistorName << " from " <<  resistorArray[i]->getResistance() << "Ohms  to "  << fixed << setprecision(2) << resistance << " Ohms" <<endl;
                resistorArray[i]->setResistance(resistance);
            }
        }   
    }
    myOwnStringStream.clear();
    myOwnStringStream.ignore(1000,'\n');
}
 
//Function to print a resistor or all resistors.
void printR(stringstream& myOwnStringStream){
    string resistorName;

    myOwnStringStream >> resistorName;
    
    //if printing all resistors, loop through the resistor array and print the information of each resistor
    if (resistorName=="all"){
        cout << "Print:"<< endl;
        for (int i=0; i<resIndex; i++)
            resistorArray[i]->print();
    }
    //if trying to print a specific resistor and the resistor name is not found, print an error.
    else if (resistorNotFound(resistorName)){
        cout << "Error: resistor " << resistorName << " not found" << endl;
    }
    //otherwise, resistor name exists and loops through resistor array to find the resistor and print its information.
    else{
        cout << "Print:" <<endl;
        for (int i =0; i<resIndex; i++){
            string name =resistorArray[i]->getName();
            if(name == resistorName)
                resistorArray[i]->print();
        }
    }
    myOwnStringStream.clear();
    myOwnStringStream.ignore(1000,'\n');
}


//Function to print a node or all nodes
void printNode (stringstream& myOwnStringStream){
    string selection;
    int nodeid1;
    char ch;
    //use peek to see if the first character of the second argument is an 'a' or a number.
    myOwnStringStream.ignore (1000,' ');
    ch=myOwnStringStream.peek();
    
    //if the character is an 'a' store argument in a string and check if the argument is 'all'.
    //if it is, loop through the nodes and print all the resistors' information in each node
    if (ch=='a'){
        myOwnStringStream >> selection;
        if (selection=="all")
            cout << "Print:" << endl;
            for (int i=0; i<=maxNodeNumber; i++)
                nodeArray[i].print(i);   
    }
    //if the character is a number, store argument in an int and check if the node is valid.
    //if it is, print the resistors' information in that node.
    else{
       myOwnStringStream >> nodeid1;
       if (nodeid1<0 || nodeid1 > maxNodeNumber)
            cout << "Error: node " << nodeid1 << " is out of permitted range 0-"<< maxNodeNumber <<endl;
       else{
           cout << "Print:" << endl;
           nodeArray[nodeid1].print(nodeid1);
       }
    }
    myOwnStringStream.clear();
    myOwnStringStream.ignore(1000,'\n');
}

//Function to delete all resistors
void deleteR (stringstream& myOwnStringStream){
    //delete all memory and allocate new arrays with the same size as before
    deleteMemory();
    cout << "Deleted: all resistors"<< endl;
    nodeArray = new Node [maxNodeNumber+1];
    resistorArray = new Resistor* [maxResistors];
    resIndex=0;    
}

//Function to change the size of the resistor and node arrays.
void maxVal (stringstream& myOwnStringStream){
    myOwnStringStream >> maxNodeNumber >> maxResistors;
    //Checks to see if arguments are positive. If not, outputs error.
    if (maxNodeNumber <= 0 || maxResistors <= 0)
        cout << "Error: maxVal arguments must be greater than 0" <<endl;
    //if arguments are positive, delete the old resistor and node arrays and allocate new memory
    else{
        cout << "New network: max node number is " << maxNodeNumber << "; max resistors is " << maxResistors <<endl;
        deleteMemory();
        nodeArray = new Node [maxNodeNumber+1];
        resistorArray = new Resistor* [maxResistors];
        resIndex=0;
    }
    myOwnStringStream.clear();
    myOwnStringStream.ignore(1000,'\n');
}

//Function that checks if a resistor name is not found in the resistor array
//if the resistor is found, return false. Otherwise return true.
bool resistorNotFound(string resistorName){
    for (int i =0; i<resIndex; i++){
        if (resistorArray[i]->getName()==resistorName)
            return false;
    }  
    return true;
}

//Function that deletes dynamically allocated memory.
void deleteMemory(){
    //loops through array to delete all pointers of the resistor array and sets the pointers to NULL
    for (int i=0; i<resIndex; i++){ 
        delete resistorArray[i];
        resistorArray[i]=NULL;
    }
    delete [] resistorArray;
    resistorArray=NULL;
    delete [] nodeArray;
    nodeArray=NULL;
}