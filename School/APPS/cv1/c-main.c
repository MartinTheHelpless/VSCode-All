#include <stdio.h>
#include <math.h>
#include <stdint.h>

uint8_t data[4] = {1, 2, 3, 4};
char dta[10] = "XXX0000";

int16_t key = -96;
int64_t extended;

uint8_t dat[4] = {0xAF, 0xBE, 0xAD, 0xDE};
int result;

void swap_endiannes();

void extend();

void compose();

void replace();

int main(int argc, char const *argv[])
{

    swap_endiannes();
    printf(
        "Array %d, %d, %d, %d\n",
        data[0],
        data[1],
        data[2],
        data[3]);

    replace();
    printf(
        "login %s \n",
        dta);

    extend();
    printf(
        "extended %ld \n",
        extended);

    compose();
    printf(
        "result %u \n",
        result);

    return 0;
}
