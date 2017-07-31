import Raspberry_pi as P2L
import time as t
from os import path

Quantatity=[]#quantatity
Lights=[]#23 light segment
sendLights=[]#3 light values being sent
#File pathways
ItemListpathway='/home/pi/P2LightData/ItemList.csv'#CSV for item array
JSONpathway='/home/pi/P2LightData/JSONData/Order.json'#json file to pull from network
filepathway='/home/pi/P2LightData/Data' #file to send when asked

"""
Step Process:

gpioSetup()
writeCommand(address,opcode,light,Quantatity,Maplights)
pullData()
resetList(Quantatity,Lights,sendLights)
getInvoice()
sendToArduinos(maplights,lights,Quantatity)
checkArduino()
resetArduino(lights,Quantatity,Maplights)
"""

P2L.gpioSetup()
P2L.pullData(ItemListpathway)
P2L.resetList()
date=t.localtime(t.time())

outputDate='%d_%d_%d'%(date[1],date[2],(date[0]%100))
filename='%s.csv'%outputDate

#filename mm_dd_yy.txt
#attach interrupt to getInvoice
#need to fix to state date with everytime and update 


while(True):
    date=t.localtime(t.time())
    checkDate='%d_%d_%d'%(date[1],date[2],(date[0]%100))
    
    P2L.getInvoice(JSONpathway)
    start = t.clock()
    theSum=P2L.sendToArduinos(Lights,sendLights,Quantatity)
    while(P2L.checkArduino):
        t.sleep(0.01)
    end = t.clock()
    P2L.resetArduino(sendLights,Quantatity,Lights)
    if not(path.isfile(filepathway+filename)):
        f = open(filepathway+name, "w")
        f.write("%s,%d,%d,%d, \n" % (outputDate,operator, theSum, (end - start)))
        """
        operator input comes from JSON file theSum is a summation
         of the number of items that is returned from sendToArduino function
        """       
        f.close()
    else:
        f = open(filepathway+name, 'a') 
        f.write("%s,%d,%d,%d,\n" %(checkDate,operator,theSum,(end - start)))
        f.close()
