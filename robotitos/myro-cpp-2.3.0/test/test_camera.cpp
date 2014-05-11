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

    PicturePtr img = robot.takePicture("color");
    img->show();

	cout << "Testing Grayscale" << endl;
    img = robot.takePicture("gray");
    img->show();

	cout << "Testing Jpeg Color" << endl;
    img = robot.takePicture("jpeg");
    img->show();

	cout << "Testing Jpeg Gray" << endl;
    img = robot.takePicture("grayjpeg");
    img->show();

	cout << "All Camera Test Completed\n";

    disconnect();

	return 0;
}

