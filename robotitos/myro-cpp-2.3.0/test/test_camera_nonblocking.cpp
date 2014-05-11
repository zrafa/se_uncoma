#include <Myro.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
//using namespace Magick;
using namespace std;

int main(int argc, char ** argv) {

    connect();

    cout << "Connected to Robot" << endl;
    cout << "Proceeding to test camera" << endl;

    cout << "Testing Color, if image looks correct close display" << endl;
    cout << "If not, try restarting robot, and rerunning test" << endl;

    PicturePtr color = robot.takePicture("color");
    show(color, "Image");
    wait(0.5);

    cout << "Testing Grayscale" << endl;
    PicturePtr gray = robot.takePicture("gray");
    gray->show("Image");
    wait(0.5);

    cout << "Testing Jpeg Color" << endl;
    PicturePtr img = robot.takePicture("jpeg");
    show(img,"Image");
    wait(0.5);

    cout << "Testing Jpeg Gray" << endl;
    img = robot.takePicture("grayjpeg");
    show(img,"Image");
    wait(0.5);

    cout << "All Camera Test Completed\n";

    disconnect();

    return 0;
}

