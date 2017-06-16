#!/bin/bash
newHome=/home/pi/scripts

echo "Starting Script"

echo "Hi, $USER! starting network"
#networking


# install programs
echo "Hi, $USER! starting install"
sudo apt-get -y install leafpad
sudo apt-get -y install vim
sudo apt-get -y install arduino
sudo apt-get -y install ntpdate
~
~
~
echo "Finished"
sleep 20
sudo reboot