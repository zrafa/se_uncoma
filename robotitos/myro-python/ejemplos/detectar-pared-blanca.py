from myro import *

def fun():
	adelante(.1)
	movimiento = 1
	while(1):
		detectar_objetos ()
		a = cuantocolor(BLANCO)
		if a > 25 :
			stop()
			wait(1)
			atras(.3, .2)
			wait(1)
			izquierda(.3, .2)
			movimiento = 0
			wait(3)
		elif movimiento == 0:
			movimiento = 1
			adelante(.1)
			
		wait(.5)


import ctypes
vision = ctypes.CDLL("/usr/local/lib/libfaivision.so")
vision.faivision_init()

ro = Scribbler("/dev/pts/15")
fun()
