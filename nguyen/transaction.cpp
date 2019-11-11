#include "transaction.h"
//----------------------------------------------------------------------------
//constructors
Transaction::Transaction()
{
}

Transaction::Transaction(char inputType, int inputIntBlockOne) {
    type = inputType;
    idOne = inputIntBlockOne;
}

Transaction::Transaction(char inputType, int inputIntBlockOne,
    int inputIntBlockTwo) {
    type = inputType;
    //modulus logic to correctly assign values
    idOne = inputIntBlockOne/10;
    accountTypeOne = inputIntBlockOne%10;
    amount = inputIntBlockTwo;
}
//this one is constructor for move transaction
Transaction::Transaction(char inputType, int inputIntBlockOne,
    int inputIntBlockTwo, int inputIntBlockThree) {
    type = inputType;
    //modulus logic to correctly assign values
    idOne = inputIntBlockOne / 10;
    amount = inputIntBlockTwo;
    accountTypeOne = inputIntBlockOne % 10;
    idTwo = inputIntBlockThree / 10;
    accountTypeTwo = inputIntBlockThree % 10;
}

//----------------------------------------------------------------------------
//destructor
Transaction::~Transaction()
{
}

//----------------------------------------------------------------------------
//print function, formatted to line up with setw()
//access information using getters.
void Transaction::printTransaction(Account inputAccount) const {
    cout << getType();
    cout << right << setw(10) << "$" << setw(6) << getAmount() <<
        setw(6);
    //if statement to change wording for withdraw
    if (getType() == 'W') {
        cout << "from ";
    }
    else {
        cout << "into ";
    }
        cout << inputAccount.getAccountName() << " fund" << endl;
}

//----------------------------------------------------------------------------
void Transaction::setType(char inputType) {
    type = inputType;
}

//----------------------------------------------------------------------------
void Transaction::setAccountTypeOne(int inputId) {
    accountTypeOne = inputId;
}

//----------------------------------------------------------------------------
//simple getters
int Transaction::getIdOne() const {
    return idOne;
}

//----------------------------------------------------------------------------
int Transaction::getIdTwo() const {
    return idTwo;
}

//----------------------------------------------------------------------------
int Transaction::getAccountTypeOne() const {
    return accountTypeOne;
}

//----------------------------------------------------------------------------
int Transaction::getAccountTypeTwo() const {
    return accountTypeTwo;
}

//----------------------------------------------------------------------------
int Transaction::getAmount() const {
    return amount;
}

//----------------------------------------------------------------------------
char Transaction::getType() const {
    return type;
}
