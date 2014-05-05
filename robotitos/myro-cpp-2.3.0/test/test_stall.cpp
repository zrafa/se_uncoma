#include<Myro.h>
#include<iostream>

using namespace std;

int main(){
    connect();
    robot.forward(1);
    wait(1);
    for(int i = 0; i < 20; i++){
        bool isStalled = robot.getStall();
        cout << isStalled << endl;
        wait(1);
    }
    disconnect();
}
