#ifndef RESISTOR_H
#define RESISTOR_H

#include <string>
#include <iostream>
using namespace std;

//Defining the resistor class
class Resistor
{
private:
   double resistance; // resistance (in Ohms)
   string name; // C++ string holding the label
   int endpointNodeIDs[2]; // IDs of nodes it attaches to
   Resistor* next;

public:
   Resistor();    
   Resistor(string name_,double resistance_,int endpoints_[2], Resistor* next_);
   ~Resistor();

   //getters and setters
   string getName() const; // returns the name
   double getResistance() const; // returns the resistance
   void setResistance (double resistance_);
   int getEndpoint1();
   int getEndpoint2();
   Resistor* getNext();

   void print ();

   friend ostream& operator<<(ostream&,const Resistor&);
   
   friend class ResistorList;
};
#endif	/* RESISTOR_H */