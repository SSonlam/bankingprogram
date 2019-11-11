#ifndef BANK_H
#define BANK_H

#include "bstree.h"
#include "client.h"
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <list>
#include "transaction.h"
#include "account.h"
using namespace std;

//-----------------------------class Bank-------------------------------------
//ADT Bank: Bank owns a binary search tree that will hold the clients
//          and also owns a queue of Transactions that will modify Clients
//          in the tree. Since bank holds all the information, bank will
//          set up the things that need to be done and pass in the values
//Implementation and assumptions:
// - File passed in will be the file we want to be working with, checks to see
// if file is opened within this class, File is correctly formatted data
// - Will be passing in Client* references because we want other classes to 
// change the original's value
// - Move function is essentially a withdraw then a deposit, so move is based
// upon changing itself to that, in that exact order.
// - Has two printings of the tree so that we can print out beginning of the
// daya and the end after the transactions.
// - Assumes correctly formatted data, with inht blocks representing some 
// values, and single UpperCased char to perform a transaction, gets ignored
// if not properly formatted
//
//----------------------------------------------------------------------------
class Bank
{
public:
    Bank();
    ~Bank();
    Bank(ifstream&);
    void buildQueue(ifstream&);
    //determine which of the (D,W,M,H) to perform and sets up for it
    void performTransactions();
    //one client pointer param to work with client of tree, 
    //Transaction param to read entire transaction line
    void deposit(Client*&, Transaction);
    //performed if case 'W' is read
    void withdraw(Client*&, Transaction);
    //2 client points to move money around, Transaction param to read 
    //whole trans
    void move(Client*&, Client*&, Transaction);
    //returns client from tree to work with
    Client* matchClient(Transaction, int);
    void printInitialTree(); //prints tree before any transactions
    void printFinishedTree(); //prints tree after transactions
private:
    BSTree bankTree; //binary search tree holding Client*
    queue <Transaction> commands; //queue of Transaction commands
};
#endif

