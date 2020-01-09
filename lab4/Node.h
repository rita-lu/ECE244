#ifndef NODE_H
#define NODE_H

#include "ResistorList.h"

// Defining the node class
class Node
{
    
//member variables
private:
   int nodeID;
   Node* next;
   ResistorList rlist;
   double voltage;
   bool vAlreadySet;

//member functions   
public:
   Node(); 
   ~Node();
   Node(int nodeid, Node* nextNode);
   
   void addResistor (string name, double resistance, int endpoints[]); 
   void print (); 
   void setV(double voltage_);
   void tempSetV(double voltage_);
   double getV();
   void unsetV();
   int getNodeID();
  
   friend class NodeList;
};

#endif