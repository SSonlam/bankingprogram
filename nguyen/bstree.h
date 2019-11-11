#ifndef BSTREE_H
#define BSTREE_H
#include <iostream>
#include <string>
#include "client.h"
#include <fstream>

using namespace std;

//-----------------------------class BSTree-----------------------------------
// ADT BSTree: finite, ordered collection of one or more items
// ordering is determined by operator< of Client class
//
// Implementation and assumptions:
// - Implemented as a binary search tree, meaning root is first item of
// input, then each following item is sorted into the tree going into the
// left subtree if it is less than, and to the right if it is greater than.
// - If the tree is empty root is nullptr
// - Items of type Client will be inserted into the tree, given that they
// are built correctly and follow the requirements, if not then they will
// simply be ignored
// - Display prints tree in order by order of BSTree's least to greatest
// and display is done recursively using a helper
// - makeEmpty() is used for destructor and uses recursion to 
// clear every element
//----------------------------------------------------------------------------
class BSTree {
public:
    BSTree();
    ~BSTree(); // calls makeEmpty which deallocates all memory
   //insert object into the tree, parameter holds pointer to object to insert
    bool insert(Client*); //insert client pointers binary tree style
    void buildTree(ifstream&); //calls insert to build the tree

    // retrieve function, first parameter is id to retrieve
    // second parameter holds pointer to found object, nullptr if not found
    bool retrieve(const int inputId, Client*&) const;
    bool isEmpty() const; //returns true if tree is empty
    void display() const; //displays the contents of a tree to cout  
    void makeEmpty(); //deletes every node of the tree

private:

    struct Node { //glue that holds data properly
        Client* data;
        Node* right;
        Node* left;
    };

    Node* root = nullptr; // root of the tree
    void displayHelper(Node*) const; //display helper
    void makeEmptyHelper(Node*) const; //makeEmpty helper
};
#endif

