#include <string>

class Car
{
private:
    std::string SPZ;
    std::string VIN;
    int id;

public:
    Car(std::string spz, std::string vin, int id);

    std::string getSPZ();

    std::string getVIN();

    int getID();
};
