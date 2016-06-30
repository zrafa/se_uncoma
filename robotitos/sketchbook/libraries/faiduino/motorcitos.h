/*
 * Controla los motorcitos legos via un arduino y un puente H L293D
 *
 * Original de
 * License: This is shareware but please give credit.
 * Webasite: http://techbitar.blogspot.com
 * Email: techbitar@gmail.com
 *
 * 
 * Copyright (c) 2012-2013 Rodolfo Del Castillo
 * Copyright (c) 2012-2013 Rafael Zurita
 *
 * The files in this package are distributed under the terms of the GNU
 * General Public License (GPL), version 2. This license is included in
 * the file COPYING.GPLv2.
 * 
 */

 
 

#ifndef MOTORCITOS_H
#define MOTORCITOS_H

void motorcitos_init();

// MOTOR FUNCTIONS
void motorstop(int motornum);
void motorforward(int motornum);
void motorback(int motornum);
void motorspeed(char motor1speed, char motor2speed);
 
#endif /* MOTORCITOS_H */

