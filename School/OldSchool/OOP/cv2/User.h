#include <string>

class User
{
private:
    int height;
    int age;
    std::string name;

public:
    User(std::string name, int age, int height);

    int getHeight();
    int getAge();
    std::string getName();

    void setHeight(int height);
    void setAge(int age);
    void setName(std::string name);

    std::string toString();
};
