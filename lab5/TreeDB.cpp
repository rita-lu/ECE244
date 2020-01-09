#include "TreeDB.h"
#include <iostream>
#include <sstream>
#include <string>

//default constructor
TreeDB::TreeDB() {
    root=NULL;
}

//destructor
TreeDB::~TreeDB() {
    if (root==NULL) return;
    clearTree(root);
}

//function that deletes all the nodes in the tree
void TreeDB::clear(){
    if (root == NULL) return;
    clearTree(root);
    root = NULL;
}

//Helper function to delete all nodes
void TreeDB::clearTree(TreeNode* nodeptr){
    if (nodeptr == NULL) return;
    clearTree(nodeptr->getLeft());
    clearTree(nodeptr->getRight());
    delete nodeptr;
    nodeptr=NULL;
}

//function to insert a new node
bool TreeDB::insert(DBentry* newEntry){
    TreeNode* nodeptr = new TreeNode(newEntry);
    if (root == NULL) { // if no nodes in tree
        root = nodeptr; 
        return true;
    } 
    bool inserted=(insertTree(nodeptr, root)); //if some nodes in the tree
    if (inserted==false) delete nodeptr;
    return inserted;
}

//helper function to insert a new node
bool TreeDB::insertTree(TreeNode* nodeptr, TreeNode* myroot){
    if (nodeptr->getEntry()->getName() == myroot->getEntry()->getName()) return false; //if node name already exists
    if (nodeptr->getEntry()->getName() < myroot->getEntry()->getName()) { // if new node name is alphabetically less than current node name, look left
        if (myroot->getLeft() == NULL) { //insert new node at end of tree
            myroot->setLeft(nodeptr);
            return true;
        }
        else insertTree(nodeptr, myroot->getLeft()); //searching for already existing node or bottom of tree recursively
    }
    else if (nodeptr->getEntry()->getName() > myroot->getEntry()->getName()) { // if new node name is alphabetically greater than current node name, look right
        if (myroot->getRight() == NULL) { // insert new node at end of tree
            myroot->setRight(nodeptr);
            return true;
        }
        else insertTree(nodeptr, myroot->getRight());
    }  
}

//function to find a node with a given name
DBentry* TreeDB::find(string name){
    if (root == NULL) return NULL; //if no nodes in tree
     return (searchTree(root, name));
}

//helper find function
DBentry* TreeDB::searchTree(TreeNode* nodeptr, string name){
    if (nodeptr == NULL) return NULL; // if no nodes in tree
    if (nodeptr->getEntry()->getName() == name){ //node found
        return nodeptr->getEntry();
    }
    else if (nodeptr->getEntry()->getName() < name) { //if name is alphabetically greater than current node name, look right
        return searchTree(nodeptr->getRight(), name);
    }
    else {
        return searchTree(nodeptr->getLeft(), name); //if name is alphabetically less than current node name, look left
    }
}

//function to remove one node
bool TreeDB::remove(string name){
    if (root == NULL){ // if no nodes in tree
        cout << "Error: entry does not exist" << endl;
        return false;
    }
    return(root->removeEntry(name, root)); //call removeEntry function in TreeNode class    
}

//function to print probe number
void TreeDB::printProbes(string name) const{
    if (root == NULL) //empty tree
        cout << "Error: entry does not exist" << endl;
    else{
        int probeNum=0;
        probesHelper(root, name, probeNum);
    }
}

//helper function to print probes
void TreeDB::probesHelper(TreeNode* nodeptr, string name, int& probeNum) const{
    if (nodeptr == NULL) { //entry not found
        cout << "Error: entry does not exist" << endl;
        return;
    }
    if (nodeptr->getEntry()->getName() == name){ //entry found and probe number returned
        probeNum++;
        cout << probeNum <<endl;
        return;
    }
    else if (nodeptr->getEntry()->getName() < name) { //looking for entry on the right
        probeNum++;
        return probesHelper(nodeptr->getRight(), name, probeNum);
    }
    else {
        probeNum++;
        return probesHelper(nodeptr->getLeft(), name, probeNum); //looking for entry on the left
    }
}

//function that counts the number of active nodes
void TreeDB::countActive () const{
    int count=0;
    if (root == NULL){ //empty tree
        cout << "0" << endl;
        return;
    }
    activeHelper(root, count);
    cout << count << endl;
}

//helper function to count active nodes
void TreeDB::activeHelper (TreeNode* nodeptr, int& count) const{
    if (nodeptr != NULL) {
        activeHelper (nodeptr->getLeft(), count);
        if (nodeptr->getEntry()->getActive()==true) count++;
        activeHelper (nodeptr->getRight(), count);
    }
}

//function to print all node information in a tree
void TreeDB:: print(){
    if (root!=NULL) printTree(root);
}

//helper print function
void TreeDB:: printTree(TreeNode* nodeptr) const {
    if (nodeptr==NULL) return; //base case
    
    //prints nodes in ascending order by name by printing in order of left, node, right.
    printTree (nodeptr->getLeft());
    
    if (nodeptr->getEntry()->getActive())
        cout << nodeptr->getEntry()->getName() << " : " << nodeptr->getEntry()->getIPaddress() << " : active" << endl;
    else
        cout << nodeptr->getEntry()->getName() << " : " << nodeptr->getEntry()->getIPaddress() << " : inactive" << endl;

    printTree (nodeptr->getRight());
}

//function to update the status of a node entry
void TreeDB:: updatestatus(string name, bool active){
    if (root == NULL) { //empty tree
        cout << "Error: entry does not exist" << endl;
    }
    statushelper(root, name, active);
}

//helper function to update the status
void TreeDB:: statushelper(TreeNode* nodeptr, string name, bool active){
    if (nodeptr==NULL){ //if reached bottom, node doesn't exist
        cout << "Error: entry does not exist" << endl;
        return;
    }
    if (nodeptr->getEntry()->getName() == name){ //node found and updated
        nodeptr->getEntry()->setActive(active);
        cout << "Success" << endl;
        return;
    }
    if (nodeptr->getEntry()->getName() > name) //look right
        statushelper(nodeptr->getRight(), name, active);
    else
        statushelper(nodeptr->getLeft(), name, active); //look left
}