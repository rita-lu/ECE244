#ifndef RESISTORLIST_H
#define RESISTORLIST_H
#include "Resistor.h"

class ResistorList {
private:
    Resistor* head;
    int numRes;
    
public:
    ResistorList();
    
    Resistor* getHead();
    int getNumRes();
    void addResistor(string name, double resistance, int endpoints[]);
    Resistor* FindResistor(string name);
    void printAll();
    void deleteAll();
    bool deleteAResistor(string name);
    
    
    ~ResistorList();
    ResistorList(const ResistorList& orig);
};

#endif /* RESISTORLIST_H */