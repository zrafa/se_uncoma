/*
 * Controla los motorcitos legos via un arduino y un puente H L293D
 *
 * Original de
 * License: This is shareware but please give credit.
 * Webasite: http://techbitar.blogspot.com
 * Email: techbitar@gmail.com
 *
 * Copyright (c) 2012-2013 Rodolfo Del Castillo
 * Copyright (c) 2012-2013 Rafael Zurita
 *
 * The files in this package are distributed under the terms of the GNU
 * General Public License (GPL), version 2. This license is included in
 * the file COPYING.GPLv2.
 * 
 */

 
#include <Arduino.h>

#include <DCMotor.h>

// DCMotor motor0(M0_EN, M0_D0, M0_D1);
// DCMotor motor1(M1_EN, M1_D0, M1_D1);

extern DCMotor motor0;
extern DCMotor motor1;

//#define NUEVA_PLACA_LD293 1

//#ifdef NUEVA_PLACA_LD293

/* map motor poles to Arduino pins */
#define motor1pole1 4 // 2
#define motor1pole2 5 // 3
#define motor2pole1 7 // 6
#define motor2pole2 8 // 7
   
/* map L293d motor enable pins to Arduino pins */
#define enablePin1 3 // 9

#define enablePin2 6 // 10


//#else /* La vieja placa LD93 */

/* map motor poles to Arduino pins */
//#define motor1pole1 2
//#define motor1pole2 3
//#define motor2pole1 6
//#define motor2pole2 7
   
/* map L293d motor enable pins to Arduino pins */
//#define enablePin1 9
//#define enablePin2 10
   
//#endif


#define M1_MAX_SPEED 255
#define M2_MAX_SPEED 255
   
#define motordelay 30

   

/* MOTOR FUNCTIONS */
void motorstop(int motornum) {
#ifdef FAIDUINO_ORIGINAL
	delay(motordelay);
	if (motornum == 1) {
		digitalWrite(motor1pole1, LOW);
		digitalWrite(motor1pole2, LOW);
	} else if (motornum == 2) {
		digitalWrite(motor2pole1, LOW);
		digitalWrite(motor2pole2, LOW);
  	}
  	delay(motordelay);
#else
	if (motornum == 1)
		motor0.brake();
	else
		motor1.brake();
#endif
	
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
   

void motorspeed(char motor1speed, char motor2speed) {

#ifdef FAIDUINO_ORIGINAL
	if (motor1speed > M1_MAX_SPEED) motor1speed = M1_MAX_SPEED; /* limit top speed */
	if (motor2speed > M2_MAX_SPEED) motor2speed = M2_MAX_SPEED; /* limit top speed */
	/* El robot actual no puede ir a menos de velocidad==30, por el peso */
	if (motor1speed < 35) motor1speed = 35; /* keep motor speed above 0 */
	if (motor2speed < 35) motor2speed = 35; /* keep motor speed above 0 */
	/* if (motor1speed < 0) motor1speed = 0; */ /* keep motor speed above 0 */
	/* if (motor2speed < 0) motor2speed = 0; */ /* keep motor speed above 0 */

	analogWrite(enablePin1, motor1speed);
	analogWrite(enablePin2, motor2speed);
#else
	if (motor1speed == 0)
		motor0.brake();
	else
		motor0.setSpeed(motor1speed);

	if (motor2speed == 0)
		motor1.brake();
	else
		motor1.setSpeed(motor2speed);

#endif

} 

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
