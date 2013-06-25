/*
 * faivision : Minima biblioteca de vision para el robot de la fai 
 * Rafael Ignacio Zurita
 */

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

#include "comm.h"
#include "faivision.h"


enum lenguaje leng;
char * robot_ip;

/*
 * Return the pixel value at (x, y)
 * NOTE: The surface must be locked before calling this!
 */
Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *(Uint32 *)p;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}


/*
 * indices 0-4 : colores (rojo, verde, azul, blanco, negro)
 * subindice 0-5 : estado (x, y, porcentaje, totx, toty, count)
 */
int objetos[5][6]; 

void reset_vars(void) {
	int i,j;

	for (i=0;i<5;i++) {
		for (j=0;j<5;j++) 
			objetos[i][j] = 0;
		objetos[i][5] = 1; /* count = 1 */
	}
}

void actualizar_subestado(int i, int x, int y) {

	objetos[i][totx] = objetos[i][totx] + x;
	objetos[i][toty] = objetos[i][toty] + y;
	objetos[i][count]++;
}

void actualizar_estado(int x1, int y1, int x2, int y2) {

	int i;

	for (i=rojo;i<=negro;i++) {
		/* printf(" i=%i, objetos count : %i\n", i, objetos[i][count]); */
		objetos[i][x] = objetos[i][totx] / objetos[i][count];
		objetos[i][y] = objetos[i][toty ]/ objetos[i][count];
		objetos[i][porc] = objetos[i][count] * 100 / ((x2-x1)/2*(y2-y1)/2);

	}
}

void detectar_objetos(int x1, int y1, int x2, int y2) {
	
	Uint8 r, g, b;
	Uint32 pixel;

	int x, y;
	char url[80];

	reset_vars();

	sprintf(url,"http://%s:8080/?action=snapshot", robot_ip);
	/* comm_get_http_file("http://10.0.20.201:8080/?action=snapshot", "archivo.jpg"); */
	comm_get_http_file(url, "archivo.jpg");

	SDL_Surface* surf;
	/* FIXME : no puedo abrir el archivo jpg con SDLimage por
	 * conflictos con myro-cpp :-(
	 */
	if (leng == C) {
		system("convert archivo.jpg archivo.bmp");
		surf = SDL_LoadBMP("archivo.bmp");
	} else
		surf = IMG_Load("archivo.jpg");

	if (surf == NULL) {
		printf("Oh My Goodness, an error : %s", IMG_GetError());
		exit(1);
	}

	for (x=x1; x<x2; x=x+2)
	for (y=y1; y<y2; y=y+2) {
		
		pixel = getpixel(surf, x, y);
		SDL_GetRGB(pixel, surf->format, &r, &g, &b);

		/* negro */
		if ((r<=60) && (g<=60) && (b<=60))
			actualizar_subestado(negro, x, y);

		/* blanco */
		else if ((r>=120) && (g>=120) && (b>=120))
			actualizar_subestado(blanco, x, y);

		/* rojo */
		else if ((r>=160) && (g<=120) && (b<=120))
			actualizar_subestado(rojo, x, y);

		/* verde */
		else if ((r<=120) && (g>=160) && (b<=120))
			actualizar_subestado(verde, x, y);

		/* azul */
		else if ((r<=120) && (g<=120) && (b>=160))
			actualizar_subestado(azul, x, y);


	}

	actualizar_estado(x1, y1, x2, y2);

	SDL_FreeSurface(surf);
}


void faivision_init(enum lenguaje l, const char *ip) {

    /* Initialize the SDL library */
    if( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        fprintf(stderr,
                "Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    /* Clean up on exit */
    atexit(SDL_Quit);
	signal(SIGINT, SIG_DFL);

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
