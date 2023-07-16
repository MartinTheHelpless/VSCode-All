#include <iostream>
#include <vector>

int main(int argc, char const *argv[])
{

    std::string apiKey = "RGAPI-ae2e0108-7d70-4fac-aa23-6315de967c72";

    std::vector<std::string>
        words = {"miniature", "statuesque", "ripe", "cabbage", "supreme", "tart", "sore", "sniff", "rampant", "refuse", "frequent", "tumble"};

    std::vector<std::string> results;

    for (int i = 0; i < words.size(); i++)
    {
        // API get translation of words[i];
        results.push_back(words[i]);
    }

    /*for (int i = 0; i < results.size(); i++)
    {
        std::cout << i << ". Original Word: " << words[i] << " as translated to "
                  << " Spanish "
                  << " is " << results[i] << std::endl;
    }*/

    // 1. Original Word: people as translated to Spanish is proce
    // 2. Original Word: people as translated to Spanish is proce
    // 3. Original Word: people as translated to Spanish is proce
    // 4. Original Word: people as translated to Spanish is proce
    // 5. Original Word: people as translated to Spanish is proce
    // 6. Original Word: people as translated to Spanish is proce

    std::string sumName;

    for (;;)
    {
        std::cout << "Gimme a summoner name " << std::endl;

        std::cin >> sumName;

        // API request on country

        // datastructure x = API::getRequest("/lol/summoner/v4/summoners/by-name/{summonerName}");

        int level = 500;

        // int level = datastructure.summonerLevel

        // Parse the results

        std::cout << "Your summoner level is: " << level << std::endl;
    }

    return 0;
}
