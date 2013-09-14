
import subprocess

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
	socatCmd = [socatBin,"pty,raw,echo=0","tcp:10.0.20.203:2000"]
	p = subprocess.Popen(socatCmd)
	#wait(2)
	return p.pid

def killallSocat():
	subprocess.call(["/usr/bin/killall", "socat"])
	


def synch():
	return subprocess.Popen(["duino_sync", "10.0.20.203"])
	
	
def flashing(pts):
	subprocess.call(["avrdude", "-C/etc/avrdude.conf", "-v", "-v", "-v", "-v", "-patmega8", "-carduino", "-P"+pts, "-b19200", "-D", "-Uflash:w:faiduino_test.cpp.hex:i"])


def init():
#	nmOff()
#	netOn()
	killallSocat()

	# sincronizamos y esperamos
	# synchOutput = synch()
	#wait(1)

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



	flashing(socat_term);


# init()
# robot.setLED("left", "on")

# end
# wait(5)
# robot.setLED("left", "off")
# killallSocat()
