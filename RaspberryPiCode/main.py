"""
Operation steps in Program
declare lists,file paths

setup GPIO
pull item placement data
reset Lists
create File for data operation log
"""
import Raspberry_pi as P2L
import time as t
from os import path

Quantatity=[]#quantatity each item with index being item length should be 182 items

Lights=[]#182 bit number for all the lights
sendLights=[]#the list of 24 bit numbers to turn on lights
#File pathways
ItemListpathway='/home/pi/P2LightData/ItemList.csv'#CSV for item placement array
JSONpathway='/home/pi/P2LightData/JSONData/Order.json'#json file to pull from network
filepathway='/home/pi/P2LightData/Data/' #file to send when asked

#system set up
P2L.gpioSetup() 
P2L.pullData(ItemListpathway)
P2L.resetList(Quantatity,Lights,sendLights)

#System Log
#filename mm_dd_yy.csv
date=t.localtime(t.time())
outputDate='%d_%d_%d'%(date[1],date[2],(date[0]%100))
outputDate2='%d/%d/%d'%(date[1],date[2],(date[0]%100))
filename='%s.csv'%outputDate


#attach interrupt to getInvoice
#need to fix to state date with everytime and update 
operator='000213456'
counter=0
while(True):
    date=t.localtime(t.time())
    checkDate='%d/%d/%d'%(date[1],date[2],(date[0]%100))

    P2L.getInvoice(JSONpathway,Quantatity)
    start = t.clock()

    theSum=P2L.sendToArduinos(Lights,sendLights,Quantatity)
    print "checking"
    while(P2L.checkArduino()):
        #if counter >120:
        break
        t.sleep(0.01)
        counter+=1
    print start
    end = t.clock()
    print end
    P2L.resetArduinos(Quantatity,Lights,sendLights)
    if not(path.isfile(filepathway+filename)):
        f = open(filepathway+filename, "w")
        f.write("date(mm_dd_yyyy),operator number,items picked,time(seconds)\n")
        f.write("%s,%s,%d,%.2f, \n" % (outputDate2,operator, theSum, round((end - start),2)))
        """
        operator input comes from JSON file theSum is a summation
         of the number of items that is returned from sendToArduino function
        """       
        f.close()
    else:
        f = open(filepathway+filename, 'a') 
        f.write("%s,%s,%d,%.2f,\n" %(checkDate,operator,theSum,round((end - start),2)))
        f.close()
