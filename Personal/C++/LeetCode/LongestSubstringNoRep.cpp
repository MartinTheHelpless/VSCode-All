#include <iostream>

int main(int argc, char const *argv[])
{
    std::string s = "dvdf";

    int letter[255];

    for (int i = 0; i < 255; i++)
        letter[i] = -1;

    char c = (char)(0);

    int longest = 0;

    int tests = 0;

    for (int i = 0; i < s.size(); i++)
    {
        c = s[i];

        if (letter[(int)c] > -1)
        {
            longest < tests ? longest = tests : longest;
            tests = 0;
            i = letter[(int)c];
            for (int j = 0; j < 255; j++)
                letter[j] = -1;
        }
        else
        {
            letter[(int)c] = i;
            tests++;
        }
    }
    longest < tests ? longest = tests : longest;
    std::cout << longest << std::endl;

    return 0;
}