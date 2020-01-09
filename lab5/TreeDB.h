#ifndef _TREEDB_H
#define _TREEDB_H

#include "TreeNode.h"
#include "DBentry.h"

class TreeDB {

private:
   TreeNode* root;
   int probesCount;
   // You will need to add additional private functions
   bool insertTree(TreeNode* nodeptr, TreeNode* myroot);
   DBentry* searchTree(TreeNode* nodeptr, string name);
   void probesHelper(TreeNode* nodeptr, string name, int& probeNum) const;
   void activeHelper (TreeNode* nodeptr, int& count) const;
   void clearTree(TreeNode* nodeptr);
   void printTree(TreeNode* nodeptr) const;
   void statushelper(TreeNode* nodeptr, string name, bool active);

public:
   // the default constructor, creates an empty database.
   TreeDB();

   // the destructor, deletes all the entries in the database.
   ~TreeDB();

   // inserts the entry pointed to by newEntry into the database. 
   // If an entry with the same key as newEntry's exists 
   // in the database, it returns false. Otherwise, it returns true.
   bool insert(DBentry* newEntry); 

   // searches the database for an entry with a key equal to name.
   // If the entry is found, a pointer to it is returned.
   // If the entry is not found, the NULL pointer is returned.
   // Also sets probesCount
   DBentry* find(string name);

   // deletes the entry with the specified name (key)  from the database.
   // If the entry was indeed in the database, it returns true.
   // Returns false otherwise.
   bool remove(string name);
	
   // deletes all the entries in the database.
   void clear();
    
   // prints the number of probes stored in probesCount
   void printProbes(string name) const;
   
   // computes and prints out the total number of active entries
   // in the database (i.e. entries with active==true).
   void countActive () const;

   //function to print all nodes
   void print();
   
   //function to update the status of a node
   void updatestatus(string name, bool active);
}; 
 
   
#endif 
