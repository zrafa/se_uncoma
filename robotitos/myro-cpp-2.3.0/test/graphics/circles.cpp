#include <Myro.h>

static const int max_circle_radius=50;

Color makeColor(){
    //creates a new color using random RGB values
    int red   = rand()%256;
    int green = rand()%256;
    int blue  = rand()%256;
    return color_rgb(red, green,blue);
}

int main(){
    const int width=500;
    const int height=500;
    GraphWin myCanvas("Circles",width,height);
    myCanvas.setBackground("white");
    // draw a bunch of random 
    // circles with random 
    // colors.
    int N = 500;
    for (int i = 0; i < N; i++) {
        // pick random center 
        // point and radius 
        // in the window
        int x = rand()%width;
        int y = rand()%height;
        int r = rand()%20 + 5;//randrange(5, 25);
        Circle c(Point(x, y), r);
        // select a random color
        c.setFill(makeColor());
        c.draw(myCanvas);
    }
    myCanvas.waitWinClosed();
}
