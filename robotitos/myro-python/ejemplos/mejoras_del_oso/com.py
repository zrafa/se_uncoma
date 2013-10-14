import socket

UDP_IP_YO = "0.0.0.0"
UDP_PORT = 5005

def comm_init():

	global sock
	sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP
	sock.bind((UDP_IP_YO, UDP_PORT))
	sock.setblocking(0)

def envio_mensaje_ganador(ip, mensaje):
	sock2 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP
	sock2.sendto(mensaje, (ip, UDP_PORT))

def leer_mensaje():
    data = 0
    try:
        data = sock.recv(512)
    except socket.error:
        '''no data yet..'''

    return data
