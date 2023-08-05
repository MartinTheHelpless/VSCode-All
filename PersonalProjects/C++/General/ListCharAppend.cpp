#include <iostream>
#include <cstring>

int main(int argc, char const *argv[])
{

    FILE *original = fopen("original.txt", "rw+");

    FILE *edited = fopen("finFile.txt", "w");

    if (edited == NULL)
    {
        std::cout << "File error." << std::endl;
        return 1;
    }

    char c;

    std::cout << "What character would you like to append on the end of each line ? " << std::endl;

    std::string appd = " & description & & & \\\\ ";

    c = getc(original);

    while (c != EOF)
    {
        if (c == '\n')
        {
            fputs(appd.c_str(), edited);
            fputc('\n', edited);
        }
        else
        {
            fputc(c, edited);
        }
        c = getc(original);
    }

    fputs(appd.c_str(), edited);
    fputc('\n', edited);

    fclose(original);
    fclose(edited);

    return 0;
}
