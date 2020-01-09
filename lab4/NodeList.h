#ifndef NODELIST_H
#define NODELIST_H

#include "Node.h"
#include "Resistor.h"
#include <cmath>

#define MIN_ITERATION_CHANGE 0.001

class NodeList {
private:
    Node* head;
    
public:
    NodeList();
    NodeList(const NodeList& orig);
   ~NodeList();
    Node* FindOrInsertNode(int nodeid);
    Node* FindNode(int nodeid);
    Resistor* FindResistor(string name);
    double modifyResistance(string name, double resistance);
    void printAllNodes();
    void deleteAllNodes();
    bool deleteOneResistor(string name); 
    bool isAnyVoltageSet();
    void solve();
    double solve2(Node* tptr);
};

#endif /* NODELIST_H */
