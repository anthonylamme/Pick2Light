import Raspberry_pi
import time as t
from os import path

Quantatity=[]#quantatity
Lights=[]#23 light segment
sendLights=[]#3 light values being sent
#File pathways
ItemListpathway='C:\\Users\\ECPROD\Desktop\\ProcessCompleteTesting.csv'#CSV for item array
JSONpathway='C:\\Users\\ECPROD\\Desktop\\Learning\\Example.json'    #json file to pull from network
filepathway= 'C:\\Users\\ECPROD\\Desktop\\Learning\\' 


"""
gpioSetup()
writeCommand(address,opcode,light,Quantatity,Maplights)
pullData()
resetList(Quantatity,Lights,sendLights)
getInvoice()
sendToArduinos(maplights,lights,Quantatity)
checkArduino()
resetArduino(lights,Quantatity,Maplights)
"""

gpioSetup()
pullData(ItemListpathway)
resetList()
date=t.localtime(t.time())

outputDate='%d_%d_%d',%(date[1],date[2],(date[0]%100))
filename='%s.txt'%outputDate)

#filename mm_dd_yy.txt
#attach interrupt to getInvoice
#need to fix to state date with everytime and update 


while(True):
    date=t.localtime(t.time())
    checkDate='%d_%d_%d',%(date[1],date[2],(date[0]%100))
    
    getInvoice(JSONpathway)
    start = t.clock()
    theSum=sendToArduinos(Lights,sendLights,Quantatity)
    while(checkArduino):
        t.sleep(0.01)
    end = t.clock()
    resetArduino(sendLights,Quantatity,Lights)
    if not(path.isfile(filepathway+filename)):
        f = open(filepathway+name, "w")
        f.write("%s,%d,%d,%d \n" % (outputDate,operator, theSum, (end - start))
        """
        operator input comes from JSON file theSum is a summation
         of the number of items that is returned from sendToArduino function
        """       
        f.close()
    else:
        f = open(filepathway+name, 'a') 
        f.write("%s,%d,%d,%d \n" % (checkDate, operator, (end - start), theSum,)
        f.close()