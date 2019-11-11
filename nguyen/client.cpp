#include "client.h"
//----------------------------------------------------------------------------
//constructors
Client::Client(){
}

Client::Client(string lName, string fName, int idInput, 
    int inputAccounts[]) {
    lastName = lName;
    firstName = fName;
    fullName = firstName + " " + lastName;
    id = idInput;
    //array of names for the accounts
    string accountNames[] = {"Money Market", "Prime Money Market",
    "Long-Term Bond", "Short-Term Bond", "500 Index Fund", 
        "Capital Value Fund", "Growth Equity Fund", "Growth Index Fund",
        "Value Fund", "Value Stock Index"};
    for (int i = 0; i < 10; i++) {
        //construct the accounts wih their name and starting balance
        Account tempAccount(accountNames[i], inputAccounts[i]);
        accounts[i] = tempAccount; //add to the account array
    }
}

Client::~Client(){
}
//----------------------------------------------------------------------------
//compares id #s, only need less than overload
bool Client::operator<(const Client & inputClient) const {
    if(id < inputClient.id){
        return true;
    }
    else {
        return false;
    }
}

//----------------------------------------------------------------------------
//prints only what we need of Client
void Client::printClient() const {
    cout << left << setw(6) << id << setw(8) << fullName << endl;
    for (int i = 0; i < 10; i++) {
        cout << setw(6) << accounts[i].balance;
    }
    cout << endl;
    cout << endl;
}

//----------------------------------------------------------------------------
//getter
int Client::getId() const{
    return id;
}

//----------------------------------------------------------------------------
//adds to corresponding account balance
void Client::performDeposit(Transaction& inputTransaction) {
    //if transaction type is originally a D or deposit 
    if (inputTransaction.getType() == 'D') {
        accounts[inputTransaction.getAccountTypeOne()].balance 
            += inputTransaction.getAmount();
        addToHistoryList(inputTransaction);
    }
    //if transaction type was originally a move then get the account
    //type of client two, because deposit is always performed
    //second in a move transaction, also if the first part of this 
    //transaction was a withdraw, that means it was a move, which means this
    // will turn into a deposit because that's basically what it is
    else if (inputTransaction.getType() == 'W') {
        accounts[inputTransaction.getAccountTypeTwo()].balance 
            += inputTransaction.getAmount();
        inputTransaction.setType('D');
        inputTransaction.setAccountTypeOne(inputTransaction.
            getAccountTypeTwo());
        addToHistoryList(inputTransaction);
    }
}

//----------------------------------------------------------------------------
bool Client::performWithdraw(Transaction& inputTransaction) {
    //total amount both money market accounts have
    int totalMoneyMarketBalance = accounts[0].balance + accounts[1].balance;
    //total amount both bonds accounts have
    int totalBondsBalance = accounts[2].balance + accounts[3].balance;

    //changes a move into a withdraw, because that's basically what it is
    if (inputTransaction.getType() == 'M') {
        inputTransaction.setType('W');
    }

    //enter this edge case if corresponding accountType doesn't have
    //enough balance to withdraw, and accountType is one of the 
    //money markets
    if (accounts[inputTransaction.getAccountTypeOne()].balance 
        - inputTransaction.getAmount() < 0 &&
        (inputTransaction.getAccountTypeOne() == 0 
            || inputTransaction.getAccountTypeOne() == 1)) {

        //if both money markets dont have enough then return false
        //and print error
        if (totalMoneyMarketBalance < inputTransaction.getAmount()) {
            cout << endl;
            cout << "Withdrawal not performed on " 
                <<accounts[inputTransaction.getAccountTypeOne()].accountName
                << " for client " << id << ";" << endl;
            cout << "      insufficient funds" << endl;
            return false;
        //both money markets combined have enough, this next part
        //this next part checks to which account were initially working
        //with then does the subtractions accordingly
        }else if(inputTransaction.getAccountTypeOne() == 0){
            accounts[1].balance -= (inputTransaction.getAmount() 
                - accounts[0].balance);
            accounts[0].balance -= accounts[0].balance;
            addToHistoryList(inputTransaction);
            return true;
        }else if (inputTransaction.getAccountTypeOne() == 1) {
            accounts[0].balance -= (inputTransaction.getAmount() 
                - accounts[1].balance);
            accounts[1].balance -= accounts[1].balance;
            addToHistoryList(inputTransaction);
            return true;
        }
        else {
            return false;
        }
    }
    //same exact logic except with the bond accounts
    else if (accounts[inputTransaction.getAccountTypeOne()].balance 
        - inputTransaction.getAmount() < 0 &&
        (inputTransaction.getAccountTypeOne() == 2 
            || inputTransaction.getAccountTypeOne() == 3)) {

        if (totalBondsBalance < inputTransaction.getAmount()) {
            cout << endl;
            cout << "Withdrawal not performed on " 
                <<accounts[inputTransaction.getAccountTypeOne()].accountName
                << " for client " << id << ";" << endl;
            cout << "      insufficient funds" << endl;
            return false;
        }
        else if (inputTransaction.getAccountTypeOne() == 2) {
            accounts[2].balance -= (totalMoneyMarketBalance 
                - accounts[0].balance);
            accounts[3].balance -= accounts[3].balance;
            addToHistoryList(inputTransaction);
            return true;
        }
        else if (inputTransaction.getAccountTypeOne() == 3) {
            accounts[2].balance -= (totalMoneyMarketBalance 
                - accounts[3].balance);
            accounts[3].balance -= accounts[3].balance;
            addToHistoryList(inputTransaction);
            return true;
        }
        else {
            return false;
        }
    }
    
    //if account has enough to withdraw then simply do the subtraction
    else if (accounts[inputTransaction.getAccountTypeOne()].balance 
        - inputTransaction.getAmount() >= 0) {

        accounts[inputTransaction.getAccountTypeOne()].balance 
            -= inputTransaction.getAmount();

        addToHistoryList(inputTransaction);
        return true;
    }
    else {
        return false;
    }
}

//----------------------------------------------------------------------------
//add a Transaction to the list
void Client::addToHistoryList(const Transaction inputTransaction) {
    historyList.push_back(inputTransaction);
}

//----------------------------------------------------------------------------
//prints 
void Client::printHistory() const {
    //formatting output
    cout << endl;
    cout << "History of transactions for client mickey mouse, client ID = " 
        << getId() << endl;
    cout << "Type      Amount  Detail" << endl;
    cout << "--------- ------- --------------------------------------" 
        << endl;
    //printing list logic
    for (Transaction v : historyList) {
        if (v.getType() == 'M') {
            v.printTransaction(accounts[v.getAccountTypeTwo()]);
        }
        else {
            v.printTransaction(accounts[v.getAccountTypeOne()]);
        }
    }
    cout << "history" << endl;
}