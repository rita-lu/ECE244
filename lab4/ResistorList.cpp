
#include "ResistorList.h"
#include <iostream>

//default constructor
ResistorList::ResistorList() {
    head=NULL;
    numRes=0;
}

//returns number of resistors connected to resistor list
int ResistorList::getNumRes(){
    return numRes;
}

//inserting a new resistor at the end of the resistor list
void ResistorList::addResistor(string name, double resistance, int endpoints[]){
    Resistor* tptr = head;
    Resistor* pptr = NULL; 
    
    //if empty list
    if (head==NULL)
        head= new Resistor(name, resistance, endpoints, tptr);
    //if not empty list, traverses through resistor list to find the end of the list and insert there
    else{
        while (tptr != NULL){
            pptr = tptr;
            tptr = tptr -> next;
        }
        pptr -> next = new Resistor(name, resistance, endpoints, tptr);
    }  
    numRes++;
}

//looks for a resistor with a given name and returns pointer to it if it exists. Otherwise, return NULL.
Resistor* ResistorList::FindResistor(string nameRes){
    Resistor* tptr = head;
    while (tptr != NULL && tptr->getName()!=nameRes)
        tptr = tptr->next;
    return tptr;
}

//prints all resistors in the resistor list
void ResistorList::printAll(){
    Resistor* tptr = head;
    while (tptr!=NULL){
        tptr->print();
        tptr=tptr->next;
    }
}

//deletes all resistors in the resistor list
void ResistorList::deleteAll(){
    Resistor* temp = head;
    numRes=0;
    while (head!=NULL){
        head=head->next;
        delete temp;
        temp=head;
    }   
}

//deletes a single resistor and returns true if a resistor is deleted
bool ResistorList::deleteAResistor(string name_){
    Resistor* pptr = NULL;
    Resistor* tptr = head;
    
    //if head is empty, doesn't delete any resistor and returns false
    if (head==NULL) return false;
    
    //while not end of list and resistor is not found in the resistor list yet, traverses through list
    while (tptr!=NULL && tptr->name!=name_){
        pptr=tptr;
        tptr=tptr->next;
    }
    
    //deleting resistor in beginning of list
    if (pptr==NULL){
        head=tptr->next;
        delete tptr;
        numRes=numRes-1;
        return true;
    }
    
    //empty list, return false since the resistor is not found in the list
    if (tptr==NULL) return false;
    
    //delete resistor in middle or end of list
    else{
        pptr->next=tptr->next;
        delete tptr;
        numRes=numRes-1;    
        return true;
    }
}

//returns the head pointer of the resistor list
Resistor* ResistorList::getHead(){
    return head;
}

ResistorList::ResistorList(const ResistorList& orig) {
}

ResistorList::~ResistorList() {
}

