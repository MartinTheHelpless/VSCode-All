#include <iostream>
#include <vector>

#define PI 3.14159265358979323846

int hashFunction(int input, int maxValue);

class HashTable
{
private:
    int size;
    std::string *array;
    int multiplier = 5;

public:
    HashTable(int size)
    {
        this->size = size;
        this->array = new std::string[this->multiplier * size];
        for (int i = 0; i < this->size * this->multiplier; i++)
            this->array[i] = "nullptr";
    };

    void insert(int key, std::string value)
    {
        int index = hashFunction(key, this->size * this->multiplier);

        if (this->array[index] == "nullptr")
            this->array[index] = value;
        else if (this->array[index + 1] == "nullptr")
            this->array[index] = value;
        else if (this->array[index + 2] == "nullptr")
            this->array[index + 3] = value;
        else if (this->array[index + 3] == "nullptr")
            this->array[index + 4] = value;
        else
            std::cout << "Error: Value could not be inserted. Please pick a different key." << std::endl;
    }

    std::string *search(int key)
    {
        int index = hashFunction(key, this->size * this->multiplier);

        std::string tmp0[this->multiplier] = {this->array[index],
                                              this->array[index + 1],
                                              this->array[index + 2],
                                              this->array[index + 3], this->array[index + 4]};

        return tmp0;
    }

    bool remove(int key)
    {
        int index = hashFunction(key, this->size * this->multiplier);

        for (int i = index; i < 4; i++)
            this->array[index + i] = "nullptr";

        return true;
    }

    void print()
    {

        for (int i = 0; i < this->size * this->multiplier; i++)
        {
            std::cout << "" << this->array[i % 4 == 0 ? i : (i - 1) % 4 == 0 ? i - 1
                                                        : (i - 2) % 4 == 0   ? i - 2
                                                        : (i - 3) % 4 == 0   ? i - 3
                                                                             : i - 4]
                      << std::endl;
        }
    }
};

int main(int argc, char const *argv[])
{

    std::string numberWords[101] = {
        "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
        "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen",
        "seventeen", "eighteen", "nineteen", "twenty",
        "twenty-one", "twenty-two", "twenty-three", "twenty-four", "twenty-five",
        "twenty-six", "twenty-seven", "twenty-eight", "twenty-nine",
        "thirty", "thirty-one", "thirty-two", "thirty-three", "thirty-four", "thirty-five",
        "thirty-six", "thirty-seven", "thirty-eight", "thirty-nine",
        "forty", "forty-one", "forty-two", "forty-three", "forty-four", "forty-five",
        "forty-six", "forty-seven", "forty-eight", "forty-nine",
        "fifty", "fifty-one", "fifty-two", "fifty-three", "fifty-four", "fifty-five",
        "fifty-six", "fifty-seven", "fifty-eight", "fifty-nine",
        "sixty", "sixty-one", "sixty-two", "sixty-three", "sixty-four", "sixty-five",
        "sixty-six", "sixty-seven", "sixty-eight", "sixty-nine",
        "seventy", "seventy-one", "seventy-two", "seventy-three", "seventy-four", "seventy-five",
        "seventy-six", "seventy-seven", "seventy-eight", "seventy-nine",
        "eighty", "eighty-one", "eighty-two", "eighty-three", "eighty-four", "eighty-five",
        "eighty-six", "eighty-seven", "eighty-eight", "eighty-nine",
        "ninety", "ninety-one", "ninety-two", "ninety-three", "ninety-four", "ninety-five",
        "ninety-six", "ninety-seven", "ninety-eight", "ninety-nine", "one hundred"};

    HashTable *hash = new HashTable(int(26));

    for (int i = 0; i < 101; i++)
        hash->insert(i, numberWords[i]);

    // hash->print();

    return 0;
}

int hashFunction(int input, int maxValue)
{
    return input * 4 % 26; // abs((int(input * PI) ^ 3) % maxValue);
}
