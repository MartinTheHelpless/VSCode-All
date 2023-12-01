#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>

struct Stack
{
    int *data;
    int capacity;
    int index;

    void initialize(int capacity)
    {
        this->data = new int[capacity];
        this->capacity = capacity;
        this->index = 0;
    }

    void push(int value)
    {
        if (index < capacity)
        {
            this->data[this->index++] = value;
        }
        else
            std::cout << "No more space." << std::endl;
    }

    int pop()
    {
        if (index > 0)
        {
            this->index--;
            return this->data[this->index];
        }
        else
            std::cout << "Nothing else to pop." << std::endl;
        return 0;
    }
};

int main(int argc, char const *argv[])
{
    Stack ammo;
    ammo.initialize(5);

    ammo.push(4);
    ammo.push(4);
    ammo.push(4);
    ammo.push(4);
    ammo.push(4);
    ammo.push(4);

    ammo.pop();
    ammo.pop();
    ammo.pop();
    ammo.pop();
    ammo.pop();

    return 0;
}
