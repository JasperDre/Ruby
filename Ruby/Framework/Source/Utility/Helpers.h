#pragma once

class MyColor
{
public:
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;

    MyColor() {}
    MyColor(unsigned char nr, unsigned char ng, unsigned char nb, unsigned char na)
    {
        r = nr;
        g = ng;
        b = nb;
        a = na;
    }
};