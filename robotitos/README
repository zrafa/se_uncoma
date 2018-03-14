# FRANKESTITO: RoboFAI

 En la Facultad de Informática en la Universidad Nacional del Comahue (UNCo) estamos desarrollando prototipos de robots educativo con visión autónomos, compatibles con  Myro. Además, a diferencia de la mayoría de los robots de bajo costo existentes compatibles con Myro, nuestra implementación cuenta con Linux embebido dentro del robot. Esto posibilita ejecutar, por ejemplo, python o prolog directamente dentro del robot.

Myro (My Robotics), es un proyecto open source que tiene como objetivo enseñar ciencias de la computación a través de la programación de robots con Python. Mas información en  Introduction to Computer Science via Robots

La metas principales son :

    Construir Robots Educativos adaptables
    Publicar el Software (firmware, software embebido, software de control, etc) como Software Libre
    Publicar la documentación de la electrónica como Open Hardware
    Enseñar la arquitectura y la programación de los Robots
    Difundir las experiencias 

Los Robots Educativos son muy utilizados actualmente, ya que se utilizan como recurso en varias disciplinas y proyectos :

    Como recurso en la difusión de la computación en las escuelas medias;
    De incentivo en el aprendizaje de la programación;
    Como recurso para ayudar a revertir la deserción universitaria;
    Como recurso para verificar en ambientes reales los desarrollos de los Grupos de Investigación en Inteligencia Artificial.
    Como elemento académico para el aprendizaje de temas de los Sistemas Embebidos. 

Caraterísticas del Robot Educativo :

    Primitivas de Movimiento básicas que permiten construir movimientos mas complejos. Utilizando Myro se potencia la libertad de movimiento con programación en alto nivel.
    Visión (sensado) del mundo a través de una Camara. Puede Hacer streaming de Video y procesar la Vision.
    Feedback a través de leds y parlante. 


## Mas Información

Para mayor información sobre el proyecto, puede dirigirse a: http://se.fi.uncoma.edu.ar/robots/

### Instalación

La instalación basica para controlar los robots de esta arquitectura (por ejemplo si usted participa de algún proyecto de extensión de la Facultad de Informática) puede encontrar el script de instalación dentro del directorio raíz bajo el nombre de "instalacion-myro.sh".

Si lo que busca es información para el armado de un robot, la instalación del linux y sus archivos fuentes, los directorios se encuentran organizados de acuerdo al hardware involucrado.

#Comentarios internos del proyecto

Para bajar el consumo de energía del Linux mr3020
http://www.techrepublic.com/blog/opensource/using-iwconfig-to-configure-settings-on-wireless-cards/3573


Para flashear el tplink
socat pty,raw,echo=0 tcp:10.0.20.201:2000
avrdude -C/etc/avrdude.conf -v -v -v -v -patmega8 -carduino -P/dev/pts/5 -b19200 -D -Uflash:w:eco_serial.hex:i
