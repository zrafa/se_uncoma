/*
 * Implementacion del protocolo de Myro (http://myro.roboteducation.org/)
 * para un robotito basado en un arduino, dos motores legos, y un puente H L293D
 *
 * Copyright (c) 2012-2013 Rodolfo Del Castillo
 * Copyright (c) 2012-2013 Rafael Zurita
 *
 * The files in this package are distributed under the terms of the GNU
 * General Public License (GPL), version 2. This license is included in
 * the file COPYING.GPLv2.
 * 
 */

#ifdef __cplusplus
 extern "C" {
#endif 

#ifndef PROTOCOL_H
#define PROTOCOL_H

char respuesta[100];
unsigned char echo[9];
char once_bytes[11];
char respuesta_tipo;
int respuesta_len;
int broadcast_name;
int enviar_respuesta;
int enviar_once_bytes;
int enviar_ocho_bytes;
int enviar_nl;
int enviar_echo;

void faiduino_init();
void faiduino_procesar(unsigned char *mensaje);

#endif /* PROTOCOL_H */

#ifdef __cplusplus
 }
#endif 
