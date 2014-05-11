#include "Picture.h"
#include "MyroInternals.h"
#include <iostream>
#include <sstream>
#include <cstdlib>

Picture::Picture(){
    this->width = this->height = 0;
}

Picture::Picture(int width, int height) {
    this->width =  width;
    this->height = height;
    this->channels = 3;
    image_data.assign(width,height,1,channels);
}

Picture::Picture(unsigned char * data, int channels, int width, int height){
    this->width = width;
    this->height = height;
    this->channels = channels;
  
    if ( channels == 3 ){
        image_data.assign(width,height,1,channels);
        loadInterlacedImage(data);
    } else {
        image_data.assign(data,width,height,1,channels);
    }
}

Picture::Picture(Picture& pic)
{
    image_data.assign(pic.image_data);
    this->width = pic.width;
    this->height = pic.height;
    this->channels = pic.channels;
}

Picture::~Picture() {
}

Pixel Picture::getPixel(int x, int y) {
    if ( x >= width || y >= height )
        Picture::out_of_bounds_error(width,height,x,y);
    Pixel result;
    if ( channels == 3 ){
        result.R = image_data(x,y,0,0);
        result.G = image_data(x,y,0,1);
        result.B = image_data(x,y,0,2);
    }
    else{
        result.R = result.G = result.B = image_data(x,y,0,0);
    }
    return result;
}

void Picture::setPixel(int x, int y, Pixel pix) {
    if ( x >= width || y >= height )
        Picture::out_of_bounds_error(width,height,x,y);
    if ( channels == 3 ){
        image_data(x,y,0,0) = pix.R;  
        image_data(x,y,0,1) = pix.G;    
        image_data(x,y,0,2) = pix.B;    
    } else {
        image_data(x,y,0,0) = pix.R;  
    }
}

void Picture::show(std::string windowname){
    displayMan.set_picture_window(image_data, windowname.c_str());
}

void Picture::show(){
    const std::string windowname = "Picture";
    displayMan.set_picture_window(image_data, windowname.c_str());
    displayMan.block_on(windowname.c_str());
}

// TODO: Implement this!
PicturePtr Picture::clone(){
    PicturePtr p(new Picture(*this));
    //Picture* newpic = new ColorPicture(*this);
    //return newpic;
    return p;
}

bool Picture::loadPicture(const char* filename){
  /* And we're done! */
  image_data.load_jpeg(filename);
  this->width = image_data.width();
  this->height = image_data.height();
  this->channels = image_data.spectrum();
  return true;
}

void Picture::savePicture(const char* filename){
  /* And we're done! */
  image_data.save_jpeg(filename);
}

void Picture::loadInterlacedImage(unsigned char* img){
    cimg_forXY(image_data,x,y){
        image_data(x,y,0,0) = img[y*width*3+x*3];
        image_data(x,y,0,1) = img[y*width*3+x*3+1];
        image_data(x,y,0,2) = img[y*width*3+x*3+2];
    }
}

int Picture::getHeight() {
    return height;
}

int Picture::getWidth() {
    return width;
}

myro_img& Picture::getRawImage(){
    return image_data;
}

void Picture::out_of_bounds_error(int width, int height, int given_width, 
                                                    int given_height){
    std::cerr << std::endl << "ERROR: Accessing Image Out of bounds." 
        << std::endl
       << "  Image Width:  " <<  width << std::endl
       << "  Image Height: " << height << std::endl
       << "  Attempted access to Pixel at (" << given_width << "," 
                        << given_height << ")" << std::endl;
    exit(1);
}

/*
Picture::IndexOutOfBoundsException::IndexOutOfBoundsException(int width, 
                                int height, int given_width, int given_height)
{
    std::stringstream ss;
    ss << "Accessing Image Out of bounds." << std::endl
       << "  Image Width:  " <<  width << std::endl
       << "  Image Height: " << height << std::endl
       << "  Attempted access to Pixel at (" << given_width << "," 
                        << given_height << ")" << std::endl;
    message = ss.str();
    //std::cerr << message << std::endl;
}

Picture::IndexOutOfBoundsException::~IndexOutOfBoundsException() throw(){
}

const char* Picture::IndexOutOfBoundsException::what() throw(){
    //std::cerr << message << std::endl;
    return message.c_str();
}
*/

// Below are the C-style Wrappers for the objects...
int getWidth(PicturePtr p)
{
        return p->getWidth();
}

int getHeight(PicturePtr p)
{
        return p->getHeight();
}

void show(PicturePtr p, std::string windowname)
{
    p->show(windowname);
}

void show(PicturePtr p)
{
    p->show();
}

Pixel getPixel(PicturePtr p, int x, int y)
{
        return p->getPixel(x, y);
}

int getPixelValue_grey(PicturePtr p, int x, int y)
{
        Pixel P=p->getPixel(x,y);
        return P.R;
}

void setPixel(PicturePtr p, int x, int y, Pixel pix)
{
        p->setPixel(x, y, pix);
}

void setPixelColor(PicturePtr p, int x, int y, int R, int G, int B)
{
        Pixel P=p->getPixel(x,y);
        P.R=R;
        P.G=G;
        P.B=B;
        p->setPixel(x, y, P);
}

PicturePtr loadPicture(const char* filename){
    PicturePtr ret(new Picture());
    if ( ret->loadPicture(filename) )
        return ret;
    // TODO: return NULL;
    return ret;
}

void loadPicture(PicturePtr p, const char* filename){
    p->loadPicture(filename);
}
void savePicture(PicturePtr p, const char* filename){
    p->savePicture(filename);
}

PicturePtr clone(PicturePtr p){
    return p->clone();
}
// END C-style Wrappers for the objects...


// Pixel Functions
inline void setRed(Pixel& p, int value){
    if(value>=0 && value <= 255){
        std::cerr << "Error: value should be between 0 and 255" << std::endl;
        return;
    }
    p.R = value;
}
inline void setGreen(Pixel& p, int value){
    if(value>=0 && value <= 255){
        std::cerr << "Error: value should be between 0 and 255" << std::endl;
        return;
    }
    p.G = value;
}
inline void setBlue(Pixel& p, int value){
    if(value>=0 && value <= 255){
        std::cerr << "Error: value should be between 0 and 255" << std::endl;
        return;
    }
    p.B = value;
}

inline int getRed(Pixel& p){
    return p.R;
}

inline int getGreen(Pixel& p){
    return p.G;
}

inline int getBlue(Pixel& p){
    return p.B;
}

PicturePtr makePicture(const char* filename){
    return loadPicture(filename);
}

PicturePtr makePicture(int columns, int rows){
    PicturePtr ptr(new Picture(columns,rows));
    return ptr;
}

PicturePtr makePicture(int columns, int rows, unsigned char* array, bool color){
    PicturePtr ptr;
    if ( color )
        ptr = PicturePtr(new Picture(array, 3, columns, rows));
    else
        ptr = PicturePtr(new Picture(array, 1, columns, rows));
    return ptr;
}
