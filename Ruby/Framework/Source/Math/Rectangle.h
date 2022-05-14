#pragma once

class Rectangle
{
public:
    int x;
    int y;
    int w;
    int h;

    Rectangle() : x(0), y(0), w(0), h(0) {}
    Rectangle(int nx, int ny, int nw, int nh) { x = nx; y = ny; w = nw; h = nh; }

    void Set(int nx, int ny, int nw, int nh) { x = nx; y = ny; w = nw; h = nh; }
};
