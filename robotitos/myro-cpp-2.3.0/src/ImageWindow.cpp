#include "ImageWindow.h"
#include "MyroInternals.h"
#include <FL/Fl.H>
#include <FL/Fl_Image.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>
#include <iostream>
#include <cstring>

ImageWindow::ImageWindow(int width, int height, char * title) 
: Fl_Window(width, height, title), 
    image(NULL),
    exclusive(new boost::mutex()),
    m(NULL),
    cond(NULL)
{ 
    unsigned char temp[width*height*3];
    std::memset(temp,255,width*height*3);
    image = new Fl_RGB_Image(temp,width,height);
}


ImageWindow::ImageWindow(int x, int y, int width,
        int height, char * title)
: Fl_Window(x, y, width, height, title),
  image(NULL),
  exclusive(new boost::mutex()), 
  m(NULL), 
  cond(NULL)
{
    unsigned char temp[width*height*3];
    std::memset(temp,255,width*height*3);
    image = new Fl_RGB_Image(temp,width,height);
}

ImageWindow::~ImageWindow(){
    delete exclusive;
    if (image) delete image;
}

void ImageWindow::loadImageSource(unsigned char * data, int width, int height) {
    boost::mutex::scoped_lock l(*exclusive);
    if(image)
        delete image;
    if(color_mode)
        image = new Fl_RGB_Image((const unsigned char*)data, width, height);
    else
        image = new Fl_RGB_Image((const unsigned char*)data, width, height,1);

}

void ImageWindow::set_color_mode(int color_mode) {
    this->color_mode = color_mode;
}

void ImageWindow::draw() {
    boost::mutex::scoped_lock l(*exclusive);
    if(image != NULL) {
        if(color_mode)
            fl_draw_image((unsigned char*)(*(image->data())), 0, 0, image->w(),
                    image->h());
        else
            fl_draw_image((unsigned char*)(*(image->data())), 0, 0, image->w(),
                    image->h(), 1);
    }
}

void ImageWindow::NotifyWhenClosed(boost::mutex* mutex, 
                                   void* condition){
                                   //boost::condition* condition){
    m = mutex;
    cond=condition;
}


int ImageWindow::handle(int event){
    //std::cerr << "ImageWindow::handle(): " << event << std::endl;
    if ( event == FL_CLOSE || event == FL_HIDE){
        //std::cerr << "ImageWindow::handle():FL_CLOSE" << std::endl;
        if ( m && cond ){
            //std::cerr << "ImageWindow::handle():inside" << std::endl;
            {
                boost::mutex::scoped_lock l(*m);
                ((boost::condition*)cond)->notify_one();
            }
            m = NULL;
            cond = NULL;
        }
    }

    return Fl_Window::handle(event);
}


void ImageWindow::refresh() {
    boost::mutex::scoped_lock l(*exclusive);
    this->redraw();
}

