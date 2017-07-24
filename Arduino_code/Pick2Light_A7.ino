#include <Pick2Light.h>

#define SCL1 8
#define SDA1 7
#define SCL2 4
#define SDA2 2
#define SCL3 6
#define SDA3 5

#define STATUS1 12

Pick2Light check= Pick2Light(SDA1,SCL1,SDA2,SCL2,SDA3,SCL3);

#define LISTSIZE 24
int ItemList[LISTSIZE];

#define bitmask1 0x01
#define bitmask2 0x02
#define bitmask3 0x04
#define bitmask4 0x08
#define bitmask5 0x10
#define bitmask6 0x20
#define bitmask7 0x40
#define bitmask8 0x80

uint8_t old1 = 0x00;
uint8_t old2 = 0x00;
uint8_t old3 = 0x00;

void setup() {
  // put your setup code here, to run once:
  check.begin();
  pinMode(STATUS1, OUTPUT);
  digitalWrite(STATUS1, LOW);
  for (int i = 0; i < LISTSIZE; i++) {
    ItemList[i] = 0;
  }
  Wire.begin(A7);
  Wire.onReceive(recieveMasterCommand);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t new1 = check.readGPIO(1,MCP23017_ADDR[0]);
  uint8_t new2 = check.readGPIO(1,MCP23017_ADDR[1]);
  uint8_t new3 = check.readGPIO(1,MCP23017_ADDR[2]);

  if (old1 != new1) {
    old1 = new1;
    new1 = 0;
    if (old1 & bitmask1) {
      Buttons(0);
    }
    else if (old1 & bitmask2) {
      Buttons(1);
    }
    else if (old1 & bitmask3) {
      Buttons(2);
    }
    else if (old1 & bitmask4) {
      Buttons(3);
    }
    else if (old1 & bitmask5) {
      Buttons(4);
    }
    else if (old1 & bitmask6) {
      Buttons(5);
    }
    else if (old1 & bitmask7) {
      Buttons(6);
    }
    else if (old1 & bitmask8) {
      Buttons(7);
    }
  }
  if (old2 != new2) {
    old2 = new2;
    new2 = 0;
    if (old2 & bitmask1) {
      Buttons(8);
    }
    else if (old2 & bitmask2) {
      Buttons(9);
    }
    else if (old2 & bitmask3) {
      Buttons(10);
    }
    else if (old2 & bitmask4) {
      Buttons(11);
    }
    else if (old2 & bitmask5) {
      Buttons(12);
    }
    else if (old2 & bitmask6) {
      Buttons(13);
    }
    else if (old2 & bitmask7) {
      Buttons(14);
    }
    else if (old2 & bitmask8) {
      Buttons(15);
    }
  }
  if (old3 != new3) {
    old3 = new3;
    new3 = 0;
    if (old3 & bitmask1) {
      Buttons(16);
    }
    else if (old3 & bitmask2) {
      Buttons(17);
    }
    else if (old3 & bitmask3) {
      Buttons(18);
    }
    else if (old3 & bitmask4) {
      Buttons(19);
    }
    else if (old3 & bitmask5) {
      Buttons(20);
    }
    else if (old3 & bitmask6) {
      Buttons(21);
    }
    else if (old3 & bitmask7) {
      Buttons(22);
    }
    else if (old3 & bitmask8) {
      Buttons(23);
    }
  }
  writeToDisplay();
  sendStatus();
  delay(100);
}
void recieveMasterCommand() {
  uint8_t opcode = Wire.read();
  uint8_t lights1 = Wire.read();
  uint8_t lights2 = Wire.read();
  uint8_t lights3 = Wire.read();

  for (int i = 0; i < LISTSIZE; i++) {
    ItemList[i] = Wire.read();
  }

  switch (opcode) {
    //clears Lights
    case 0x00: {
        clearEverything();
        break;
      }
    //turnlights on that need to be turned on
    case 0x01: {
        turnOnLights(lights1, lights2, lights3);
        break;
      }
  }
}
//status:complete
void turnOnLights(uint8_t lights1, uint8_t lights2, uint8_t lights3) {
  check.writeGPIOAB(lights1,MCP23017_ADDR[0]);//maybe << 8
  check.writeGPIOAB(lights2,MCP23017_ADDR[1]);
  check.writeGPIOAB(lights3,MCP23017_ADDR[2]);
}
//status not complete
void sendStatus() {
  //port A is Buttons (0)
  if (check.readGPIO(0,MCP23017_ADDR[0]) == 0 && check.readGPIO(0,MCP23017_ADDR[1]) == 0 && check.readGPIO(0,MCP23017_ADDR[2]) == 0) {
    digitalWrite(STATUS1, HIGH);
    while(1){}
  }
  else{
    digitalWrite(STATUS1, LOW);
  }
  
}
//status:Complete
void clearEverything() {
  check.writeGPIOAB(0x00,MCP23017_ADDR[0]);
  check.writeGPIOAB(0x00,MCP23017_ADDR[1]);
  check.writeGPIOAB(0x00,MCP23017_ADDR[2]);
  for (int i = 0; i < LISTSIZE; i++) {
    ItemList[i] = 0;
  }
  digitalWrite(STATUS1, LOW);
}

void turnOffLight(int i) {
  switch (i) {
    case 0: {
        check.digitalWrite(0, LOW,MCP23017_ADDR[0]);
        break;
      }
    case 1: {
        check.digitalWrite(1, LOW,MCP23017_ADDR[0]);
        break;
      }
    case 2: {
        check.digitalWrite(2, LOW,MCP23017_ADDR[0]);
        break;
      }
    case 3: {
        check.digitalWrite(3, LOW,MCP23017_ADDR[0]);
        break;
      }
    case 4: {
        check.digitalWrite(4, LOW,MCP23017_ADDR[0]);
        break;
      }
    case 5: {
        check.digitalWrite(5, LOW,MCP23017_ADDR[0]);
        break;
      }
    case 6: {
        check.digitalWrite(6, LOW,MCP23017_ADDR[0]);
        break;
      }
    case 7: {
        check.digitalWrite(7, LOW,MCP23017_ADDR[0]);
        break;
      }
    case 8: {
        check.digitalWrite(0, LOW,MCP23017_ADDR[1]);
        break;
      }
      
    case 9: {
        check.digitalWrite(1, LOW,MCP23017_ADDR[1]);
        break;
      }
    case 10: {
        check.digitalWrite(2, LOW,MCP23017_ADDR[1]);
        break;
      }
    case 11: {
        check.digitalWrite(3, LOW,MCP23017_ADDR[1]);
        break;
      }
    case 12: {
        check.digitalWrite(4, LOW,MCP23017_ADDR[1]);
        break;
      }
    case 13: {
        check.digitalWrite(5, LOW,MCP23017_ADDR[1]);
        break;
      }
    case 14: {
        check.digitalWrite(6, LOW,MCP23017_ADDR[1]);
        break;
      }
    case 15: {
        check.digitalWrite(7, LOW,MCP23017_ADDR[1]);
        break;
      }
    case 16: {
        check.digitalWrite(0, LOW,MCP23017_ADDR[2]);
        break;
      }
    case 17: {
        check.digitalWrite(1, LOW,MCP23017_ADDR[2]);
        break;
      }
    case 18: {
        check.digitalWrite(2, LOW,MCP23017_ADDR[2]);
        break;
      }
    case 19: {
        check.digitalWrite(3, LOW,MCP23017_ADDR[2]);
        break;
      }
    case 20: {
        check.digitalWrite(4, LOW,MCP23017_ADDR[2]);
        break;
      }
    case 21: {
        check.digitalWrite(5, LOW,MCP23017_ADDR[2]);
        break;
      }
    case 22: {
        check.digitalWrite(6, LOW,MCP23017_ADDR[2]);
        break;
      }
    case 23: {
        check.digitalWrite(7, LOW,MCP23017_ADDR[2]);
        break;
      }
    default: {
        Serial.println("error in lights");
        break;
      }
  }
}
void Buttons(int i)
{
  switch (i)
  {
    case 0: {
        ItemList[i]--;
        if (ItemList == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 1: {
        ItemList[i]--;
        if (ItemList == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 2: {
        ItemList[i]--;
        if (ItemList == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 3: {
        ItemList[i]--;
        if (ItemList == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 4: {
        ItemList[i]--;
        if (ItemList == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 5: {
        ItemList[i]--;
        if (ItemList == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 6: {
        ItemList[i]--;
        if (ItemList == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 7: {
        ItemList[i]--;
        if (ItemList == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 8: {
        ItemList[i]--;
        if (ItemList == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 9: {
        ItemList[i]--;
        if (ItemList == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 10: {
        ItemList[i]--;
        if (ItemList == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 11: {
        ItemList[i]--;
        if (ItemList == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 12: {
        ItemList[i]--;
        if (ItemList == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 13: {
        ItemList[i]--;
        if (ItemList == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 14: {
        ItemList[i]--;
        if (ItemList == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 15: {
        ItemList[i]--;
        if (ItemList == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 16: {
        ItemList[i]--;
        if (ItemList == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 17: {
        ItemList[i]--;
        if (ItemList == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 18: {
        ItemList[i]--;
        if (ItemList == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 19: {
        ItemList[i]--;
        if (ItemList == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 20: {
        ItemList[i]--;
        if (ItemList == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 21: {
        ItemList[i]--;
        if (ItemList == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 22: {
        ItemList[i]--;
        if (ItemList == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 23: {
        ItemList[i]--;
        if (ItemList == 0) {
          turnOffLight(i);
        }
        break;
      }
  }
}
void writeToDisplay(){
    uint8_t i2count=0;
    uint8_t addcount=0;
    
    for(int i=0;i<LISTSIZE;i++){
        check.print(ItemList[i], DEC);
        check.writeDisplay(Display_i2c_addr[addcount],i2count);
        if(addcount==7){
            i2count++;
            addcount=0;
        }
        else{
            addcount++;
        }
    }
}
