#include "KeyValue.h"

KeyValue::KeyValue(int key, double value)
{
    this->key = key;
    this->value = value;
}

KeyValue::~KeyValue()
{
    delete this->next;
}

int KeyValue::getKey()
{
    return this->key;
}

double KeyValue::getValue()
{
    return this->value;
}

KeyValue *KeyValue::cNext(int n)
{
    KeyValue *nKey = new KeyValue(n, n + 1);

    this->next = nKey;

    if (n == 1)
        nKey->next = nullptr;
    else
        nKey->next = nKey->cNext(n - 1);

    return nKey;
}

void KeyValue::fNext(int n)
{

    if (this->next != nullptr)
        std::cout << "This key is not end of the chain." << std::endl;
    else
    {
        KeyValue *poleK[n];

        for (size_t i = 0; i < n; i++)
        {
            poleK[i] = new KeyValue(i, i);

            i > 0 ? poleK[i - 1]->next = poleK[i] : this->next = poleK[0];
        }
    }
}

KeyValue *KeyValue::getPtr(int n)
{
    if (this->next->next == nullptr && n != 1)
        return this->next;

    if (n != 1)
        return (this->next)->getPtr(n - 1);
    else
        return this->next;
}

double KeyValue::getNValue(int n)
{
    if (this->next == nullptr && n != 1)
        return this->value;

    if (n > 1)
        return (this->next)->getNValue(n - 1);
    else
        return this->next->value;
}

void KeyValue::delKey(int n)
{

    if (n == 2)
    {
        KeyValue *temp = this->next;

        this->next = this->next->next;

        temp = nullptr;
    }
    else
        this->delKey(n - 1);
}
