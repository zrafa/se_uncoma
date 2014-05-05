#include <Myro.h>
#include <math.h>
#include <iostream>

using namespace std;

int main(int argc, char ** argv) {

    connect();

    robot.setForwardness("fluke-forward");

	cout << "Connected to Robot\n";
	cout << "Proceeding to test motor commands\n";

	std::vector<int> sensors;

	robot.set("Led", 0, 1);
	robot.set("Led", 1, 1);
	robot.set("Led", 2, 1);

	std::vector<std::string> info = robot.getInfo();
	for(unsigned int i = 0; i < info.size(); i++) {
		std::cout << info.at(i) << std::endl;
	}

	//robot->set("name", "FooBar");
	//robot->set("PASSWORD", "SPAZ");

	robot.set("Led", "center", 0);
	robot.set("Led", "left", 0);
	robot.set("Led", "right", 0);
	robot.set("fowardness", 1);

	std::vector<int> obstacle;
	while(1) {
		obstacle = robot.getObstacle();
		for(unsigned int i = 0; i < obstacle.size(); i++) {
			std::cout << obstacle.at(i) << " ";
		}
		std::cout << std::endl;
		if(obstacle.at(1) < 1000) {
			robot.move(1,0);
		}
		else {
			robot.stop();
			robot.beep(0.5, 400);
			robot.move(0, 1);
			robot.beep(0.5, 400, 400);
		}
	}
    disconnect();

	return 0;
}
