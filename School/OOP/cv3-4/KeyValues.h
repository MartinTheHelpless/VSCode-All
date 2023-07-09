#include "KeyValue.cpp"

class KeyValues
{
private:
    KeyValue **keyValues;
    int count;

public:
    KeyValues(int n);
    ~KeyValues();

    KeyValue *Create(int k, double v);
    KeyValue *Find(int k);
    KeyValue *Remove(int k);
};
