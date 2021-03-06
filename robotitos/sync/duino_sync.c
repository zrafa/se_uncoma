/* Simple Ejemplo que sincroniza con el robot de la FAI */

/*
 *
 * Copyright (c) 2012-2013 Rodolfo Del Castillo
 * Copyright (c) 2012-2013 Rafael Zurita
 *
 * The files in this package are distributed under the terms of the GNU
 * General Public License (GPL), version 2. This license is included in
 * the file COPYING.GPLv2.
 * 
 */


/* 
 * Sincronizar es "conversar" con el robot (con el atmega8), para que
 * el robot se posicione a la espera del primer byte de un nuevo paquete con
 * instrucciones.
 */

/* 
 * Este sync consulta dos veces el nombre al robot. Si en el primer
 * intento, el robot estaba en un estado "indefinible", recién
 * a la segunda consulta de su nombre quedará en correcta sintonia.
 */

/* 
 * Testeado en Debian
 * Robot con placa Linux tp-link mr3020
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

#include <unistd.h>
#include <fcntl.h>


int main (int argc, char *argv[]) {

	int sockfd;
	int len;
	struct sockaddr_in address;
	int res, i;

	if (argc != 2) {
		printf("Uso: robot_sync IP_ADDRESS\n");
		exit(1);
	}

	/*  Crear socket cliente */
    	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	/*  Socket local */
	address.sin_family = AF_INET;
	/* address.sin_addr.s_addr = inet_addr("10.0.20.201"); */
	address.sin_addr.s_addr = inet_addr(argv[1]);
	address.sin_port = htons(2000);
	len = sizeof(address);

	/*  Conectamos el socket con el socket del servidor */
	res = connect(sockfd, (struct sockaddr *)&address, len);
	if (res == -1) {
		perror("oops: client3");
		exit(1);
	}

	printf("Cliente conectado : %i. Esperamos un momento ...\n", sockfd);

		usleep(51400);
	/*  Leemos y escribimos al servidor 2 net */

	char getname[9] = {0x4e, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
	char echo[9];
	char respuesta[8];

	int ok = 0;

	int flags;
	flags = fcntl(sockfd, F_GETFL, 0); /* get current file status flags */
	flags |= O_NONBLOCK;		/* turn off blocking flag */
	fcntl(sockfd, F_SETFL, flags);		/* set up non-blocking read */

	for (i=0;i<2;i++)	/* queremos ejecutar el siguiente while dos
				 * veces para estar seguros que sincronizamos pidiendo el nombre
				 */
	printf("Enviando y recibiendo : ");
	while (1) {

		usleep(51400);
		printf(".");	 /* Intentando escribir (send) */

		res = write(sockfd, &getname[0], 1);
		if (res == -1) {
			printf("Problema al escribir. Finalizando la ejecucion ...\n");
			ok = 1;
			break;
		}
		usleep(51400);

		printf(".");	/* Intentando leer (receive) */
		res = read(sockfd, &echo[0], 1);
		if (res == -1)
			printf(".");	/* Todavia NO recibimos el byte */
		else {
			printf(".");	/* Hemos recibido un byte */

			res = read(sockfd, &echo[1], 8);
			if (res == 8) {
				printf(".");	/* Recibimos los 8 que faltaban.. saliendo */
				printf ("\nRespuesta : %s .", &echo[0]);
				printf(".");	/* Nos las jugamos a leer 8 mas */
				res = read(sockfd, &respuesta[0], 8);

				printf ("\nRespuesta : %s\n", &respuesta[0]);
				ok = 0;
			} else {
				printf("\nNo recibimos los 8 que faltaban. Recibimos: %i. Saliendo..\n", res);
				ok = 1;
			}
			break;
		}
	}

	close(sockfd);
	exit(ok);
}
