#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include "defines.h"

class Ghost
{
private:
    int m_ID;
    int m_State; // Scatter, chase, frightened and eaten modes - 0, 1, 2, 3 respectively
    int m_Direction;
    int m_NextDirection;
    int m_Speed;

    int m_ChangeTimes[6] = {6, 20, 6, 20, 6, 15};

    Uint32 m_ScaredStartTicks;

    SDL_Color m_Color;

    std::pair<int, int> m_ScatterTarget;
    std::pair<int, int> m_ChaseTarget;

    float m_X;
    float m_Y;
    float m_FrameMove;

    void ChangeDirection(char map[31][29]);
    void SetNextDirection(uint32_t timer, char map[31][29]);
    void ChangeDirectionIfOnCrossroad(int pacManX, int pacManY, int pacManDir, int blinkyX, int blinkyY, char map[31][29]);
    void UpdateState(Uint32 ticks, char map[31][29]);
    void GetNextDirection(std::pair<int, int> &target, char map[31][29]);

    std::pair<int, int> GetChaseTile(int ghostID, int pacManX, int pacManY, int pacManDir, int blinkyX, int blinkyY);

    int GetRandomFreeDirection(int base_X, int base_Y, char map[31][29]);
    int GetFreeDirection(int base_X, int base_Y, std::pair<int, int> &target, char map[31][29]);

public:
    Ghost(int id, float x, float y, int direction, float speed, std::pair<int, int> scatter, SDL_Color color);

    void Update(char map[31][29], int pacManX, int pacManY, int pacManDir, int blinkyX, int blinkyY, Uint32 ticks);

    void SetColor(SDL_Color color) { m_Color = color; }
    void SetState(int state)
    {
        if (state == 2)
            m_ScaredStartTicks = SDL_GetTicks();
        else
            m_ScaredStartTicks = 0;

        if (state == 0 || state == 1)
        {
            m_Speed = 2;
            m_NextDirection = (m_Direction + 2) % 4;
        }
        else if (state == 2)
        {
            m_Speed = 1;
            m_NextDirection = (m_Direction + 2) % 4;
        }
        else
            m_Speed = 4;

        m_State = state;
    }

    int GetId() { return m_ID; }
    int GetState() { return m_State; }
    int GetDirection() { return m_Direction; }

    float GetX()
    {
        return m_X;
    }
    float GetY() { return m_Y; }
    float GetSpeed() { return m_Speed; }

    std::pair<int, int> GetScatterTile() { return m_ScatterTarget; }
    std::pair<int, int> GetChaseTile() { return m_ChaseTarget; }

    SDL_Color GetColor()
    {

        if (m_State == 2)
            return {33, 33, 222, 0};
        else if (m_State == 3)
            return {35, 35, 35, 0};
        else if (m_State == 1 || m_State == 0)
            return m_Color;
        else
            return m_Color;
    }
};