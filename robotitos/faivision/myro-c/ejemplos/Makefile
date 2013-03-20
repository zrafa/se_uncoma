all:
	gcc -o motor -L/usr/local/lib -lmyro-cpp /usr/local/lib/MyroC.o motor.c
	gcc -o motor2 -L/usr/local/lib -lmyro-cpp -lfaivision /usr/local/lib/MyroC.o motor2.c
	gcc -o detectar-bordes-rojos -L/usr/local/lib -lmyro-cpp -lfaivision /usr/local/lib/MyroC.o detectar-bordes-rojos.c
	gcc -o encontrar-caja-negra -L/usr/local/lib -lmyro-cpp -lfaivision /usr/local/lib/MyroC.o encontrar-caja-negra.c
	gcc -o seguidor-linea -L/usr/local/lib -lmyro-cpp -lfaivision /usr/local/lib/MyroC.o seguidor-linea.c

clean:
	rm motor motor2 detectar-bordes-rojos encontrar-caja-negra seguidor-linea
