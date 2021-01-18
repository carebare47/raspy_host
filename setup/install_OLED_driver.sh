#!/bin/bash
direc=$(pwd)
mkdir oled
cd oled
wget http://wiki.52pi.com/images/9/9b/1306-0.91-CODE.zip
unzip 1306-0.91-CODE.zip
sudo apt-get install -y build-essential git-core libi2c-dev i2c-tools lm-sensors && echo "i2c-bcm2708
i2c-dev" #| sudo tee /etc/modules
cd 1306-0.91-CODE
sudo make
