#include <iostream>
#include <string>
#include "Resistor.h"
#include "Node.h"
#include "NodeList.h"
using namespace std;

//Prototype for 'Rparser' function.
class Rparser{
public:
    Rparser();
    int parser();
    
    void insertR (stringstream&);
    void modifyR (stringstream&);
    void printR (stringstream&);
    void printNode (stringstream&);
    void deleteR (stringstream&);
    void setV (stringstream&);
    void unsetV (stringstream&);
    void solve();
    
private: 
    NodeList nlist;
};