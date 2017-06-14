#!/bin/bash
newHome=/home/pi/scripts
clear

echo "Starting Script"

echo "Hi, $USER!"

sudo -s
wpa_passphrase ECD_WiFi 3CDg20!5 >> /etc/wpa_supplicant.conf
wpa_supplicant -B -D wext -i wlan0 -c /etc/wpa_supplicant.conf

sudo apt-get -y install leafpad
sudo apt-get -y install vim
sudo apt-get -y install arduino
sudo apt-get -y install ntpdate

echo "Finished"
