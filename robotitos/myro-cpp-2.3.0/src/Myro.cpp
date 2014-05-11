#include "Myro.h"
#include <sys/time.h>
#include <time.h>
#include <cmath>
#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <cstdlib>
#include <string>
#include <vector>
#include <stdarg.h>
#include <boost/algorithm/string/trim.hpp>

static time_t start_time;
static bool running = false;

Scribbler robot;

void wait(double time) {
	int utime = (int)(time * pow(10,6));
	if(time != 0)
		usleep(utime);
}

bool timeRemaining(double desired_time) {	
	if(!running) {
		running = true;
        start_time = time(NULL);
		return true;
	}

    if ( difftime(time(NULL), start_time) >= desired_time ){
      running = false;
      return false;
    }
    return true;
}

double currentTime(){
    time_t theTime = time(NULL);
    return (double)theTime;
}

double randomNumber(){
    return (double)rand()/RAND_MAX;
}

void connect(std::string port){
	int status = robot.connect(port); 
	if(status < 0) { 
		exit(-1);
	}
    std::cout << "Connected to Robot" << std::endl;
}

void disconnect(){
    robot.stop();
	robot.disconnect();
}

static std::vector<std::string> tokenize_string(std::string str, 
                                 char seperator, bool trim_whitespace){
    std::string temp;
    std::vector<std::string> tokens; 
    for (int i = 0; i < (int)str.length(); i++){
        if ( str[i] == seperator && !temp.empty() ){
            if(trim_whitespace) boost::algorithm::trim(temp);
            tokens.push_back(temp);
            temp.clear();
        } else if ( str[i] != seperator ){
            temp += str[i];
        }
    }
    if ( !temp.empty() ){
        if(trim_whitespace) boost::algorithm::trim(temp);
        tokens.push_back(temp);
    }
    return tokens;
}

std::string askQuestion(std::string question, std::string answerString, 
                        char seperator, bool trim_whitespace){
    return askQuestionVector(question, 
                tokenize_string(answerString,seperator,trim_whitespace));
}

/*
std::string askQuestion(const char* question, ...){
    std::vector<const char*> answers;
    va_list list;
    va_start(list, question);
    const char* answer = va_arg(list,const char*);
    while ( answer != NULL ){
        answers.push_back(answer);
        answer = va_arg(list,const char*);
    }
    va_end(list);
    return askQuestionVector(question,answers);
}
*/

std::string askQuestionVector(std::string question, 
                              std::vector<std::string> answers){
    using namespace std;
    while(true){
        string answer;
        cout << "Myro Question: " << question << endl;
        cout << "Valid Answers: " << endl;
        for (unsigned int i = 0; i < answers.size(); i++){
            cout << "   " << answers[i] << endl;
        }
        getline(cin,answer);
        //cin.ignore();
        for (unsigned int i = 0; i < answers.size(); i++){
            if (answer == answers[i])
                return answer;
        }
        cout << "Invalid Selection" << endl;
    }
}
