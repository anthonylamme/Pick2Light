# -*- coding: utf-8 -*-
#Python Client for Slack
#to shutdown os.system("shutdown now -h")
#to restart 
#send file

import re
import os
import time
import json
import psutil
import BotOps as OPS

from slackclient import SlackClient

P2L_Token="xoxb-218658603927-YryWXgMNzDkKZh6pNMOFgwl6"
myName="pick2light_test2"
path="/home/pi/Scripts/RoboticArmCode/RpiAddtion/Bash/Data/test.csv"
slack_client =SlackClient(P2L_Token)

user_list = slack_client.api_call("users.list")
for user in user_list.get('members'):
    if user.get('name') == myName:
        slack_user_id = user.get('id')
        break
    
if slack_client.rtm_connect():
    print "Connected"
    
    while True:
        for message in slack_client.rtm_read():
            if 'text' in message and message['text'].startswith("<@%s>"%slack_user_id):
                
                print "Message received: %s" % json.dumps(message, indent=2)
                
                message_text = message['text'].\
                    split("<@%s>" % slack_user_id)[1].\
                    strip()

                if re.match(r'.*(shutdown).*', message_text, re.IGNORECASE):

                    slack_client.api_call(
                        "chat.postMessage",
                        channel=message['channel'],
                        text="\n shutting down in 10 secs",
                        as_user=True)
                    
                    OPS.ShutDownOp(10)
                    
                if re.match(r'.*(restart).*',message_text,re.IGNORECASE):

                    slack_client.api_call(
                        "chat.postMessage",
                        channel=message['channel'],
                        text="\n Restarting in 10 secs",
                        as_user=True)
                    
                    OPS.RestartOp(10)
                          
                if re.match(r'.*(send).*',message_text,re.IGNORECASE):

                    slack_client.api_call(
                        "chat.postMessage",
                        channel=message['channel'],
                        text="\n Sending Report",
                        as_user=True)

                    slack_client.api_call(
                        "files.upload",
                        channels=message['channel'],
                        file=open(path,'rb'),
                        filename='test.csv',
                        filetype='auto',
                        initail_comment='\n Here you go')
                          
                if re.match(r'.*(cpu).*',message_text,re.IGNORECASE):

                    cpu_pct=psutil.cpu_percent(interval=1,percpu=False)
                    
                    slack_client.api_call(
                        "chat.postMessage",
                        channel=message['channel'],
                        text="\n My CPU is at %s%%."%cpu_pct,
                        as_user=True)
                          
                if re.match(r'.*(memory|ram).*',message_text,re.IGNORECASE):

                    mem=psutil.virtual_memory()
                    mem_pct =mem.percent
                    
                    slack_client.api_call(
                        "chat.postMessage",
                        channel=message['channel'],
                        text="\n My memory is at %s%%."%mem_pct,
                        as_user=True)
                          
                if re.match(r'.*(temperature).*',message_text,re.IGNORECASE):
                    
                    file_object  = open('/sys/class/thermal/thermal_zone0/temp', 'r') 
                    temp=file_object.read(2)

                    slack_client.api_call(
                        "chat.postMessage",
                        channel=message['channel'],
                        text="\n My temperature is at %s."%temp,
                        as_user=True)
                          
                if re.match(r'.*(help).*',message_text,re.IGNORECASE):
                    
                    slack_client.api_call(
                        "chat.postMessage",
                        channel=message['channel'],
                        text="\n Always happy to help\n Type: shutdown to shutdown \n Type: restart to restart\n Type: send to recieve report\n Type: CPU to recieve percent of CPU used\n Type: memory or ram to recieve percent of ram used\n Type: temperture to recieve temperture data \n cancel to cancel shutdown",
                        as_user=True)
                    
                if re.match(r'.*(cancel).*',message_text,re.IGNORECASE):

                    slack_client.api_call(
                        "chat.postMessage",
                        channel=message['channel'],
                        text="\n cancelling previous shutdown/restart",
                        as_user=True)

                    OPS.CancelOp()    
            time.sleep(1)
