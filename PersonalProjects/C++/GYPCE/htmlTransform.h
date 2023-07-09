#pragma once
#include <iostream>

void transportTxt(char stopChar, FILE *inputFile, FILE *outputFile)
{
    char c;

    c = fgetc(inputFile);

    while (c != stopChar && c != EOF)
    {
        fputc(c, outputFile);
        c = fgetc(inputFile);
    }
}

void putTextInHtml(FILE *txtFile, FILE *outputFile)
{
    char c;

    c = fgetc(txtFile);

    while (c != EOF)
    {
        c != '\n' ? fputc(c, outputFile) : fputs("<br>\n    ", outputFile);
        c = fgetc(txtFile);
    }
}
