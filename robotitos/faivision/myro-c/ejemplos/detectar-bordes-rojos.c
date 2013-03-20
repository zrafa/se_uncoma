/* * * * *
 * detectar_bordes_rojos : mueve el robot dentro de un ambiente delimitado
 * por un borde color rojo.
 *
 * Autor: Rafael Ignacio Zurita
 */

#include "MyroC.h"
#include <stdlib.h>
#include <stdio.h>
#include "faivision.h"

int main (int argc, char *argv[]) 
{
	int p;

	const char * nombre;

	rConnect("192.168.2.100");  
	faivision_init();
	while (1) {
		sleep(3);
		detectar_objetos (1, 1, 160, 120);

		p = objeto_porc(rojo);
		printf("El color ocupa = %i % \n", p);
		if (p >=20)
                        rTurnLeft(.4, .05);
		else
			rForward(.4, .05);
	}

  	rDisconnect();
	exit(0);


/*
	nombre = rGetName();
	printf ("El nombre del robot es : #%s#\n", nombre);
*/

  return 0;
}
