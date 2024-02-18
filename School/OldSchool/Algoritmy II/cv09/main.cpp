#include <iostream>
#include <vector>

int maxCoins(std::vector<std::vector<int>> *vect, int x, int y, int dimX, int dimY, std::string *path);

int main(int argc, char const *argv[])
{

    std::vector<std::vector<int>> board = {
        {0, 0, 0, 0, 1, 0, 1, 0, 0, 1},
        {1, 0, 1, 0, 1, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 1, 1, 1, 0, 0, 1},
        {0, 1, 1, 1, 0, 1, 1, 0, 1, 1},
        {1, 1, 1, 0, 0, 1, 1, 0, 1, 1},
        {0, 1, 0, 0, 0, 0, 0, 1, 1, 1},
        {0, 1, 0, 1, 1, 1, 1, 0, 0, 0},
        {1, 1, 1, 0, 0, 1, 1, 1, 0, 1},
        {1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
        {1, 1, 0, 0, 0, 1, 0, 0, 0, 1},
        {1, 1, 0, 0, 0, 0, 0, 1, 1, 0},
        {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 1, 0, 0, 0, 0, 1, 1, 1, 1},
        {0, 0, 1, 1, 1, 0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 1, 1, 0},
        {0, 1, 1, 0, 0, 1, 1, 0, 0, 1},
        {0, 0, 0, 1, 1, 1, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 0, 0, 1, 0},
        {1, 0, 1, 1, 0, 0, 0, 1, 0, 1},
        {0, 0, 0, 0, 1, 1, 1, 0, 1, 1},
        {0, 0, 0, 1, 0, 1, 1, 0, 0, 0},
        {0, 1, 0, 1, 0, 0, 1, 1, 0, 0},
        {0, 0, 1, 1, 0, 1, 0, 1, 1, 0},
        {1, 1, 1, 1, 0, 1, 0, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

    std::string path = "";

    int x = maxCoins(&board, 0, 0, board[0].size(), board.size(), &path);

    std::cout << path << " -- " << x << std::endl;

    return 0;
}

int maxCoins(std::vector<std::vector<int>> *vect, int x, int y, int dimX, int dimY, std::string *path)
{

    if ((x + 1) >= dimX && (y + 1) >= dimY)
        return (*vect)[y][x];
    else if ((x + 1) >= dimX)
        return (*vect)[y][x] + maxCoins(vect, x, y + 1, dimX, dimY, path);
    else if ((y + 1) >= dimY)
        return (*vect)[y][x] + maxCoins(vect, x + 1, y, dimX, dimY, path);
    else
    {
        int r = maxCoins(vect, x + 1, y, dimX, dimY, path);
        int d = maxCoins(vect, x, y + 1, dimX, dimY, path);

        if (r >= d)
            return (*vect)[y][x] + r;
        else
            return (*vect)[y][x] + d;
    }
}