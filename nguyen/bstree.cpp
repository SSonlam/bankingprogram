#include "bstree.h"

//constructors
BSTree::BSTree()
{
}

BSTree::~BSTree()
{
    makeEmpty();
}

//----------------------------------------------------------------------------
//function to insert a Client* into the binary tree, sets first value
//as the root then sorts future data going to the left subtree is value
//is smaller, and to the right if value is higher
bool BSTree::insert(Client* input) {
    Node* ptr = new Node;
    if(ptr == nullptr) return false;            // out of memory
    ptr->data = input;
    ptr->left = ptr->right = nullptr;

    if (isEmpty()) { //empty tree sets root to first client pointer
        root = ptr;
    }else {
        Node* current = root; // walking pointer
        bool inserted = false;                 // whether inserted yet
        // if item is less than current item, insert in left subtree,
        // otherwise insert in right subtree
        while (!inserted) {
            if (*ptr->data < *current->data) {
                if (current->left == nullptr) {              // insert left
                    current->left = ptr;
                    inserted = true;
                }
                else
                    current = current->left;               // one step left
            }
            else {
                if (current->right == nullptr) {             // insert right
                    current->right = ptr;
                    inserted = true;
                }
                else
                    current = current->right;              // one step right
            }
        }
    }
    return true;
}

//----------------------------------------------------------------------------
//check root to see if is nullptr
bool BSTree::isEmpty() const {
    if (root == nullptr) {
        return true;
    }else {
        return false;
    }
}

//----------------------------------------------------------------------------
//builds binary tree by first building Clients, then inserting into tree
void BSTree::buildTree(ifstream& infile) {
    string lastName; //temp holder to read in last name
    string firstName; //temp holder to read in first name
    int idNumber; //temp holder to read in id number
    int bankAccounts[10]; //temp holder to hold 0-9 balances
    while (!infile.eof()) {
        //read in data from file assuming correct format
        while (infile >> lastName >> firstName >> idNumber) {
            //loop to fill bankAccounts array (0-9)

            for (int i = 0; i < 10; i++) {
                infile >> bankAccounts[i];
            }

            //builds client with constructor then insert into tree
            Client *tempClient = new Client(lastName, firstName, 
                idNumber, bankAccounts);
            insert(tempClient);
        }
    }
}

//----------------------------------------------------------------------------
//recursively prints all nodes of the binary tree
void BSTree::display()const {
    displayHelper(root);
}

//----------------------------------------------------------------------------
void BSTree::displayHelper(Node* ptr)const {
    //check for empty tree
    if (root == nullptr) {
        cout << "The tree is empty" << endl;
    }else{
        if (ptr->left != nullptr) {
            displayHelper(ptr->left);
        }

        ptr->data->printClient();

        if (ptr->right != nullptr) {
            displayHelper(ptr->right);
        }
    }
}

//----------------------------------------------------------------------------
//function to retrieve reference of client pointer, stores to second param
bool BSTree::retrieve(int inputId, Client*& ptrHolder) const {
    //check to see empty tree
    if (root == nullptr) {
    cout << "Cannot perform retrieve, tree is empty" << endl;
    return false;
    }//calls client.getId to match ids
    //check to see if root is matching client
    else if (inputId == root->data->getId()) {
        ptrHolder = root->data;
        return true;
    }

    Node* current = root; // starts current at root
    //iterates through tree to try to find client
    while (current != nullptr) {
        if (inputId == current->data->getId()) {
            ptrHolder = current->data;
            return true;
        }

        if (inputId < current->data->getId()) {
            current = current->left;               // one step left
        }
        else {
            current = current->right;              // one step right
        }

    }
    //false if cannot find after iteration of tree
    return false;
}

//----------------------------------------------------------------------------
//uses recursion to delete every node of the tree
void BSTree::makeEmpty() {
    makeEmptyHelper(root);
    root = nullptr;

}

//----------------------------------------------------------------------------
void BSTree::makeEmptyHelper(Node* ptr) const{
    if (ptr == nullptr) return;

            // first delete both subtrees 
        makeEmptyHelper(ptr->left);
        makeEmptyHelper(ptr->right);

        // then delete the node 
        delete(ptr->data);
        delete(ptr);
}
