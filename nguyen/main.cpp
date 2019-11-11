#include <iostream>
#include <fstream>
#include "bank.h"

using namespace std;
//-----------------------class main-------------------------------------------
//* class main, basically the driver class, creates a Bank, in which the 
// bank will build the tree. The queue of commands will be within the 
// instance of the Bank class, so buildQueue is also called on our bank
// object. Then the transactions will need to be called to perform all of
// them, and the rest is output to screen for visibility.
//----------------------------------------------------------------------------
int main() {
    //read in file, checks to see correct file in function
    ifstream inClientData("lab5data.txt");
    ifstream inCommands("lab5command.txt");
    //create Bank that holds a BSTree of clients from file
    Bank tester(inClientData);
    //prints tree at beginning of day
    tester.printInitialTree();
    tester.buildQueue(inCommands);
    tester.performTransactions();
    //prints tree at end of the day
    tester.printFinishedTree();
    return 0;
}