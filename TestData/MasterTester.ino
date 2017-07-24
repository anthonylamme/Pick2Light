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

#define bitmask1 1
#define bitmask2 2
#define bitmask3 4
#define bitmask4 8
#define bitmask5 16
#define bitmask6 32
#define bitmask7 64
#define bitmask8 128

uint8_t old1 = 0x00;
uint8_t old2 = 0x00;
uint8_t old3 = 0x00;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Begin");
  check.begin();
  for (int i = 0; i < LISTSIZE; i++) {
    ItemList[i] = 0;
  }
  Serial.println("Begin Command");
  recieveMasterCommand();
}
void loop() {
  int i=0;
  while(i < 10000){
    for(int j=0;j < LISTSIZE; j++){    
      ItemList[j]=i;
      if(i<512){
        turnOnLights(i,i,i);
      }
      else{
        turnOnLights(511,511,511);
      }
      writeToDisplay();
    }
    i+=1;
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
void recieveMasterCommand() {
  for (int i = 0; i < LISTSIZE; i++) {
    ItemList[i] = 0;
  }
  turnOnLights(511,511,511);
}
void turnOnLights(uint8_t lights1, uint8_t lights2, uint8_t lights3) {
  check.writeGPIOAB(lights1,MCP23017_ADDR[0]);//maybe << 8
  check.writeGPIOAB(lights2,MCP23017_ADDR[1]);
  check.writeGPIOAB(lights3,MCP23017_ADDR[2]);
}
boolean sendStatus() {
  //port A is Buttons (0)
  if (check.readGPIO(0,MCP23017_ADDR[0]) == 0  && (check.readGPIO(0,MCP23017_ADDR[1]) == 0) && (check.readGPIO(1,MCP23017_ADDR[2]) == 0)) {
    return true;
  }
  else 
    return false;
}
void clearEverything() {
  check.writeGPIOAB(0x00,MCP23017_ADDR[0]);
  check.writeGPIOAB(0x00,MCP23017_ADDR[1]);
  check.writeGPIOAB(0x00,MCP23017_ADDR[2]);
  for (int i = 0; i < 24; i++) {
    ItemList[i] = 0;
  }
}
void Buttons(int i)
{
  switch (i)
  {
    case 0: {
        ItemList[i]--;
        if (ItemList[i] == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 1: {
        ItemList[i]--;
        if (ItemList[i] == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 2: {
        ItemList[i]--;
        if (ItemList[i] == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 3: {
        ItemList[i]--;
        if (ItemList[i] == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 4: {
        ItemList[i]--;
        if (ItemList[i] == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 5: {
        ItemList[i]--;
        if (ItemList[i] == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 6: {
        ItemList[i]--;
        if (ItemList[i] == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 7: {
        ItemList[i]--;
        if (ItemList[i] == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 8: {
        ItemList[i]--;
        if (ItemList[i] == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 9: {
        ItemList[i]--;
        if (ItemList[i] == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 10: {
        ItemList[i]--;
        if (ItemList[i] == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 11: {
        ItemList[i]--;
        if (ItemList[i] == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 12: {
        ItemList[i]--;
        if (ItemList[i] == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 13: {
        ItemList[i]--;
        if (ItemList[i] == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 14: {
        ItemList[i]--;
        if (ItemList[i] == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 15: {
        ItemList[i]--;
        if (ItemList[i] == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 16: {
        ItemList[i]--;
        if (ItemList[i] == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 17: {
        ItemList[i]--;
        if (ItemList[i] == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 18: {
        ItemList[i]--;
        if (ItemList[i] == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 19: {
        ItemList[i]--;
        if (ItemList[i] == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 20: {
        ItemList[i]--;
        if (ItemList[i] == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 21: {
        ItemList[i]--;
        if (ItemList[i] == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 22: {
        ItemList[i]--;
        if (ItemList[i] == 0) {
          turnOffLight(i);
        }
        break;
      }
    case 23: {
        ItemList[i]--;
        if (ItemList[i] == 0) {
          turnOffLight(i);
        }
        break;
      }
  }
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
