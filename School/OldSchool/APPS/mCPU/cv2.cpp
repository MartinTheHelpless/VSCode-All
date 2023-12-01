#include "mbed.h"

// LEDs on K64F-KIT - instances of class DigitalOut

DigitalOut leds[8] = {PTC0, PTC1, PTC2, PTC3, PTC4, PTC5, PTC7, PTC8};

DigitalIn b1(PTC9);
DigitalIn b2(PTC10);
DigitalIn b3(PTC11);

DigitalOut r(PTB10);
DigitalOut g(PTB11);
DigitalOut b(PTB18);

int led = 0;

int ledBr = 10;

bool up = false;

int times = 0;

void ledChange();

void rgbLed();

int main()
{
    Ticker tik;
    tik.attach(ledChange, 1ms);
    // tik.attach(rgbLed, 1ms);
    while (true)
    {
    }
}

void ledChange()
{

    if (b2 == 0 && times % 150 == 0)
    {
        leds[led] = 0;
        leds[led == 0 ? 7 : led - 1] = 0;
        leds[led == 0 ? 6 : led == 1 ? 6
                                     : led - 2] = 0;
        led++;
        led >= 8 ? led = 0 : led;
    }
    else if (b1 == 0 && times % 150 == 0)
    {
        leds[led] = 0;
        leds[led == 7 ? 0 : led + 1] = 0;
        leds[led == 7 ? 1 : led == 6 ? 0
                                     : led + 2] = 0;
        led--;
        led < 0 ? led = 7 : led;
    }
    else if (b3 == 0 && times % 100 == 0)
    {
        ledBr >= 10 ? up = false : up;
        ledBr < 0 ? up = true : up;

        up == false ? ledBr -= 2 : ledBr += 2;
    }

    if (times % 11 <= ledBr)
    {
        leds[led] = 1;
        leds[led == 0 ? 7 : led - 1] = 1;
        leds[led == 0 ? 6 : led == 1 ? 6
                                     : led - 2] = 1;
    }
    else
    {
        leds[led] = 0;
        leds[led == 0 ? 7 : led - 1] = 0;
        leds[led == 0 ? 6 : led == 1 ? 6
                                     : led - 2] = 0;
    }

    times++;
    times >= 100 ? times = 0 : times;
}

void rgbLed()
{

    if (b1 == 0 && times % 125 == 0)
    {
        r >= 1 ? r = 0 : r = 1;
    }
    else if (b2 == 0 && times % 125 == 0)
    {
        g >= 1 ? g = 0 : g = 1;
    }
    else if (b3 == 0 && times % 125 == 0)
    {
        b >= 1 ? b = 0 : b = 1;
    }

    if (r == 0 && g == 0 && b == 0)
    {
        r = 1;
        b = 1;
    }

    times++;
}