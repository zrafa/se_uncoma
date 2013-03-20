
from myro import *
from myro import getName as nombre
from myro import forward as adelante, backward as atras
from myro import turnLeft as izquierda, turnRight as derecha
import subprocess
import Image

faivisionlib = ""
ROJO=0
VERDE=1
AZUL=2
BLANCO=3
NEGRO=4


def nmOff():
	subprocess.call(["/etc/init.d/network-manager", "stop"])

def nmOn():
	subprocess.call(["/etc/init.d/network-manager", "start"])

def netOn():
	subprocess.call(["/sbin/iwconfig", "wlan0","essid","OpenWrt"])
	subprocess.call(["/sbin/ifconfig", "wlan0","192.168.2.101"])
	#subprocess.call(["/bin/ping", "-c 4", "192.168.2.100"])

def lsterms():
	return subprocess.check_output(["ls", "/dev/pts"])

def spawnSocat():
	import os
	from subprocess import Popen
	# socat_cmd = "socat pty,raw,echo=0 tcp:192.168.2.100:2000"
	socatBin = "/usr/bin/socat"
	socatCmd = [socatBin,"pty,raw,echo=0","tcp:192.168.2.100:2000"]
	p = subprocess.Popen(socatCmd)
	return p.pid

def synch():
	return subprocess.check_output(["./getname"])
	
def faivision():
	import ctypes
	global faivisionlib
	faivisionlib = ctypes.CDLL("/usr/local/lib/libfaivision.so")
	faivisionlib.faivision_init()

def foto():
	url = "http://192.168.2.100:8080?action=snapshot"
	img = "snapshot.png"
	urllib.urlretrieve(url,img)
	
def verfoto(): 
	foto()
	img = Image.open("snapshot.png")
	img.show()

def buscarcolor(color):
	faivisionlib.detectar_objetos (1, 1, 160, 120) 
	return faivisionlib.objeto_x(color)

def cuantocolor(color):
	faivisionlib.detectar_objetos (1, 1, 160, 120) 
	return faivisionlib.objeto_porc(color)
	
def init():
	nmOff()
	netOn()
	synchOutput = synch()
	#print "SYNCH ",synchOutput
	terms_before = lsterms()
	socatPid = spawnSocat()
	#print "socat pid = ",socatPid
	terms_after = lsterms()
	#print "TERMS BEFORE ",terms_before
	#print "TERMS AFTER ",terms_after
	socat_term = ''
	for t in terms_after:
		if not t in terms_before:
			socat_term = "/dev/pts/%d" % (int(t))
	#print "SOCAT_TERM ",socat_term
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
	return robot



