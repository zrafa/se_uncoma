#include<Myro.h>
#include<iostream>

using namespace std;

Pixel red = {255,0,0};
Pixel green = {0,255,0};
Pixel blue = {0,0,255};
Pixel white = {255,255,255};
Pixel black = {0,0,0};

int main(){

    connect();
    robot.setForwardness("fluke-forward");
    //VideoStream vs(robot, VideoStream::COLOR);
    GraphWin win("Joystick", 500, 500);
    //vs.startStream();

    Circle cir(Point(250,250), 250);
    cir.setWidth(3);
    cir.draw(win);

    // Constantly poll the mouse position and draw a circle
    Point dir;
    Point m;
    Point center(250,250);
    Line l(center,center);
    int button=0;
    while(!win.isClosed()){
        m = win.getCurrentMouse(button);
        if (m.getX() >= 0 && m.getY() >= 0 && button){
            dir = center - m;
            //std::cerr << m.getX() << " " << m.getY() << std::endl;
            //std::cerr << dir.getX() << " " << dir.getY() << std::endl;
            robot.move(dir.getY()/250.0,dir.getX()/250.0);
            //std::cerr << "m.getX(): " << m.getX() << std::endl
            //          << "m.getY(): " << m.getY() << std::endl;
            l.undraw();
            l = Line(center, m);
            l.setWidth(3);
            l.draw(win);
        }
        else{
            l.undraw();
            robot.move(0,0);
            //std::cerr << "l.undraw(): " << std::endl;
        }
        wait(0.05);
    }
    //vs.endStream();
    //win.waitWinClosed();
    disconnect();
    return 0;
}
