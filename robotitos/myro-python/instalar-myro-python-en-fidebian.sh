#!/bin/bash

# Version para FIDEBIAN

echo " - Chequeamos python 2.7"
dpkg -l python2.7 || exit 1

echo " - Instalamos paquetes basicos"
sudo apt-get -y install  git-core build-essential python-serial python-tk libsdl1.2debian libsdl1.2-dev libsdl-image1.2 libsdl-image1.2-dev libcurl3 libcurl3-gnutls libcurl3-nss libcurl4-nss-dev socat curl   unzip idle || exit 1

echo " - Bajamos el repositorio git de todo el software"
git clone https://github.com/zrafa/se_uncoma.git || exit 1

echo " - Instalamos otras dependencias necesarias para cvblob"
sudo apt-get install cmake libcv-dev libopencv-dev python-tk python-pil.imagetk


echo " - Instalamos la biblioteca cvblob"
cd se_uncoma/robotitos/faivision/cvblob/
tar xvf cvblob-0.10.4-src.tgz 
cd cvblob
cmake .
make
sudo make install


echo " - Instalamos la biblioteca de vision"
cd ../..
make clean
make
sudo make install || exit 1

echo " - Instalamos el programa de sincronizacion"
cd ../sync/
make clean
make
sudo make install || exit 1

echo " - Instalamos MyRo"
cd ../myro-python/
unzip myro-2.9.1.zip
sudo python setup.py install

echo " - Instalamos la version del scribbler.py de la FAI"
sudo cp scribbler.py /usr/local/lib/python2.7/dist-packages/myro/robots/scribbler.py







