#!/bin/sh

# Author: Kamil Rog
# This Script Installs dependencies for AgroPi application, web-server and builds application

# THIS HAS NOT BEEN TESTED

BASEDIR=$(dirname $0)
echo "Script location: ${BASEDIR}"
# Enabble I2C etc..

echo "Installing Ubuntu Packages..."
# Install all Ubuntu Packages
sudo apt-get update -y
sudo apt-get upgrade -y
sudo apt-get install git -y
sudo apt-get install cmake -y
sudo apt-get install flex -y
sudo apt-get install bison -y
sudo apt-get install libboost-all-dev -y
sudo apt-get install libi2c-dev -y
sudo apt-get install cppcheck -y
sudo apt-get install doxygen -y
sudo apt-get install graphviz -y
sudo apt-get install build-essential -y
sudo apt-get install cmake pkg-config build-essential git -y
sudo apt-get install libwebp-dev libjasper-dev libopenexr-dev libv4l-dev libavformat-dev -y 
sudo apt-get install libxvidcore-dev libx264-dev libdc1394-22-dev libgstreamer-plugins-base1.0-dev libgstreamer1.0-dev libavcodec-dev  -y
sudo apt-get install libtiff-dev libpng-dev libjpeg-dev libswscale-dev -y
sudo apt-get install libhdf5-dev libhdf5-103 -y
sudo apt-get install libgtk-3-dev libqtwebkit4 libqt4-test libqtgui4 python3-pyqt5 -y
sudo apt-get install python3-dev python3-pip python3-testresources python3-numpy -y
sudo apt-get install libcpprest-dev -y
sudo apt-get install mongodb -y
sudo apt-get install libpthread-stubs0-dev
sudo apt-get install cmake gfortran -y
sudo apt-get install libjpeg-dev libtiff-dev libgif-dev -y
sudo apt-get install libavcodec-dev libavformat-dev libswscale-dev -y
sudo apt-get install libgtk2.0-dev libcanberra-gtk* -y
sudo apt-get install libxvidcore-dev libx264-dev libgtk-3-dev -y
sudo apt-get install libtbb2 libtbb-dev libdc1394-22-dev libv4l-dev -y
sudo apt-get install libopenblas-dev libatlas-base-dev libblas-dev -y
sudo apt-get install libjasper-dev liblapack-dev libhdf5-dev -y
sudo apt-get install protobuf-compiler -y
# Web nginx server dependencies.
sudo apt install nginx -y
sudo apt-get install -y jq
sudo apt-get install libcurl4-openssl-dev -y
sudo apt-get install libfcgi-dev -y
sudo apt install nodejs -y
sudo apt install npm -y
sudo apt install curl -y
sudo npm install dygraphs -y
# OpenCV 
sudo apt install -y g++
sudo apt install -y clang
sudo apt install -y make
sudo apt install -y ninja-build
sudo apt install -y wget unzip
sudo apt install -y libatlas-base-dev liblapacke-dev gfortran
sudo apt install -y libhdf5-dev libhdf5-103
sudo apt install -y libavresample-dev
sudo apt install -y libeigen3-dev
sudo apt install -y default-jdk
sudo apt install -y libopenjpeg-dev

# Install OpenCV
echo "Installing OpenCV in ~ directory..."
cd ~
git clone https://github.com/opencv/opencv.git
git clone https://github.com/opencv/opencv_contrib.git
mkdir ~/opencv/build
cd ~/opencv/build
cmake -D CMAKE_BUILD_TYPE=RELEASE \
    -D CMAKE_INSTALL_PREFIX=/usr/local \
    -D OPENCV_EXTRA_MODULES_PATH=~/opencv_contrib/modules \
    -D ENABLE_NEON=ON \
    -D ENABLE_VFPV3=ON \
    -D BUILD_TESTS=OFF \
    -D INSTALL_PYTHON_EXAMPLES=OFF \
    -D OPENCV_ENABLE_NONFREE=ON \
    -D CMAKE_SHARED_LINKER_FLAGS=-latomic \
    -D BUILD_EXAMPLES=OFF ..

make -j$(nproc)

sudo make install
sudo ldconfig

#sudo nano /etc/dphys-swapfile (Return CONF_SWAPSIZE=2048 back to the default CONF_SWAPSIZE=100)
#sudo systemctl restart dphys-swapfile

# Back to working directory
cd BASEDIR

# Install Web Server Dependencies
echo "Installing Web Server Depenencies..."
cd BASEDIR/web
python3 -m venv venv
source venv/bin/activate
pip install -r requirements.txt
cd BASEDIR

# Build AgroPi
echo "Building AgroPi Applicaiton..."
mkdir build
cd build
cmake ..
make test ARGS="-V"  
make
echo "AgroPi Sucessfully Installed..."

# Copy nginx files to 
cd BASEDIR/src/nginx
cp nginx-sites-enabled-default /etc/nginx/site-enabled/default
# Reload nginx
sudo systemctl reload nginx

