#include <iostream>
#include "Bank.cpp"

int main(int argc, char const *argv[])
{

    int clientIDs = 0;

    int accountIDs = 0;

    Bank *myBank = new Bank();

    myBank->createAccount(accountIDs++, myBank->createClient(clientIDs++, "Martin Burian"));

    Account *myAcc = myBank->getAccount(accountIDs - 1);

    std::cout << myAcc->getBalance() << std::endl;

    myAcc->deposit(1520);

    std::cout << myAcc->getBalance() << std::endl;

    return 0;
}
