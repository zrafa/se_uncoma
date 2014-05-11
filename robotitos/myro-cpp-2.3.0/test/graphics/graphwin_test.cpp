#include<Myro.h>
#include<iostream>

using namespace std;

Pixel red = {255,0,0};
Pixel green = {0,255,0};
Pixel blue = {0,0,255};
Pixel white = {255,255,255};
Pixel black = {0,0,0};

int main(){

    cerr << "Creating GraphWin" << endl;
    GraphWin win("My Window", 500, 500);
    cerr << "Created GraphWin" << endl;

    cerr << "Creating Rectangle" << endl;
    Rectangle rect(Point(0,100), Point(50,150));
    /*
    rect.setFill(red);
    rect.setOutline(blue);
    rect.setWidth(3);
    */
    rect.draw(win);

    Rectangle rect2(Point(100,0), Point(150,50));
    rect2.setFill(blue);
    rect2.setOutline(red);
    rect2.setWidth(3);
    rect2.draw(win);

    Circle cir(Point(400,50), 50);
    cir.setFill(blue);
    cir.setOutline(white);
    cir.setWidth(3);
    cir.draw(win);

    Text t(Point(200,250), "Hello, World!");
    t.setSize(43);
    t.draw(win);

    Line arrow(Point(350,50), Point(450,450));
    arrow.setArrow("both");
    arrow.setWidth(10);
    arrow.draw(win);

    int i = 0;
    bool b = true;
    while(rect.getP1().getX() < 500){
        if ( i % 4 == 0){
            win.setBackground(black);
        } else if ( i % 2 == 0 ){
            win.setBackground(green);
        }
        i++;
        rect.move(5,0);
        if ( rect2.getP1().getY() > 300 ){
            if (b){
                rect2.undraw();
                cir.undraw();
            }
            b=false;
        }
        else{
            rect2.move(0,5);
            cir.move(0,5);
        }
        wait(0.2);
    }
    win.close();
    //win.waitWinClosed();
    return 0;
}
