import json
import os
import time
"""
sleep 30s; shutdown -h now
"""
path="wow"
def ShutDownOp(seconds=0):
    time.sleep(seconds)
    os.system("shutdown now -h")
def RestartOp(seconds=0):
    time.sleep(seconds)
    os.system("shutdown -r -t 1")
def sendData(path):
    
