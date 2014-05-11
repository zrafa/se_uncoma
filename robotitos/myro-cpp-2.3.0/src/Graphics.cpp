#include <Graphics.h>
#include <MyroInternals.h>
#include <iostream>
#include <assert.h>
#include <cmath>
#include <cstdlib>

// ====================
// Internal Messages
// ====================

// Declaration of "draw messages"
enum graphics_object_type{
    GRAPHICS_OBJECT_POINT,
    GRAPHICS_OBJECT_OVAL,
    GRAPHICS_OBJECT_CIRCLE,
    GRAPHICS_OBJECT_RECTANGLE,
    GRAPHICS_OBJECT_LINE,
    GRAPHICS_OBJECT_POLYGON,
    GRAPHICS_OBJECT_TEXT,
    GRAPHICS_OBJECT_IMAGE
};
struct draw_message_common{
    int refCount;
    graphics_object_type type;
    GOL_reg registration;
    Color fill;
    Color outline;
    int width;
    GraphWin* canvas;
};

struct base_msg{};

struct DrawMessage{
    draw_message_common* common;
    base_msg* data;
    base_msg* extra;
};

struct point_draw_msg : public base_msg{
    int x;
    int y;
};

struct bb_draw_msg : public base_msg{
    Point pt1;
    Point pt2;
};

struct circle_draw_msg : public base_msg{
    Point centerPoint;
    int radius;
};

struct line_draw_msg : public base_msg{
    std::string arrow_type;
};

struct polygon_draw_msg : public base_msg{
    cil::CImg<int> pts;
    std::vector<Point> points;
    std::vector<Line> outline_lines;
};

struct text_draw_msg : public base_msg{
    std::string text;
    std::string font;
    int size;
    bool background;
    std::string style;
    Point anchor;
};

struct image_draw_msg : public base_msg{
    PicturePtr img;
    Point anchor;
};
// ====================
// END Internal Messages
// ====================

static unsigned char red[] = {255,0,0};

static inline void debug_rectangle(myro_img& img, int x, int y){
    img.draw_rectangle(x-2,y-2,x+2,y+2, red);
}

template <typename T>
static void swap(T& one, T& two){
    T temp;
    temp = one;
    one = two;
    two = temp;
}

int FindColor(const char *name, Color *colorPtr);

Color color_rgb(unsigned char r, unsigned char g, unsigned char b){
    Color c;
    c.R = r;
    c.G = g;
    c.B = b;
    return c;
}
Color inline makeColor(unsigned char r, unsigned char g, unsigned char b){
    return color_rgb(r,g,b);
}

Color string_to_color(std::string color){
    Color f;
    FindColor(color.c_str(), &f);
    return f;
}

// ====================
// GraphWin
// ====================
GraphWin::GraphWin(std::string title, int width, int height, bool autoFlush)
: title(title),
  background(width,height,1,3),
  result(width,height,1,3),
  width(width),
  height(height),
  autoFlush(autoFlush)
{
    background.fill(255);
    result.fill(255);
    init();
    update();
}

GraphWin::GraphWin(std::string title, myro_img* img, bool autoFlush)
: title(title),
  background(*img),
  result(*img),
  width(width),
  height(height),
  autoFlush(autoFlush)
{
    init();
    update();
} 

GraphWin::GraphWin(std::string title, myro_img& img, bool autoFlush)
: title(title),
  background(img),
  result(img),
  width(width),
  height(height),
  autoFlush(autoFlush)
{
    init();
    update();
} 

GraphWin::~GraphWin(){
    if (thread){
        thread->close();
        thread = NULL;
        //delete thread;
    }
    //while (!drawlist.empty())
    //    undraw(drawlist.front()+1);
}

void GraphWin::init(){
    // This will create the window
    displayMan.set_picture_window(background, title.c_str());
    thread = displayMan.get_winobj(title.c_str());
}

void GraphWin::setAutoflush(bool autoFlush){
    this->autoFlush = autoFlush;
}

void GraphWin::plot(int x, int y, Color color){
}

void GraphWin::plotPixel(int x, int y, Color color){
}

void GraphWin::setBackground(Color color){
    if ( background.spectrum() == 1 )
        background.assign(width,height,1,3);
    cimg_forXY(background,x,y){
        background(x,y,0,0) = color.R;
        background(x,y,0,1) = color.G;
        background(x,y,0,2) = color.B;
    }
    check_and_update();
}
void GraphWin::setBackground(std::string color){
    Color c = string_to_color(color);
    this->setBackground(c);
    check_and_update();
}

void GraphWin::setBackground(PicturePtr img){
    background = img->getRawImage();
    background.resize(width,height,1,3,6);
    check_and_update();
}

void GraphWin::close(){
    if ( thread ) {
        thread->close();
        thread = NULL;
    }
}

bool GraphWin::isClosed(){
    return this->thread->isClosed(); 
}

void GraphWin::waitWinClosed(){
    if ( this->thread ){
        displayMan.block_on(title.c_str());
        thread = NULL;
    }
}

Point GraphWin::getMouse(){
    return this->thread->getMouseClick();
}

Point GraphWin::checkMouse(){
    return this->thread->getLastClick();
}

Point GraphWin::getCurrentMouse(int& button){
    return this->thread->getMouseCoords(button);
}

GOL_reg GraphWin::draw(GraphicsObject* obj){
    drawlist.push_back(obj->drawData);
    obj->drawData->common->refCount++;
    GOL_reg registration = --drawlist.end();
    this->check_and_update();
    return registration;
}

void GraphWin::undraw(GOL_reg reg){
    DrawMessage* msg = *reg;
    msg->common->refCount--;
    drawlist.erase(reg);
    if ( msg->common->refCount <= 0 ){
        std::cerr << "Cleaning up Object" << std::endl;
        // Then we have to clean it up, because the object has gone away
        if ( msg->extra  ) free( msg->extra );
        if ( msg->data   ) free( msg->data );
        if ( msg->common ) free( msg->common );
        if ( msg         ) free( msg );
    }
    this->check_and_update();
}

void GraphWin::update(){
    // Copy Background to result
    if ( background.spectrum() == 1 ){
        cimg_forXY(background,x,y){
            result(x,y,0,0) = background(x,y,0,0);
            result(x,y,0,1) = background(x,y,0,0);
            result(x,y,0,2) = background(x,y,0,0);
        }
    }else {
        result = background;
    }
    for(GOL_reg it = drawlist.begin(); it != drawlist.end(); it++)
        assert(GraphWin::draw_message((*it), result));

    if ( thread )
        thread->change_image(result);
}

void GraphWin::check_and_update(){
    if ( autoFlush )
        update();
}

void GraphWin::saveImage(std::string filename){
    update();
    result.save_jpeg(filename.c_str());
}

void draw_line(Point p1, Point p2, std::string arrow_type, int width, 
        unsigned char* outlinecolor, myro_img& canvas){
    if ( arrow_type == "first" ){
        canvas.draw_arrow(p2.getX(), p2.getY(), p1.getX(), p1.getY(), outlinecolor);
    }
    else if ( arrow_type == "last" ){
        canvas.draw_arrow(p1.getX(), p1.getY(), p2.getX(), p2.getY(), outlinecolor);
    }
    else if ( arrow_type == "both" ){
        canvas.draw_arrow(p2.getX(), p2.getY(), p1.getX(), p1.getY(), outlinecolor);
        canvas.draw_arrow(p1.getX(), p1.getY(), p2.getX(), p2.getY(), outlinecolor);
    }
    if ( width > 1 ){
        int x0=p1.getX(),x1=p2.getX(),y0=p1.getY(),y1=p2.getY();
        bool steep = abs(y0-y1) > abs(x0-x1);
        if ( steep ){
            swap(x0,y0);
            swap(x1,y1);
        }
        if ( x0 > x1 ){
            swap(x0,x1);
            swap(y0,y1);
        }
        int deltax = x1-x0;
        int deltay = abs(y1-y0);
        float error = 0;
        float deltaerr = (float)(deltay) / (deltax);
        int ystep = y0 < y1 ? 1 : -1;
        int y = y0;
        // This is a sort of weird bresenhams thing where I sweep the end
        // points so i can draw a "thick" line
        for (int x = x0; x <= x1; x++){
            if ( steep )
                canvas.draw_circle(y,x,ceil(width/2.0),outlinecolor);
            else
                canvas.draw_circle(x,y,ceil(width/2.0),outlinecolor);
            error += deltaerr;
            if ( error >= 0.5 ){
                y += ystep;
                error -= 1.0;
            }
        }
    }
    else if (width == 1){
        canvas.draw_line(p1.getX(), p1.getY(), p2.getX(), p2.getY(), outlinecolor);
    }
}

std::vector<Point> update_points(polygon_draw_msg* msg, Color lineColor, int width){
    Point p;
    std::vector<Point> ret;
    msg->outline_lines.clear();
    msg->outline_lines.push_back(Line(msg->points[msg->points.size()-1],msg->points[0]));

    for (int i = 0; i < (int)msg->points.size(); i++){
        if (i+1 < (int)msg->points.size())
            msg->outline_lines.push_back(Line(msg->points[i],msg->points[i+1]));
        ret.push_back(msg->points[i]);
        p = msg->points[i];
        msg->pts(i,0) = p.getX();
        msg->pts(i,1) = p.getY();
    }
    for (int i = 0; i < (int)msg->outline_lines.size(); i++){
        msg->outline_lines[i].setWidth(width);
        msg->outline_lines[i].setOutline(lineColor);
    }
    return ret;
}

bool GraphWin::draw_message(DrawMessage* msg, myro_img& canvas){
    unsigned char color[] = {msg->common->fill.R, msg->common->fill.G, msg->common->fill.B};
    unsigned char outlinecolor[] = {msg->common->outline.R, msg->common->outline.G, msg->common->outline.B};
    int width = msg->common->width;
    switch(msg->common->type){
    case GRAPHICS_OBJECT_POINT:
    {
        point_draw_msg* data = (point_draw_msg*)msg->data;
        int x = data->x, y = data->y;
        canvas(x,y,0,0) = msg->common->outline.R;
        canvas(x,y,0,1) = msg->common->outline.G;
        canvas(x,y,0,2) = msg->common->outline.B;
    }
    break;
    case GRAPHICS_OBJECT_OVAL:
    case GRAPHICS_OBJECT_CIRCLE:
    {
        bb_draw_msg* data = (bb_draw_msg*)msg->data;
        Point center = Point((data->pt1.getX()+data->pt2.getX())/2, 
                             (data->pt1.getY()+data->pt2.getY())/2);
        int r0 = abs(center.getX() - data->pt2.getX());
        int r1 = abs(center.getY() - data->pt2.getY());
        if ( width ){
            canvas.draw_ellipse(center.getX(),center.getY(), r0, r1, 0, outlinecolor);
            canvas.draw_ellipse(center.getX(), center.getY(), r0-width, r1-width, 0, color);
        }
        else{
            canvas.draw_ellipse(center.getX(),center.getY(), r0, r1, 0, color);
        }
    }
    break;
    case GRAPHICS_OBJECT_RECTANGLE:
    {
        bb_draw_msg* data = (bb_draw_msg*)msg->data;
        if ( width ){
            bb_draw_msg* data = (bb_draw_msg*)msg->data;
            int leftx = std::min(data->pt1.getX(),data->pt2.getX())+width;;
            int rightx = std::max(data->pt1.getX(), data->pt2.getX())-width;
            int topy = std::min(data->pt1.getY(), data->pt2.getY())+width;
            int bottomy = std::max(data->pt1.getY(), data->pt2.getY())-width;
            canvas.draw_rectangle(data->pt1.getX(), data->pt1.getY(), 
                                  data->pt2.getX(), data->pt2.getY(), outlinecolor);
            canvas.draw_rectangle(leftx,topy,rightx,bottomy, color);
        }
        else{
            canvas.draw_rectangle(data->pt1.getX(), data->pt1.getY(), 
                                  data->pt2.getX(), data->pt2.getY(), color);
        }
    }
    break;
    case GRAPHICS_OBJECT_LINE:
    {
        std::string arrow_type = ((line_draw_msg*)(msg->extra))->arrow_type;
        bb_draw_msg* data = (bb_draw_msg*)msg->data;
        Point p1 = data->pt1;
        Point p2 = data->pt2;
        draw_line(p1, p2, arrow_type, width, outlinecolor, canvas);
    }
    break;
    case GRAPHICS_OBJECT_POLYGON:
    {
        polygon_draw_msg* data = (polygon_draw_msg*)msg->data; 
        std::vector<Point> debug = update_points(data,msg->common->outline,width);
        canvas.draw_polygon(data->pts, color);
        if ( width == 1 ){
            canvas.draw_polygon(data->pts, outlinecolor, 1, ~0U);
        } else if ( width > 1 ){
            for (int i = 0; i < (int)data->outline_lines.size(); i++)
                draw_line(data->outline_lines[i].getP1(), data->outline_lines[i].getP2(), 
                          "none", width, outlinecolor, canvas);
        }
    }
    break;
    case GRAPHICS_OBJECT_TEXT:
    {
        text_draw_msg* data = (text_draw_msg*)msg->data;
        if ( data->background ){
            canvas.draw_text(data->anchor.getX(), data->anchor.getY(), data->text.c_str(), 
                             outlinecolor, color, 1, data->size);
        }
        else{
            canvas.draw_text(data->anchor.getX(), data->anchor.getY(), data->text.c_str(), 
                             outlinecolor, 0, 1, data->size);
        }
    }
    break;
    case GRAPHICS_OBJECT_IMAGE:
    {
        image_draw_msg* data = (image_draw_msg*)msg->data;
        canvas.draw_image(data->anchor.getX(), data->anchor.getY(), data->img->getRawImage());
    }
    break;
    default:
    return false;
    break;
    }
    return true;
}

// ====================
// GraphicsObject
// ====================
GraphicsObject::GraphicsObject()
{
  drawData = new DrawMessage();
  drawData->common = new draw_message_common();
  //drawData = (DrawMessage*)malloc(sizeof(DrawMessage));
  //drawData->common = (draw_message_common*)malloc(sizeof(draw_message_common));
  drawData->common->refCount = 1;
  drawData->common->canvas  = NULL;
  drawData->common->fill    = color_rgb(255,255,255);
  drawData->common->outline = color_rgb(0,0,0);
  drawData->common->width   = 1;
  drawData->data = drawData->extra = NULL;
}

GraphicsObject::GraphicsObject(Color fill, Color outline, int width)
{
  drawData = new DrawMessage();
  drawData->common = new draw_message_common();
  drawData->common->refCount = 1;
  drawData->common->canvas  = NULL;
  drawData->common->fill    = fill;
  drawData->common->outline = outline;
  drawData->common->width   = width;
  drawData->data = drawData->extra = NULL;
}

GraphicsObject::~GraphicsObject(){
}

void GraphicsObject::setFill(Color color){
    drawData->common->fill=color;
    if ( drawData->common->canvas )
        drawData->common->canvas->check_and_update();
}

void GraphicsObject::setFill(std::string color){
    Color c = string_to_color(color);
    this->setFill(c);
}

Color GraphicsObject::getFill(){
    return drawData->common->fill;
}

void GraphicsObject::setOutline(Color color){
    drawData->common->outline=color;
    if ( drawData->common->canvas )
        drawData->common->canvas->check_and_update();
}

void GraphicsObject::setOutline(std::string color){
    Color c = string_to_color(color);
    this->setOutline(c);
}

Color GraphicsObject::getOutline(){
    return drawData->common->outline;
}

void GraphicsObject::setWidth(int width){
    drawData->common->width = width;
    if ( drawData->common->canvas )
        drawData->common->canvas->check_and_update();
}

int GraphicsObject::getWidth(){
    return drawData->common->width;
}

void GraphicsObject::draw(GraphWin* canvas){
    if ( !drawData->common->canvas ){
        drawData->common->canvas = canvas;
        drawData->common->registration = drawData->common->canvas->draw(this);
        //assert( *(drawData->common->registration) == this );
    }
    else {
        // Throw an exception or something
    }
}

void GraphicsObject::draw(GraphWin& canvas){
    this->draw(&canvas);
}

void GraphicsObject::undraw(){
    if ( drawData->common->canvas ){
        drawData->common->canvas->undraw(drawData->common->registration);
        drawData->common->canvas = NULL;
    }
    else{
        // Throw an exception
    }
}

// ====================
// Point
// ====================
Point::Point()
{
    drawData->common->type = GRAPHICS_OBJECT_POINT;
    //data = (point_draw_msg*)malloc(sizeof(point_draw_msg));
    data = new point_draw_msg();
    drawData->data = data;
    data->x = 0;
    data->y = 0;
}
Point::Point(int x, int y)
{
    drawData->common->type = GRAPHICS_OBJECT_POINT;
    data = new point_draw_msg();
    drawData->data = data;
    data->x = x;
    data->y = y;
}
/*
Point::Point(const Point& p){
    this->x = p.x;
    this->y = p.y;
}
*/
Point* Point::clone(){ return new Point(data->x,data->y); }
int Point::getX(){ return data->x; }
int Point::getY(){ return data->y; }
void Point::move(int dx, int dy){
    data->x += dx;
    data->y += dy;
    if ( drawData->common->canvas )
        drawData->common->canvas->check_and_update();
}
Point& Point::operator+=(const Point& rhs){
    data->x += rhs.data->x;
    data->y += rhs.data->y;
    return *this;
}
Point Point::operator+(const Point& other){
    Point result;
    result.data->x = data->x;
    result.data->y = data->y;
    result += other;
    return result;
}
Point& Point::operator-=(const Point& rhs){
    data->x -= rhs.data->x;
    data->y -= rhs.data->y;
    return *this;
}
Point Point::operator-(const Point& other){
    Point result;
    result.data->x = data->x;
    result.data->y = data->y;
    result -= other;
    return result;
}
/*
void Point::draw_command(myro_img& canvas){
}
*/

// ====================
// _BBox
// ====================
_BBox::_BBox(Point p1, Point p2){
    //data = (bb_draw_msg*)malloc(sizeof(bb_draw_msg));
    data = new bb_draw_msg();
    drawData->data = data;
    data->pt1 = p1;
    data->pt2 = p2;
}

void _BBox::move(int dx, int dy){
    Point d(dx,dy);
    data->pt1 += d;
    data->pt2 += d;
    if ( drawData->common->canvas ) 
        drawData->common->canvas->check_and_update();
}

Point _BBox::getP1(){ return data->pt1; };
Point _BBox::getP2(){ return data->pt2; };
Point _BBox::getCenter(){ 
    return Point((data->pt1.getX()+data->pt2.getX())/2, 
                 (data->pt1.getY()+data->pt2.getY())/2);
}

// ====================
// Oval
// ====================
Oval::Oval(Point p1, Point p2)
: _BBox(p1,p2)
{
    drawData->common->type = GRAPHICS_OBJECT_OVAL;
}

Oval* Oval::clone(){
    return new Oval(data->pt1, data->pt2);
}

// ====================
// Circle
// ====================
Circle::Circle(Point center, int radius)
: Oval(Point(center.getX()-radius,center.getY()-radius),Point(center.getX()+radius,center.getY()+radius))
{
    drawData->common->type = GRAPHICS_OBJECT_CIRCLE;
    extra = new circle_draw_msg();
    drawData->extra = extra;
    extra->centerPoint = center;
    extra->radius = radius;
}

int Circle::getRadius(){
    return extra->radius;
}
/*
void Circle::draw_command(myro_img& canvas){

}
*/

// ====================
// Rectangle
// ====================
Rectangle::Rectangle(Point p1, Point p2)
: _BBox(p1,p2)
{
    drawData->common->type = GRAPHICS_OBJECT_RECTANGLE;
}

// ====================
// Line
// ====================
Line::Line(Point p1, Point p2, std::string arrow_type)
: _BBox(p1,p2)
{
    drawData->common->type = GRAPHICS_OBJECT_LINE;
    extra = new line_draw_msg();
    drawData->extra = extra;
    extra->arrow_type = arrow_type;
}

void Line::setArrow(std::string type){
    if ( type == "first" ||
         type == "last"  ||
         type == "both"  ||
         type == "none" )
        extra->arrow_type = type;
    else{
        std::cerr << "Line::setArrow(): Bad Type: " << type << std::endl;
        // TODO: Throw Exception
    }
}

// ====================
// Polygon
// ====================
Polygon::Polygon(std::vector<Point> points)
{
    drawData->common->type = GRAPHICS_OBJECT_POLYGON;
    data = new polygon_draw_msg();
    drawData->data = data;
    data->pts.assign(points.size(),2);
    data->points = points;
}

std::vector<Point> Polygon::getPoints(){
    return data->points;
}

void Polygon::move(int dx, int dy){
    Point d(dx,dy);
    for (int i = 0; i < (int)data->points.size(); i++){
        data->points[i] += d;
    }
    if ( drawData->common->canvas ) 
        drawData->common->canvas->check_and_update();
}

// ====================
// Text
// ====================
Text::Text(Point anchor, std::string text)
: GraphicsObject(color_rgb(0,0,0), color_rgb(0,0,0), 0)
{
    drawData->common->type = GRAPHICS_OBJECT_TEXT;
    data = new text_draw_msg();
    drawData->data = data;
    data->text = text;
    data->font = "helvetica";
    data->size = 13;
    data->background = false;
    data->style = "normal";
    data->anchor = anchor;
}

std::string Text::getText(){ return data->text; }
void Text::setText(std::string text){ data->text = text; }
Point Text::getAnchor(){ return data->anchor; }
void Text::setAnchor(Point anchor){ data->anchor=anchor; }
void Text::setFace(std::string font){
    // TODO
    //Joke's On you because I don't support any font other than the default!
}
void Text::setSize(int size){
    data->size = size;
}

void Text::setStyle(std::string style){
    // TODO: Yeah I don't support this either
}

void Text::setTextColor(Color color){ this->setOutline(color); }
void Text::setTextColor(std::string color){ this->setOutline(color); }

void Text::drawBackground(bool background){
    data->background = background;
}

void Text::move(int dx, int dy){
    data->anchor += Point(dx,dy);
    if ( drawData->common->canvas )
        drawData->common->canvas->check_and_update();
}

// ====================
// Image
// ====================
Image::Image(Point anchor, std::string filename)
: GraphicsObject(color_rgb(0,0,0), color_rgb(0,0,0), 0)
{
    PicturePtr thePicture = makePicture(filename.c_str());
    drawData->common->type = GRAPHICS_OBJECT_IMAGE;
    data = new image_draw_msg();
    drawData->data = data;
    data->anchor = anchor;
    data->img = thePicture;
}

Image::Image(Point anchor, PicturePtr img){
    drawData->common->type = GRAPHICS_OBJECT_IMAGE;
    data = new image_draw_msg();
    drawData->data = data;
    data->anchor = anchor;
    data->img = img;
}

Point Image::getAnchor(){ return data->anchor; }
void Image::setAnchor(Point anchor){ data->anchor=anchor; }

Pixel Image::getPixel(int x, int y){
    return data->img->getPixel(x,y);
}

void Image::setPixel(int x, int y, Color c){
    data->img->setPixel(x,y,c);
}

void Image::save(std::string filename){
    data->img->savePicture(filename.c_str());
}

void Image::move(int dx, int dy){
    data->anchor += Point(dx,dy);
}
