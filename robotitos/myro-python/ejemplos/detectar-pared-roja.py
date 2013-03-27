from myro import *

def fun():
	ro.forward(.1)
	movimiento = 1
	while(1):
		vision.detectar_objetos (1, 1, 160, 120)
		a = vision.objeto_porc(0)
		if a > 20 :
			ro.stop()
			wait(3)
			ro.turnLeft(.3, .5)
			movimiento = 0
			wait(3)
		elif movimiento == 0:
			movimiento = 1
			ro.forward(.1)
			
		wait(.5)


import ctypes
vision = ctypes.CDLL("/usr/local/lib/libfaivision.so")
vision.faivision_init()

ro = Scribbler("/dev/pts/3")
fun()
