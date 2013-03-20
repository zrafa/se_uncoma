/*
 * Controla los motorcitos legos via un arduino y un puente H L293D
 *
 * Original de
 * License: This is shareware but please give credit.
 * Webasite: http://techbitar.blogspot.com
 * Email: techbitar@gmail.com
 */
 
 
#ifdef __cplusplus
 extern "C" {
#endif 

#ifndef MOTORCITOS_H
#define MOTORCITOS_H

void motorcitos_init();

// MOTOR FUNCTIONS
void motorstop(int motornum);
void motorforward(int motornum);
void motorback(int motornum);
void motorspeed(int motor1speed, int motor2speed);
 
#endif /* MOTORCITOS_H */

#ifdef __cplusplus
 }
#endif 
