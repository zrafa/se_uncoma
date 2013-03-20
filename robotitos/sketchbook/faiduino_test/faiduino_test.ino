/*
 * Implementacion del protocolo de Myro (http://myro.roboteducation.org/)
 * para un robotito basado en un arduino, dos motores legos, y un puente H L293D
 *
 * http://fai.uncoma.edua.ar
 * 
 * Copyright (c) 2012-2013 Rodolfo Del Castillo
 * Copyright (c) 2012-2013 Rafael Zurita
 * 
 * Los eventos del serial : Original creado 9 May 2011 by Tom Igoe
 * The example code is in the public domain.
 * http://www.arduino.cc/en/Tutorial/SerialEvent
 */

/*#include <string.h>*/
#include <stdlib.h>
#include <protocol.h>
#include <motorcitos.h>
#define TIMEOUT 1000

int procesar_mensaje;
unsigned char *mensaje;

void setup() {

	faiduino_init();

	Serial.begin(9600);
	
        mensaje = (unsigned char *)malloc(9);
}

void loop() {
  
        if (enviar_echo) {
          sendecho(echo, 9);
          enviar_echo = 0;
        }

        if (enviar_respuesta) {
          sendanswer(respuesta, respuesta_len);
          enviar_respuesta = 0;
        }

        if (enviar_nl) {
	  sendnl();  
          enviar_nl = 0;
        }

        if (enviar_once_bytes) {
          sendanswer(once_bytes, 11);
          enviar_once_bytes = 0;
        }

        
}


void blink() {
	digitalWrite(13, HIGH);   // set the LED on
	delay(1000);              // wait for a second
	digitalWrite(13, LOW);    // set the LED offS600 
}

void sendnl() {
	Serial.write('\n');
}

void sendecho(const unsigned char *msj, int len) {
	int i;
	char val;

	for (i=0; i<len; i++) {
		val = msj[i];
		Serial.write(val);
	}
}

void sendanswer(const char *msj, int len) {
	int i;
	char val;

	for (i=0; i<len; i++) {
		val = msj[i];
		Serial.write(val);
	}
}

#define N_TIPOS 43		/* cantidad de tipos de mensajes posibles */
unsigned char tipos[N_TIPOS] = { 33, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 64, 79, 80, 81, 50, 51, 55, 56, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 119, 111, 112, 113, 114 };

/* es_codigo: devuelve 1 si unsigned char t es un codigo de mensaje valido */
int es_codigo(unsigned char t) {
	int i;

	for (i=0; i<N_TIPOS; i++)
		if (t == tipos[i])
			return 1;

	return 0;
}



/*
 * SerialEvent occurs whenever a new data comes in the
 * hardware serial RX.  This routine is run between each
 * time loop() runs, so using delay inside loop can delay
 * response.  Multiple bytes of data may be available.
 *
 * Obtenemos un mensaje y lo procesamos
 */
void serialEvent() {
  
	int i;
	char inChar;

	while (Serial.available()) {
                broadcast_name = 0;
                
		/* buscamos el inicio de un nuevo mensaje */
		inChar = (char)Serial.read();

/*		while (!es_codigo(inChar))
			inChar = (char)Serial.read();*/

		/* ha comenzado a llegar un nuevo mensaje */
		mensaje[0] = (unsigned char)inChar;

                i=1;
                while (i<9) {
        	while (Serial.available()) {	
       			inChar = (char)Serial.read();
			mensaje[i] = (unsigned char)inChar;
                        i++;
                }
                }

		break;
	}

        faiduino_procesar(mensaje);
        
}


