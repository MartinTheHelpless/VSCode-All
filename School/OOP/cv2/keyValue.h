#include <string>

class keyValue
{
private:
    int key;
    double value;

public:
    keyValue(int key, double value);

    int getKey();
    double getValue();

    void setKey(int key);
    void setValue(double value);
};
