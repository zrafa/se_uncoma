#pragma once
#include <Myro.h>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>
//#include <boost/shared_ptr.hpp>
#include <vector>
#include <queue>
#include <MyroCImg.h>
#include <Graphics.h>

typedef std::list<CImg_display*> DisplayList;
typedef std::list<CImg_display*>::iterator DL_reg;

// Inherit from this to get threading.  The usage is:
//     threaded.start()
//     threaded.join()
// Implement the run() function as the thread.
class Threaded {
    public:
        Threaded();
        ~Threaded();
        virtual void start();
        virtual void stop();
        void join();
        bool running();
    protected:
        volatile bool stopRequested;
    private:
        void startRun();
        virtual void run() = 0;
        volatile bool _running;
        boost::thread * runThread;
        //boost::shared_ptr<boost::thread> runThread; 
        boost::mutex startup_mutex;
        boost::condition startup_condition;
};

typedef std::map<std::string, CImg_display*> myro_cimg_display_map;

struct window_request{
    boost::condition c;
    std::string window_name;
    myro_img* img;
};

class DisplayMan : public Threaded{
    public:
        DisplayMan();
        ~DisplayMan();
        virtual void run();
        // To be called by users
        void set_picture_window(myro_img& img, const char* window_name);
        void block_on(const char* window_name);
    private:
        CImg_display* get_winobj(const char* window_name);
        // To be called by the run() thread
        CImg_display* myset_picture_window(myro_img& img, const char* window_name);
        //void mynonblock_display_window(const char* window_name);
    private:
        myro_cimg_display_map display_map;
        boost::mutex mutex;
        std::queue<window_request*> requests;

        friend class GraphWin;
};

class CImg_display{
    public:
        bool isClosed();
        void run();
        void change_image(myro_img* img);
        void change_image(myro_img& img);
        Point getMouseClick();
        Point getLastClick();
        Point getMouseCoords(int& buttons);
        std::string getName();
        void close();
        void NotifyWhenClosed(window_request * req);
    private:
        CImg_display(myro_img& img, const char* window_name);
        CImg_display(myro_img* img, const char* window_name);
    private:
        std::list<GraphicsObject*> draw_commands;
        myro_img img;
        std::string window_name;
        boost::mutex img_mutex;
        boost::condition mouse;
        bool img_changed;
        cil::CImgDisplay displaywin;
        int mx;
        int my;
        int clickedx;
        int clickedy;
        int button;
        bool requestClose;
        window_request* close_notify;

        friend class DisplayMan;
};


// This is a factory function that will return a pointer to the Display thread, so the caller can 
// then block on it if they so choose.
//CImg_display * set_picture_window(myro_img& img, const char* window_name);

// This is a funciton that has its own thread behind it to join() any display window threads that 
// exit, to avoid a memory leak. 
//void nonblock_display_window(CImg_display* thread);


extern DisplayMan displayMan;
