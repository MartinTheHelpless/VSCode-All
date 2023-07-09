#include <string>

#include "keyValue.h"

keyValue::keyValue(int key, double value)
{
    this->key = key;
    this->value = value;
}

int keyValue::getKey()
{
    return this->key;
}
double keyValue::getValue()
{
    return this->value;
}

void keyValue::setKey(int key)
{
    this->key = key;
}
void keyValue::setValue(double value)
{
    this->value = value;
}