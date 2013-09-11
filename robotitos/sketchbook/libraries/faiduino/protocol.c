/*
 * Implementacion del protocolo de Myro (http://myro.roboteducation.org/)
 * para un robotito basado en un arduino, dos motores legos, y un puente H L293D
 *
 * Copyright (c) 2012-2013 Rodolfo Del Castillo
 * Copyright (c) 2012-2013 Rafael Zurita
 *
 * The files in this package are distributed under the terms of the GNU
 * General Public License (GPL), version 2. This license is included in
 * the file COPYING.GPLv2.
 * 
 */


#include "motorcitos.h";
#include "protocol.h";
#include "Arduino.h";

#define	SOFT_RESET 33

#define	GET_ALL 65 
#define	GET_ALL_BINARY 66  
#define	GET_LIGHT_LEFT 67  
#define	GET_LIGHT_CENTER 68  
#define	GET_LIGHT_RIGHT 69  
#define	GET_LIGHT_ALL 70  
#define	GET_IR_LEFT 71  
#define	GET_IR_RIGHT 72  
#define	GET_IR_ALL 73  
#define	GET_LINE_LEFT 74  
#define	GET_LINE_RIGHT 75  
#define	GET_LINE_ALL 76  
#define	GET_STATE 77  
#define	GET_NAME1 78
#define	GET_NAME2 64
#define	GET_STALL 79  
#define	GET_INFO 80  
#define	GET_DATA 81  

#define	GET_PASS1 50
#define	GET_PASS2 51

#define	SET_PASS1 55
#define	SET_PASS2 56
#define	SET_SINGLE_DATA 96
#define	SET_DATA 97
#define	SET_ECHO_MODE 98
#define	SET_LED_LEFT_ON 99 
#define	SET_LED_LEFT_OFF 100
#define	SET_LED_CENTER_ON 101
#define	SET_LED_CENTER_OFF 102
#define	SET_LED_RIGHT_ON 103
#define	SET_LED_RIGHT_OFF 104
#define	SET_LED_ALL_ON 105
#define	SET_LED_ALL_OFF 106
#define	SET_LED_ALL 107 
#define	SET_MOTORS_OFF 108
#define	SET_MOTORS 109 
#define	SET_NAME1 110 
#define	SET_NAME2 119
#define	SET_LOUD 111
#define	SET_QUIET 112
#define	SET_SPEAKER 113
#define	SET_SPEAKER_2 114


#define TIMEOUT	1000

struct faiduino_st {
	char nombre[8];
	char nombre2[8];

} faiduino;


void faiduino_init() {

	faiduino_soft_reset();
        broadcast_name = 0;
	enviar_respuesta = 0;
	enviar_echo = 0;
	enviar_nl = 0;
	enviar_once_bytes = 0;
}

static void mensaje_echo(char *res) {
	memcpy(echo, res, 9);
	enviar_echo = 1;
}

static void mensaje_espurio_once_bytes(void) {
	char res[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	memcpy(once_bytes, res, 11);
        enviar_once_bytes = 1;
}

static void mensaje_respuesta(char *res, int n) {
	memcpy(respuesta, res, n);
	respuesta_len = n;
        enviar_respuesta = 1;
}

void faiduino_set_name1(unsigned char *nombre) {
	char res[] = {SET_NAME1, 0, 0, 0, 0, 0, 0, 0, 0 };

	memcpy(faiduino.nombre, nombre, 8);
	mensaje_echo(res);
	mensaje_espurio_once_bytes();
}

void faiduino_set_name2(unsigned char *nombre) {

	char res[] = {SET_NAME2, 0, 0, 0, 0, 0, 0, 0, 0 };

	memcpy(faiduino.nombre2, nombre, 8);
	mensaje_echo(res);
	mensaje_espurio_once_bytes();
}

static void  faiduino_motores_feedback_init() {
        /* test de los motores */
        motorspeed(60, 60);
        motorback(1);
        motorback(2);        
        delay(800);
        motorstop(1);
        motorstop(2);
        delay(1000);
        motorforward(1);
        motorforward(2);        
        delay(800);
        motorstop(1);
        motorstop(2);
}

static void  faiduino_led_feedback_init() {
	int i = 0;

	for (i=0;i<5;i++) {
		digitalWrite(13, HIGH);
		delay(1000);
		digitalWrite(13, LOW);
		delay(500);
	}

	for (i=0;i<5;i++) {
		digitalWrite(13, HIGH);
		delay(200);
		digitalWrite(13, LOW);
		delay(200);
	}

}


void faiduino_soft_reset() {
	char *n = "Frankest";
	char *n2 = "ito     ";

	motorcitos_init();

	/* leds */
	pinMode(13, OUTPUT);
	pinMode(12, OUTPUT);
	/* speaker */
	pinMode(11, OUTPUT);

	faiduino_led_feedback_init();
	faiduino_motores_feedback_init();

	memcpy(faiduino.nombre, n, 8);
	memcpy(faiduino.nombre2, n2, 8);
}

void faiduino_get_all() {
	char res[] = {0, 0, 0, 0, 0, 0, 0, 0, 0 };

	mensaje_respuesta(res, 9);
}

void faiduino_get_all_binary() {
	char res[] = {0, 0, 0, 0, 0, 0, 0};
	
	mensaje_respuesta(res, 7);
	faiduino_get_all();
}

void faiduino_get_light_left() {
}

void faiduino_get_light_center() {
}

void faiduino_get_light_right() {
}

void faiduino_get_light_all() {
}

void faiduino_get_ir_left() {
}

void faiduino_get_ir_right() {
}

void faiduino_get_ir_all() {
}

void faiduino_get_line_left() {
}

void faiduino_get_line_right() {
}

void faiduino_get_line_all() {
}

void faiduino_get_state() {
}

void faiduino_get_name1() {
	char res[] = {GET_NAME1, 0, 0, 0, 0, 0, 0, 0, 0 };

	mensaje_echo(res);
	mensaje_respuesta(faiduino.nombre, 8);
	
	/* digitalWrite(13, HIGH);
	delay(1000);
	digitalWrite(13, LOW); */
}

void faiduino_get_name2() {
	char res[] = {GET_NAME2, 0, 0, 0, 0, 0, 0, 0, 0 };

	mensaje_echo(res);
	mensaje_respuesta(faiduino.nombre2, 8);
}

void faiduino_get_stall() {
}

void faiduino_get_info() {
	
	char res[] = {GET_INFO, 0, 0, 0, 0, 0, 0, 0, 0 };
	mensaje_echo(res);
        /* enviar_nl = 1; */
}

void faiduino_get_data() {
}


void faiduino_get_pass1() {
}

void faiduino_get_pass2() {
}


void faiduino_set_pass1() {
}

void faiduino_set_pass2() {
}

void faiduino_set_single_data() {
}

void faiduino_set_data() {
}

void faiduino_set_echo_mode() {
}

void faiduino_set_led_left_on() {
	digitalWrite(13, HIGH);
}

void faiduino_set_led_left_off() {
	digitalWrite(13, LOW);
}

void faiduino_set_led_center_on() {
}

void faiduino_set_led_center_off() {
}

void faiduino_set_led_right_on() {
	digitalWrite(12, HIGH);
}

void faiduino_set_led_right_off() {
	digitalWrite(12, LOW);
}

void faiduino_set_led_all_on() {
}

void faiduino_set_led_all_off() {
}

void faiduino_set_led_all() {
}


void faiduino_set_motors_off() {
	char res[] = {SET_MOTORS_OFF, 0, 0, 0, 0, 0, 0, 0, 0};

	motorstop(1);
	motorstop(2);

	mensaje_echo(res);
	mensaje_espurio_once_bytes();
}

/*
 * SET_MOTORS 	109
 * Format: 109 rightmotor leftmotor 0 0 0 0 0 0
 * Notes: 0 = full speed backwards, 100 = stop, 200 = full speed forward
 */
void faiduino_set_motors(unsigned char speed1, unsigned char speed2) {
	unsigned char m1speed;
	unsigned char m2speed;

	if (speed1 < 100)
		m1speed = (99-speed1) * 255 / 99;
	else if (speed1 > 100)
		m1speed = (speed1-101) * 255 / 99;

	if (speed2 < 100)
		m2speed = (99-speed2) * 255 / 99;
	else if (speed2 > 100)
		m2speed = (speed2-101) * 255 / 99;

	motorspeed(m1speed, m2speed);

	if (speed1 < 100) motorback(1);
	else if (speed1 > 100) motorforward(1);
	else motorstop(1);

	if (speed2 < 100) motorback(2);
	else if (speed2 > 100) motorforward(2);
	else motorstop(2);

	char res[] = {SET_MOTORS, m1speed, m2speed, speed1, speed2, 0, 0, 0, 0 };

	mensaje_echo(res);
	mensaje_espurio_once_bytes();
}


void faiduino_set_loud() {
}

void faiduino_set_quiet() {
}

void faiduino_set_speaker(unsigned char duracion, unsigned char frecuencia) {
	analogWrite(11, frecuencia);      // Almost any value can be used except 0 and 255
	delay(duracion*1000);          // wait for a delayms ms
	analogWrite(11, 0);       // 0 turns it off
}

void faiduino_set_speaker_2() {
}


/* faiduino_procesar: procesa el mensaje obtenido */
void faiduino_procesar(unsigned char *mensaje) {
	char res[] = {GET_INFO, 0, 0, 0, 0, 0, 0, 0, 0 };

	switch (mensaje[0]) {
	case SOFT_RESET:
		faiduino_soft_reset();
		break;

	case GET_ALL:
		faiduino_get_all();
		break;

	case GET_ALL_BINARY:
		faiduino_get_all_binary();
		break;
	
	case GET_LIGHT_LEFT:
	case GET_LIGHT_CENTER:
	case GET_LIGHT_RIGHT:
	case GET_LIGHT_ALL:
	case GET_IR_LEFT:
	case GET_IR_RIGHT:
	case GET_IR_ALL:
	case GET_LINE_LEFT:
	case GET_LINE_RIGHT:
	case GET_LINE_ALL:
	case GET_STATE:
		mensaje_echo(res);
		break;
	case GET_NAME1:
		faiduino_get_name1();
		break;

	case GET_NAME2:
		faiduino_get_name2();
		break;

	case GET_STALL:
		break;
	case GET_INFO:
		faiduino_get_info();
		break;

	case GET_DATA:

	case GET_PASS1:
	case GET_PASS2:

	case SET_PASS1:
	case SET_PASS2:
	case SET_SINGLE_DATA:
	case SET_DATA:
		mensaje_echo(res);
		break;
	case SET_ECHO_MODE:
		mensaje_echo(res);
		mensaje_espurio_once_bytes();
		break;
	case SET_LED_LEFT_ON:
		faiduino_set_led_left_on();
		mensaje_echo(res);
		mensaje_espurio_once_bytes();
		break;
	case SET_LED_LEFT_OFF:
		faiduino_set_led_left_off();
		mensaje_echo(res);
		mensaje_espurio_once_bytes();
		break;
	case SET_LED_CENTER_ON:
	case SET_LED_CENTER_OFF:
	case SET_LED_RIGHT_ON:
		faiduino_set_led_right_on();
		mensaje_echo(res);
		mensaje_espurio_once_bytes();
		break;
	case SET_LED_RIGHT_OFF:
		faiduino_set_led_right_off();
		mensaje_echo(res);
		mensaje_espurio_once_bytes();
		break;
	case SET_LED_ALL_ON:
	case SET_LED_ALL_OFF:
		mensaje_echo(res);
		mensaje_espurio_once_bytes();
		break;
	case SET_LED_ALL:
		mensaje_echo(res);
		mensaje_espurio_once_bytes();
		break;
	case SET_MOTORS_OFF:
		faiduino_set_motors_off();
		break;

	case SET_MOTORS:
		faiduino_set_motors(mensaje[1], mensaje[2]);
		break;

	case SET_NAME1:
		faiduino_set_name1(&mensaje[1]);
		break;

	case SET_NAME2:
		faiduino_set_name2(&mensaje[1]);
		break;

	case SET_LOUD:
	case SET_QUIET:
	case SET_SPEAKER:
	case SET_SPEAKER_2:
		faiduino_set_speaker(mensaje[1], mensaje[2]);
		mensaje_echo(res);
		mensaje_espurio_once_bytes();
		break;
	default :
		mensaje_echo(res);
		break;
	}
}

