#include "KeyValues.cpp"

int main(int argc, char const *argv[])
{

    KeyValue *myKey = new KeyValue(456, 891);

    myKey->fNext(8);

    std::cout << myKey->getNValue(5) << std::endl;

    myKey->delKey(5);

    std::cout << myKey->getNValue(5) << std::endl;

    return 0;
}
