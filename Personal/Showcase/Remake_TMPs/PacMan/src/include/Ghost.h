#pragma once
#include <SDL2/SDL.h>
#include <iostream>

class Ghost
{
private:
    int m_ID;
    int m_State; // Scatter, chase, frightened and eaten modes - 0, 1, 2, 3 respectively
    int m_NextState;
    int m_Direction;
    int m_NextDirection;
    std::pair<int, int> m_ScatterTarget;
    std::pair<int, int> m_ChaseTarget;
    SDL_Color m_Color;

    float m_X;
    float m_Y;
    float m_Speed;

    void SetNextDirection(char map[31][29]);
    std::pair<int, int> GetChaseTile(int ghostID, int pacManX, int pacManY, int pacManDir, int blinkyX, int blinkyY);

public:
    Ghost(int id, float x, float y, int direction, float speed, std::pair<int, int> scatter, SDL_Color color);

    void SetSpeed(float speed) { m_Speed = speed; }
    void SetColor(SDL_Color color) { m_Color = color; }
    void SetState(int state) { m_NextState = state; }

    void Update(char map[31][29], int pacManX, int pacManY, int pacManDir, int blinkyX, int blinkyY);

    int GetMode() { return m_State; }

    float GetX() { return m_X; }
    float GetY() { return m_Y; }
    float GetSpeed() { return m_Speed; }

    SDL_Color GetColor() { return m_Color; }
    std::pair<int, int> GetChaseTile() { return m_ChaseTarget; }
    std::pair<int, int> GetScatterTile() { return m_ScatterTarget; }
};