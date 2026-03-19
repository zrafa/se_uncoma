
from robofaiAzul import *
init()
import random


iz=0

def buscar(color):
  while(True):
	c=0
	while(c<40):

		detectar_objetos()
		x = buscarcolor(color)
		c=cuantocolor(color)
		if x == 0:
			derecha(.5, .1)
		else :
	#		stop()
	#		izquierda(.5, .1)
	#		izquierda(.5, .1)
			wait(.5)
			detectar_objetos()
			x = buscarcolor(color)
			c=cuantocolor(color)
			if x < 40 :
				izquierda(.5, .1)
			elif x > 120 :
				derecha(.5, .1)
			else :
				adelante(.5, .1)
			wait(.2)

		iz = 0
			

#buscar(AZUL)
buscar(ROJO)
#stop()

