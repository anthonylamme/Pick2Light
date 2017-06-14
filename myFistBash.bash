#!/bin/bash
newHome=/home/pi/scripts
clear

echo "Starting Script"

echo "Hi, $USER!"

sudo apt-get -y install leafpad
sudo apt-get -y install vim
sudo apt-get -y install arduino
sudo apt-get -y install ntpdate

echo "Finished"
