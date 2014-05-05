#include <Myro.h>
#include <VideoStream.h>
#include <Filter.h>
#include <list>
#include <sstream>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

class PictureInPicture: public Filter {

    public:
        PictureInPicture(Scribbler& rob): rob(rob) {}
        ~PictureInPicture(){}

        virtual void filter(Picture* image) {
            PicturePtr colorImage = rob.takePicture("jpeg");

            int height = image->getHeight();
            int width = image->getWidth();
            int reduction = 4;

            int reduced_height = height/reduction;
            int reduced_width = width/reduction;


            for(int h = 0; h < reduced_height; h++) {
                for(int w = 0; w < reduced_width; w++) {
                    image->setPixel((width-reduced_width)+w,h,
                            colorImage->getPixel(reduction*w,reduction*h));
                }
            }

        }

    protected:
        Scribbler& rob;

};

/*
class Record : public Filter {
    public:

    Record(string location, string fileName, 
            int height, int width, int color_mode) 
        : Filter(height, width, color_mode) {
        this->location = location;
        this->fileName = fileName;
        imageList = new list<Image>();
    }

    ~Record(){
        string full_file = location + fileName;
        writeImages( imageList->begin(), imageList->end(), full_file );
        imageList->clear();
        delete imageList;
    }

    void filter(unsigned char * image) {
        Image robotImage(256,192, "RGB", CharPixel,image); 
        imageList->push_back(robotImage);
    }

    private:

    string location;
    string fileName;

    list<Image> * imageList;

};
*/

int main(int argc, char ** argv) {

    int enablePnp = 0;
    int enableRecord = 0;

    int check_index = 1;
    int path_index = -1;
    int file_name_index = -1;

    if(argc > 1) {
        if(!strcmp(argv[1], "record")) { 
            enableRecord = 1;
            check_index += 3;
            path_index = 2;
            file_name_index = 3;
        }
        else if(!strcmp(argv[1], "pnp")) {
            enablePnp = 1;
            check_index++;
        }
        else if(strcmp(argv[1], "none"))
            fprintf(stderr, "Invalid Filter Opition\n");
        if(argc > check_index) {
            if(!strcmp(argv[check_index], "record")) {
                enableRecord = 1;
                check_index += 3;
                path_index = check_index - 2;
                file_name_index = check_index - 1;
            }
            else if(!strcmp(argv[check_index], "pnp")) {
                enablePnp = 1;
                check_index++;
            }
            else if(strcmp(argv[check_index], "none"))
                fprintf(stderr, "Invalid Filter Opition\n");
        }
    }
    else if(argc < 2) {
        fprintf(stderr, "Usuage: ./test_blob pnp|record path filename|none\n");
        return -1;
    }
    
    if(argc < check_index) {
        fprintf(stderr, 
                "Usuage: ./test_blob pnp|record path filename|none\n");
        return -1;
    }

    connect();

    cout << "Connected to Robot\n";
    cout << "Proceeding to Train Blob\n";

    int mid_w = 256/2;
    int mid_h = 192/2;

    int x1 = mid_w - 10;
    int y1 = mid_h - 10;
    int x2 = mid_w + 10;
    int y2 = mid_h + 10;

    Pixel red = {255,0,0};

    int train = 0;
    string toTrain;

    PicturePtr showpic = robot.takePicture();
    PicturePtr trainpic = showpic->clone();
    while(!train) {
        for(int h = y1; h < y2; h++) {
            for(int w = x1; w < x2; w++) {
                showpic->setPixel(w,h,red);
            }
        }
        cout << "Use this image to train?" << endl;
        if(fork() == 0) {
            showpic->show();
            exit(0);
        }
        cin >> toTrain;
        if(toTrain == "y" || toTrain == "yes")
            train = 1;
    }
    robot.conf_rle_range(trainpic->getRawImage(), x1, y1, x2, y2);

    cout << "Proceeding to Test Blob Tracking\n";

    PictureInPicture * pnp;
    //Record * record;
    VideoStream foo(robot, 2);

    if(enablePnp) { 
        pnp = new PictureInPicture(robot);
        foo.addFilter(pnp);
    }
    /*
    if(enableRecord) {  
        record = new Record(argv[path_index], argv[file_name_index], 
                256,192,1);
        foo.addFilter(record);
    }
    */
    foo.startStream();

    int close = 0;
    string done;
    while(!close) {
        cout << "Enter E or Exit to quit\n";
        cin >> done;
        if(done == "E" || done == "Exit" || done == "e" || done == "exit")
            close = 1;
    }

    foo.endStream();
    if(enablePnp) 
        delete pnp;
    /*
    if(enableRecord)
        delete record;
        */
    disconnect();

    return 0;
}
