/*
 * faivision : Minima biblioteca de vision para el robot de la fai 
 * Written 2011-2013 by Rafael Ignacio Zurita y Rodolfo del Castillo
 *
 * This package is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or 
 * (at your option) any later version.
 *
 * See the file COPYING.GPL for details.
 */

/* #include <SDL/SDL.h> */
/* #include <SDL/SDL_image.h> */
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

#include "comm.h"
#include "faivision.h"
// #include "detectar_colores.h"


enum lenguaje leng;
char * robot_ip;


extern void detectar_colores( char *archivo, int objetos[5][6]);

/*
 * indices 0-4 : colores (rojo, verde, azul, blanco, negro)
 * subindice 0-5 : estado (x, y, porcentaje, totx, toty, count)
 */
int objetos[5][6]; 
unsigned char rgb[5][3]; 

void reset_vars(void) {
	int i,j;

	for (i=0;i<5;i++) {
		for (j=0;j<5;j++) 
			objetos[i][j] = 0;
		objetos[i][5] = 1; /* count = 1 */
	}
}

void detectar_objetos(int x1, int y1, int x2, int y2) {
	
	char url[80];

	reset_vars();

	sprintf(url,"http://%s:8080/?action=snapshot", robot_ip);
	/* comm_get_http_file("http://10.0.20.201:8080/?action=snapshot", "archivo.jpg"); */
	comm_get_http_file(url, "archivo.jpg");

	detectar_colores("archivo.jpg", objetos);
}

void faivision_init(enum lenguaje l, const char *ip) {

	leng = l;

	robot_ip = strdup(ip);
	/* FIXME : deberiamos ver que sucede si strdup() falla */

}


int objeto_x(int c) {
	return objetos[c][x];
}

int objeto_y(int c) {
	return objetos[c][y];
}

int objeto_porc(int c) {
	return objetos[c][porc];
}
