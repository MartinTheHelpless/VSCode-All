#include <string>

class Driver
{
private:
    std::string name;
    int licenseID;

public:
    Driver(std::string name, int id);

    std::string getName();

    int getID();
};
