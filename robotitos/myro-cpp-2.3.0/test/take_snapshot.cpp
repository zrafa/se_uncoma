#include <Myro.h>
#include <VideoStream.h>
#include <iostream>
#include <string>
#include <cstring>
#include <iostream>
#include <cmath>
#include <cstdio>


int main(int argc, char ** argv) {

    int color_mode = -1;

    if(argc != 2) {
        fprintf(stderr, 
                "Usuage: ./snapshot_taker color|gray\n");
        return -1;
    }
    else if(!strcmp(argv[1], "color")) {
        color_mode = 1;
    }
    else if(!strcmp(argv[1], "gray")) {
        color_mode = 0;
    }
    else {
        fprintf(stderr, 
                "Usuage: ./snapshot_taker color|gray\n");
        return -1;
    }

    connect();

    VideoStream video(&robot, color_mode);

    video.startStream();

    int close = 0;
    std::string quit;
    while(!close) {
        std::cout << "Type in E or Exit to quit & Take Picture\n";
        std::cin >> quit;
        if(quit == "E" || quit == "Exit" || quit == "e" || quit == "exit")
            close = 1;
    }
    PicturePtr pic = robot.takePicture( argv[1] );
    pic->savePicture("snapshot.jpg");
    video.endStream();
    //sleep(5);
    //std::cout << "restarting" << std::endl;
    //}
    disconnect();
    return 1;
}

