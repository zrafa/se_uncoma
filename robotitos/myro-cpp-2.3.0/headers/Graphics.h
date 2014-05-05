#pragma once
#include <Picture.h>
#include <list>
#include <vector>

struct DrawMessage;
struct draw_message_common;
struct point_draw_msg;
struct bb_draw_msg;
struct circle_draw_msg;
struct line_draw_msg;
struct polygon_draw_msg;
struct text_draw_msg;
struct image_draw_msg;
struct base_msg;
typedef std::list<DrawMessage*> GraphicsObjectList;
typedef std::list<DrawMessage*>::iterator GOL_reg;

/** @defgroup graphics Graphics Tools
 * The collection of all Drawing Commands
 * @{
 */


/// Pixel from Picture.h and Color are the same.
typedef Pixel Color;

// Forward declartions
class CImg_display;
class GraphicsObject;
class Point;
class GraphWin;

/**
 * Create a color "object" with the given r,g,b values
 *
 * @param r Red value
 * @param g Green value
 * @param b Blue value
 */
Color color_rgb(unsigned char r, unsigned char g, unsigned char b);
/**
 * Create a color "object" with the given r,g,b values
 *
 * @param r Red value
 * @param g Green value
 * @param b Blue value
 */
Color makeColor(unsigned char r, unsigned char g, unsigned char b);
/**
 * Get a Color object from a given string name
 *
 * @param color The name of the color you want. Colors are indicated by 
 * strings. Most normal colors such as 'red', 'purple', 'green', 'cyan', 
 * etc. should be available. Many colors come in various shades, such as 
 * 'red1', 'red2','red3', 'red4', which are increasingly darker shades of red.
 */
Color string_to_color(std::string color);


/**
 * A GraphWin object represents a window on the screen where graphical images 
 * may be drawn. A program may define any number of GraphWins. Each GraphWin 
 * object represents a different open window.
 */
class GraphWin{
    public:
        /**
         * Create a GraphWin with a white background.
         * 
         * @param title The Window Title
         * @param width The Window Width
         * @param height The Window Height
         * @param autoFlush Automatically redraw on a change (default true)
         */
        GraphWin(std::string title="Graphics Window", int width=200, int height=200, bool autoFlush=true);
        /**
         * Create a GraphWin with a given image as the background.
         * 
         * @param title The Window Title
         * @param img The image you wish to set as the background.
         * @param autoFlush Automatically redraw on a change (default true)
         */
        GraphWin(std::string title, myro_img& img, bool autoFlush=true);
        /**
         * Create a GraphWin with a given image as the background.
         * 
         * @param title The Window Title
         * @param img The image you wish to set as the background.
         * @param autoFlush Automatically redraw on a change (default true)
         */
        GraphWin(std::string title, myro_img* img, bool autoFlush=true);
        ~GraphWin();
        /**
         * Set whether auto flush is on (image automatically updated 
         * at any change of drawing.) 
         * 
         * Turning this off will give better performance, but you must
         * make sure that you call update() yourself to update the 
         * image. By default this is on, so unless you turn off autoFlush,
         * you never need to call update() yourself.
         */
        void setAutoflush(bool autoFlush);
        /**
         * Set the background pixel x,y to the given color
         */
        void plot(int x, int y, Color color);
        /**
         *  Draws the pixel at the ``raw'' position  ignoring any coordinate 
         *  transformations set up by setCoords.
         */
        void plotPixel(int x, int y, Color color);
        ///Set the entire background to be the given color.
        void setBackground(Color color);
        ///Set the entire background to be the given color.
        void setBackground(std::string color);
        ///Set the entire background to be the given image (will stretch
        /// the image to fit the window.)
        void setBackground(PicturePtr img);
        /// Close the window programatically.
        void close();
        /// Check if the window has been closed (programatically or by the user.)
        bool isClosed();
        /// Function that will not return until the user has closed the GraphWin 
        /// window
        void waitWinClosed();
        /**
         * Blocks until the user clicks somewhere on the image, and returns that
         * point.
         */
        Point getMouse();
        /**
         * Does the same as getMouse() but does not wait until the user has 
         * clicked, just gets the current mouse position. If the mouse is not 
         * on the window, then it will return a point of -1,-1. 
         */
        Point checkMouse();
        /**
         * Get the current mouse status, the return value is the x,y position
         * of the pointer, and the int (passed by reference) is the status of 
         * the mouse button
         */
        Point getCurrentMouse(int& button);
        /**
         * Redraw the image.
         */
        void update();
        // Check to see if we are supposed to auto-redraw, and if so do it
        // TODO: This should be private, but I'm getting errors here...
        void check_and_update();
        /** 
         * Save the current state of the graphwin into an image. 
         */
        void saveImage(std::string filename);
    private: 
        static bool draw_message(DrawMessage* msg, myro_img& canvas);
        GOL_reg draw(GraphicsObject* obj);
        void undraw(GOL_reg reg);
        void init();
        std::string title;
        myro_img background;
        myro_img result;
        int width;
        int height;
        bool autoFlush;
        GraphicsObjectList drawlist;
        CImg_display * thread;
        friend class GraphicsObject;
};

/**
 * A Generic GraphicsObject class that is the Parent class for every other 
 * class which can be drawn onto a GraphWin.
 */
class GraphicsObject{

    public:
        GraphicsObject();
        GraphicsObject(Color fill, Color outline, int width);
        ~GraphicsObject();
        /// Set the Fill of the shape
        void setFill(Color color);
        /// Set the Fill of the shape
        void setFill(std::string color);
        /// Get the Fill of the shape
        Color getFill();
        /// Set the outline of the shape
        void setOutline(Color color);
        /// Set the outline of the shape
        void setOutline(std::string color);
        /// Get the Outline of the shape
        Color getOutline();
        /// Set the width of the outline around the shape
        void setWidth(int width);
        /// Get the width of the outline around the shape
        int getWidth();
        /// Draw the object to a given GraphWin
        void draw(GraphWin* canvas);
        /// Draw the object to a given GraphWin
        void draw(GraphWin& canvas);
        /**
         * Undraws the object from a graphics window. This produces an error 
         * if the object is not currently drawn.
         */
        void undraw();
        /**
         * Moves the shape dx units in the x direction and dy units in the y 
         * direction.
         */
        virtual void move(int dx, int dy)=0;
    protected:
        /// This function gets implemented by child classes to implement
        /// how to draw itself, the GraphWin calls this on all of its 
        /// registered GraphicObjects.
        //virtual void draw_command(myro_img& canvas)=0;
        DrawMessage* drawData;
//        boost::shared_ptr<GraphicsObject::DrawPair> drawdata;
    friend class GraphWin;
};

/**
 * Represents a single point on an image. This class is often used to specify 
 * the locations of more advanced Shapes, but can also be used, and drawn 
 * on its own.
 */
class Point : public GraphicsObject{
    public:
        Point();
        /// Constructs the point with the given coordinates
        Point(int x, int y);
        Point* clone();
        /// Get the X value of the point.
        int getX();
        /// Get the Y value of the point.
        int getY();
        Point& operator+=(const Point &rhs);
        Point operator+(const Point &rhs);
        Point& operator-=(const Point &rhs);
        Point operator-(const Point &rhs);
        virtual void move(int dx, int dy);
    protected:
        //virtual void draw_command(myro_img& canvas);
    private:
        point_draw_msg* data;
};

/**
 * @internal 
 * A private class which other shapes which use a bounding box inherits from.
 */
class _BBox : public GraphicsObject{
    public:
        _BBox(Point p1, Point p2);
        virtual void move(int dx, int dy);
        Point getP1();
        Point getP2();
        Point getCenter();
    protected:
        bb_draw_msg* data;
};

/**
 * Represents an Oval.
 */
class Oval : public _BBox{
    public:
        /// Create an oval with the given bounding box determined by p1 and p2
        Oval(Point p1, Point p2);
        Oval* clone();
    protected:
        //virtual void draw_command(myro_img& canvas);
};

/**
 * Represents a Circle.
 */
class Circle : public Oval{
    public:
        /// Creates a circle at the given center, with the given radius
        Circle(Point center, int radius);
        int getRadius();
//        virtual void draw_command(myro_img& canvas);
    protected:
        circle_draw_msg* extra;
};

/// Represents a Rectangle
class Rectangle : public _BBox{
    public:
        /// Creates a Rectangle formed with the points p1 and p2.
        Rectangle(Point p1, Point p2);
    protected:
        //virtual void draw_command(myro_img& canvas);
};

/// Represents a Line, or Arrow
class Line : public _BBox{
    public:
        /// Creates a Line (or Arrow) from p1 to p2
        Line(Point p1, Point p2, std::string arrow_type="none");
        /// str can be "first", "last", "both", or none. Default is "none"
        void setArrow(std::string type);
    protected:
        //virtual void draw_command(myro_img& canvas);
        line_draw_msg* extra;
    friend class Polygon;
};

/// Represents any arbitrary Polygon
class Polygon : public GraphicsObject{
    public:
        /// Create a Polygon from the given vector of points.
        Polygon(std::vector<Point> points);
        /// Get all the points that represents the polygon.
        std::vector<Point> getPoints();
        virtual void move(int dx, int dy);
    protected:
        //virtual void draw_command(myro_img& canvas);
    private:
        std::vector<Point> update_points();
        polygon_draw_msg * data;
};

/// Used for displaying text on the GraphWin
class Text: public GraphicsObject{
    public:
        /// Create a Text object at the point anchor with the given text.
        Text(Point anchor, std::string text);
        /// Get the text
        std::string getText();
        /// Change what the text says
        void setText(std::string text);
        /// Get the position of the text
        Point getAnchor();
        /// Change the position of the text
        void setAnchor(Point anchor);
        /**
         * Change the font of the text.
         * @warning This is not implemented, and does nothing!
         */
        void setFace(std::string font);
        /**
         * Change the size of the font.
         */
        void setSize(int size);
        /**
         * Changes font to the given style. Possible values are: 'normal', 
         * 'bold', 'italic', and 'bold italic'.
         * 
         * @warning This is not implemented, and does nothing!
         */
        void setStyle(std::string style);
        ///Changes the color of the text.
        void setTextColor(Color color);
        ///Changes the color of the text.
        void setTextColor(std::string color);
        ///Boolean value to set to draw a background box behind the text 
        ///(default false)
        void drawBackground(bool background);
    protected:
        //virtual void draw_command(myro_img& canvas);
        virtual void move(int dx, int dy);
    private:
        text_draw_msg* data;
};

class Image : public GraphicsObject{
    public:
        /// Create an Image object from a filename (must be a jpeg file)
        Image(Point anchor, std::string filename);
        /// Create an Image object from a PicturePtr object
        Image(Point anchor, PicturePtr img);
        /// Get the position of the image
        Point getAnchor();
        /// Set the position of the iamge
        void setAnchor(Point anchor);
        /// Get the Pixel value at the x,y position
        Pixel getPixel(int x, int y);
        /// Set the Pixel Value at the x,y position
        void setPixel(int x, int y, Color c);
        /// Save the given image (must be a jpeg)
        void save(std::string filename);
        virtual void move(int dx, int dy);
    private:
        image_draw_msg* data;
};

///@}
