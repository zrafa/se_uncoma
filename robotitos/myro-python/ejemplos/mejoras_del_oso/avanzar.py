from robot import *
from time import sleep

init()

print "Hola, "+nombre()+" te saluda"
color = input("Ingrese color buscado (BLANCO, ROJO, NEGRO): ")

for i in range(10):
	donde = buscarcolor(color)
	verfoto()
	if 70 <= donde and donde <= 90:
		adelante(.3,1)
	elif donde < 70:
		izquierda(.3,.1)
	else:
		derecha(.3,.1)
	
	sleep(5)	

