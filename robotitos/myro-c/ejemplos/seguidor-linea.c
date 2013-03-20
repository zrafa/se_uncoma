/*
 * seguidor_de_linea : sigue una linea color negra
 *
 * Autor : Rafael Ignacio Zurita
 */

#include "MyroC.h"
#include <stdlib.h>
#include <stdio.h>
#include "faivision.h"

int main (int argc, char *argv[]) 
{
	int x;

	const char * nombre;

	rConnect("192.168.2.100");  
	faivision_init();
	while (1) {
		sleep(3);
		detectar_objetos (1, 60, 160, 100);

		x = objeto_x(negro);
		printf("El color negro a la x = %i \n", x);
		if ((x >=40) && (x <= 120))
			rForward(.3, .1);
                else if (x < 40)
                        rTurnLeft(.3, .05);
                else if (x > 120)
                        rTurnRight(.3, .05);

	}

  	rDisconnect();
	exit(0);


/*
	nombre = rGetName();
	printf ("El nombre del robot es : #%s#\n", nombre);
*/

  return 0;
}
