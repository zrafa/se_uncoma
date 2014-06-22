/*
 * comm.h : curl module
 * 
 * Written 2011-2013 by Rafael Ignacio Zurita y Rodolfo del Castillo
 *
 * This package is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or 
 * (at your option) any later version.
 *
 * See the file COPYING.GPL for details.
 */


#ifndef COMM_H
#define COMM_H

void comm_init(void);
void comm_get_http_file(const char *url, const char *file);


#endif          /* COMM_H */

