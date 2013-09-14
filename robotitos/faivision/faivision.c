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
int rgb[5][3]; 

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
		objetos[i][y] = objetos[i][toty] / objetos[i][count];
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
         * ALGUIEN QUE ENCUENTRE UNA SOLUCION
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
		else if ((r>(g+40)) && (r>(b+40)))
			actualizar_subestado(rojo, x, y);

		/* verde */
		else if ((g>(r+40)) && (g>(b+40)))
			actualizar_subestado(verde, x, y);

		/* azul */
		else if ((b>(g+40)) && (b>(r+40)))
			actualizar_subestado(azul, x, y);


	}

	actualizar_estado(x1, y1, x2, y2);

	SDL_FreeSurface(surf);
}

void calibrar_color(Uint8 c, Uint8 r, Uint8 g, Uint8 b) {
	rgb[c][rojo] = r;
	rgb[c][verde] = g;
	rgb[c][azul] = b;
	
}

void rgb_init(void) {
	int i;
	for (i=rojo;i<negro;i++)
		calibrar_color(i, 0, 0, 0) 
}

int calibrado(Uint8 c) {

	/* suponemos que si son todos iguales a cero no esta calibrado */
	if (rgb[c][rojo] == 0) && (rgb[c][verde] == 0) && (rgb[c][azul] == 0)
		return 0;

	return 1
}
int es_color(Uint8 c, Uint8 r, Uint8 g, Uint8 b) {

	if (( (r-30) > rgb[c][rojo] ) && ( rgb[c][rojo] < (r+30))) && 
	(( (g-30) > rgb[c][verde] ) && ( rgb[c][verde] < (g+30))) && 
	(( (b-30) > rgb[c][azul] ) && ( rgb[c][azul] < (b+30)))
		return 1;

	return 0;
}

void detectar_color(int x1, int y1, int x2, int y2) {
	
	Uint8 r, g, b;
	int rp, gp, bp;	/* promedios */
	Uint32 pixel;

	int x, y;
	char url[80];

	rp = 0; gp = 0; bp = 0;

	sprintf(url,"http://%s:8080/?action=snapshot", robot_ip);
	/* comm_get_http_file("http://10.0.20.201:8080/?action=snapshot", "archivo.jpg"); */
	comm_get_http_file(url, "archivo.jpg");

	SDL_Surface* surf;
	/* FIXME : no puedo abrir el archivo jpg con SDLimage por
	 * conflictos con myro-cpp :-(
         * ALGUIEN QUE ENCUENTRE UNA SOLUCION
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

	for (x=x1; x<x2; x=x+1)
	for (y=y1; y<y2; y=y+1) {
		
		pixel = getpixel(surf, x, y);
		SDL_GetRGB(pixel, surf->format, &r, &g, &b);

		rp = rp + r;
		gp = gp + g;
		bp = bp + b;
	}

	SDL_FreeSurface(surf);
	
	rp = rp / ((x2-x1)*(y2-y1));
	gp = gp / ((x2-x1)*(y2-y1));
	bp = bp / ((x2-x1)*(y2-y1));
	printf("r=%i, g=%i, b=%i.\n", rp, gp, bp);
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
         * ALGUIEN QUE ENCUENTRE UNA SOLUCION
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
		if calibrado(negro) && es_color(negro, r, g, b)
			actualizar_subestado(negro, x, y);
		else if ((r<=60) && (g<=60) && (b<=60))
			actualizar_subestado(negro, x, y);

		/* blanco */
		if calibrado(blanco) && es_color(blanco, r, g, b)
			actualizar_subestado(blanco, x, y);
		else if ((r>=150) && (g>=150) && (b>=150))
			actualizar_subestado(blanco, x, y);

		/* rojo */
		if calibrado(rojo) && es_color(rojo, r, g, b)
			actualizar_subestado(rojo, x, y);
		else if ((r>(g+40)) && (r>(b+40)))
			actualizar_subestado(rojo, x, y);

		/* verde */
		if calibrado(verde) && es_color(verde, r, g, b)
			actualizar_subestado(verde, x, y);
		else if ((g>(r+40)) && (g>(b+40)))
			actualizar_subestado(verde, x, y);

		/* azul */
		if calibrado(azul) && es_color(azul, r, g, b)
			actualizar_subestado(azul, x, y);
		else if ((b>(g+40)) && (b>(r+40)))
			actualizar_subestado(azul, x, y);

	}

	actualizar_estado(x1, y1, x2, y2);

	SDL_FreeSurface(surf);
}

void detectar_objetos(int x1, int y1, int x2, int y2) {
	
	Uint8 r, g, b;
	Uint32 pixel;

	int x, y;
	char url[80];

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
