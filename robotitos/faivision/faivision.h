/*
 * faivision : Minima biblioteca de vision para el robot de la fai 
 *
 * Written 2011-2013 by Rafael Ignacio Zurita y Rodolfo del Castillo
 *
 * This package is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or 
 * (at your option) any later version.
 *
 * See the file COPYING.GPL for details.
 */


enum color {rojo, verde, azul, blanco, negro}; 
enum estado {x, y, porc, totx, toty, count}; 
enum lenguaje {python, C};

void detectar_objetos(int x1, int y1, int x2, int y2);

void faivision_init(enum lenguaje l, const char *ip);

int objeto_x(int c);		/* consultar posicion X del color c */
int objeto_y(int c);		/* consultar posicion Y del color c */
int objeto_porc(int c);		/* consultar porcentaje del color c */

/* Obsoleto */
void calibrar_color(unsigned char c);
