/* serial.cpp : conexion para BT, modificado para usar una conexion TCP 
 * Written by Rafael Ignacio Zurita <rafa@fi.uncoma.edu.ar>
 */

#include "serial.h"
#include <termios.h>
#include <stdio.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string>



#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define DEBUG 1

serial::serial(int baudrate, int block_read) {
	fd = -1;
	this->baudrate = baudrate;
	this->blocking = block_read;
}

serial::~serial() {
}

int serial::connect_serial(const char * device) {
	int len, res;


	/*  Crear socket cliente */
    	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	/*  Socket local */
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(device);
	address.sin_port = htons(2000);
	len = sizeof(address);

	/*  Conectamos el socket con el socket del servidor */
	res = connect(sockfd, (struct sockaddr *)&address, len);
	if (res == -1) {
		perror("oops: client3");
		return res;
	}

	if (DEBUG) printf("Cliente iniciado : %i. Esperamos 10 segundos\n", sockfd);
	sleep(10);

	int flags;
	flags = fcntl(sockfd, F_GETFL, 0); /* get current file status flags */
	flags |= O_NONBLOCK;		/* turn off blocking flag */
	fcntl(sockfd, F_SETFL, flags);		


        char getname[9] = {0x4e, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
        char echo[9];
        char respuesta[8];

        int nosync = 1;
        int no_salir = 1;

        while (nosync) {

		printf("Sincronizando.. Esperar\n");
		printf("Tratamos de escribir. ");

                res = write(sockfd, &getname[0], 1);
		usleep(55000);
                if (res == -1) {
                        printf("Problema al escribir. ..\n");
			continue;
                }

		printf("Tratamos de leer 1. ");

                res = read(sockfd, &echo[0], 1);
		usleep(55000);
                if (res == -1)
                        printf("Todavia NO recibimos el byte\n");
                else {
                        printf("Recibi 1\n");

                        res = read(sockfd, &echo[1], 8);
			usleep(55000);
                        if (res == 8) {
                                printf("Recibi los 8 que faltaban.. saliendo\n");
                                printf ("Respuesta : %s\n", &echo[0]);
                                printf("Nos las jugamos a leer 8 mas ");
                                res = read(sockfd, &respuesta[0], 8);
				usleep(55000);

                                printf ("Respuesta : %s\n", &respuesta[0]);

                                if (!strncmp(respuesta,"Frankest", 8)) nosync = 0;
                        } else {
                                printf("No recibimos los 8 que faltaban. Recibimos: %i. ..\n", res);
                        }
                }
        }

	return res;
}

void serial::disconnect() {
	close(sockfd);
	fd = -1;
}

int serial::_write(unsigned char * buf, int bytes) {
	int tmp;
	int res = 0;

	printf("buf[0]=%d \n", buf[0]);

	for(; res < bytes; ) {
		printf("1 reswrite = %i bytes = %i\n", res, bytes);
		tmp = res;
		res += write(sockfd, buf + res, bytes - res);
		usleep(55000);
		printf("2 reswrite = %i bytes = %i\n", res, bytes);
		if (res == -1) res = tmp;
		printf("3 reswrite = %i bytes = %i\n", res, bytes);
	}

	return res;
}

int serial::_read(unsigned char * buf, int bytes) {

	int tmp;
	int res = 0;

	for(; res < bytes; ) {
		printf("1 res = %i bytes = %i\n", res, bytes);
		tmp = res;
		res += read(sockfd, buf + res, bytes - res);
		usleep(55000);
		printf("2 res = %i bytes = %i\n", res, bytes);
		if (res == -1) res = tmp;
		printf("3 res = %i bytes = %i\n", res, bytes);
	}

	return res;
}

void serial::flush_input() {
	if (DEBUG) printf("test flush \n");
}

void serial::flush_output() {
	if (DEBUG) printf("test flush  output \n");
}
