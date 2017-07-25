#Python Client for Slack
#to shutdown os.system("shutdown now -h")
#to restart 
#send file
import re
import os
import time
import json

import BotsOps

from slackclient import SlackClient

#P2L_Token="token2"
#Alarm_Token="token1"
myName="alarmclock"

slack_client =SlackClient(P2L_Token)

user_list = slack_client.api_call("user.list")
for user in user_list.get('members'):
    if user.get('name')== myName:
        slack_user_id = user.get('id')
        break
if slack_client.rtm_connect();
    print "Connected"
    
    while True:
        for message in slack_client.rtm_read():
            if 'text' in message and message['text'].startswith("<@%s>"%slack_user_id):
                
                print "Message received: %s" % json.dumps(message, indent=2)
                
                message_text=message['text'].\
                    split("<@%s>" %slack_user_id[1].\
                    strip()
                if re.match(r'.*(shutdown).*',message_text,re.IGNORECASE);
                    slack_client.api_call(
                        "chat.postMessage",
                        channel=message['channel'],
                        text="Message recieved: Shutting down"
                        as_user =True)
                    ShutDownOp(10);
                    
                if re.match(r'.*(restart).*',message_text,re.IGNORECASE);
                    slack_client.api_call(
                        "chat.postMessage",
                        channel=message['channel'],
                        text="Message recieved: Restarting in 10 secs"
                        as_user =True)
                     RestartOps(10);
                if re.match(r'.*(send).*',message_text,re.IGNORECASE);
                    slack_client.api_call(
                        "chat.postMessage",
                        channel=message['channel'],
                        text="Sending Report"
                        as_user =True)
                        SendDataOp(path
            time.sleep(1)