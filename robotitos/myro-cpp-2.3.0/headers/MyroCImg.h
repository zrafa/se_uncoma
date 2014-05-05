#ifndef __MYRO_CIMG_H
#define __MYRO_CIMG_H

#if defined(__CYGWIN__) ||  defined(WIN32) || defined(_WIN32) || defined(__WINDOWS__)
#define NOMINMAX
#include<windows.h>
#include<rpcndr.h>
#define _snprintf snprintf
#define _vsnprintf vsnprintf
#define cimg_OS 2
#endif

#include <cstdio>
#include <cstdlib>
/*
extern "C"{
#include <jpeglib.h>
#include <jerror.h>
}


// Use the jpeg_buffer to decompress a jpeg image from memory (instead of from file)
#define cimg_plugin "CImg/jpeg_buffer.h"
*/

// So the CImg Library wants you to #define certian things to "enable" or "diable" 
// functionality.
#define cimg_use_jpeg
#include <CImg/CImg.h>


namespace cil = cimg_library;
typedef cil::CImg<unsigned char> myro_img;
#endif
