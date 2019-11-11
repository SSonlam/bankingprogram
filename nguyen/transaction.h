#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <iostream>
#include <iomanip>
#include "account.h"

using namespace std;

//------------------------    class Transaction-------------------------------
// *Transaction is essentially a class to read in a commands to perform one 
// one of class type Client. Constructors are read in assuming data format 
// of char int int, or of char int int int, in cases of performing a move
// transaction. 
// *Implementation and assumptions:
// - Transactionconstructor reads int blocks and performs
// modulus logic to split the corresponding ints into their correct place
// - Correctly formatted inputs
// - Getters and setters for the values needed
// - printTransaction is essentially a version of operator overloading <<
// - Int values initialized in header to avoid behind the scene accidents
//----------------------------------------------------------------------------
class Transaction
{
public:
    //constructors
    Transaction();
    Transaction(char, int);
    Transaction(char, int, int);
    Transaction(char, int, int, int);
    //destructor
    ~Transaction();
    //getters
    int getIdOne() const;
    int getIdTwo() const;
    int getAccountTypeOne() const;
    int getAccountTypeTwo() const;
    int getAmount() const;
    char getType() const;
    //setters
    void setAccountTypeOne(int);
    void setType(char);
    //prints transaction, paramater is for getting
    //correct accountName
    void printTransaction(Account) const;
private:
    char type; //Transaction type (D,W,M,H)
    int idOne = 0; //will be the first id
    int amount = 0; //amount the transaction wants to work with
    int accountTypeOne = -1; //account type 0-9
    int idTwo = 0; //id of second person if working with "Move"
    int accountTypeTwo = -1; //account tyoe 0-9 of second id
};
#endif