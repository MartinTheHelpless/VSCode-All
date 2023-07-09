#include <iostream>
#include "htmlTransform.h"
#include <cstring>

int main(int argc, char const *argv[])
{
    // argument: 1 - original html, output file, txt file

    const char *fonts[7] = {"Arial", "Verdana", "Tahoma", "Trebuchet MS", "Times New Roman", "Georgia", "Courier New"};

    FILE *originalHTML = fopen(argv[1], "rt+");

    if (originalHTML == NULL)
    {
        std::cout << "ORIGINAL HTML" << std::endl;
        return 1;
    }

    FILE *outputHTML = fopen(argv[2], "wt+");

    if (outputHTML == NULL)
    {
        std::cout << "OUTPUT HTML" << std::endl;
        return 1;
    }

    FILE *txtFile = fopen(argv[3], "rt+");

    if (outputHTML == NULL)
    {
        std::cout << "txt file" << std::endl;
        return 1;
    }

    char line[255];

    int fontNumber = -1;

    fgets(line, 18, txtFile);

    for (int i = 0; i < 7; i++)
    {
        if (strstr(line, fonts[i]) != NULL)
        {
            fontNumber = i;
            break;
        }
    }

    if (fontNumber == -1)
    {
        std::cout << "Nepodporovaný font" << std::endl;
        return 1;
    }

    fgets(line, 255, txtFile);
    char *token = NULL;
    token = strtok(line, "\n");

    if (token != NULL && (strstr(token, ".jpg") != NULL || strstr(token, ".png") != NULL || strstr(token, ".jpeg") != NULL))
    {
        transportTxt('*', originalHTML, outputHTML);
        fputs(token, outputHTML);
        transportTxt('*', originalHTML, outputHTML);
        fputs(fonts[fontNumber], outputHTML);
        transportTxt('*', originalHTML, outputHTML);
        putTextInHtml(txtFile, outputHTML);
        transportTxt('*', originalHTML, outputHTML);
    }
    else
    {
        transportTxt('*', originalHTML, outputHTML);
        fputs(token, outputHTML);
        transportTxt('*', originalHTML, outputHTML);
        fputs(fonts[fontNumber], outputHTML);
        transportTxt('*', originalHTML, outputHTML);
        putTextInHtml(txtFile, outputHTML);
        transportTxt('*', originalHTML, outputHTML);
    }

    fclose(originalHTML);
    fclose(outputHTML);
    fclose(txtFile);
}
