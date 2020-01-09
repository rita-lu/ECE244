/*This program allows to user to insert, modify, print a resistor, print a node value or delete a resistor.
 The program checks for any invalid arguments, errors in values and proper number of arguments in a line.
 The program will exit when the user enters CTRL-D which will send an End-Of-File (EOF) marker.*/

#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

//This is the constant that defines the maximum value for a node number.
#define MAX_NODE_NUMBER 5000

int main() {
    //declaration of variables
    string line;
    string command;
    bool moreLines = true;

    //declaration of functions to check if argument is invalid or if there is too few arguments.
    bool checkInvalid(stringstream&);
    bool checkTooFew(stringstream&);
    
    //declaration of functions that deal with the different commands
    void insertR (stringstream&);
    void modifyR (stringstream&);
    void printR (stringstream&);
    void printNode (stringstream&);
    void deleteR (stringstream&);
    
    //gets a line from a user, if 'eof', end file
    cout << "> ";
    getline(cin, line);
    if (cin.eof()) {
       moreLines = false;
    }
   
    //Until the user has ended the file, run this code
    while (moreLines) {
        
        stringstream myOwnStringStream(line); //get string stream from user
        
        // Stores a command and checks if valid command, if it is, check if there is another argument after
        // If there is no argument after, outputs too few arguments
        myOwnStringStream >> command; 
        if ((command != "insertR") && (command != "modifyR") && (command != "printR") && (command != "printNode") 
                && (command != "deleteR")){
            cout << "Error: invalid command" << endl;
        }
        else if (myOwnStringStream.eof()){
            cout << "Error: too few arguments" << endl;
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
        }
        // when the line has been processed and an output is given, receive next line from user.
        cout << "> ";
        getline(cin, line);
        
        // if the user ends the file, the program exits. Otherwise, processes another line.
        if (cin.eof())
            moreLines = false;
        else
           moreLines = true;
        }
        return 0;
    }

//Function that returns true if an argument is a valid argument.
bool checkInvalid (stringstream& argument){
    if (argument.fail()){
        if (!argument.eof())
            return (true);
    }
}

//Function that returns true if there are too few arguments in a line.
bool checkTooFew (stringstream& argument){
    if (argument.fail()){
        if (argument.eof())
            return (true);
    }
}

//Function to insert a resistor
void insertR (stringstream& myOwnStringStream){
    string resistorName;
    double resistance;
    int nodeid1, nodeid2;
    bool few, wrongArg = false;
    char ch, test;
    //checks the validity of the first argument (resistor name) before storing the next argument and so on.
    myOwnStringStream >> resistorName;
    few=checkTooFew(myOwnStringStream);
    if (resistorName == "all")
        cout << "Error: resistor name cannot be the keyword \"all\" "<< endl;
    else if (few){
        cout << "Error: too few arguments"<< endl;
    }
    else{
        //if resistor name is valid, store resistance value.
        myOwnStringStream >> resistance;
        few=checkTooFew(myOwnStringStream);
        wrongArg = checkInvalid(myOwnStringStream);
        if (wrongArg)
            cout << "Error: invalid argument" << endl;
        else if (resistance < 0 && !few)
            cout << "Error: negative resistance" <<endl;
        else if (few)
            cout << "Error: too few arguments" << endl;
        else{
            //if resistance is valid, store the value of the first node id.
            myOwnStringStream >> nodeid1;
            few=checkTooFew(myOwnStringStream);
            wrongArg= checkInvalid(myOwnStringStream);
            if (wrongArg)
                cout << "Error: invalid argument" << endl;
            else if (few)
                cout << "Error: too few arguments" << endl;
            else if (nodeid1<0 || nodeid1>MAX_NODE_NUMBER)
                cout << "Error: node " << nodeid1<< " is out of permitted range 0-5000" << endl;
            else{
                // if the first node id is valid, store the value of the second node id.
                myOwnStringStream >> nodeid2;
                few=checkTooFew(myOwnStringStream);
                if (few)
                    cout << "Error: too few arguments" << endl;
                else{
                    // check to see whether the node id is fully a number and not a number combined
                    // with other characters
                    ch=myOwnStringStream.peek();
                    if (myOwnStringStream.eof() && !few) {
                        wrongArg= checkInvalid(myOwnStringStream);
                        if (wrongArg)
                            cout << "Error: invalid argument" << endl;
                        else if (nodeid2<0 || nodeid2>MAX_NODE_NUMBER)
                            cout << "Error: node " << nodeid2<< " is out of permitted range 0-5000" << endl;
                        else if (nodeid2==nodeid1)
                            cout << "Error: both terminals of resistor connect to node " << nodeid2 <<endl;
                        else
                            cout << "Inserted: resistor " << resistorName << " " << fixed << setprecision(2) << resistance << " Ohms " <<
                                nodeid1 << " -> " << nodeid2 <<endl;
                    }
                    // If there is empty space after last argument (second node id), test to see if there is
                    // anything after the space. If there is, check to see if there are too many arguments.
                    else if (ch==' ' || ch=='\t'){
                            myOwnStringStream >> test;
                            if (myOwnStringStream.eof()){
                                cout << "Inserted: resistor " << resistorName << " " << fixed << setprecision(2) << resistance << " Ohms " <<
                                nodeid1 << " -> " << nodeid2 <<endl;
                            }
                            else 
                                cout << "Error: too many arguments" <<endl;
                    }
                    // if not empty space or eof after the last argument, the argument is invalid.
                    else 
                        cout << "Error: invalid argument" << endl;
                }

            }   
        }     
    } 
    myOwnStringStream.clear();
    myOwnStringStream.ignore(1000,'\n');
}

//Function to modify a resistor value
void modifyR (stringstream& myOwnStringStream){
    string resistorName;
    double resistance;
    bool few, wrongArg = false;
    char ch, test;
    
    //stores the resistor name and checks if it is valid.
    myOwnStringStream >> resistorName;
    few=checkTooFew(myOwnStringStream);
    if (resistorName == "all")
        cout << "Error: resistor name cannot be the keyword \"all\" "<< endl;
    else if (few){
        cout << "Error: too few arguments"<< endl;
    }
    else{
        // if resistor name is valid, store the resistance value and check if it is valid.
        myOwnStringStream >> resistance;
        few=checkTooFew(myOwnStringStream);
        if (few)
            cout << "Error: too few arguments" << endl;
        else{
            //using peek() to check if there is any other non-integer character behind the resistance value.
            ch=myOwnStringStream.peek();
            if (myOwnStringStream.eof() && !few){
                wrongArg = checkInvalid(myOwnStringStream);
                if (wrongArg)
                    cout << "Error: invalid argument" << endl;
                else if (resistance < 0 && !few)
                    cout << "Error: negative resistance" <<endl;
                else
                    cout << "Modified: resistor " << resistorName << " to " << fixed << setprecision(2) << resistance << " Ohms" <<endl;
            }
            //if the character after the resistance value is empty space, check if too many arguments or not.
            else if (ch==' '|| ch=='\t'){
                wrongArg = checkInvalid(myOwnStringStream);
                myOwnStringStream >> test;
                if (wrongArg)
                    cout << "Error: invalid argument" << endl;
                else if (resistance < 0 && !few)
                    cout << "Error: negative resistance" <<endl;
                else if (myOwnStringStream.eof()){
                    cout << "Modified: resistor " << resistorName << " to " << fixed << setprecision(2) << resistance << " Ohms" <<endl;
                }
                else
                    cout << "Error: too many arguments" <<endl;
            }
            // if character after resistance is not empty space and not end of the line, the 
            //resistance value is an invalid argument.
            else
                cout << "Error: invalid argument" << endl;
        }

    }
    myOwnStringStream.clear();
    myOwnStringStream.ignore(1000,'\n');
}

//Function to print a resistor or all resistors.
void printR(stringstream& myOwnStringStream){
    string resistorName;;
    bool few = false;
    char test;
    // gets the resistor name and checks if it is valid.
    myOwnStringStream >> resistorName;
    few=checkTooFew(myOwnStringStream);
    if (few)
            cout << "Error: too few arguments" << endl;
    else{
        //tests to see if there is any other argument after the last argument
        myOwnStringStream >> test;
        if (myOwnStringStream.eof()){
            if (resistorName=="all")
                cout << "Print: all resistors"<< endl;
            else
                cout << "Print: resistor " << resistorName <<endl;
        }
        else 
            cout << "Error: too many arguments" <<endl;
    }
    myOwnStringStream.clear();
    myOwnStringStream.ignore(1000,'\n');
}

//Function to print a node or all nodes
void printNode (stringstream& myOwnStringStream){
    string resistorName, selection;
    int nodeid1;
    char ch, test;
    
    myOwnStringStream.ignore (1000,' ');
    ch=myOwnStringStream.peek();

    //if the first character of the argument is an 'a' check to see if it is 'all'. If not, it is an 
    //invalid argument. Also checks for too many arguments.
    if (ch=='a'){
        myOwnStringStream >> selection;
        myOwnStringStream >> test;
        if (myOwnStringStream.eof()){
            if (selection!="all")
                cout << "Error: invalid argument"<< endl;
            else
                cout << "Print: all nodes" << endl;
        }
        else 
            cout << "Error: too many arguments" <<endl;
    }
    // if the first character of the argument is a number or a negative sign, tries to store the number
    // if it fails to store number, it is not an integer or 'all' so it is an invalid argument.
    // Also checks the validity of the node id value if it is an integer.
    else if ((ch>='0' && ch<='9') || (ch=='-')){
        myOwnStringStream >> nodeid1;

        //checks to see if there is anything behind the integer. If there is, it is an invalid argument.
        //This is done by checking if it is end of line or whitespace after the integer. If not, there is something
        //behind the integer so it is invalid.
        ch=myOwnStringStream.peek();
        if (myOwnStringStream.eof()){
           if (nodeid1<0 || nodeid1 > MAX_NODE_NUMBER)
                cout << "Error: node " << nodeid1 << " is out of permitted range 0-5000" <<endl;
           else
               cout << "Print: node " << nodeid1 << endl;
        }
        else if (ch==' ' || ch=='\t'){
            myOwnStringStream >> test;
            if (nodeid1<0 || nodeid1 > MAX_NODE_NUMBER)
                cout << "Error: node " << nodeid1 << " is out of permitted range 0-5000" <<endl;
            else if (myOwnStringStream.eof())
                cout << "Print: node " << nodeid1 << endl;
            else
                cout << "Error: too many arguments" <<endl;
        }
        else
            cout << "Error: invalid argument" <<endl;
    }
    else
        cout << "Error: invalid argument" <<endl;
    myOwnStringStream.clear();
    myOwnStringStream.ignore(1000,'\n');
}

//Function to delete a resistor
void deleteR (stringstream& myOwnStringStream){
    string resistorName;
    bool few = false;
    char test;
    
    //checks the validity of the resistor name and arguments.
    myOwnStringStream >> resistorName;
    few=checkTooFew(myOwnStringStream);
    if (few)
            cout << "Error: too few arguments" << endl;
    else{
        myOwnStringStream >> test;
        if (myOwnStringStream.eof()){
            if (resistorName=="all")
                cout << "Deleted: all resistors"<< endl;
            else
                cout << "Deleted: resistor " << resistorName <<endl;
        }
        else 
            cout << "Error: too many arguments" <<endl;
    }
    myOwnStringStream.clear();
    myOwnStringStream.ignore(1000,'\n'); 
}