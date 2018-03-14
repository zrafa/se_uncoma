#!/bin/bash
#Script para la instalación de Myro en FIDebian y Debian Testing testeado al 14-03-18.
#El siguiente script instala las librerias necesarias para que funcione Myro correctamente, permitiendo la conexión de la computadora
# con cualquier robot de arquitectura Frankestito, así como permite la conexión con el simulador.

echo " - Chequeamos python 2.7"
dpkg -l python2.7 || exit 1

echo " - Instalamos paquetes basicos"
apt-get -y install  git-core build-essential python-serial python-tk \
	libsdl1.2debian libsdl1.2-dev libsdl-image1.2 libsdl-image1.2-dev \
	libcurl3 libcurl3-gnutls libcurl3-nss libcurl4-nss-dev socat curl   \
	unzip idle-python2.7|| exit 1

echo " - Bajamos el repositorio git de todo el software"
git clone https://github.com/zrafa/se_uncoma.git || exit 1

echo " - Instalamos MyRo"
cd se_uncoma/robotitos/myro-python/
unzip myro-2.9.1.zip
python setup.py install








