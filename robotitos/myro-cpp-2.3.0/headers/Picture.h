#ifndef __PICTURE_H__
#define __PICTURE_H__

#include<exception>
#include<string>
#include<MyroCImg.h>
#include<MyroSmartPointer.h>
/** @defgroup picture Picture Operations
 * The collection of all Picture Related commands and operations
 * @{
 */
class Picture;
typedef MyroSmartPointer<Picture> PicturePtr;

/**
 * A pixel structure that respesents a single pixel of an Image. 
 */
struct Pixel {
    unsigned char R;
    unsigned char G;
    unsigned char B;
};

/** 
 * Set the Red channel of the pixel. 
 *
 * @param value Should be between 0->255
 */
void setRed(Pixel& p, int value);
/** 
 * Set the Green channel of the pixel. 
 *
 * @param value Should be between 0->255
 */
void setGreen(Pixel& p, int value);
/** 
 * Set the Blue channel of the pixel. 
 *
 * @param value Should be between 0->255
 */
void setBlue(Pixel& p, int value);

/**
 * Get the Red value of the given pixel
 */
int getRed(Pixel& p);
/**
 * Get the Green value of the given pixel
 */
int getGreen(Pixel& p);
/**
 * Get the Blue value of the given pixel
 */
int getBlue(Pixel& p);


/**
 * @class Picture
 *
 * The abstract Picture object that represents a picture taken from a robot. 
 *
 * @author Richard Edwards, John Hoare
 */
class Picture {
    public:
    /*
     * Exception that is thrown if the Picture is indexed out of Bounds
    class IndexOutOfBoundsException : public std::exception {
        public:
            IndexOutOfBoundsException(int width, int height, 
                                      int given_width, int given_height);
            ~IndexOutOfBoundsException() throw();
            virtual const char* what() throw();
        private: 
            std::string message;
    };
     */

    public:

        Picture();
        Picture(int width, int height);
        Picture(unsigned char * data, int channels, int width, int height);
        Picture(Picture& pic);
        ~Picture();

        /**
         * @return A pixel struct representing the pixel at x,y
         */
        virtual Pixel getPixel(int x, int y);
        /**
         * Set the value of a pixel at x,y to be the given pixel pix.
         */
        virtual void  setPixel(int x, int y, Pixel pix);
        /**
         * Display the picture on the screen.
         * 
         * This function will immediately return, and will not wait for the 
         * user to close the window.
         *
         * @param windowname The name of the window to show the image in. If
         *      the named window does not already exist, then it will create 
         *      a new window, if it already exists, it will draw the image
         *      into that window. 
         */
        virtual void show(std::string windowname);
        /**
         * Display the picture on the screen.
         *
         * This function will block (wait) until the user has closed the 
         * window, before the program continues running.
         *
         */
        virtual void show();
        /**
         * Get a pointer to the underlying memory representing the 
         * image.
         */
        myro_img& getRawImage();

        /** 
         * Get a "clone" of this picture. A clone is also a copy. 
         * If you'd like another copy of this picture use this function.
         *
         *
         * Example: 
         * Picture* pic = robot.takePicture("color");
         * Picture* pic2 = pic->clone();
         *
         * From this you'll have two "copies" of the same picture, so you're 
         * free to change around "pic" without worry of changing "pic2" 
         *
         * @return A clone of this picture
         */
        virtual PicturePtr clone();

        int getHeight();
        int getWidth();

        /**
         * Load an image from a filename, for now, only jpeg files are 
         * supported.
         *
         * @param filename The file to read from.
         * @return True if load sucessful, false if fails (for wrong
         * colorspace, etc.)
         */
        virtual bool loadPicture(const char* filename);

        /**
         * Save an image to a file, only jpeg files are supported. 
         * A .jpg will be appended to the given filename.
         *
         * @param filename The name of the file you save (without the .jpg 
         *  file extention)
         */
        virtual void savePicture(const char* filename);

        /**
         * Static method to print out an error message when a user has 
         * gone out of bounds. 
         */
        static void out_of_bounds_error(int width, int height, 
                            int given_width, int given_height);

    private:
        void loadInterlacedImage(unsigned char* img);
    protected:

        //unsigned char * image_data;
        //cimg_library::CImg<unsigned char> image_data;
        myro_img image_data;
        int width;
        int height;
        int channels;
};
// functions added for lab 6 by Nick
int getWidth(PicturePtr p);
int getHeight(PicturePtr p);
void show(PicturePtr p, std::string windowname);
void show(PicturePtr p);
Pixel getPixel(PicturePtr p, int x, int y);
int getPixelValue_grey(PicturePtr p, int x, int y);
void setPixel(PicturePtr p, int x, int y, Pixel pix);
void setPixelColor(PicturePtr p, int x, int y, int R, int G, int B);
PicturePtr clone(PicturePtr p);

/// Create a picture object from a saved image
PicturePtr loadPicture(const char* filename);
/// Load an image into the given Picture object
void loadPicture(PicturePtr p, const char* filename);
/// Save the Image to a file
void savePicture(PicturePtr p, const char* filename);

/// Create a picture object from a saved image
PicturePtr makePicture(const char* filename);

/// Create a blank picture 
PicturePtr makePicture(int columns, int rows);

/**
 * Create a new picture from an array ( a column-major sequence of 0-255 values that
 * represent Red, Green, Blue (in that order))
 * 
 * The length of the array MUST be exactly columns*rows*3 if color is true, or un-
 * specified, otherwise, if color is false, it must be columns*rows.
 */
PicturePtr makePicture(int columns, int rows, unsigned char* array, bool color=true);


///@}

#endif
