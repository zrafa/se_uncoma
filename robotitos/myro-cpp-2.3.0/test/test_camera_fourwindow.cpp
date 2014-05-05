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
    color->show("Color");

    cout << "Testing Grayscale" << endl;
    PicturePtr gray = robot.takePicture("gray");
    gray->show("Gray");

    cout << "Testing Jpeg Color" << endl;
    PicturePtr jpeg = robot.takePicture("jpeg");
    jpeg->show("Color JPEG");

    cout << "Testing Jpeg Gray" << endl;
    PicturePtr grayjpeg = robot.takePicture("grayjpeg");
    grayjpeg->show("Gray JPEG");

    cout << "All Camera Test Completed\n";
    cout << "Waiting 10 seconds" << endl;
    wait(10);

    disconnect();

    return 0;
}

