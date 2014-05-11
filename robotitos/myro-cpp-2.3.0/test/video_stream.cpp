/** @file 
 * 
 * @brief An example using the VideoStream and Filters
 *
 * This file creates several example filters, and will 
 * have them turned on based on the provided command-line
 * arguments. 
 */

#include <Myro.h>
#include <VideoStream.h>
#include <Filter.h>
#include <iostream>
#include <string>
#include <cstring>
#include <iostream>
#include <cmath>
#include <cstdio>

class InvertFilter: public Filter {

    public:
    virtual void filter(Picture * image) {
        int height = image->getHeight();
        int width = image->getWidth();

        Pixel temp;
        for(int h = 0; h < height/2; h++) {
            for(int w = 0; w < width; w++) {
                temp = image->getPixel(w,h);
                image->setPixel(w,h, image->getPixel(w,(height-1)-h));
                image->setPixel(w,(height-1)-h,temp);
            }
        }
    }

    private:
};

class LightMask: public Filter {
    
    public:

    virtual void filter(Picture * image) {

        //int color_mode = getColorMode();
        //if(color_mode)
        //    return;

        int imageHeight = image->getHeight();
        int imageWidth  = image->getWidth();

        int numPartitions = 4;
        int partition_width = imageWidth/numPartitions;

        int shadePartition;
        double brightEst = 0;
        int partition_sum[6] = {0,0,0,0,0,0};

        // Sum up each partition
        for(int y = 0; y < imageHeight; y++) {
            for(int partition = 0; partition < numPartitions; partition++) {
                for(int x = partition*partition_width; x < (partition+1)*partition_width; x++) {
                    //partion[j] += image[(h * imageWidth) + (h * partition_width) + k];
                    Pixel pix = image->getPixel(x,y);
                    partition_sum[partition] += pix.R + pix.G + pix.B;
                }
            }
        }

        // Determine which partition is the brightest
        shadePartition = 0;
        brightEst = partition_sum[0]/(imageHeight * partition_width);
        for(int i = 1; i < numPartitions; i++) {
            if( partition_sum[i]/(imageHeight * partition_width) > brightEst ) {
                shadePartition = i;
                brightEst = partition_sum[i]/(imageHeight * partition_width);
            }
        }

        Pixel black = {0,0,0};
        // Make every region thats not the drawn one black
        for(int y = 0; y < imageHeight; y++) {
            for(int partition = 0; partition < numPartitions; partition++) {
                if ( partition != shadePartition ){
                    for(int x = partition*partition_width; x < (partition+1)*partition_width; x++) {
                        image->setPixel(x,y,black);
                    }
                }
            }
        }
    }

};

int main(int argc, char ** argv) {

    int color_mode = -1;
    int enableInvert = 0;
    int enableLightMask = 0;

    if(argc < 2) {
        fprintf(stderr, 
                "Usuage: ./video_stream color|gray invert|light|none\n");
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
                "Usuage: ./video_stream color|gray invert|light|none\n");
        return -1;
    }

    if(argc < 5 && argc > 2) {
        if(!strcmp(argv[2], "invert"))
            enableInvert = 1;
        else if(!strcmp(argv[2], "light"))
            enableLightMask = 1;
        else if(strcmp(argv[2], "none"))
            fprintf(stderr, "Invalid Filter Opition\n");

        if(argc > 3) {
            if(!strcmp(argv[3], "invert"))
                enableInvert = 1;
            else if(!strcmp(argv[3], "light"))
                enableLightMask = 1;
            else if(strcmp(argv[3], "none"))
                fprintf(stderr, "Invalid Filter Opition\n");
        }
    }

    connect();

    InvertFilter * myInvertFilter;
    LightMask * myLightMask;
    VideoStream video(&robot, color_mode);

    if(enableInvert) {
        myInvertFilter = new InvertFilter();
        video.addFilter(myInvertFilter);
    }
    if(enableLightMask) {
        myLightMask = new LightMask();
        video.addFilter(myLightMask);
    }

    //while(true){
    video.startStream();

    int close = 0;
    std::string quit;
    while(!close) {
        std::cout << "Type in E or Exit to quit\n";
        std::cin >> quit;
        if(quit == "E" || quit == "Exit" || quit == "e" || quit == "exit")
            close = 1;
    }
    video.endStream();
    //sleep(5);
    //std::cout << "restarting" << std::endl;
    //}
    disconnect();
    if(enableInvert)
        delete myInvertFilter;
    if(enableLightMask)
        delete myLightMask;
    return 1;
}

