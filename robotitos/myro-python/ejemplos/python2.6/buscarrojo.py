from robofai2 import *
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
		elif x < 40 :
			izquierda(.2, .1)
		elif x > 120 :
			derecha(.2, .1)
		else :
			adelante(.3, .1)

		iz = 0
		wait(2)
			

#buscar(AZUL)
#buscar(ROJO)
#stop()
