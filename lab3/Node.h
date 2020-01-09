#ifndef NODE_H
#define NODE_H

#define MAX_RESISTORS_PER_NODE 5

// Defining the node class
class Node
{
private:
    
   int numRes; // number of resistors currently connected
   int resIDArray[MAX_RESISTORS_PER_NODE]; // stores the index of each resistor connected

public:
   Node(); 
   ~Node();

   // Checks to see if the resistor can be added to position rIndex
   // in the resistor array. Returns true if yes, otherwise false.
   bool canAddResistor(int rIndex);
   
   // Updates resIDArray to make the resistor in position rIndex in
   // the resistor array connected to this node.
   void addResistor (int rIndex); 

   // prints the whole node
   // nodeIndex is the position of this node in the node array.
   void print (int nodeIndex); 

};

#endif
