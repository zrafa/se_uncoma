#ifndef __SCRIBBLER_H__
#define __SCRIBBLER_H__

#include <Robot.h>
#include <Picture.h>
#include <vector>
#include <map>
#include <MyroForwardDec.h>

/**
 * @addtogroup robot
 * @{
 */

/**
 * @class Scribbler
 *
 * A port of the existing IPRE Scribbler Python code to C++. 
 * The original authors of the python based code are
 * Keith O'Hara and Doug Blank.
 *
 * @brief This class implements all of the needed methods and 
 * components for controlling a scribbler robot.
 *
 * @author Richard Edwards, John Hoare
 */
class Scribbler: public Robot {
    public: 
        struct AllData{
            int line[2];
            bool stall;
            int bright[3];
            int obstacle[3];
            int ir[2];
            int light[3];
            double battery;
            public:
            AllData(){
                for (int i=0; i < 3; i++){
                    bright[i] = 0;
                    obstacle[i] = 0;
                    light[i] = 0;
                }
                line[0] = line[1] = 0;
                ir[0]=ir[1]=battery=0;
                stall = false;
            }
            AllData(const AllData& d){
                for (int i=0; i < 3; i++){
                    bright[i] = d.line[i];
                    obstacle[i] = d.line[i];
                    light[i] = d.line[i];
                    if ( i != 2 ){
                        ir[i]   = d.ir[i];
                        line[i] = d.line[i];
                    }
                }
                stall = d.stall;
            }
        };

	public:

    /// Default Constructor
	Scribbler();
    /// Default Destructor
	~Scribbler();

	/**
	 * Used to connect to the robot, and on use it will ask the user to
	 * specify the desired com port.
	 *
	 * @return returns a value less than 0 to indicate failure and
	 * a positive value greater than or equal to zero to indicate success.
	 */
	int connect(std::string port);

	/**
	 * Attempts to disconnect from the robot.
	 *
	 * @return returns a value less than 0 to indicate failure, and
	 * a positive value greater than or equal to zero to indicate success.
	 */
	int disconnect();

	/**
	 * Move issues a desired velocity and desired angular velocity,
	 * 
	 * @param translate - velocity [-1,1]
	 * @param rotate - angular velocity [-1,1]
	 */
	void move(double translate, double rotate, double z=0);

	/**
	 * Function for giving the robot a desired angular velocity.
	 * @param amount - angular velocity [-1,1]
	 */
	void rotate(double amount);

	/**
	 * Function for giving the robot a desired velocity.
	 *
	 * @param amount - angular velocity [-1,1]
	 */
	void translate(double amount);

	/**
	 * Function for cutting off power to the robot's motors.
	 */
	void hardStop();

	/**
	 * TODO: Restart is not yet supported!
	 */
	void restart();

	/**
	 * Function for sending tones to the robot.
	 *
	 * @param duration - time specified in seconds
	 * @param freq - the frequency of the tone
	 * @param freq2 - an optional second frequency, defaults to 0
	 */
	void beep(double duration, int freq, int freq2 = 0);

	/**
	 * Store a single byte value on the robot.
	 * There are 8 byte values which can be accessed and modified.
	 *
	 * @param position - index bounded on [0,7]
	 * @param value - the desired value, bounded on [0,255] 
	 */
	void setData(int position, int value);

	/**
	 * Performs the same operations as setData, however using a 
	 * different robot message, which doesn't require the 
	 * resubmission of all 8 bytes.
	 *
	 * @param position - index bounded on [0,7]
	 * @param value - the desired value, bounded on [0,255]
	 */
	void setSingleData(int position, int value);

	/**
	 * Used to turn the robot's echo mode on or off.
	 *
	 * @param value - 0 for off, and 1 for on
	 */
	void setEchoMode(int value);

	/**
	 * Changes the 16 byte name stored on the robot to the
	 * specified 16 byte name.
	 * 
	 * @param newName - A character string that isn't longer than
	 * 16 characters(does not count null character).
	 */
	void setName(std::string newName);

	/**
	 * Changes the 16 byte password stored on the robot to the
	 * new specified 16 byte password.
	 *
	 * @param password - A character string that isn't longer than
	 * 16 characters(does not count null character).
	 */
	void setPassword(std::string password);

	//setting functions
	/**
	 * A general purpose set function which allows you to set
	 * an item at position on/off or set an item at position to value.
	 *
	 * Example: 
	 * set(led, 1, 0) - sets the center led to the off position.
	 * set(whitebalance, 1) - turns the camera's white balance on.
	 *
	 * @param item - the desired item
	 * @param position - the desired position or item value
	 * @param value - the value for the desired item at position.
	 */
	int set(std::string item, int position, int value = 0);

	/**
	 * A general purpose set function which allows you to setting 
	 * an item at position to value, or setting an item to the value
	 * position.
	 *
	 * Example:
	 * set(led, "front", 1) - sets front led to on
	 * set("name" "Scribby") - sets the robot's name to Scribby
	 *
	 * @param item - the desired item
	 * @param position - the desired position or value for item
	 * @param value - the value for the desired item at position.
	 */
	int set(std::string item, std::string position, double value = 0);

	/**
	 * A general purpose get function which will query the specified
	 * item for all data, or particular data specified by the position
	 * vector.
	 *
	 * Example
	 * get("name") - return a pointer to the robot's name.
	 * get("info") - returns all information about the robot.
	 * 
	 * @param item - the desired item to query
	 * @param position - a vector for issuing more detailed queries on
	 *                   an item.
	 *
	 * @return The return value is a void * pointer, it is up to the caller
	 * to know which return value they are expecting and to cast accordingly.
	 */
	void * get(std::string item, std::vector<std::string> position 
			= std::vector<std::string>()); 

	/**
	 * A general purpose get function which will query the specified
	 * item for data specified by the position vector.
	 *
	 * Example:
	 * get("light", std::vector<int>(3,0)) :
	 * returns a pointer to a vector containing three readings from
	 * light sensor 0.
	 *						
	 * @return The return value is a void * pointer, it is up to the caller
	 * to know which return value they are expecting and to cast accordingly.
	 */
	void * get(std::string item, std::vector<int> position);

    /**
     * Determine if the robot is stalled or not.
     *
     * NOTE: Every time you issue a move command, the stall sensor resets, 
     * and it needs to wait a short time to see whether the motors are stalled. 
     * This means that the sensor won’t give accurate results if you test it 
     * too soon after the robot starts to move.
     *
     * @returns True if stalled, False otherwise.
     */
    bool getStall();

    /**
     * Gets which direction the robot is set to be forward
     *
     * @return "fluke-forward" or "scribbler-forward"
     */
    std::string getForwardness();

    /**
     * Gets the volume that the speaker is set to be
     *
     * @return 1 for "loud" 0 for "quiet"
     */
    int getVolume();


    /**
     * Get the Line sensors
     *
     * @return Vector of 2 integers representing the left, and right line 
     * sensors. Value of 0 means that the line is seen, 1 means line not seen.
     */
    std::vector<int> getLine();

    /**
     * Return if an "obstacle" was seen for each Ir sensor.
     *
	 * @return A vector of values ranging from 0 - 6000 for each 
     * Obstacle Sensor. The larger the value the closer to an obstacle. 
     * However, the quality of the IR sensors decays over time. So it 
     * may be possible for the upper bound to be lower than 6000.
     */
    std::vector<int> getObstacle();


    /**
     * read one of the Fluke's virtual light sensors. The Fluke's virtual 
     * light sensors report the total intensity in the left, center, and 
     * right sides of the Fluke's camera.
     *
     * @return A vector of integers representing the Fluke's virtual light
     * sensors.
     */
    std::vector<int> getBright();

    /**
     * Gets all of the IR sensors on the scribbler.
     *
     * @return A vector of integers representing the value of each IR sensor
     * on the scribbler.
     */
    std::vector<int> getIR();

    /**
     * Get a specific direction of the IR sensors
     * 0 - Left
     * 1 - Right
     * @param direction The direction to get: 0-left 1-right
     * @return IR value, -1 if error
     */
    int getIR(int direction);

    /**
     * Get a specific direction of the IR sensors
     * 
     * @param direction The direction to get: "left" or "right"
     * @return IR value, -1 if error
     */
    int getIR(std::string direction);

    /**
     * Get the values of the light sensors.
     *
     * @return A vector of ints each one corresponding to a light sensor. 
     * 0 is left sensor, 1 is center, and 2 is right light sensor. 
     */
    std::vector<int> getLights();

	/**
	 * Every set command will read the values for all eleven on board robot
	 * sensors, and store them internally within a sensor array. This,
	 * function returns a vector containing those previously read sensor
	 * values. 
	 *
	 * @return A vector containing the robot's last sensor update.
	 * Order: Light 0, 1, 3
	 *		  ir 4, 5
	 *		  line 6, 7
	 *		  stall 8
	 */
	std::vector<int> getLastSensors();
		

	/**
	 * Use to toggle the front led on or off.
	 *
	 * @param value - 0 for off and 1 for on.
	 */
	void setLEDFront(int value);

	/**
	 * Used to set the back led to the specified value.
	 *
	 * @param value - specify an intensity for the rear led.
	 *				  value is bounded on [0.0,1.0]
	 */
	void setLEDBack(double value);

	/**
	 * Used to set the robot's forward direction. The fluke
	 * can either be set to forward, or the light sensors on the
	 * rear of the robot can be set as the forward direction.
	 *
	 * @param direction - the robot's desired forward direction.
	 *					  ("fluke-forward" or "scribbler-forward")
	 */
	void setForwardness(std::string direction);

	/**
	 * Used to set the robot's forward direction.
	 *
	 * @param direction - 1 for fluke-forward and 0 for scribbler-forward
	 */
	void setForwardness(int direction);

	/**
	 * Used to set the power amount for the dongle's IR sensors.
	 *
	 * @param power - desired power value bounded on [0,255]
	 */
	void setIRPower(int power);

	/**
	 * Used to turn the camera's white balance on or off.
	 *
	 * @param value - 0 white balance off, 1 white balance on
	 */
	void setWhiteBalance(int value);

	/**
	 * Not yet supported
	 */
	void reboot();

	/**
	 * Used to configure the blob tracking feature within the robot,
	 * by providing a picture and a specifying the top left and
	 * bottom right corner of a bounding box. The bounding box will
	 * the define the pixels of interest for configuring the desired
	 * pixel values.
	 *
	 * @param picture - 256x192 RGB Image
	 * @param x1 - top left bounding box corner x value.
	 * @param y1 - top left bounding box corner y value.
	 * @param x2 - bottom right bounding box corner x value.
	 * @param y2 - bottom right bounding box corner y value.
	 */
	void conf_rle_range(unsigned char * picture, int x1, int y1, int x2,
			int y2);

	/**
	 * Used to manually define the bounds for a blob configuration in
	 * YUV color space. Note, this generally will not be used unless one
	 * wishes to write a different blob configuration other than the
	 * one provided by conf_rle_range.
	 *
	 * @param y_low  - Y Lower bound
	 * @param y_high - Y Upper bound
	 * @param u_low  - U Lower bound
	 * @param u_high - U Upper bound
	 * @param v_low  - V Lower bound
	 * @param y_low  - Y_lower bound
	 */
	void configureBlob(int y_low = 0, int y_high = 255,
					   int u_low = 0, int u_high = 255,
					   int v_low = 0, int v_high = 255,
					   int smooth_thresh=4);

    /**
     * Get all of the available sensor data in the AllData structure.
     */
    Scribbler::AllData getAll();

	/**
	 * Read the current voltage value for the batteries.
	 *
	 * @return The voltage remaining of the battery, from 0.0 to 9.0
	 */
	double getBattery();
	
	/**
	 * Reads the value for a specified dongle IR sensor.
	 *
	 * Example:
	 * getObstacle("left")
	 *
	 * @param value - The desired IR sensor to query.
	 * @return A value ranging from 0 - 6000. The larger the value
	 * the closer to an obstacle. However, the quality of the IR
	 * sensors decays over time. So it may be possible for the upper
	 * bound to be lower than 6000.
	 */
	int getObstacle(std::string value);

	/**
	 * Read the value for a specified dongle IR sensor.
	 *
	 * Example:
	 * getObstacle(1)
	 *
	 * @param value - The desired IR sensor to query.
	 * @return A value ranging from 0 - 6000. The larger the value
	 * the closer to an obstacle. However, the quality of the IR
	 * sensors decays over time. So it may be possible for the
	 * upper bound to be lower than 6000.
	 */
	int getObstacle(int value);

	/**
	 * The camera has three different window's which it can use for
	 * returning light intensity. getBright allows you to query a
	 * particular window for its intensity value.
	 *
	 * Example:
	 * getBright("right")
	 *
	 * @param value - The desired window to query.
	 * @return An integer represent the light intensity for the specified
	 * window.
	 */
	int getBright(std::string value); 

	/**
	 * Used to query a specified light sensor located on the rear of the
	 * robot. 
	 *
	 * Example:
	 * getLight("left")
	 *
	 * @param value - The desired light sensor.
	 * @return An two byte integer representing the light reading
	 * from the specified light sensor.
	 */
	int getLight(std::string value = "none");

	/**
	 * Used to query a specified light sensor located on the rear of the
	 * robot.
	 *
	 * Example
	 * getLight(1)
	 *
	 * @param value - The desired light sensor.
	 * @return A two byte integer representing the light reading 
	 * from the specified light sensor.
	 */
	int getLight(int value);

	/**
	 * Used to take pictures in the RGB and Gray Scale color space.
	 * Also, once the blob tracking is configured it will return an
	 * image with the areas of interest in white, and the areas of
	 * non-interest in black.
	 *
	 * @param type - Valid values, "jpeg", "grayjpeg", "color", "gray", and "blob"
	 * @return unsigned char array containing the image information.
	 */
	PicturePtr takePicture(std::string type =  "color");
	
	/*
	 * Not yet functional. This version is intended to be used for
	 * taking the jpeg images. However, get jpeg scan is still buggy.
	 */
	//unsigned char * takePicture(std::string type , int &size);

	/**
	 * Given that the blob tracking is configured, this function
	 * returns the number of pixels that match the specified blob
	 * and the x,y location related to said blob.
	 *
	 * @return A vector with the following data order:
	 *		   numpixels,
	 *		   x_location,
	 *		   y_location
	 */
	std::vector<int> getBlob(); //not sure about this either

	/**
	 * This turns off White Balance, Gain Control, and Exposure Control
	 */
	void darkenCamera(int level = 0);

	/**
	 * This turns on White Balance, Gain Control, and Exposure Control
	 */
	void autoCamera();

	/**
	 * @return Returns the name of the robot.
	 */
	std::string getName();

	/**
	 * @return Returns the password stored on the robot.
	 */
	std::string getPassword();

	/**
	 * This returns information about the robot's dongle, firmware,
	 * and communication mode.
	 *
	 * @return The vector contains strings formated as item:value
	 * Example: fluke:2.7.8
	 */
	std::vector<std::string> getInfo();

	/**
	 * @param position An optional vector used to specify desired byte indexes.
	 * @return This function returns either all 8 bytes stored on the robot,
	 * or a set of the data based on the input vector. 
	 *
	 * Example: A vector containing 1, 2, 3 will return the data bytes
	 * stored at index 1, 2, and 3.
	 */
	std::vector<int> getData(std::vector<int> position = std::vector<int>());

	private:

	/**
	 * Used to send the correct motor values to the robot, based on
	 * the desired translation and rotation values.
	 * 
	 * @param translate - the desired translation value.
	 * @param rotate - the desired rotation value.
	 */
	void _adjustSpeed(double translate, double rotate);

	/**
	 * A function that is used to pack and send all set commands.
	 *
	 * Each set command is padded to 9 bytes, and consist of a message
	 * header and message body. When using this function remember to
	 * specify a terminating parameter of -1. It is possible to send
	 * multiple set commands through this function. 
	 *
	 * @param message_header - the message header for the set command.
	 * @param ... - n parameters with the final value being -1. NULL
	 * is not usable since some commands use 0 as a valid transmission
	 * value.
	 */
	int _set(int message_header, ...);

	/**
	 * This function supports sending all none dongle get commands. With
	 * variable read capabilities, it can either read in byte mode,
	 * word mode, or line mode. 
	 *
	 * @param message_header - the message header for the desired get command.
	 * @param bytes - the number of bytes to be sent(not padded to 9)
	 * @param mode - specifies the desired reading mode for responses.
	 */
	int * _get(int message_header, int bytes, std::string mode = "byte");

	/**
	 * Sends the correct speaker values for a beep command with one freq.
	 */
	int _set_speaker(int freq, int duration);	
	//Overloaded!
	
	/**
	 * Sends the correct speaker values for a beep command with two freq.
	 */
	int _set_speaker(int freq, int freq2, int duration);

	/**
	 * A dongle set command for setting the power level on the dongle
	 * ir sensors. 
	 *
	 * @param power - The desired power value between [0,255]
	 */
	int set_ir_power(int power);

	//Private Camera Related Functions
	/**
	 * Used to set camera parameters.
	 *
	 * @param addr - The address for the parameter
	 * @param byte - The value to be stored
	 */
	int set_cam_param(unsigned char addr, unsigned char byte);

	//Need to figure out what these actually do for documentation
	int conf_window(unsigned char window, unsigned char x_low, 
			unsigned char y_low, unsigned char x_high, unsigned char y_high,
			unsigned char x_step, unsigned char y_step);
	int conf_gray_window(unsigned char window, unsigned char lx, 
			unsigned char ly, unsigned char ux, unsigned char uy, 
			unsigned char xstep, unsigned char ystep);
	int conf_gray_image();

	/**
	 * Configures the color range in YUV space for run length encoded
	 * images. 
	 */
	int conf_rle(unsigned char delay = 90, unsigned char smooth_tresh = 4, 
				 unsigned char y_low = 0, unsigned char y_high = 254,
				 unsigned char u_low = 51, unsigned char u_high = 136,
				 unsigned char v_low = 190, unsigned char v_high = 254);

	/**
	 * Used to take a picture a color picture from the robot,
	 * in YUV color space and convert it to RGB color space.
	 *
	 * @return An RGB image with width 256 and height 192.
	 */
	unsigned char * grab_array_rgb();

	/**
	 * @return A gray scale image with width 256 and height 192.
	 */
	unsigned char * grab_gray_array();

	/**
	 * Used to upscale the 128 x 96 robot gray scale images to
	 * 256 x 192.
	 *
	 * @return A gray scale image with width 256 and height 192.
	 */
	unsigned char * quadrupleSize(unsigned char * gb, 
			int width, int size);

	/**
	 * Note this will be changed a later date to be gray scale, however
	 * right now it is easier to display as RGB within the Magick++
	 * api.
	 *
	 * @return A RGB black and white image with width 256 and heigh 192
	 */
	unsigned char * grab_blob_array();

	/**
	 * Not yet fully functional, but is used to grab the jpeg header
	 * from the robot.
	 */
	unsigned char * read_jpeg_header(int &size);

	/**
	 * Not yet fully functional, but is used to grab the physical
	 * jpeg scan from the robot.
	 */
	std::vector<unsigned char> read_jpeg_scan();

	/**
	 * Currently reads a 128x192 color jpeg from the robot,
	 * it is is undecided on who's responsibility it will
	 * be to resize the image to 256x192
	 *
	 * @param reliable - determines the quality for the jpeg.
	 * @param size - used to convey back to the caller the size of the
	 * jpeg array.
	 * @return Used to take a color jpeg image from the robot. 
	 *
	 */
	unsigned char * grab_jpeg_color(int reliable, int &size);

	unsigned char * grab_jpeg_gray(int reliable, int &size);

	unsigned char * jpegStretch(unsigned char * jpegBuffer, int color_space,
			int &size);


	/**
	 * Used to send messages to the robot that require padding,
	 * and have variable echo or sensor mode. 
	 *
	 * @param buf - unpadded message
	 * @param bytes - number of bytes stored in buf
	 * @param echo - default value 1, set to 0 to not read an echo
	 * @param sensor - default value 1, set to 0 to not read 
	 * the scribbler on board sensor data.
	 */
	int send_message(unsigned char * buf, int bytes, int echo = 1, 
			int sensor = 1);

	/**
	 * Used to read messages from the robot. (Blocking Call)
	 *
	 * @param buf - a buffer for storing the read response.
	 * @param bytes - the number of bytes to be read.
	 */
	int read_message(unsigned char * buf, int bytes);

	/**
	 *@return A two byte value read from the robot.
	 */
	int read_2byte();

	/**
	 *@return A three byte value read from the robot.
	 */
	int read_3byte();

	/**
	 * Writes two bytes to the robot.
	 */
	int write_2byte(int value);

	/**
	 * Reads a specified memory segment from the robot.
	 *
	 * @param page - the memory page address
	 * @param offset - the offset into the page.
	 *
	 * @return the value stored at the memory segment.
	 */
	int read_mem(int page, int offset);

	/**
	 * Not yet supported
	 */
	int write_mem(int page, int offset, int byte);

	/**
	 * Not yet supported
	 */
	int erase_mem(int page);

	/**
	 * Converts a specified YUV to its corresponding RGB values.
	 */
	int yuv2rgb(int Y, int U, int V, unsigned char &R, 
			unsigned char &G, unsigned char &B);

	/**
	 * Convert a specified RGB to its corresponding YUV values.
	 */
	int rgb2yuv(int R, int G, int B, int &Y, int &U, int &V);


	int dongle; //if robot has dongle or not
	unsigned char * sensors;
	unsigned char * data; //not sure what this is for yet!

	serial * con;

	int volume;

	double lastRotate;
	double lastTranslate;

	//camera settings, the values are hard coded into the constructor
	//however, they are changeable so they aren't global constants, or
	//static constants.
	unsigned char CAM_PID;
	unsigned char CAM_PID_DEFAULT;
	unsigned char CAM_VER;
	unsigned char CAM_VER_DEFAULT;
	unsigned char CAM_BRT;
	unsigned char CAM_BRT_DEFAULT;
	unsigned char CAM_EXP;
	unsigned char CAM_EXP_DEFAULT;
	unsigned char CAM_COMA;
	unsigned char CAM_COMA_DEFAULT;

	unsigned char CAM_COMA_WHITE_BALANCE_ON;
	unsigned char CAM_COMA_WHITE_BALANCE_OFF;

	unsigned char CAM_COMB;
	unsigned char CAM_COMB_DEFAULT;
	unsigned char CAM_COMB_GAIN_CONTROL_ON;
	unsigned char CAM_COMB_GAIN_CONTROL_OFF;

	unsigned char CAM_COMB_EXPOSURE_CONTROL_ON;
	unsigned char CAM_COMB_EXPOSURE_CONTROL_OFF;

    boost::mutex* robot_lock;
    boost::mutex* image_lock;

    // Videostream Cleanup Stuff!
    private:
    boost::mutex* videoStreamLock;
    int  registerVideoStream(VideoStream* vs);
    void unregisterVideoStream(int id);
    int  newid;
    bool shutdown;
    std::map<int,VideoStream*> videostreams;
    friend class VideoStream;
};

///@}

#endif
