#include "MyroInternals.h"
#include <iostream>

DisplayMan displayMan;

//------------------------------
// Threaded
//------------------------------

Threaded::Threaded() : stopRequested(false), _running(false), runThread(NULL) {};

Threaded::~Threaded(){
    if ( this->running() )
        this->stop();
    if ( runThread )
        delete runThread;
}

void Threaded::start() {
    assert(!runThread);
    stopRequested = false;
    boost::mutex::scoped_lock l(startup_mutex);
    runThread = new boost::thread(boost::bind(&Threaded::startRun, this));
    startup_condition.wait(l);
}
void Threaded::stop() {
    assert(runThread);
    stopRequested = true;
    this->join();
}
void Threaded::join() { 
    if ( runThread ){
        runThread->join(); 
        delete runThread;
        runThread = NULL;
    }
}

bool Threaded::running(){
    boost::mutex::scoped_lock l(startup_mutex);
    return _running;
}

void Threaded::startRun(){
    {
        // Hey I'm the new thread, and I've started running!
        boost::mutex::scoped_lock l(startup_mutex);
        _running = true;
        startup_condition.notify_one();
    }
    this->run();
    {
        boost::mutex::scoped_lock l(startup_mutex);
        _running = false;
    }
}

CImg_display::CImg_display(myro_img& img, const char* window_name) 
: img(img),
  window_name(window_name), 
  img_changed(false),
  displaywin(this->img,window_name),
  mx(-1),my(-1),clickedx(-1),clickedy(-1),
  requestClose(false),
  close_notify(NULL)
{}

CImg_display::CImg_display(myro_img* img, const char* window_name) 
: img(*img),
  window_name(window_name), 
  img_changed(false),
  displaywin(this->img,window_name),
  mx(-1),my(-1),clickedx(-1),clickedy(-1),
  requestClose(false),
  close_notify(NULL)
{}

bool CImg_display::isClosed(){
    return displaywin.is_closed();
}

void CImg_display::run(){
    //std::cerr << "CImg_display::run()" << std::endl;
    //cil::CImgDisplay displaywin(img,window_name.c_str());
    //mx = my = -1;

    //while ( !stopRequested && !displaywin.is_closed()){
    //    displaywin.wait(50);
        {
            boost::mutex::scoped_lock l(img_mutex);
            if (!displaywin.is_closed()) {
                if ( requestClose ){
                    displaywin.close();
                    return;
                }
                if ( img_changed ){
                    img_changed = false;
                    displaywin.display(img);
                }
                mx = displaywin.mouse_x();
                my = displaywin.mouse_y();
                button = displaywin.button();
                // If its valid, send a wakeup to the mouse condition variable, if we're 
                if ( mx >= 0 && my >= 0 && button ){
                    clickedx = mx;
                    clickedy = my;
                    mouse.notify_all();
                }
            }
        }
    //}
}

void CImg_display::change_image(myro_img& img){
    //std::cerr << "changing image" << std::endl;
    boost::mutex::scoped_lock l(img_mutex);
    this->img.assign(img);
    this->img_changed = true;
}

void CImg_display::change_image(myro_img* img){
    this->change_image(*img);
}

std::string CImg_display::getName(){
    return window_name;
}

void CImg_display::close(){
    boost::mutex::scoped_lock l(img_mutex);
    requestClose = true;
}

void CImg_display::NotifyWhenClosed(window_request* req){
    this->close_notify = req;
}

Point CImg_display::getMouseClick(){
    boost::mutex::scoped_lock l(img_mutex);
    mouse.wait(img_mutex);
    return Point(clickedx,clickedy);
}

Point CImg_display::getLastClick(){
    boost::mutex::scoped_lock l(img_mutex);
    return Point(clickedx,clickedy);
}

Point CImg_display::getMouseCoords(int& button){
    boost::mutex::scoped_lock l(img_mutex);
    button = this->button;
    return Point(mx,my);
}

DisplayMan::DisplayMan(){
    this->start();
}

DisplayMan::~DisplayMan(){
    this->stop();
}

void DisplayMan::run(){
    myro_cimg_display_map::iterator it;
    while(!stopRequested){
        // Wait so we don't just sit spinnning on the cpu. 
        // 20ms gives us an acceptable polling/update speed
        cil::cimg::wait(20);
        {
            boost::mutex::scoped_lock l(mutex);
            // Service all the new window requests
            while ( !requests.empty() ){
                //std::cerr << "DisplayMan::run(): making a window?" << std::endl;
                window_request* req = requests.front();
                requests.pop();
                //std::cerr << "DisplayMan::run(): making a window?" << std::endl;
                //req->disp = myset_picture_window(*(req->img), req->window_name.c_str());
                this->myset_picture_window(*(req->img), req->window_name.c_str());
                req->c.notify_one();
                //std::cerr << "DisplayMan::run(): making a window?: done!" << std::endl;
            }

            for (it = display_map.begin(); it != display_map.end();){
                CImg_display *t = it->second;
                if ( t->isClosed() ){
                    // Notify that window was closed if there is someone who 
                    // wants to know
                    if ( t->close_notify ){
                        t->close_notify->c.notify_one();
                    }
                    //t->join();
                    display_map.erase(it++);
                }
                else{
                    it->second->run();
                    it++;
                }
            }
        }
    }
}

void DisplayMan::set_picture_window(myro_img& img, const char* window_name){
    window_request req;
    req.window_name = window_name;
    req.img = &img;
    boost::mutex::scoped_lock l(mutex);
    requests.push(&req);
    req.c.wait(l);
}

void DisplayMan::block_on(const char* window_name){
    window_request blk;
    boost::mutex::scoped_lock l(mutex);
    myro_cimg_display_map::iterator it = display_map.find(window_name);
    if ( it == display_map.end() ){
        // TODO: Do something if asked to block on a non-existant window
        std::cerr << "ERROR: block_on did not get a window to block with" << std::endl;
    }
    else{
        CImg_display* disp = it->second;
        disp->NotifyWhenClosed(&blk);
        blk.c.wait(mutex);
        // When we get here, the window has been closed!
    }
}

CImg_display* DisplayMan::get_winobj(const char* window_name){
    boost::mutex::scoped_lock l(mutex);
    myro_cimg_display_map::iterator it = display_map.find(window_name);
    if ( it == display_map.end() ){
        return NULL;
    }
    else{
        CImg_display* disp = it->second;
        return disp;
    }
}


// Must already have mutex to call me!
CImg_display* DisplayMan::myset_picture_window(myro_img& img, const char* window_name){
    CImg_display* disp;
    myro_cimg_display_map::iterator it = display_map.find(window_name);
    if ( it == display_map.end() ){
        disp = new CImg_display(img, window_name);
        //disp->start();
        display_map[window_name] = disp;
    }
    else{
        disp = it->second;
        //display_map.erase(it);
        disp->change_image(img);
    }
    return disp;
}

