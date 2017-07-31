/*
Header file for library to control Arduinos 
*/

#ifndef Pick2Light_h
#define Pick2Light_h

#include <Wire.h> //normal i2c library
#include <SlowSoftWire.h> //software i2c library

//i2c address for adruinos
#define A1 0x03 
#define A2 0x04
#define A3 0x05
#define A4 0x06
#define A5 0x07
#define A6 0x08
#define A7 0x09
#define A8 0x10
//7 segment display definitions for Commands
#define LED_ON 1
#define LED_OFF 0

#define HT16K33_BLINK_CMD 0x80
#define HT16K33_BLINK_DISPLAYON 0x01
#define HT16K33_BLINK_OFF 0
#define HT16K33_BLINK_2HZ  1
#define HT16K33_BLINK_1HZ  2
#define HT16K33_BLINK_HALFHZ  3

#define HT16K33_CMD_BRIGHTNESS 0xE0

#define SEVENSEG_DIGITS 5
#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2
#define BYTE 0
//MCP23017 base address
#define MCP23017_ADDRESS 0x20

// registers
#define MCP23017_IODIRA 0x00
#define MCP23017_IPOLA 0x02
#define MCP23017_GPINTENA 0x04
#define MCP23017_DEFVALA 0x06
#define MCP23017_INTCONA 0x08
#define MCP23017_IOCONA 0x0A
#define MCP23017_GPPUA 0x0C
#define MCP23017_INTFA 0x0E
#define MCP23017_INTCAPA 0x10
#define MCP23017_GPIOA 0x12
#define MCP23017_OLATA 0x14


#define MCP23017_IODIRB 0x01
#define MCP23017_IPOLB 0x03
#define MCP23017_GPINTENB 0x05
#define MCP23017_DEFVALB 0x07
#define MCP23017_INTCONB 0x09
#define MCP23017_IOCONB 0x0B
#define MCP23017_GPPUB 0x0D
#define MCP23017_INTFB 0x0F
#define MCP23017_INTCAPB 0x11
#define MCP23017_GPIOB 0x13
#define MCP23017_OLATB 0x15

#define MCP23017_INT_ERR
//used for error checking 
#define DEVSIZE 11
#define MCP23017_AMOUNT 3
#define SEGMENT_AMOUNT 8
//number table for 7 segment displays do not change
static const uint8_t numbertable[] = {
	0x3F, /* 0 */
	0x06, /* 1 */
	0x5B, /* 2 */
	0x4F, /* 3 */
	0x66, /* 4 */
	0x6D, /* 5 */
	0x7D, /* 6 */
	0x07, /* 7 */
	0x7F, /* 8 */
	0x6F, /* 9 */
	0x77, /* a */
	0x7C, /* b */
	0x39, /* C */
	0x5E, /* d */
	0x79, /* E */
	0x71, /* F */
};
//address list for displays
static const uint8_t Display_i2c_addr[]={
    0x70,
    0x71,
    0x72,
    0x73,
    0x74,
    0x75,
    0x76,
    0x77,
};
//address lists for MCP23017
static const uint8_t MCP23017_ADDR[]={
    0x00,
    0x01,
    0x02,
};
class Pick2Light{
    public:
        Pick2Light(void);
        Pick2Light(uint8_t _sda1,uint8_t _scl1,uint8_t _sda2,uint8_t _scl2,
                   uint8_t _sda3,uint8_t _scl3);
        //Backpack
        void begin(void);
        void testBus(int);
        void testConnection(void);
        
        void writeToDisplay(int ItemList[],int size);
        
        void turnOnAllOscilators(void);
        void setAllBrightness(uint8_t b);//complete
        void allBlinkRate(uint8_t b);//Complete
        void writeDisplay(uint8_t _addr,uint8_t Type);
        void clear(void);//Complete
        
        uint16_t displaybuffer[8]; 
        
        void init(uint8_t a);
        //7 segment
        size_t write(uint8_t c);

        void print(char, int = BYTE);
        void print(unsigned char, int = BYTE);
        void print(int, int = DEC);
        void print(unsigned int, int = DEC);
        void print(long, int = DEC);
        void print(unsigned long, int = DEC);
        void print(double, int = 2);
        void println(char, int = BYTE);
        void println(unsigned char, int = BYTE);
        void println(int, int = DEC);
        void println(unsigned int, int = DEC);
        void println(long, int = DEC);
        void println(unsigned long, int = DEC);
        void println(double, int = 2);
        void println(void);
        
        void writeDigitRaw(uint8_t x, uint8_t bitmask);//need
        void writeDigitNum(uint8_t x, uint8_t num, boolean dot = false);
        void drawColon(boolean state);
        void printNumber(long, uint8_t = 2);
        void printFloat(double, uint8_t = 2, uint8_t = DEC);//Delete
        void printError(void);//needs writeDigitRaw
        void writeColon(uint8_t, uint8_t);
        //MCP
                
        void pinMode(uint8_t p, uint8_t d, uint8_t i2caddr);
        void digitalWrite(uint8_t p, uint8_t d, uint8_t i2caddr);
        void pullUp(uint8_t p, uint8_t d, uint8_t i2caddr);
        uint8_t digitalRead(uint8_t p, uint8_t i2caddr);
        
        void writeGPIOAB(uint16_t , uint8_t i2caddr);
        uint16_t readGPIOAB(uint8_t i2caddr);
        uint8_t readGPIO(uint8_t b, uint8_t i2caddr);
    
    private:
        uint8_t position;
        
        uint8_t bitForPin(uint8_t pin);
        uint8_t regForPin(uint8_t pin, uint8_t portAaddr, uint8_t portBaddr);
        
        uint8_t readRegister(uint8_t addr,uint8_t i2caddr);
        void writeRegister(uint8_t addr, uint8_t value, uint8_t i2caddr);

        void updateRegisterBit(uint8_t p, uint8_t pValue, uint8_t portAaddr, uint8_t portBaddr, uint8_t i2caddr);
};
#endif
