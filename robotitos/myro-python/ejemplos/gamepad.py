
from myro import *

robotito = Scribbler("/dev/pts/3")
wait(5)
robotito.stop()
while 1: robotito.move(*getGamepad("robot"))
