#include "KeyValues.h"

KeyValues::KeyValues(int n)
{
    this->keyValues = new KeyValue *[n];
    this->count = 0;
}

KeyValues::~KeyValues()
{
    for (int i = 0; i < this->count; i++)
    {
        delete this->keyValues[i];
    }
    delete[] this->keyValues;
}

KeyValue *KeyValues::Create(int k, double v)
{

    KeyValue *newKv = new KeyValue(k, v);
    this->keyValues[this->count] = newKv;
    this->count++;
    return newKv;
}

KeyValue *KeyValues::Find(int k)
{

    for (int i = 0; i < this->count; i++)
        if (this->keyValues[i]->getKey() == k)
            return this->keyValues[i];

    return nullptr;
}

KeyValue *KeyValues::Remove(int k)
{

    for (int i = 0; i < this->count; i++)
        if (this->keyValues[i]->getKey() == k)
        {
            KeyValue *kv = this->keyValues[i];
            this->keyValues[i] = this->keyValues[count--];
            this->keyValues[count] = nullptr;
            return kv;
        }

    return nullptr;
}