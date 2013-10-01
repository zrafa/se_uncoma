import socket

UDP_IP_YO = "0.0.0.0"
UDP_IP_DELOTRO = "10.0.20.100"
UDP_PORT = 5005
MENSAJE = "Gano Policia"

def comm_init():

	global sock
	sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP
	sock.bind((UDP_IP_YO, UDP_PORT))
	sock.setblocking(0)

def envio_mensaje_ganador():
	sock2 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP
	sock2.sendto(MENSAJE, (UDP_IP_DELOTRO, UDP_PORT))

def leer_mensaje():
    data = 0
    try:
        data = sock.recv(512)
    except socket.error:
        '''no data yet..'''

    return data
