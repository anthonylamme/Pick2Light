
"""
This Script will be the script that will be running the arduinos with the
Raspberry PI. It will be using I2C communication with Arduino's 1 through Eight
It will be using a usb Scanner to scan barcodes and send data to the network
The network will send a JSON file to the Pi which the Pi will determine which
Arduinos will be used.
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
##Pin Definitions
bus=smbus.SMBus(1)
GPIO.setmode(GPIO.BOARD)

##arduino addresses
arduinoAddresses=[0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x10]
arduinoStatus=[8,10,12,16,18,22,24,26]
itemList=[]
#bitmask for lighting
bitmask=[0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80]
#opcodes for arduino
turnOn=0x01#turn on lights
turnOff=0x00#reset lights


def gpioSetup():
    GPIO.setup(arduinoStatus,GPIO.IN)
"""
writes to Arduinos, needs address of arduino and the opcode that will be sent
input: address and operation code
output: Void
"""
def writeCommand(address,opcode,light=[],item=[],Maplights=[]):
    bus.write_byte(address,opcode)
    for x in range(0,len(lights)):
        bus.write_byte(address,lights[x])
    for y in range(0,len(item)):
        bus.write_byte(address,item[y])
    for x in range(0,2):
        lights[x]=0
    for x in range(0,23):
        Maplights[x]=0

"""
Pulls information into itemList on location of items
input:file path to file
output:void
"""
def pullData(path):
    with open(path) as f:
        reader = csv.reader(f,delimiter=',')
        for row in reader:
            for j in range(0,C):
                itemList.append(int(row[j]))

"""
Resets Lists to create and sent to zero
"""
def resetList(Quantatity=[],Lights=[],sendLights=[]):
    if(len(Quantatity)>0):
        for x in range(0,len(itemList)):
            Quantatity[x]=0
    else:
        for y in range(0,len(itemList)):
            Quantatity.append(0)
    if(len(Lights)>0):
        for x in range(0,23):
            Lights[x]=0
    else:
        for y in range(0,23):
            Lights.append(0)
    if(len(sendLights)>0):
        for x in range(0,2):
            sendLights[x]=0
    else:
        for y in range(0,2):
            sendLights.append(0)
"""
This function will pull information from JSON file to place into Quantatity list
Input: File path for JSON file
Output: Void
"""
def getInvoice(path2):
    with open(path2) as f:
        data = json.load(f)
    for r in data['Inventory']:
        Quantatity[itemList.index(r['item'])]=r['quant']
"""
Sends information to arduinos to turn lights on
"""
def sendToArduinos(Lights=[],sendLights=[],Quantatity=[]):
    #A1
    theSum=0
    count=0
    index=0
    shift=0
    for x in range(0,23):
        if Quantatity[x]>0:
            theSum=theSum+Quantatity[x]
            Lights[count]=1
            sendLights[index]+=Lights[count]<<shift
        else:
            Lights[count]=0
            sendLights[index]+=Lights[count]<<shift
        count+=1
        shift+=1
        if(shift>7):
            index+=1
            shift=0
    writeCommand(arduinoAddresses[0],turnOn,sendLights,Quantatity,Lights)
    #A2

    count=0
    index=0
    shift=0
    for x in range(26,49):
        if Quantatity[x]>0:
            theSum=theSum+Quantatity[x]
            Lights[count]=1
            sendLights[index]+=Lights[count]<<shift
        else:
            Lights[count]=0
            sendLights[index]+=Lights[count]<<shift
        count+=1
        shift+=1
        if(shift>7):
            index+=1
            shift=0
    writeCommand(arduinoAddresses[1],turnOn,sendLights,Quantatity,Lights)
    #A3
    count=0
    index=0
    shift=0
    for x in range(52,75):
        if Quantatity[x]>0:
            theSum=theSum+Quantatity[x]
            Lights[count]=1
            sendLights[index]+=Lights[count]<<shift
        else:
            Lights[count]=0
            sendLights[index]+=Lights[count]<<shift
        count+=1
        shift+=1
        if(shift>7):
            index+=1
            shift=0
    writeCommand(arduinoAddresses[2],turnOn,sendLights,Quantatity,Lights)
    #A4
    index=0
    shift=0
    count=0
    for x in range(78,101):
        if Quantatity[x]>0:
            theSum=theSum+Quantatity[x]
            Lights[count]=1
            sendLights[index]+=Lights[count]<<shift
        else:
            Lights[count]=0
            sendLights[index]+=Lights[count]<<shift
        count+=1
        shift+=1
        if(shift>7):
            index+=1
            shift=0
    writeCommand(arduinoAddresses[3],turnOn,sendLights,Quantatity,Lights)
    #A5
    index=0
    shift=0
    count=0
    for x in range(104,127):
        if Quantatity[x]>0:
            theSum=theSum+Quantatity[x]
            Lights[count]=1
            sendLights[index]+=Lights[count]<<shift
        else:
            Lights[count]=0
            sendLights[index]+=Lights[count]<<shift
        count+=1
        shift+=1
        if(shift>7):
            index+=1
            shift=0
    writeCommand(arduinoAddresses[4],turnOn,sendLights,Quantatity,Lights)
    #A6
    index=0
    shift=0
    count=0
    for x in range(130,153):
        if Quantatity[x]>0:
            theSum=theSum+Quantatity[x]
            Lights[count]=1
            sendLights[index]+=Lights[count]<<shift
        else:
            Lights[count]=0
            sendLights[index]+=Lights[count]<<shift
        count+=1
        shift+=1
        if(shift>7):
            index+=1
            shift=0
    writeCommand(arduinoAddresses[5],turnOn,sendLights,Quantatity,Lights)
    #A7
    index=0
    shift=0
    count=0
    for x in range(156,180):
        if Quantatity[x]>0:
            theSum=theSum+Quantatity[x]
            Lights[count]=1
            sendLights[index]+=Lights[count]<<shift
        else:
            Lights[count]=0
            sendLights[index]+=Lights[count]<<shift
        count+=1
        shift+=1
        if(shift>7):
            index+=1
            shift=0
    writeCommand(arduinoAddresses[6],turnOn,sendLights,Quantatity,Lights)
    index=0
    shift=0
    count=0
    #A8
    ctr = 24
    for x in range(0,7):
        if (Quantatity [ctr]>0):
            theSum=theSum+Quantatity[ctr]
            Lights[x] = 1
            sendLights[0]+=Lights[x]<<x
        else:
            Lights[x] = 0
            sendLights[0]+=Lights[x]<<x
        if ctr % 2 == 0:
            ctr+=1
        else:
            ctr+=25
    ctr=128
    index=8
    for x  in range(0,7):
        if(ctr<=182):
            if (Quantatity [ctr]>0):
                theSum=theSum+Quantatity[ctr]
                Lights[index] = 1
                sendLights[1]+=Lights[index]<<x
            else:
                Lights[index] = 0
                sendLights[1]+=Lights[index]<<x
            if ctr % 2 == 0:
                ctr+=1
            else:
                ctr+=25
        else:
            Lights[index] = 0
            sendLights[1]+=Lights[index]<<x
        index+=1
    writeCommand(arduinoAddresses[7],turnOn,sendLights,Quantatity,Lights)
    return theSum
"""
Checks Arudino if items are picked
"""
def checkArduino():
    count=0
    for x in range(0,len(arduinoStatus)):
        if GPIO.input(arduinoStatus[x]):
            count+=1
    if count==8:
        return True
    else:
        return False
def resetArduinos(lights=[],item=[],Maplights=[]):
    for x in range(0,len(arduinoAddresses)):
        writeCommand(arduinoAddresses[x],turnOff,lights,item,Maplights)
    resetList(item,Maplights,lights)
