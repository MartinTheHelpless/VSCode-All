#include <stdio.h>

char tst[] = "Ah00j pr0gr4m444tor33!";

char tst2[] = "Dobry den ). Nejde vam zapnout pocitac (";

int cislice(char *pole);

int prvni_bit(int t_cislo);

void nahradit(char *pole);

int main()
{

    printf("\"%s\" ma nejdelsi sekvenci cislic %d\n", tst, cislice(tst));
    /*
    nahradit(tst2);

    printf("%s\n", tst2);*/

    int rnd = 64;

    printf("Prvni bit s hodnotou 1 je na pozici %d --- %d\n", prvni_bit(64), rnd);

    return 0;
}