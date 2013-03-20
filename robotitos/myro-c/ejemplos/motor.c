/* * * * *
 * Test de conexion con el robot. Autor : Rafael Ignacio Zurita
 */

#include "MyroC.h"
#include <stdlib.h>
#include <stdio.h>

int 
main()
{
	const char * nombre;

	rConnect("192.168.2.100");  

        rForward(.6,1);
	sleep(1);
	rStop();

	nombre = rGetName();
	printf ("El nombre del robot es : #%s#\n", nombre);

	exit(0);
}
