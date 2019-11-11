#ifndef CLIENT_H
#define CLIENT_H
#include <string>
#include <iostream>
#include <iomanip>
#include <list>
#include "transaction.h"
#include "account.h"

using namespace std;
//---------------------------class Client-------------------------------------
//Data Type: Client will be the data that the bank has on the client
//          assigned to them will be everything they need in a bank context
//          Also holds an array of type Account, this is their 0-9 bank
//          accounts, each one with balance and account type
//ADT list: will be a list object holding a finite amount of Transactions
//          in the order they were pushed into the list
//Implementation and assumptions:
// - Data being passed for Client constructor will be the values needed
// - All ids will be four positive digits
// - Having a Transaction passed into the bank functions will perform
//   their following commands onto the current Client's data
// - printClient() formats the data as it wants to be seen
//----------------------------------------------------------------------------
class Client
{
public:
    Client();
    //constructor to initialize input from file
    Client(string, string, int, int[]);
    bool operator<(const Client&) const; //will compare id #
    int getId() const; //getter
    //print only the needed parts of client
    void printClient() const;
    void performDeposit(Transaction&) ; //adds to balance of account
    //subtract from account balance if balance has enough funds
    bool performWithdraw(Transaction&);
    //will push a Transaction into the list
    void addToHistoryList(const Transaction);
    //print out entire content of history list
    void printHistory() const;
    ~Client(); //destructor
    //stores list of Transactions for each Client

private:
    //list gets added to when a Transaction is successfully
    //performed for client
    list <Transaction> historyList;
    string lastName; //first input from file
    string firstName; //second input from file
    string fullName; //just makes printing out name easier
    int id; //third input from file
    Account accounts[10];//4th-14th input from file
};
#endif

