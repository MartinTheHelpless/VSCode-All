#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <SDL2/SDL.h>

using namespace std;

class car
{
public:
    string make;
    string model;
    int year;
    string color;

    car(string make, string model, int year, string color)
    {

        this->make = make;
        this->model = model;
        this->year = year;
        this->color = color;
    }

    void getInfo()
    {

        cout << "This car is a " << make << " " << model << " from the year " << year << " in " << color << " version." << endl;
    }
};

class bankAccount
{

public:
    string name;
    double balance;

    bankAccount(double balance, string name)
    {
        this->name = name;
        this->balance = balance;
    }

    void getBalance()
    {

        cout << name << " has " << balance << " $ on their account at the moment." << endl;
    }

    void withdraw(double amount)
    {
        balance -= amount;
    }
};

int main(int argc, char const *argv[])
{

    bankAccount acc1(3547.5, "Bender");
    bankAccount acc2(10000, "Lucas");
    bankAccount acc3(4500, "Chandler");

    acc1.getBalance();
    acc1.withdraw(1547.5);
    acc1.getBalance();

    acc2.getBalance();
    acc2.withdraw(1547.5);
    acc2.getBalance();

    acc3.getBalance();
    acc3.withdraw(1547.5);
    acc3.getBalance();

    car classic("Ford", "Mustang", 1969, "Striped Black");

    classic.getInfo();

    return 0;
}
