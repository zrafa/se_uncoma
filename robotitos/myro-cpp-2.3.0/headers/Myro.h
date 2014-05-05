#ifndef __MYRO_H__
#define __MYRO_H__

/** @file 
 * This header defines general robot opitions, as well as the construction,
 * of a global robot variable. The global robot is created upon calling
 * connect and destroyed upon calling disconnect.
 */

#include <Scribbler.h>
#include <Graphics.h>
#include <VideoStream.h>

extern Scribbler robot;

/** @defgroup myro_general General Myro Commands
 * This group contains general Myro Commands which are general "helper" 
 * functions, but don't use the robot or picture functions.
 * @{
 */

/// Connect the global robot
void connect(std::string port="");
/// Disconnect the global robot
void disconnect();

/** @defgroup myro_general General Myro Commands
 * This group contains general Myro Commands which are general "helper" 
 * functions, but don't use the robot or picture functions.
 * @{
 */

/** 
 * Like sleep, but takes an argument of seconds, 
 * and can take a fraction of seconds.
 *
 * @param time The number of seconds to wait
 */
void wait(double time);

/**
 * Returns true until start_time ammount of time has passed.
 * 
 * For use in loops that you would like to run for longer then a certain number
 * of minutes.
 */
bool timeRemaining(double start_time);

/**
 * Returns the time, in seconds, since the epoch.
 */
double currentTime();

/**
 * Returns a random number in the range of 0.0 and 1.0
 */
double randomNumber();


/**
 * Pop open a dialog box asking the user to answer a question. 
 *
 * First, give askQuestion a string that is the question, if nothing else is
 * given, Yes/No are the answers, otherwise any number of strings is given as 
 * answers. 
 * 
 * @param question Is the question to ask.
 * @param answerString is a string representing the answers, separated by the 
 *      "seperator" character. By default it is a ","
 * @param seperator The separator to tokenize the answerString with. This is provided
 *      in case you would want a comma in one of your answers.
 * @param trim_whitespace Default true, will strip all whitespace from around answers
 */
std::string askQuestion(std::string question, std::string answerString="Yes,No", 
                        char seperator=',', bool trim_whitespace=true);

/**
 * Alternative version of askQuestion, which takes a vector of the possible 
 * answers.
 *
 * @param question The question to ask.
 * @param answers A vector of strings which are the possible answers to the 
 *      question. If an empty vector is provided, then the defaults are "Yes"
 *      and "No"
 */
std::string askQuestionVector(std::string question, std::vector<std::string> answers);

/// @}

#endif // __MYRO_H__
