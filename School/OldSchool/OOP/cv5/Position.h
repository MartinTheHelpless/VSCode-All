#include <string>

class Position
{
private:
    long double x;
    long double y;

public:
    Position(long double x, long double y);

    long double getLng();

    long double getLat();
};
