#include <Pick2Light.h>

#define SCL1 8
#define SDA1 7
#define SCL2 4
#define SDA2 2
#define SCL3 6
#define SDA3 5


Pick2Light check= Pick2Light(SDA1,SCL1,SDA2,SCL2,SDA3,SCL3);
#define LISTSIZE 24
int ItemList[LISTSIZE];
uint8_t count=0x00;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("Begin");
  check.begin();
  for (int i = 0; i < LISTSIZE; i++) {
      ItemList[i] = 0;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  int k=0000;
  int i;
  while(k<10000){
    for(i=0;i<8;i++){
        check.print(k,DEC);
        check.drawColon(true);
        check.writeDisplay(Display_i2c_addr[i],0);
        Serial.println(k, DEC);
        if(k==9999){
          k=Display_i2c_addr[i];
          check.print(k,HEX);
          check.writeDisplay(Display_i2c_addr[i],0);
          Serial.println(k, DEC);
          delay(1000);
          k=9999;
        }
    }
    k+=1111;
    if(k>10000){
      k=0;
    }
    delay(500);
  }
}

