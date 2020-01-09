#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

#include "TreeDB.h"
#include "DBentry.h"
#include "TreeNode.h"

int main() {
    string line;
    string command, name, status;
    int IPaddress;
    bool moreLines = true;
    
    TreeDB tree; //create a TreeDB object
  
    //gets a line from a user, if 'eof', end file
    cout << "> ";
    getline(cin, line);
    if (cin.eof())
       moreLines = false;  
    
    //while the user hasn't exited, run this code
    while (moreLines) {   
        stringstream myOwnSS(line); //get string stream from user
        myOwnSS >> command; 

        if (command == "insert"){ //insert command
            myOwnSS >> name >> IPaddress >> status;  
            DBentry* newdb;
            
            if (status=="active")
                newdb = new DBentry(name, IPaddress, 1);
            else
                newdb = new DBentry(name, IPaddress, 0);
            
            bool inserted = tree.insert(newdb);
            if(inserted) cout << "Success" << endl;
            else cout << "Error: entry already exists" << endl;
        }
        
        else if (command == "find"){ //find command
            myOwnSS >> name;  
            DBentry* newdb = tree.find(name);
            if (newdb==NULL) cout << "Error: entry does not exist" << endl;
            else{
                if (newdb->getActive())
                    cout << newdb->getName() << " : " << newdb->getIPaddress() << " : active" << endl;
                else
                    cout << newdb->getName() << " : " << newdb->getIPaddress() << " : inactive" << endl;
            }
        }
        
        else if (command == "remove"){ //command to remove a node
            myOwnSS >> name;  
            bool done = tree.remove(name);
            if (done) cout << "Success" << endl;
            else cout << "Error: entry does not exist" << endl;
        }
        
        else if (command == "printall"){ //command to print all nodes
            tree.print();
        }
        
        else if (command == "printprobes"){ //command to print probe number
            myOwnSS >> name;  
            tree.printProbes(name);
        }
        
        else if (command == "removeall"){ //command to remove all nodes
            tree.clear();
            cout << "Success" << endl;
        }
        
        else if (command == "countactive"){ //command to count the number of nodes that are active
            tree.countActive();
        }
        
        else if (command == "updatestatus"){ //comand to update the status of a node
            myOwnSS >> name>> status;  
            if(status=="active")
                tree.updatestatus(name, 1);
            else
                tree.updatestatus(name, 0);
        }
        myOwnSS.clear();
        myOwnSS.ignore(1000,'\n'); 
        
        // when the line has been processed and an output is given, receive next line from user.
        cout << "> ";
        getline(cin, line);
        
        // if the user ends the file, the program exits and memory is deleted. Otherwise, processes another line.
        if (cin.eof())
            moreLines = false;
        else
           moreLines = true;
    }
    return 0;
}
