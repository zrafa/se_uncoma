from robofai1 import *
import random



iz=0

def buscar(color):

	c=0
	while(c<40):

		detectar_objetos()
		x = buscarcolor(color)
		c=cuantocolor(color)
		print x
		print c
		if c == 0 :
			derecha(.3, .1)
		elif x == 0 :
			derecha(.3, .1)
		elif x < 40 :
			izquierda(.3, .1)
		elif x > 120 :
			derecha(.3, .1)
		else :
			adelante(.3, .1)

		iz = 0
		wait(2)

#Izquierda(0.5,0.5)
	beep(2)	
	luz_izq_on ()
	wait(3)
	luz_izq_off ()
