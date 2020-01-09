#include "TreeNode.h"
#include <iostream>
#include <sstream>
#include <string>

//constructor
TreeNode::TreeNode(DBentry* _entryPtr) {
    entryPtr=_entryPtr;
    left=NULL;
    right=NULL;
}

//destructor
TreeNode::~TreeNode() {
    delete entryPtr;
}

// sets the left child of the TreeNode.
void TreeNode::setLeft(TreeNode* newLeft){
    left=newLeft;
}

// sets the right child of the TreeNode
void TreeNode::setRight(TreeNode* newRight){
    right=newRight;
}

// gets the left child of the TreeNode.
TreeNode* TreeNode::getLeft() const{
    return left;
}

// gets the right child of the TreeNode
TreeNode* TreeNode::getRight() const{
    return right;
}

// returns a pointer to the DBentry the TreeNode contains. 
DBentry* TreeNode::getEntry() const{
    return entryPtr;
}

//function that removes an entry from tree
bool TreeNode:: removeEntry (string name, TreeNode*& nodeptr){ 
    if (name > entryPtr->getName()){
        if (right == NULL) return false; //node doesn't exist
        else return right->removeEntry(name, right); //look for entry on right
    }
    else if (name < entryPtr->getName()){
        if (left == NULL) return false; //node doesn't exist
        else return left->removeEntry(name, left); //look for entry on left
    }
    else{
        if (left==NULL && right==NULL){ //node to be deleted is a leaf node
            delete nodeptr;
            nodeptr=NULL;
        }
        else if (left==NULL){ //node to be deleted only has right subtree
            nodeptr=right;
            delete this;
        }
        else if (right==NULL){
            nodeptr=left; //node to be deleted only has left subtree
            delete this;
        }
        else{ //2 subtrees are connected to node to be deleted
            TreeNode* temp = left->getReplacement(left); //returns pointer to node that is the max node on left subtree
            string newname=temp->getEntry()->getName(); //stores name of max node on left subtree
            int newIP=temp->getEntry()->getIPaddress(); //stores IPaddress of max node on left subtree
            bool newActive=temp->getEntry()->getActive(); //stores status of max node on left subtree
            
            removeEntry (temp->getEntry()->getName(), temp); //deletes the max node on left subtree
            //sets the values of the node to be removed to the values of the max node values on left subtree
            nodeptr->getEntry()->setName(newname);   
            nodeptr->getEntry()->setIPaddress(newIP);
            nodeptr->getEntry()->setActive(newActive);        
        }
        return true;
    }
}

//returns pointer to node that is the max node on left subtree
TreeNode*& TreeNode:: getReplacement(TreeNode*& nodeptr){
    if (right == NULL) return (nodeptr);
    else return right->getReplacement(right);
}
