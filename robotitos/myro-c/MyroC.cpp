/* * * * * * * * * * * * * * * * * * * * * *
 * MyroC.cpp  --  C function adapter library for the Myro-C++ environment.
 *
 * Authors:
 * April O'Neill
 * David Cowden
 * Dilan Ustek
 * Erik Opavsky
 *
 * * * * * * * * * * * * * * * * * * * * * * /

/* C wrapper function library which adapts the Myro C++ environment to a C 
   interface. Although the C++ robot class is declared and instantiated here,
   all calls to the robot object are repacked as simple procedure calls.
   Thus, from a user's perspective, programs can be written in C,
   even though the underlying compiler will need to be g++ to handle
   the Myro/C++ package.
*/

#include "Myro.h"

/* MyroC should be included AFTER Myro.h for compatibility with the 
 * Pixel typedef */

#include "MyroC.h"

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <stdlib.h>
#include <vector>
#include <cstring>

/* procedures involving Myro's underlying robot
 */

// turns the C string into a C++ string and connects to that port
extern "C" void 
rConnect (const char * port)
{
  std::string myPort (port);
  connect (myPort);
}

// calls the disconnect function
extern "C" void 
rDisconnect ()
{
  disconnect();
}

// calls the robot object's beep function
extern "C" void 
rBeep (double duration, int freq)
{
  robot.beep (duration, freq, 0);
}

// calls the robot object's 2nd beep function
extern "C" void 
rBeep2 (double duration, int freq1, int freq2)
{
  robot.beep (duration, freq1, freq2);
}


// calls the robot object's turnLeft function
extern "C" void 
rTurnLeft (double speed, double time)
{
  robot.turnLeft (speed, time);
}

// calls the robot object's turnRight function
extern "C" void 
rTurnRight (double speed, double time)
{
  robot.turnRight (speed, time);
}

// calls the robot object's turn function
extern "C" void 
rTurn (double speed, double time)
{
  robot.turn (speed, time);
}

// calls the robot object's turn function
extern "C" void 
rTurnSpeed (char * direction, double speed, double time)
{
  robot.turn (direction, speed, time);
}

// calls the robot object's forward function
extern "C" void 
rForward (double speed, double time)
{
  robot.forward (speed, time);
}

// calls the robot object's backward function
extern "C" void 
rBackward (double speed, double time)
{
  robot.backward (speed, time);
}

// calls the robot object's motors function
extern "C" void 
rMotors (double leftSpeed, double rightSpeed)
{
  robot.motors (leftSpeed, rightSpeed);
}

// calls the robot object's move function
extern "C" void 
rMove (double translate, double rotate)
{
  robot.move(translate, rotate, 0); //the zero parameter is unused..
}

// calls the robot object's rotate function
extern "C" void 
rRotate (double amount)
{
  robot.rotate (amount);
}

// calls the robot object's translate function
extern "C" void 
rTranslate (double amount)
{
  robot.translate (amount);
}

// calls the robot object's stop function
extern "C" void 
rStop()
{
  robot.stop();
}

// calls the robot object's hardStop function
extern "C" void 
rHardStop()
{
  robot.hardStop();
}

/* Changes the 16 byte name stored in the robot to the 16-byte name given 
   if < 16 bytes given, name is filled with null characters
   if >= 16 bytes given, name is truncated to 15 bytes plus null
*/
extern "C" void 
rSetName (const char * name)
{ 
  std::string newName = name;
  robot.setName (newName);
}

// calls the robot object's getName function and converts it to a C string.
extern "C" const char * 
rGetName()
{
  std::string name = robot.getName();
  std::size_t found; 
  found=name.find_last_not_of(" \t\f\v\n\r");
  if (found!=std::string::npos)
    name.erase(found+1);
  else
    name.clear();            // str is all whitespace
  
  return name.c_str();
}

// calls the robot object's takePicture function with no parameters.
extern "C" Picture *
rTakePicture () 
{
  
  return (new PicturePtr (robot.takePicture()))->get();
}

//TODO: add blob image functions
/* NOT WORKING * 
   extern "C" Picture * takePictureBlob () 
   {
   return takePicture("blob");
   }
*/

/* create a blank picture of the specified size
 */
extern "C" Picture *
rMakePicture (int cols, int rows) 
{
  return (new PicturePtr (makePicture (cols, rows)))->get();
}

/* display a specified Picture pic
 * NOTE: this is a blocking call..
 *
 */
extern "C" void 
rShowPicture (Picture * pic)
{
  pic->show();
}

/* display a specified Picture pic
 * NOTE: this is a non-blocking call..
 *
 */
extern "C" void
rDisplayPicture (Picture * pic, const char * wname)
{
  std::string win = wname;
  pic->show(win);
}

// calls the picture object's getHeight function
extern "C" int 
rGetPictureHeight (Picture * pic)
{
  return pic->getHeight();
}

// calls the picture object's getWidth function
extern "C" int 
rGetPictureWidth (Picture * pic)
{
  return pic->getWidth();
}

// calls the picture object's clone function
extern "C" Picture *
rClonePicture (Picture * pic) 
{
  return (new PicturePtr(pic->clone()))->get();
}  

// calls the picture object's savePicture function
extern "C" void 
rSavePicture (Picture * pic, const char * file)
{
  pic->savePicture(file);
}

// calls the loadPicture function
extern "C" Picture *
rLoadPicture (const char * file)
{ 
  return (new PicturePtr(loadPicture(file)))->get();
}

// calls the picture object's getRawImage function
/* return a pointer to the underlying raw picture data in the Picture
 * struct. */

extern "C" unsigned char *
rGetRawPictureData (Picture * pic)
{
  return pic->getRawImage();
}

// calls the picture object's getPixel function
/* Pixel is returned as a struct containing the R,G,B color values for the
   pixel as defined in the header. */
extern "C" Pixel 
rGetPicturePixel (Picture * pic, int row, int col)
{
  return pic->getPixel (row, col);
}

// calls the picture object's setPixel function
extern "C" void
rSetPicturePixel (Picture * pic, int row, int col, Pixel pix)
{
  pic->setPixel(row, col, pix);
}


//TODO:
/**
 * add BLOB functions..
 */

// calls the robot object's setWhiteBalance function
extern "C" void 
rSetWhiteBalance (int value)
{
  robot.setWhiteBalance (value);
}

// calls the robot object's darkenMyroCamera function
extern "C" void 
rDarkenMyroCamera (int level)
{
  robot.darkenCamera(level);
}

// calls the robot object's autoMyroCamera function
extern "C" void 
rAutoMyroCamera()
{
  robot.autoCamera();
}

// calls the robot object's getLights function
extern "C" int* 
rGetLightsAll (int vals[3])
{
  std::vector<int> v = robot.getLights();
  *(vals)       = v[0];
  *(vals + 1) = v[1];
  *(vals + 2) = v[2];
  return vals;
}

// calls the robot object's getLight function
extern "C" int 
rGetLightTxt (char * value)
{
  return robot.getLight (value);
}

// calls the robot object's getLight function
extern "C" int 
rGetLightNum (int value)
{
  return robot.getLight (value);
}

// calls the robot object's getForwardness function
extern "C" const char * 
rGetForwardness()
{
  return (*(new std::string(robot.getForwardness()))).c_str();
}

// calls the robot object's setForwardness function
extern "C" int 
rSetForwardnessTxt (const char * name)
{
  std::string str;
  str = name;
  if (!str.compare ("fluke-forward") || !str.compare ("scribbler-forward")) 
    {
      robot.setForwardness (str); 
      return 1;
    }
  return 0;
}

// calls the robot object's setForwardness function
extern "C" void 
rSetForwardnessNum (int direction)
{
  robot.setForwardness (direction);
}

// calls the robot object's getStall function
extern "C" int 
rGetStall()
{ 
  return (int) robot.getStall();
}

// calls the robot object's getObstacle function
/* getObstacle stores the values of the IR sensors in the three element 
 * array vals[3] that is passed to it. the array will be modified to 
 * contain the sensor values.
 */
extern "C" int * 
rGetObstacleAll (int vals[3])
{
  std::vector<int> v = robot.getObstacle();
  *(vals)     = v[0];
  *(vals + 1) = v[1];
  *(vals + 2) = v[2];
  return vals;
}

// calls the robot object's getObstacle function
extern "C" int 
rGetObstacleTxt (char * value)
{
  return robot.getObstacle (value);
}

// calls the robot object's getObstacle function
extern "C" int 
rGetObstacleNum (int value)
{
  return robot.getObstacle (value);
}

// calls the robot object's getLine function
extern "C" int * 
rGetLine (int vals[2])
{
  std::vector<int> v = robot.getLine();
  *(vals)     = v[0];
  *(vals + 1) = v[1]; 
  return vals;
}

// calls the robot object's getBright function
extern "C" int * 
rGetBrightAll (int vals[3])
{
  std::vector<int> v = robot.getBright();
  *(vals)     = v[0];
  *(vals + 1) = v[1];
  *(vals + 2) = v[2];
  return vals;
}

// calls the robot object's getBright function
extern "C" int 
rGetBrightTxt (char * value)
{
  std::string v = value;
  return robot.getBright (v);
}

// calls the robot object's get function
extern "C" int* 
rGetIRAll (int vals[2])
{
  std::vector<int> v = robot.getIR();
  *(vals)     = v[0];
  *(vals + 1) = v[1];
  return vals;
}

// calls the robot object's getIR function
extern "C" int 
rGetIRNum (int direction)
{
  return robot.getIR (direction);
}

// calls the robot object's getIR function
extern "C" int 
rGetIRTxt (char * direction)
{
  return robot.getIR (direction);
}

// calls the robot object's getLastSensors function
extern "C" int * 
rGetLastSensors (int vals[11])
{
  std::vector<int> v = robot.getLastSensors();
  int i;
  for(i = 0 ; i < 11; i++)
    *(vals+i) = v[i];
  return vals;
}

// calls the robot object's setLEDFront function
extern "C" void 
rSetLEDFront (int value)
{
  robot.setLEDFront (value);
}

// calls the robot object's setLEDBack function
extern "C" void 
rSetLEDBack (int value)
{
  robot.setLEDBack (value);
}

// calls the robot object's setIRPower function
extern "C" void 
rSetIRPower (int power)
{
  robot.setIRPower (power);
}

// calls the robot object's getBattery function
extern "C" double 
rGetBattery()
{
  return robot.getBattery();
}

// calls the robot object's getInfo function
extern "C" char ** 
rGetInfo(char * vals[4])
{
  std::vector<std::string> v = robot.getInfo();
  *(vals)     = const_cast<char*> (v[0].c_str());
  *(vals + 1) = const_cast<char*> (v[1].c_str());
  *(vals + 2) = const_cast<char*> (v[2].c_str()); 
  *(vals + 3) = const_cast<char*> (v[2].c_str()); 
  return vals;
}

// calls the robot object's setData function
/*
  Store a single byte value on the robot.
  There are 8 byte values which can be accessed and modified.
  posistion can range from 0 to 7 while value should be within the bounds 
  of the char type.
*/
extern "C" void 
rSetData(int position, char value)
{
  robot.setSingleData(position, value);
}

// return the value stored in position position
extern "C" char
rGetData(int position)
{
  std::vector<int> v (1, position);
  return robot.getData(v)[0];
}


/* --------- SET -------- */
// calls the robot object's set function
extern "C" int 
rSet (char * item, int position, double value)
{
  std::string itm = item;
  return robot.set (itm, position, value);
}

// calls the robot object's set function
extern "C" int 
rSetPos (char * item, char * position, double value)
{
  std::string itm = item;
  std::string pos = position;
  return robot.set (itm, pos, value);
}

/* --------- GET --------- */
//TODO: getTxt and getNum are stubs. 
// calls the robot object's get function
/* getTxt mallocs space for the array of values and returns a pointer to it
 * the user should be aware of this and free the space when done using it.
 * It is up to the user to manage the returned array.
*/
extern "C" void * 
rGetTxt (char * item, char * position[], int size)
{
  //TODO: STUB
  return (void *) NULL;
}

// calls the robot object's get function
extern "C" void * 
rGetNum (char * item, int position[], int size)
{
  //TODO: STUB
  return (void *) NULL;
}


// ?????????????????????????? WHAT IS ECHOMODE ?????????????????????????? //
//Turns the robot's echo mode on or off; 1 for on, 0 for off
extern "C" void rSetEchoMode (int value)
{
  return robot.setEchoMode (value);
} 
