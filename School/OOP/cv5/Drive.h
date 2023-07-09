#include <string>
#include <vector>
#include "Driver.cpp"
#include "Car.cpp"
#include "Position.cpp"

class Drive
{
private:
    Driver *driver;
    Car *car;

    Position **positions;
    int positionCount;

public:
    Drive(Driver *driver, Car *car);
    ~Drive();

    void addPosition(long double x, long double y);

    double getTotalDistance();
};
