#include<Myro.h>
#include<iostream>

using namespace std;

Pixel red = {255,0,0};
Pixel green = {0,255,0};
Pixel blue = {0,0,255};
Pixel white = {255,255,255};
Pixel black = {0,0,0};

int main(){

    GraphWin win("My Window", 500, 500);
    win.setBackground("blue");

    std::vector<Point> pts;
    pts.push_back(Point(100,100));
    pts.push_back(Point(150,120));
    pts.push_back(Point(220,450));
    pts.push_back(Point(120,420));


    Polygon poly(pts);
    poly.setWidth(5);
    poly.draw(win);

    win.waitWinClosed();
    return 0;
}
