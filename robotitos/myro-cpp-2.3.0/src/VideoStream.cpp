#include "VideoStream.h"
#include <assert.h>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <exception>
#include "MyroInternals.h"
#include <MyroCImg.h>

#define image_height 192
#define image_width 256

class DisplayThread : public Threaded{
    public:
    DisplayThread(Scribbler* robot, int colormode,
                          std::vector<Filter*>* filters,
                              boost::mutex& _filterLock);
    //virtual void start();
    virtual void run();
    //void stop();
    private:
    std::vector<Filter*>* filters;
    boost::mutex& filterLock;
    Scribbler* robot;
    int color_mode;
};


VideoStream::VideoStream(Scribbler * scrib, int color_mode)
: filterLock(new boost::mutex()){
    this->myScrib = scrib;
    this->color_mode = color_mode;
    this->filters = new std::vector<Filter*>();
    this->running = false;
}

VideoStream::VideoStream(Scribbler& scrib, int color_mode) 
: filterLock(new boost::mutex()){
    this->myScrib = &scrib;
    this->color_mode = color_mode;
    this->filters = new std::vector<Filter*>();
    this->running = false;
}

VideoStream::~VideoStream() {
    this->endStream();
    filters->clear();
    delete filterLock;
    delete filters;
}


// Dispaly/Update Thread
DisplayThread::DisplayThread(Scribbler* robot, int colormode, std::vector<Filter*>* filters,
                                          boost::mutex& _filterLock)
:  Threaded(), filterLock(_filterLock)
{
    this->robot = robot;
    this->color_mode = colormode;
    this->filters = filters;
}

void DisplayThread::run() {
    PicturePtr img_cur;
    PicturePtr img_new;

    while(!this->stopRequested){
        //std::cerr << "DisplayThread::run()" << std::endl;
        //printf("display_stream() Waiting on Picture\n");
        switch(this->color_mode) {
            case 0: 
                img_new = robot->takePicture("grayjpeg");
                break;
            case 1:
                img_new = robot->takePicture("jpeg");
                break;
            case 2:
                img_new = robot->takePicture("blob");
                break;
            default: 
            {
                throw "Invalid Color Mode\n";
            }
        }
        // If we got a NULL picture, shut down thread
        if ( img_new.get() == NULL )
            this->stopRequested = true;

        if ( this->stopRequested ) break;

        //printf("display_stream() Picture Received\n");

        {
            boost::mutex::scoped_lock l(filterLock);
            for(unsigned int i = 0; i < this->filters->size(); i++) {
                this->filters->at(i)->applyFilter(img_new);
            }
        }

        show(img_new, "Video Stream");

        /*
        if ( img_cur != NULL ){
            delete img_cur;
        }*/
        img_cur = img_new;

        //boost::thread::yield();
        //usleep(1000); //hack to slow down the capture thread
                      //so that the other threads are scheduled
        //printf("display_stream() Image Updated\n");

    }
    return;
}


void VideoStream::startStream() {
    if ( !running ){
        display_thread = new DisplayThread(myScrib, color_mode,filters, *filterLock);

        display_thread->start();
        running = true;
    }
}

int VideoStream::addFilter(Filter * filter) {
    boost::mutex::scoped_lock l(*filterLock);
    //pthread_mutex_lock(filterLock);
    int result = 0;
    filters->push_back(filter);
    result = filters->size()-1;
    //pthread_mutex_unlock(filterLock);
    return result;
}

int VideoStream::delFilter(int filter_location) {
    if(filter_location < 0 || filter_location >= (int)filters->size())
        return -1;

    boost::mutex::scoped_lock l(*filterLock);
    filters->erase(filters->begin() + filter_location);

    return 0;
}

void VideoStream::endStream() {
    if ( running ){

        display_thread->stop();

        delete display_thread;
        running = false;
    }
}

