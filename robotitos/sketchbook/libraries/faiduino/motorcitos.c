/*
 * Controla los motorcitos legos via un arduino y un puente H L293D
 *
 * Original de
 * License: This is shareware but please give credit.
 * Webasite: http://techbitar.blogspot.com
 * Email: techbitar@gmail.com
 */
 
#include <Arduino.h>

/* map motor poles to Arduino pins */
#define motor1pole1 2
#define motor1pole2 3
#define motor2pole1 6
#define motor2pole2 7
   
/* map L293d motor enable pins to Arduino pins */
#define enablePin1 9
#define enablePin2 10
   
#define M1_MAX_SPEED 255
#define M2_MAX_SPEED 255
   
#define motordelay 30

void motorcitos_init() {

	/* 
	 * set mapped L283D motor1 and motor 2 enable pins on Arduino to output
	 * (to turn on/off motor1 and motor2 via L293D)
	 */
	pinMode(enablePin1, OUTPUT);
	pinMode(enablePin2, OUTPUT);
  
	/* set mapped motor poles to Arduino pins (via L293D) */
	pinMode(motor1pole1, OUTPUT);
	pinMode(motor1pole2, OUTPUT);
	pinMode(motor2pole1, OUTPUT);
	pinMode(motor2pole2, OUTPUT);
	motorspeed(0, 0);
	motorstop(2);
	motorstop(1);
}  
   

/* MOTOR FUNCTIONS */
void motorstop(int motornum) {
	delay(motordelay);
	if (motornum == 1) {
		digitalWrite(motor1pole1, LOW);
		digitalWrite(motor1pole2, LOW);
	} else if (motornum == 2) {
		digitalWrite(motor2pole1, LOW);
		digitalWrite(motor2pole2, LOW);
  	}
  	delay(motordelay);
}
   

void motorforward(int motornum) {
	if (motornum == 1) {
		digitalWrite(motor1pole1, HIGH);
		digitalWrite(motor1pole2, LOW);
	} else if (motornum == 2) {
		digitalWrite(motor2pole1, LOW);
		digitalWrite(motor2pole2, HIGH);
	}
	delay(motordelay);
}
   

void motorback(int motornum) {
	if (motornum == 1) {
		digitalWrite(motor1pole1, LOW);
		digitalWrite(motor1pole2, HIGH);
	} else if (motornum == 2) {
		digitalWrite(motor2pole1, HIGH);
		digitalWrite(motor2pole2, LOW);
	}
	delay(motordelay);
}
   

void motorspeed(int motor1speed, int motor2speed) {

	if (motor1speed > M1_MAX_SPEED) motor1speed = M1_MAX_SPEED; /* limit top speed */
	if (motor2speed > M2_MAX_SPEED) motor2speed = M2_MAX_SPEED; /* limit top speed */
	/* El robot actual no puede ir a menos de velocidad==30, por el peso */
	if (motor1speed < 35) motor1speed = 35; /* keep motor speed above 0 */
	if (motor2speed < 35) motor2speed = 35; /* keep motor speed above 0 */
	/* if (motor1speed < 0) motor1speed = 0; */ /* keep motor speed above 0 */
	/* if (motor2speed < 0) motor2speed = 0; */ /* keep motor speed above 0 */

	analogWrite(enablePin1, motor1speed);
	analogWrite(enablePin2, motor2speed);
} 

