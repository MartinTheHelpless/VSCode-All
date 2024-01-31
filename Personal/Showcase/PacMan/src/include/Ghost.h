#pragma once
#include <SDL2/SDL.h>

class Ghost
{
private:
    int m_Id;
    int m_Speed;
    int m_Mode; // Scatter, chase, frightened and eaten modes - 0, 1, 2, 3 respectively
    SDL_Color m_Color;

public:
    Ghost(int id, int speed, int algorithm, SDL_Color color)
        : m_Id(id), m_Speed(speed), m_Mode(algorithm), m_Color(color) {}

    void SetSpeed(int speed) { m_Speed = speed; }
    void SetColor(SDL_Color color) { m_Color = color; }
    void SetMode(int mode) { m_Mode = mode; }

    int GetID() { return m_Id; }
    int GetSpeed() { return m_Speed; }
    int GetMode() { return m_Mode; }

    SDL_Color GetColor() { return m_Color; }
};