#pragma once
#include <SDL2/SDL.h>
#include <iostream>

class Ghost
{
private:
    int m_State; // Scatter, chase, frightened and eaten modes - 0, 1, 2, 3 respectively
    int m_Direction;
    int m_NextDirection;
    std::pair<int, int> m_ScatterTarget;
    SDL_Color m_Color;

    float m_X;
    float m_Y;
    float m_Speed;

    void SetNextDirection(char map[31][29]);

public:
    Ghost(float x, float y, int direction, float speed, std::pair<int, int> scatter, SDL_Color color);

    void SetSpeed(int speed) { m_Speed = speed; }
    void SetColor(SDL_Color color) { m_Color = color; }
    void SetMode(int mode) { m_State = mode; }

    void Update(char map[31][29]);

    int GetMode() { return m_State; }

    float GetX() { return m_X; }
    float GetY() { return m_Y; }
    float GetSpeed() { return m_Speed; }

    SDL_Color GetColor() { return m_Color; }
};