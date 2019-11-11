#include "account.h"

//default constructor
Account::Account(){
}

//constructor to initialize account
Account::Account(string accountNameInput, int balanceInput) {
    accountName = accountNameInput;
    balance = balanceInput;
}
string Account::getAccountName() const {
    return accountName;
}

Account::~Account(){
}
