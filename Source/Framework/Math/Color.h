#pragma once

class Color
{
public:
    unsigned char myRed;
    unsigned char myGreen;
    unsigned char myBlue;
    unsigned char myAlpha;

    Color() : myRed(0), myGreen(0), myBlue(0), myAlpha(0) {}
    Color(unsigned char aRed, unsigned char aGreen, unsigned char aBlue, unsigned char anAlpha)
    {
        myRed = aRed;
        myGreen = aGreen;
        myBlue = aBlue;
        myAlpha = anAlpha;
    }
};