#include "NodeList.h"
#include <iostream>

//default constructor
NodeList::NodeList() {
    head = NULL;
}

//function that finds and returns a pointer to a node or inserts a node if the node doesn't exist.
Node* NodeList::FindOrInsertNode(int nodeid){
    Node* tptr = head;
    Node* pptr = NULL;
    
    //if head is null, it is empty list and inserting node at beginning of list
    if (head==NULL){
        head = new Node(nodeid, tptr);
        return head;
    }
    else{
        // traversing through the linked list
        while (tptr != NULL && nodeid > tptr->nodeID ){
            pptr = tptr;
            tptr = tptr-> next;
        }
        //insert at end of list
        if (tptr==NULL){
            pptr->next = new Node(nodeid, tptr);
            return pptr->next;
        }
        //if node already exists in the list, return pointer to the node
        else if (tptr->nodeID == nodeid) return tptr;
        //if inserting at beginning of non-empty list 
        else if (pptr==NULL){
            head = new Node(nodeid, tptr);
            return head;
        }
        // inserting in the middle of the list.
        else{
            pptr->next = new Node(nodeid, tptr);
            return pptr->next;
        }   
    }
}

//tries to find a certain node in the list, returns pointer to node if it exists. Otherwise, returns NULL.
Node* NodeList::FindNode(int nodeid){
    Node* tptr=head;
    //traverses through the node list until node with nodeid is found or until reaches end of node list.
    while (tptr != NULL && tptr->nodeID != nodeid)
        tptr = tptr -> next;    
    return tptr;
}

//find a resistor in the node list by calling 'findResistor' function of resistor list for each node. Returns a pointer to 
//the resistor if it resistor is found. Otherwise, returns NULL;
Resistor* NodeList:: FindResistor(string name){
    Resistor* temp = NULL;
    Node* tptr = head;
    //loop until the end of node list is reached or resistor is found. If not found, return NULL.
    while (temp==NULL && tptr!=NULL){
        temp=tptr->rlist.FindResistor(name);
        tptr=tptr->next;
    }
    return temp;
}

//modifies a resistor in the node list
double NodeList::modifyResistance(string name, double resistance){
    Node* tptr = head;
    Resistor* r1 = NULL;
    Resistor* r2 = NULL;
    double oldresistance;
    
    // traverses through node list to find and return a pointer that has the name of the resistor
    while(tptr!= NULL && r1==NULL){
        r1 = tptr->rlist.FindResistor(name);
        tptr = tptr -> next;
    }
    
    // traverses through node list to find a second pointer in a different node of the same name
    while(tptr!=NULL && r2==NULL){
        r2 = tptr->rlist.FindResistor(name);
        tptr = tptr -> next;
    }
    
    //if the resistors are not found return -1, else return the old resistance and change resistors in 2 nodes to new resistance.
    if(r1 == NULL || r2 == NULL) return (-1);
    else{
        oldresistance = r1->getResistance();
        r1->setResistance(resistance);
        r2->setResistance(resistance);
        return (oldresistance);
    }
}

//prints all nodes in the list
void NodeList::printAllNodes(){
    Node* temp = head;
    while (temp!=NULL){
        temp->print();
        temp=temp->next;
    }
}

//deletes all nodes in the list by first deleting all the resistors in the node, then the node itself.
void NodeList::deleteAllNodes(){
    Node* temp=head;
    while (temp!=NULL){
        temp->rlist.deleteAll();
        head=head->next;
        delete temp;
        temp=head;
    }
}

//deletes a resistor by deleting 2 resistor in the node list and returns true if deleted
bool NodeList::deleteOneResistor(string name){
    Node* temp = head;
    int i = 0;
    bool deletedRes;
    
    //goes through nodes in node list and looks for 2 resistors of the given name in the resistor lists.
    while (temp!=NULL && i<2){
        deletedRes=false;
        deletedRes = temp -> rlist.deleteAResistor(name);
        if (deletedRes)
            i=i+1;
        temp = temp->next;
    }
    if (i==2) return true;
    else return false;
}

//returns false if none of the voltages in the node list are set
bool NodeList::isAnyVoltageSet(){
    Node* temp=head;
    //loops through node list and returns true if there is one voltage that is set
    while (temp!=NULL){
        if (temp->vAlreadySet==true) return true;
        temp=temp->next;
    }
    return false;
}

//function that solves for unknown voltages
void NodeList::solve(){
    double newV;
    bool solved=false;
    double iterationchange;
    Node* n1 = head;
    
    //loops while the node voltages have not yet been solved
    while (!solved){
        solved=true;
        n1 = head;
        
        //loops through the node list
        while (n1!=NULL){
            //if the node that n1 is pointing to does not have its voltage set yet, run this code
            if (n1->vAlreadySet==false){
                //solves for new voltage at the node using Gauss-Seidel method on the node
                newV = solve2(n1);
                iterationchange = abs (newV-(n1->getV())); //calculates the change in the node voltage
                n1->tempSetV(newV); //sets the voltage to the calculated voltage
                //if any one node voltage in the node list changes by more than 0.001, will calculate all node voltages in the list again using the method
                if (iterationchange>MIN_ITERATION_CHANGE) 
                    solved=false; 
            }
            n1=n1->next;    
        }
    }
    //when calculation is done, loops through the node list and prints all node information
    n1=head;
    while (n1!=NULL){
        cout << "Node " << n1->nodeID << ": " << n1->voltage << " V" << endl;
        n1=n1->next;
    }
}

//function that solves for new voltage at one node that is pointed to by tptr
double NodeList::solve2(Node* tptr){ 
    double sum1=0; //sum that stores the value for v1/Ra + v2/Rb + v3/Rc part of the equation
    double sum2=0; //sum that stores the value for 1/Ra + 1/Rb + 1/Rc part of the equation
    double answer; 
        
    Resistor* r1 = tptr->rlist.getHead();
    
    //loops through resistor list of a node
    while (r1!=NULL){
        //looks for the endpoint that is not the nodeid of the node pointed to by tptr and uses that nodeid's voltage in calculation of sum1
        //in other words, finds all the node voltages that is connected to the the node pointed to by tptr
        if(r1->getEndpoint1() == tptr -> getNodeID()){
            sum1 = sum1 + (FindNode(r1->getEndpoint2())->getV())/(r1->getResistance());
        }
        if(r1->getEndpoint2()== tptr ->getNodeID()){
            sum1 = sum1 + (FindNode(r1->getEndpoint1()))->getV()/(r1->getResistance());
        }
        sum2 = sum2 + 1/(r1->getResistance()); 
        r1=r1->getNext();
    }
    //calculates new voltage and returns this voltage
    answer = (1/sum2)*sum1;
    return answer;
}

NodeList::NodeList(const NodeList& orig) {
}

//destructor
NodeList::~NodeList() {
}
