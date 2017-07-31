# This script will allow for the SlackBot.py and the main.py to run in  parallel

#!/bin/bash -x

sudo python /home/pi/Scripts/Pick2Light/RaspberryPiCode/SLackBot/SlackBot.py  &  sudo python /home/pi/Scripts/Pick2Light/RaspberryPiCode/main.py
