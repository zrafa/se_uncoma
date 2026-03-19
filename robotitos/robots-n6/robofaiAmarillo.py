
from myro import *
from myro import getName as nombre
from myro import forward as adelante, backward as atras
from myro import turnLeft as izquierda, turnRight as derecha
import subprocess
import Image

vision = ""
robot = ""
ROJO=0
VERDE=1
AZUL=2
BLANCO=3
NEGRO=4

PYTHON=0

def nmOff():
	subprocess.call(["/etc/init.d/network-manager", "stop"])

def nmOn():
	subprocess.call(["/etc/init.d/network-manager", "start"])

def netOn():
	# subprocess.call(["/sbin/iwconfig", "wlan0","essid","robotsfai"])
	# subprocess.call(["/sbin/ifconfig", "wlan0","10.0.20.5"])
	subprocess.call(["/sbin/ifconfig", "br0:1","10.0.20.5"])
	#subprocess.call(["/bin/ping", "-c 4", "192.168.2.100"])

def lsterms():
	return subprocess.Popen(["ls", "/dev/pts"], stdout=subprocess.PIPE).communicate()[0]

def spawnSocat():
	import os
	from subprocess import Popen
	# socat_cmd = "socat pty,raw,echo=0 tcp:192.168.2.100:2000"
	socatBin = "/usr/bin/socat"
	socatCmd = [socatBin,"pty,raw,echo=0","tcp:10.0.20.220:2000"]
	p = subprocess.Popen(socatCmd)
	wait(2)
	return p.pid

def killallSocat():
	subprocess.call(["/usr/bin/killall", "socat"])
	

def synch():
	return subprocess.Popen(["duino_sync", "10.0.20.220"])
	
	
def faivision():
	import ctypes
	global vision
	vision = ctypes.CDLL("/usr/local/lib/libfaivision.so")
	vision.faivision_init(PYTHON, "10.0.20.220")

def foto():
	url = "http://10.0.20.220:8080?action=snapshot"
	img = "snapshot.png"
	urllib.urlretrieve(url,img)
	
def verfoto(): 
	foto()
	img = Image.open("snapshot.png")
	img.show()

def detectar_objetos():
	vision.detectar_objetos (1, 1, 160, 120) 

def calibrar_color(color):
	vision.calibrar_color(color)

def buscarcolor(color):
	return vision.objeto_x(color)

def cuantocolor(color):
	return vision.objeto_porc(color)
	
def luz_izq_on():
	setLED("left", "on")

def luz_izq_off():
	setLED("left", "off")

def luz_der_on():
	setLED("right", "on")

def luz_der_off():
	setLED("right", "off")

def bipbip():
	beep(.3, .29)
	beep(.3, .29)

def parpadear():
	for i in range(3):
		luz_izq_on()
		luz_der_on()
		wait(.3)
		luz_izq_off()
		luz_der_off()
		wait(.3)


def init():
#	nmOff()
#	netOn()
	killallSocat()

	# sincronizamos y esperamos
	synchOutput = synch()
	wait(4)

	# print "SYNCH ",synchOutput
	terms_before = lsterms()
	socatPid = spawnSocat()
	# print "socat pid = ",socatPid
	terms_after = lsterms()
	# print "TERMS BEFORE ",terms_before
	# print "TERMS AFTER ",terms_after
	socat_term = ''
	terms_before_w = terms_before.split()
	terms_after_w = terms_after.split()
	for t in terms_after_w:
		# print  t
		if not t in terms_before_w:
			socat_term = "/dev/pts/%d" % (int(t))
	print "SOCAT_TERM ",socat_term
	global robot
	robot = Scribbler(socat_term)
	robot.getName()
	faivision()
	print "FUNCIONES"
	print "nombre(),"
	print "adelante(.3,.2), atras(.3,.2),"
	print "derecha(.3,.2), izquierda(.3,.2),"
	print "foto(), verfoto(),"
	print "buscarcolor(COLOR), cuantocolor(COLOR)"
	print "ROJO, VERDE, AZUL, BLANCO, NEGRO"


# init()
# robot.setLED("left", "on")

# end
# wait(5)
# robot.setLED("left", "off")
# killallSocat()
