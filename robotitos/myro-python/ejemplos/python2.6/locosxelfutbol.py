from robofai2 import *
init()
import random

#init()

iz=0

def buscar(color):

#	encontrado = 0
#	while encontrado == 0:
	c=0
	while(c<40):
	#for i in range(20):

		detectar_objetos()
		x = buscarcolor(color)
		c=cuantocolor(color)
#	if x == 0:
#		if iz==0:
##			izquierda(.2)
#			iz = 1
#		continue
#	elif x < 50 :
		if x == 0:
			derecha(.3, .1)
		else :
			stop()
			izquierda(.3, .1)
			izquierda(.3, .1)
			wait(4)
			detectar_objetos()
			x = buscarcolor(color)
			c=cuantocolor(color)
			if x < 40 :
				izquierda(.3, .1)
			elif x > 120 :
				derecha(.3, .1)
			else :
				adelante(.5, .1)
			wait(1)

		iz = 0
			

#buscar(AZUL)
buscar(ROJO)
#stop()
