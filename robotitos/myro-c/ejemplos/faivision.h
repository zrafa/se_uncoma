/*
 * faivision : Minima biblioteca de vision para el robot de la fai 
 * Rafael Ignacio Zurita
 */

enum color {rojo, verde, azul, blanco, negro}; 
enum estado {x, y, porc, totx, toty, count}; 

void detectar_objetos(int x1, int y1, int x2, int y2);

void faivision_init(void);

int objeto_x(int c);
int objeto_y(int c);
int objeto_porc(int c);
