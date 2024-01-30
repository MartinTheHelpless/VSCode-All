#pragma once

class Ghost
{
private:
    struct Color
    {
        int m_R;
        int m_G;
        int m_B;
        int m_A;
        Color(int r, int g, int b, int a) : m_R(r), m_G(g), m_B(b), m_A(a) {}
    };

    int m_Id;
    int m_Speed;
    int m_Algorithm; // index of a algorithm to decide the ghost path
    Color m_Color;

public:
    Ghost(/* args */);
    ~Ghost();
};