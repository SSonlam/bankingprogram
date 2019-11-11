#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

using namespace std;
//--------------------------class Account-------------------------------------
//- Account class is used as an element of an array that each Client 
// will have in their data, 0-9 always labelled the same account
// and has an int balance to store their money.
//----------------------------------------------------------------------------
class Account
{
public:
    Account();
    Account(string, int); //initializer
    string getAccountName() const;
    ~Account();
//private:
    string accountName; //identifier for accounts 0-9
    int balance; //money balance
};
#endif

