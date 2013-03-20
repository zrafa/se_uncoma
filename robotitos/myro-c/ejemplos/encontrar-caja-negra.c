/*
 * encontrar_caja_negra : busca un dibujo en el piso color negro.
 * Los bordes del "ambiente" deben ser color rojo.
 * Cuando encuentra el dibujo negro baila.
 *
 * Autor: Rafael Ignacio Zurita
 */

#include "MyroC.h"
#include <stdlib.h>
#include <stdio.h>
#include "faivision.h"

int main (int argc, char *argv[]) 
{
	int pn, pr;

	const char * nombre;

	rConnect("192.168.2.100");  
	faivision_init();

	while (1) {
		sleep(1);
		detectar_objetos (1, 1, 160, 120);

		pr = objeto_porc(rojo);
		pn = objeto_porc(negro);
		printf("El color rojo ocupa = %i % \n", pr);
		printf("El color negro ocupa = %i % \n", pn);
		if (pr >=10)
                        rTurnLeft(.4, .05);
		else
			rForward(.4, .05);

		if (pn >=20)
                        rTurnRight(.5, 2);
	}

  	rDisconnect();
	exit(0);


/*
	nombre = rGetName();
	printf ("El nombre del robot es : #%s#\n", nombre);
*/

  return 0;
}
