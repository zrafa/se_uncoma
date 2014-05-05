#include<Myro.h>
#include<MyroIO.h>
#include<iostream>
#include<vector>

using namespace std;

int main(){
    connect();
    for (int i = 0; i < 10; i++){
        vector<int> allir = robot.getIR();
        cout << "All: " << allir << endl;
        cout << "Left  (int) " << robot.getIR(0) << endl;
        cout << "Right (int) " << robot.getIR(1) << endl;
        cout << "Left  (string) " << robot.getIR("left") << endl;
        cout << "Right (string) " << robot.getIR("right") << endl << endl;
    }
    disconnect();
    return 0;
}
