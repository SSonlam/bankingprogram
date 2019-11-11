#include "bank.h"

//----------------------------------------------------------------------------
Bank::Bank()
{
}

//constructor to build tree
Bank::Bank(ifstream& infile) {
    if (!infile) {
        cout << "Error opening File";
        exit(1);
    }
    bankTree.buildTree(infile);
}
//destructor
Bank::~Bank()
{
}

//----------------------------------------------------------------------------
//builds queue assuming correctly formatted data, passed in blocks of ints
//to a Transaction constructor. Within the Transaction constructor will
//deal with how to correctly correspond the blocks of ints to their correct
//places
void Bank::buildQueue(ifstream& inputCommands) {
    if (!inputCommands) {
        cout << "Error opening file" << endl;
        exit(1);
    }
    char transactionType;
    int firstIntBlock;
    int secondIntBlock;
    int thirdIntBlock;
    Client* tempPtr;
    //assuming correctly formatted data, will correctly match file input to
    //chars and ints
    while (inputCommands >> transactionType) {
        if (transactionType == 'D') {
            inputCommands >> firstIntBlock >> secondIntBlock;
            Transaction tempTrans(transactionType, 
                firstIntBlock, secondIntBlock);

            if (bankTree.retrieve(tempTrans.getIdOne(), tempPtr)) {
                commands.push(tempTrans);
            }
            else {
                cout << "Unknown client ID " 
                    << tempTrans.getIdOne() << " requested" << endl;
            }

        }else if (transactionType == 'W') {
            inputCommands >> firstIntBlock >> secondIntBlock;
            Transaction tempTrans(transactionType, 
                firstIntBlock, secondIntBlock);
            //if valid Client id, will add Transaction to the command queue
            if (bankTree.retrieve(tempTrans.getIdOne(), tempPtr)) {
                commands.push(tempTrans);
            }else {
                cout << "Unknown client ID " << tempTrans.getIdOne() <<
                    " or " << tempTrans.getIdTwo() << " requested" << endl;
            }

        }

        else if (transactionType == 'M') {
            inputCommands >> firstIntBlock >> secondIntBlock 
                >> thirdIntBlock;
            Transaction tempTrans(transactionType, firstIntBlock,
                secondIntBlock, thirdIntBlock);
            //if valid Client id, will add Transaction to the command queue
            if (bankTree.retrieve(tempTrans.getIdOne(), tempPtr) &&
                bankTree.retrieve(tempTrans.getIdTwo(), tempPtr)) {
                commands.push(tempTrans);
            }else {
                cout << "Unknown client ID " << tempTrans.getIdOne() << 
                    " or " << tempTrans.getIdTwo() << " requested" << endl;
            }

        } else if (transactionType == 'H') {
            inputCommands >> firstIntBlock;
            Transaction tempTrans(transactionType, firstIntBlock);
            //if valid Client id, will add Transaction to the command queue
            if (bankTree.retrieve(tempTrans.getIdOne(), tempPtr)) {
                commands.push(tempTrans);
            }else {
                cout << "Unknown client ID " << tempTrans.getIdOne() 
                    << " requested" << endl;
            }

        }
        else {
            cout << "Unknown transaction type '" << transactionType
                << "' requested" << endl;
            //reads in next 2 ints to discard, assumes that after an invalid
            //transaction type there will only be 2 ints after
            inputCommands >> firstIntBlock >> secondIntBlock;
        }
        
    }
}

//----------------------------------------------------------------------------
//checks to see what kind of transaction it is, then performs it
//calling the corresponding function to perform
void Bank::performTransactions() {
    Client* clientHolder1; // client to perform transactions on
    Client* clientHolder2; // if move called than this holds second client
    char transChecker; // checks to see Transaction type
    Transaction tempTrans; // Transaction to hold front of queue
    while (!commands.empty()) {
        tempTrans = commands.front();
        transChecker = tempTrans.getType();
        //deposit
        if (transChecker == 'D') {
            clientHolder1 = matchClient(tempTrans, 1);
            deposit(clientHolder1, tempTrans);
            commands.pop();
        }
        //withdraw
        else if (transChecker == 'W') {
            clientHolder1 = matchClient(tempTrans, 1);
            withdraw(clientHolder1, tempTrans);
            commands.pop();
        }
        //move
        else if (transChecker == 'M') {
            clientHolder1 = matchClient(tempTrans, 1);
            clientHolder2 = matchClient(tempTrans, 2);
            move(clientHolder1, clientHolder2, tempTrans);
            commands.pop();
        }
        //history
        else if(transChecker == 'H'){
            clientHolder1 = matchClient(tempTrans, 1);
            clientHolder1->printHistory();
            commands.pop();
        }
    }
}

//----------------------------------------------------------------------------
//deposit performed when 'D' is read. Takes in Client pointer reference
//to add value (deposit).
void Bank::deposit(Client*& inputClient, Transaction inputTransaction) {
    //reference of client so that data gets universally changed
    Client& tempClient = *inputClient; //made to perform function
    tempClient.performDeposit(inputTransaction);
}

//----------------------------------------------------------------------------
void Bank::withdraw(Client*& inputClient, Transaction inputTransaction) {
    Client& tempClient = *inputClient; //made to perform function
    tempClient.performWithdraw(inputTransaction);
}

//----------------------------------------------------------------------------
void Bank::move(Client*& inputClientOne, Client*& inputClientTwo,
    Transaction inputTransaction) {
    Client& tempClient1 = *inputClientOne;
    Client& tempClient2 = *inputClientTwo;
    //for move function, will only deposit into second client if it is 
    //withdrawn successfully from first client
    if (tempClient1.performWithdraw(inputTransaction)) {
        tempClient2.performDeposit(inputTransaction);
    }
}

//----------------------------------------------------------------------------
//this retrieves the client we need to work with from the tree
Client* Bank::matchClient(Transaction inputTransactionOne, int oneOrTwo) {
    Client* tempPtr;
    //one or two statement is to deal with move, and whether or not we want
    //to retrieve the first client or the second in the Transaction
    if (oneOrTwo == 1) {
        bankTree.retrieve(inputTransactionOne.getIdOne(), tempPtr);
    }
    else{
        bankTree.retrieve(inputTransactionOne.getIdTwo(), tempPtr);
    }
    return tempPtr;
}

//----------------------------------------------------------------------------
void Bank::printInitialTree() {
    cout << "Initial Balances:" << endl;
    bankTree.display();
}

//----------------------------------------------------------------------------
void Bank::printFinishedTree() {
    cout << endl;
    cout << "Final Balances:" << endl;
    bankTree.display();
}

