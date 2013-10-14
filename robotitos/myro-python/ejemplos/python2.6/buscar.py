from robofai1 import *


def buscar(color):

	c = 0
	while (c < 40):

		detectar_objetos()
		x = buscarcolor(color)
		c = cuantocolor(color)
		print x
		print c
		
		# Si todavia no lo ve'
		if c == 0 :
			izquierda(.3, .1)

		# Si lo ve pero esta a la izq
		elif x < 40 :
			izquierda(.3, .1)

		# Si lo ve pero esta a la der
		elif x > 120 :
			derecha(.3, .1)

		# Si lo tiene en frente
		else :
			adelante(.3, .1)

		# Esperamos dos segundos para que el robot obtenga
		# la foto correcta de lo que actualmente ve.
		esperar(2)

# Encontro' el color, festejamos :
	beep(2)	
	luz_izq_on ()
	derecha(.6, 1)
	esperar(2)
	luz_izq_off ()
	izquierda(.6, 1)
