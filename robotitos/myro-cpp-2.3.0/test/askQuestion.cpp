#include<Myro.h>
#include<VideoStream.h>
#include<iostream>

int main(){
    //connect();
    //VideoStream vs(robot,VideoStream::COLOR);
    //vs.startStream();

    std::cout << askQuestion("How are you today?","  good   , Better, best, Awesome, Super") << std::endl;
    //vs.endStream();
    //disconnect();
    return 0;
}
