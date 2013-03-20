/* * * * * * * * * * * * * * * * * * * * * * 
 * MyroC.h  -- Header for the MyroC extern C interface.
 *
 * Authors: 
 * April O'Neill
 * David Cowden
 * Dilan Ustek
 * Erik Opavsky
 *
 * * * * * * * * * * * * * * * * * * * * * * /

 /* Index of all functions.

 1- GENERAL                 2- MOVEMENT
 rConnect                   rTurnLeft
 rDisconnect                rTurnRight
 rBeep                      rTurn
 rSetName                   rTurnSpeed
 rGetName                   rForward
 rGetTxt                    rBackward
 rGetNum                    rMotors
 rSet                       rMove
 rSetPos                    rRotate
 rSetLEDFront               rTranslate
 rSetLEDBack                rStop
 rGetBattery                rHardStop
 rSetData
 rGetData


 3- PICTURES                4- SENSORS
 rTakePicture               rGetLightsAll
 rShowPicture               rGetLightTxt
 rDisplayPicture            rGetLightNum
 rMakePicture               rGetForwardness
 rGetPictureHeight          rSetForwardnessTxt
 rGetPictureWidth           rSetForwardnessNum
 rClonePicture              rGetStall
 rSavePicture               rGetObstacleAll
 rLoadPicture               rGetObstacleTxt
 rGetRawPictureData         rGetObstacleNum
 rGetPicturePixel           rGetLine
 rSetPicturePixel           rGetBrightAll
 rSetWhiteBalance           rGetBrightTxt
 rDarkenMyroCamera          rGetIRAll
 rAutoMyroCamera            rGetIRNum
                            rGetIRTxt
                            rGetLastSensors
                            rSetIRPower
                            rGetInfo                             
                            rSetEchoMode

*/

/* Note: There is an r in the beginning of every function to make it 
   easier to understand whether it is a robot function. */

#ifndef _MyroC
#define _MyroC

/*  Allow header to function for both C and C++ */

#if defined(__cplusplus)
extern "C"
{
#endif

  //TODO: Detail each function and parameter. 
  //      Similar parameters or operations can be grouped.


  /* 1- GENERAL */

  /* connects program to Scribbler */
  void rConnect (const char * port);

  /* disconnects program from Scribbler */
  void rDisconnect();

  /* function for sending tone to the robot */
  void rBeep (double duration, int freq);

  /* 
   * function for sending two tones to the robot
   * The tones are executed concurrently.
   */
  void rBeep2 (double duration, int freq1, int freq2);

  /* Changes the 16 byte name stored in the robot to the 16-byte name given */
  /* if < 16 bytes given, name is filled with null characters
     if >= 16 bytes given, name is truncated to 15 bytes plus null
  */
  void rSetName (const char * name);

  /* returns information about the name of the robot */
  const char * rGetName();

  // get and set Functions
  /* - - - / ^ . ^ \ - - - *
   * The get family of functions both require a string requesting the item
   * information that should be returned.
   *  The possible options include:
   config
   stall
   forwardness
   startsong
   version
   data
   info
   name
   password
   volume
   battery
   blob
   light
   line
   obstacle
   bright
   picture
   all
   Options should be passed in as a string..
  */

  // Currently not implemented. Function is a stub. Perhaps implemented later.
  /* General method to ask the specified item for all data */
  void * rGetTxt (char * item, char * position[], int size);

  // Currently not implemented. Function is a stub. Perhaps implemented later.
  /* General method to ask the specified item for all data, or some 
     specified vector */
  void * rGetNum (char * item, int position[], int size);

  // Currently not implemented. Function is a stub. Perhaps implemented later.
  // TODO: Document set and setPos better.
  /* General method to set items (e.g. on/off, or set an item at a position 
     to  value)  
  */
  int rSet (char * item, int position, double value);

  // Currently not implemented. Function is a stub. Perhaps implemented later.
  /* General method to set an item at a position to value, or set an item to
     the value position.
  */
  int rSetPos (char * item, char * position, double value);

  /* toggles the front LED on (1) or off (0) */
  void rSetLEDFront (int value);

  /* toggles the back LED on (1) or off (0) */
  void rSetLEDBack (int value);

  /* reads the current voltage from the batteries */
  double rGetBattery();

  /*
   * Store a single byte value on the robot.
   * There are 8 byte values which can be accessed and modified.
   * posistion can range from 0 to 7 while value should be within the bounds
   * of the char type.
   */
  void rSetData (int position, char value);

  /* returns the value of data stored at the position */
  char rGetData (int position);





  /* 2- MOVEMENT */

  /* Speed is between -1 and 1. 
     Time can be any positive number. Can also have decimal numbers.
  */

  /* turns Scribbler left for a specified time and speed */
  void rTurnLeft (double speed, double time);

  /* turns Scribbler right for a specified time and speed */
  void rTurnRight (double speed, double time);

  /* turns Scribbler at a specified speed for a specified time 
   * negative speeds turn right, positive speeds turn left
   */
  void rTurn (double speed, double time);

  /* turns Scribbler in direction for a specified time at a 
     specified speed */
  void rTurnSpeed (char * direction, double speed, double time);

  /* moves Scribbler forward for a specified time and speed */
  void rForward (double speed, double time);

  /* moves Scribbler backward for a specified time and speed */
  void rBackward (double speed, double time);

  /* directs robot motion with given speeds for the left and right motors
     continues until given another motion command or disconnected */
  void rMotors (double leftSpeed, double rightSpeed);

  /* sets the robot's forward speed and turn speed. It can be any number 
     between -1 and 1 inclusively.     
     continues until given another motion command or disconnected */
  void rMove (double translate, double rotate);
 
  /* sets the robot's desired turn speed between -1 and 1 inclusively 
     continues until given another motion command or disconnected */
  void rRotate (double amount);

  /* sets the robot's desired forward speed between -1 and 1 inclusively 
     continues until given another motion command or disconnected */
  void rTranslate (double amount);

  /* directs robot to stop movement */
  void rStop();

  /* cuts power to the motor of the robot */
  void rHardStop();

  //End Robot Functions



  /* 3- PICTURES */

  /* Export the Picture type in a form C can recognize */
  typedef struct Picture Picture;

  /* Export the Pixel structure for general use with Pictures */
  
  /* The Pixel struct typedef must be wrapped in a preprocessor directive
     --  because when compiling MyroC against the Myro libraries, the Pixel 
     --  struct is already defined. However, this struct is also needed 
     by users
     --  only compling against the MyroC library and should be included in 
     --  that case.
  */
#ifndef __PICTURE_H__
  typedef struct Pixel {
    unsigned char R;
    unsigned char G;
    unsigned char B;
  } Pixel;
#endif

  /* NOT WORKING
     /* Returns a blob....... 
     Picture * takePictureBlob ();*/

  //TODO:
  /*
   * add BLOB functions..
   */

  /* Takes a color picture with the Fluke camera 
   * The picture is returned as a Picture * type which can be used with other
   * picture functions.
   */
  Picture * rTakePicture();

  /* create a blank picture of specified size */
  Picture * rMakePicture (int cols, int rows);

  /* Display a specified Picture.  This is a blocking call, program 
   * will not continue until picture is closed.
   */
  void rShowPicture (Picture * pic);

  /* Display a specified Picture in a new window titled wname. This function 
   * does NOT block further execution.
   */
  void rDisplayPicture (Picture * pic, const char * wname);

  /* return the height, in pixels, of the Picture pic */
  int rGetPictureHeight (Picture * pic);

  /* return the width, in pixels, of the Picture pic */
  int rGetPictureWidth (Picture * pic);

  /* return a copy of the specified Picture pic */
  Picture * rClonePicture (Picture * pic);
  
  /* write Picture pic to a file *file */
  void rSavePicture (Picture * pic, const char * file);

  /* Load a picture from a file. Pictures may only be of the jpeg format.
   */
  Picture * rLoadPicture (const char * file);
  
  /* return a pointer to the underlying raw picture data in the Picture
   * struct.
   */
  unsigned char * rGetRawPictureData (Picture * pic);
  
  /* return the Pixel from Picture pic at location (row, col).
     Pixel is returned as a struct containing the R,G,B color values for the
     pixel.
  */
  Pixel rGetPicturePixel (Picture * pic, int row, int col);

  /* Set the Pixel at location (row, col) in Picture to the specified 
     Pixel Pix. */
  void rSetPicturePixel (Picture * pic, int row, int col, Pixel pix);

  /* turns the camera's white balance on (1) or off (0) */
  void rSetWhiteBalance (int value);

  /* turns OFF: white balance, gain control, and exposure control */
  void rDarkenMyroCamera (int level);

  /* turns ON: white balance, gain control, and exposure control */
  void rAutoMyroCamera();

  // End Picture functions.


  /* 4- SENSORS */

  /*  TODO: Explain why functions that alter the arrays passed to them also
      return the address of that array.*/

  /* Get the values of the three light sensors in an array.
     The lower the value, the brighter the light.*/
  int * rGetLightsAll (int vals[3]);

  /* asks a specified light sensor for a reading (e.g. "left") */
  int rGetLightTxt (char * value);

  /* asks a specified light sensor on the rear of the robot for a reading 
     (e.g. 0, 1, or 2) */
  int rGetLightNum (int value);

  /* returns the string "fluke-forward" or "scribbler-forward" depending on 
     the forwardness */
  const char * rGetForwardness();

  /* sets Scribbler to either "fluke-forward" or "scribbler-forward"
     returns 1 on success, 0 on failure
  */
  int rSetForwardnessTxt (const char * name);

  /* set the robot's forward direction to "fluke-forward" (1) or 
     "scribbler-forward" (0)
     This forwardness stays until changed. */
  void rSetForwardnessNum (int direction);

  // currently not working
  /* returns 1 if stalled(has something in front of it that prevents it from 
     moving), 0 if not stalled (does not have anything in front of it that 
     prevents it from moving)
     This forwardness stays until changed */
  int rGetStall();
  
  /* rGetObstacleAll stores the values of the left, center and right IR sensors 
     in the three element array vals[3] that is passed to it.  The 
     value of the left sensor is stored in the first location, center in the
     second, and the value of the right sensor is stored in the third
  
     returns a pointer to the vals array

     the values of vals will be 0 if no obstacle is seen. Returns values 
     closer to 6000 as obstacle gets closer.  The first value shows left sens
     or and the second value returns right sensor. As battery degrades, 
     sensor degrades (systematically lower numbers).
     number varies greatly, be wary.
   
     the array vals will be modified to contain the sensor values.
  */
  int * rGetObstacleAll (int vals[3]);
 
  /* reads the value for a specified fluke dongle IR sensor 
     ("left", "middle"/"center", or "right")
     Returns 0 if no obstacle is seen. Returns values closer to 6000 as 
     obstacle gets closer. 
     As battery degrades, sensor degrades (systematically lower numbers). 
  */
  int rGetObstacleTxt (char * value);
 
  /* reads the value for a specified dongle IR sensor (0 for left, 1 for
     middle, 2 for right)
     Returns 0 if no obstacle is seen. Returns values closer to 6000 as 
     obstacle gets closer. 
     As battery degrades, sensor degrades (systematically lower numbers). 
  */
  int rGetObstacleNum (int value);
 
  /* gets the line sensors of Scribbler. 0 means the line is seen and 1 means
     line not seen. Line is a black line on a white surface.
     First element of returned array is left sensor; second is 
     right sensor. 
  */
  int * rGetLine (int vals[2]);

  // Currently not working.  Program hangs upon call.
  /* reads the Fluke's virtual light sensors. Modifies the array vals[3]
     and returns a pointer to it 
  */
  int * rGetBrightAll (int vals[3]);

  // Currently not working.  Program hangs upon call.
  /* reads one of the Fluke's virtual light sensors. */
  int rGetBrightTxt (char * value);

  /* Returns a pointer to the modified array vals that contains the 
     Scribbler object detecting IR sensors.
     1 means there's an obstacle seen by the IR sensors.
     0 means there are no obstacles seen by the IR sensors. 
  */
  int * rGetIRAll (int vals[2]);

  /* Get value from a specific IR object sensor: 0 is left, 1 is right.
     If returned 1, there's an obstacle seen by the IR sensor.
     If returned 0, there are no obstacles seen by the IR sensor */
  int rGetIRNum (int direction);

  /* Get value from a specific IR object sensor: "left" or "right" .  
     If returned 1, there's an obstacle seen by the IR sensor. 
     If returned 0, there are no obstacles seen by the IR sensor */
  int rGetIRTxt (char * direction);

  // Elements in return array are currently unknown.
  /* Reads the values for all 11 robot sensors and stores them in an array.
     Example return: Light 0, 1, 3 ir 4, 5 line 6, 7 stall 8
  */
  int * rGetLastSensors (int vals[11]);
 
  /* sets the power amount for the dongle's IR sensors */
  void rSetIRPower (int power);

  /* returns information about the robot's dongle , firmware, and 
     communication mode */
  char ** rGetInfo (char *vals[4]);

  /* Turns the robot's echo mode on or off; 1 for on, 0 for off 
     Functionality is undetermined at this time. */
  void rSetEchoMode (int value);

#if defined(__cplusplus)
}
#endif

#endif
