#pragma once

class Rectangle
{
public:
    float myX;
    float myY;
    float myWidth;
    float myHeight;

    Rectangle() : myX(0.0f), myY(0.0f), myWidth(0.0f), myHeight(0.0f) {}
    Rectangle(float nx, float ny, float nw, float nh) { myX = nx; myY = ny; myWidth = nw; myHeight = nh; }
};
