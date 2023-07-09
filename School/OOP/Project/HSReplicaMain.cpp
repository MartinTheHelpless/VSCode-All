#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "Player.cpp"

int display = 0;

int main(int argc, char const *argv[])
{

    std::cout << "What would you like to be called ? " << std::endl;

    std::string name;

    std::cin >> name;

    Player *me = new Player(name);

    Player *bot = new Player(name);

    while (true)
    {
        switch (display)
        {
        case 0: // MENU
            std::cout << "1. Play\n2. Collection\n3. Settings\n4. Quit" << std::endl;
            std::cin >> display;
            break;

        case 1: // Play

            /*
            1. Create two player objects with a class, class specific hearo power, deck, name, 30hp
            2. Decide which player goes first (Probably just alternate between going 1st and 2nd)
            3. Draw cards accordnigly and randomly (3 for 1st player 4 for 2nd + coin)
            4. Give an option to re-draw each card once
            5. Redraw cards if requested
            6. Give 2nd player a coin and organize cards on the bottom of the screen
            7. Start turn of the first player - x mana - turnNum <= 10 ? x = turnNum : x = 10;
            8. Highlight playable cards in some color, restrict non-playable card movement
            9. Do actions accordnig to cards played - end turn, hero power target, etc.
            10. Change turns and let enemy play
            */
            break;

        case 2: // Collection
            /*
            1. Display the collection in a grid (Probably 4 by 2 with a standard card format)
            2. Filter by class, show card attributes (name, rarity, class, mana cost, etc.)
            3. Give the options to see all collectable card, change pages, filter cards, etc.
            4. Disenchant cards or maybe just exchange a card for another (only once per card)
            5. Keep count of all cards and display amount owned under card or in a corner
            */
            break;

        case 3: // Settings.
            while (display != 2)
            {
                std::cout << "1. Change Name\n2. Back To Menu" << std::endl;
                std::cin >> display;
                if (display == 1)
                {
                    std::cout << "What name would you like ? \n";
                    std::cin >> name;
                    me->changeName(name);
                    std::cout << "We shall now call you " << me->getName() << std::endl;
                }
            }
            display = 0;
            break;

        case 4: // Quit
            return 0;
            break;

        default:
            display = 0;
            break;
        }
    }

    return 0;
}
