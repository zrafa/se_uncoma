#include<Myro.h>
#include<iostream>

int main(){
    connect();
    GraphWin win("Cascading Windows", 400, 300);
    for (int i = 0; i < 10; i++){
        Point anchor(10+i*30, 10+i*20);
        Image img(anchor, robot.takePicture());
        img.draw(win);
    }
    disconnect();
}
