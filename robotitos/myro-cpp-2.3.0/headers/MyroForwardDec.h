/** 
 * @file 
 *
 * Forward declarations so client code doesn't need to have boost installed, 
 * for say if we build with boost libraries statically linked.
 */
#ifndef __MYROFORWARD_DEC_H__
#define __MYROFORWARD_DEC_H__

// Forward Declarations
namespace boost{  
    class mutex; 
};
class VideoStream;
class serial;

class DisplayThread;


#endif
