
"""
This Script will be the script that will be running the arduinos with the
Raspberry PI. It will be using I2C communication with Arduino's 1 through Eight
It will be using a usb Scanner to scan barcodes and send data to the network
The network will send a JSON file to the Pi which the Pi will determine which
Arduinos will be used.

Need:
pull JSON file function

"""
#GPIO2=SDA1 PIN3
#GPIO3=SCL1 PIN5

#GPIO14=A1 PIN8
#GPIO15=A2 PIN10
#GPIO18=A3 PIN12
#GPIO23=A4 PIN16
#GPIO24=A5 PIN18
#GPIO25=A6 PIN22
#GPIO8=A7 PIN24
#GPIO7=A8 PIN26

#PIN2=5V
#PIN1=3.3v
#PIN14=GROUND
import smbus
import RPi.GPIO as GPIO##Runs GPIO
import csv
import json##Library to handle Json files
import time as t

ROWS=7 #number of rows to consider
COLUMNS=26 #number of columns to consider
NUMBER_MCP=3
##Pin Definitions
bus=smbus.SMBus(1)
GPIO.setmode(GPIO.BOARD)


##arduino addresses
arduinoAddresses=[0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x10]#arduino slave addresses
arduinoStatus=[8,10,12,16,18,22,24,26]#status pins when set high mean arduino is finished
itemList=[]#placement list

#bitmask for lighting
bitmask=[0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80]

#opcodes for arduino
turnOn=0x01#turn on lights
turnOff=0x00#reset lights

"""
This function sets up the General Purpose Pins on the Raspberry PI to be input
these pins are used to see that status of the Arduinos while they are running
"""
def gpioSetup():
    GPIO.setup(arduinoStatus,GPIO.IN)
"""
Pulls information into itemList on location of items
input:file path to file
output:void
"""
def pullData(path):
    #print 'Pulling Layout'
    with open(path,'rb') as f:
        reader = csv.reader(f,delimiter=',')
        for row in reader:
            for j in range(0,COLUMNS):
                itemList.append(row[j])
    #print itemList
"""
Resets Lists to create and sent to zero
input: three lists that need to reset
output: none
"""
def resetList(Quantatity=[],Lights=[],sendLights=[]):
    #print 'reseting Lists'
    #print len(Quantatity)
    if(len(Quantatity)>0):
        for x in range(0,len(itemList)):
            Quantatity[x]=0
    else:
        for y in range(0,len(itemList)):
            Quantatity.append(0)
    if(len(Lights)>0):
        for x in range(0,len(itemList)):
            Lights[x]=0
    else:
        for y in range(0,len(itemList)):
            Lights.append(0)
    if(len(sendLights)>0):
        for x in range(0,NUMBER_MCP):
            sendLights[x]=0
    else:
        for y in range(0,NUMBER_MCP):
            sendLights.append(0)
    #print 'Quant'
    #print Quantatity
    #print 'Lights'
    #print Lights
    #print 'sendLights'
    #print sendLights
"""
This function will pull information from JSON file to place into Quantatity list
Input: File path for JSON file and List to have the amount placed in
Output: Void
"""
def getInvoice(path2,Quantatity=[]):
    #print 'getting Invoice'
    #print path2
    
    data = json.load(open(path2))
    #print data
    #print ''
    for r in data['Inventory']:
        #print itemList.index('%s'%r['item'])
        Quantatity[itemList.index('%s'%r['item'])]=r['quant']
    #print Quantatity
"""
Sends information to arduinos to turn lights on
input:  Three lists:
        First being the quantatiy of each item in the cell
        Second being the 24 bit number for the light
        Third being the list of 24 bit numbers for the lights
output: Sum of all items on list
"""
def sendToArduinos(Lights=[],sendLights=[],Quantatity=[]):
    #print 'starting send ARDUINO'
    A8 = [24,25,50,51,76,77,102,103,128,129,154,155,180,181]
    items = [0,0,0,0,0,0,0]
    send8Lights=[0,0,0]
    theSum = 0
    index = 0
    shift = 0
    
    index8 = 0
    shift8 = 0
    i = 0
    j = 0
    items[0]=Quantatity[0:23]
    #print len(items[0])
    items[1]=Quantatity[26:49]
    #print len(items[1])
    items[2]=Quantatity[52:75]
    #print len(items[2])
    items[3]=Quantatity[78:101]
    #print len(items[3])
    items[4]=Quantatity[104:127]
    #print len(items[4])
    items[5]=Quantatity[130:153]
    #print len(items[5])
    items[6]=Quantatity[156:179]
    #print len(items[6])
    items.append(A8)
    #print len(items[7])
    for x in range(0,len(Quantatity)):
        #print 'x: %s'%x
        if x not in A8:
            if Quantatity[x] > 0:
                theSum += Quantatity[x]
                Lights[x] = 1
                sendLights[index] += Lights[x] << shift
            else:
                Lights[x] = 0
                sendLights[index] += Lights[x] << shift
            print sendLights[index]
            shift += 1
            if shift > 7:
                index += 1
                shift = 0
            if index == 3:
                index = 0
                writeCommand(arduinoAddresses[i],turnOn,sendLights,items[i])
                i+=1
        else:
            if Quantatity[x] > 0:
                theSum += Quantatity[x]
                items[7][j]=Quantatity[x]
                j+=1
                Lights[x] = 1
                send8Lights[index8] += Lights[x] << shift8
            else:
                items[7][j]=Quantatity[x]
                j+=1
                Lights[x] = 0
                send8Lights[index8] += Lights[x] << shift8
            shift8 += 1
            #print send8Lights[index8]
            if shift > 7:
                index8 += 1
                shift8 = 0
                
    writeCommand(arduinoAddresses[7],turnOn,send8Lights,items[7])
    #print items
    
    #print theSum
    
    return theSum
"""
This function resets Arduinos and Lists to be ready for next order
input:  Three lists:
        First being the quantatiy of each item in the cell
        Second being the 24 bit number for the light
        Third being the list of 24 bit numbers for the lights
output: Void
        
"""
def resetArduinos(item=[],lights=[],sendLights=[]):
    #print 'starting reset ARDUINO'
    for x in range(0,len(arduinoAddresses)):
        writeCommand(arduinoAddresses[x],turnOff,lights,item)
    resetList(item,lights,sendLights)
"""
writes to Arduinos, needs address of arduino and the opcode that will be sent
input: address and operation code
output: Void
"""
def writeCommand(address,opcode,lights=[],item=[]):
    #print 'write command for %s'%address
    #print opcode
    #print lights
    #print item
    print 'Opcode %s: %s'%(address,opcode)
    #bus.write_byte(address,opcode)
    t.sleep(0.2)
    for x in range(0,len(lights)):
        print 'Lights %s: %s'%(address,lights[x])
        #bus.write_byte(address,lights[x])
        #t.sleep(0.2)
    for y in range(0,len(item)):
        print 'Quantatity %s: %s for item %s'%(address,item[y],y)
        #bus.write_byte(address,item[y])
        #t.sleep(0.2)
    for x in range(0,NUMBER_MCP):
        lights[x]=0

"""
Checks Arudino if items are picked
"""
def checkArduino():
    #print 'checking'
    count=0
    for x in range(0,len(arduinoStatus)):
        if GPIO.input(arduinoStatus[x]):
            count+=1
    if count==8:
        #print 'all inputs'
        return False
    else:
        #print 'no inputs'
        return True
