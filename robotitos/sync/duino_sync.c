/* Simple Ejemplo utilizando sockets con ser2net para enviar mensajes al robot */

/* Este programa le consulta al robot su nombre, y luego hace forward(1,2) */

/* 
 * Testeado en Debian
 * Robot con bluetooth
 * Debian PC configurado con el bluetooth viendo el robot
 * ser2net instalado en Debian
 *   configuracion de ser2net en Debian : cat /etc/ser2net.conf
 *   2000:raw:666:/dev/rfcomm0:9600 8DATABITS NONE -XONXOFF -RTSCTS
 * Reiniciamos ser2net /etc/init.d/ser2net restart
 * Ejecutamos este programa
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


int main(void) {

	int sockfd;
	int len;
	struct sockaddr_in address;
	int res, i;

	/*  Crear socket cliente */
    	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	/*  Socket local */
	address.sin_family = AF_INET;
	// address.sin_addr.s_addr = inet_addr("192.168.2.100");
	address.sin_addr.s_addr = inet_addr("10.0.20.201");
	address.sin_port = htons(2000);
	len = sizeof(address);

	/*  Conectamos el socket con el socket del servidor */
	res = connect(sockfd, (struct sockaddr *)&address, len);
	if (res == -1) {
		perror("oops: client3");
		exit(1);
	}

	printf("Cliente iniciado : %i. Esperamos 8 segundos\n", sockfd);

		usleep(51400);
	/*  Leemos y escribimos al servidor 2 net */

	char getname[9] = {0x4e, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
	char echo[9];
	char respuesta[8];

	int ok = 0;
	int no_salir = 1;

	int flags;
	flags = fcntl(sockfd, F_GETFL, 0); /* get current file status flags */
	flags |= O_NONBLOCK;		/* turn off blocking flag */
	fcntl(sockfd, F_SETFL, flags);		/* set up non-blocking read */

	for (i=0;i<2;i++)	/* queremos ejecutar el siguiente while dos
				 * veces para estar seguros que sincronizamos pidiendo el nombre
				 */
	while (1) {

		usleep(51400);
			printf("Tratamos de escribir. \n");

		res = write(sockfd, &getname[0], 1);
		if (res == -1) {
			printf("Problema al escribir. Salgo..\n");
			ok = 1;
			break;
		}
		usleep(51400);

			printf("Tratamos de leer 1. \n");
		res = read(sockfd, &echo[0], 1);
		if (res == -1)
			printf("Todavia NO recibimos el byte\n");
		else {
			printf("Recibi 1\n");

			res = read(sockfd, &echo[1], 8);
			if (res == 8) {
				printf("Recibi los 8 que faltaban.. saliendo\n");
				printf ("Respuesta : %s\n", &echo[0]);
				printf("Nos las jugamos a leer 8 mas \n");
				res = read(sockfd, &respuesta[0], 8);

				printf ("Respuesta : %s\n", &respuesta[0]);

				ok = 0;
				break;
			} else {
				printf("No recibimos los 8 que faltaban. Recibimos: %i. Saliendo..\n", res);
				ok = 1;
				break;
			}
		}
	}

	close(sockfd);
	exit(ok);
}
