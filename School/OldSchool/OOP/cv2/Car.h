#include <string>

class Car
{
private:
    std::string make;
    std::string type;
    std::string color;
    int makeYear;
    int horsePower;

public:
    Car(std::string make, std::string type, std::string color, int makeYear, int horsePower);

    std::string getMake();
    std::string getType();
    std::string getColor();
    int getMakeYear();
    int getHP();

    void setMake(std::string make);
    void setType(std::string type);
    void setColor(std::string color);
    void setMakeYear(int year);
    void setHP(int hp);

    std::string toString();
};
