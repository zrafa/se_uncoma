import ctypes
from myro import *

# Nos conectamos al robot
robot = Scribbler("/dev/pts/23")

# Faivision
l = ctypes.CDLL('/usr/local/lib/libfaivision.so')
l.faivision_init()

# Tomamos una foto y la analizamos
l.detectar_objetos (1, 1, 160, 120)
l.objeto_porc(3)       # Consultamos el color blanco
83                      # 83% de la foto es de color blanco
l.objeto_x(3)       # Consultamos el "centro" del color blanco
120                     # El centro en X es el pixel 120 

# Consultando el Nombre
robot.getName()
Frankestito

# Moviendo el robot
robot.forward(2, .5)

# Haciendo beep durante 3 segundos
robot.beep(3, 20)

# Encendiendo el led de la izquierda
robot.setLED("left", "on")


quit()
