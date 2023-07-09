#include <string>
#include <iostream>

class KeyValue
{
private:
    int key;
    double value;
    KeyValue *next = nullptr;

public:
    KeyValue(int key, double value);

    ~KeyValue();

    int getKey();
    double getValue();

    KeyValue *cNext(int n);

    void fNext(int n);

    KeyValue *getPtr(int n);

    double getNValue(int n);

    void delKey(int n);
};
