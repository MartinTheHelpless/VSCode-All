#include <iostream>
#include <vector>

int main(int argc, char const *argv[])
{

    std::vector<std::string> words = {"miniature", "statuesque", "ripe", "cabbage", "supreme", "tart", "sore", "sniff", "rampant", "refuse", "frequent", "tumble"};

    std::vector<std::string> results;

    for (int i = 0; i < words.size(); i++)
    {
        // API get translation of words[i];
        results.push_back(words[i]);
    }

    for (int i = 0; i < results.size(); i++)
    {
        std::cout << i << ". Original Word: " << words[i] << " as translated to "
                  << " Spanish "
                  << " is " << results[i] << std::endl;
    }

    // 1. Original Word: people as translated to Spanish is proce
    // 2. Original Word: people as translated to Spanish is proce
    // 3. Original Word: people as translated to Spanish is proce
    // 4. Original Word: people as translated to Spanish is proce
    // 5. Original Word: people as translated to Spanish is proce
    // 6. Original Word: people as translated to Spanish is proce

    return 0;
}
