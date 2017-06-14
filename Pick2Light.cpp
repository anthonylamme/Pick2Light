#ifdef __AVR
  #include <avr/pgmspace.h>
#elif defined(ESP8266)
  #include <pgmspace.h>
#endif

#include "Pick2Light.h"

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


#ifndef _BV
  #define _BV(bit) (1<<(bit))
#endif

#ifndef _swap_int16_t
#define _swap_int16_t(a, b) { int16_t t = a; a = b; b = t; }
#endif

SlowSoftWire i2c0;
SlowSoftWire i2c1;
SlowSoftWire i2c2;

//void constructor
Pick2Light::Pick2Light(void){
    
}
//constructor
Pick2Light::Pick2Light(uint8_t _SDA1,uint8_t _SCL1,uint8_t _SDA2,
                        uint8_t _SCL2,uint8_t _SDA3,uint8_t _SCL3){
    i2c0= SlowSoftWire(_SDA1,_SCL1);
    i2c1= SlowSoftWire(_SDA2,_SCL2);
    i2c2= SlowSoftWire(_SDA3,_SCL3);
    //pinMode(_status, OUTPUT);
    position = 0;
}
/*
begins i2c buses and all 7 segment displays
*/
void Pick2Light::begin(void){
    i2c0.begin();
    i2c1.begin();
    i2c2.begin();
    turnOnAllOscilators();
    setAllBrightness(15);
    allBlinkRate(HT16K33_BLINK_OFF);
    
    for(int i=0;i<3;i++){        
        // set defaults!
        // all inputs on port A and B
        writeRegister(MCP23017_IODIRA,0xff,MCP23017_ADDR[i]);
        writeRegister(MCP23017_IODIRB,0xff,MCP23017_ADDR[i]);
        pinMode(21, OUTPUT,MCP23017_ADDR[i]); //Light 1
        pinMode(22, OUTPUT,MCP23017_ADDR[i]); //Light 2
        pinMode(23, OUTPUT,MCP23017_ADDR[i]); //Light 3
        pinMode(24, OUTPUT,MCP23017_ADDR[i]); //Light 4
        pinMode(25, OUTPUT,MCP23017_ADDR[i]); //Light 5
        pinMode(26, OUTPUT,MCP23017_ADDR[i]); //Light 6
        pinMode(27, OUTPUT,MCP23017_ADDR[i]); //Light 7
        pinMode(28, OUTPUT,MCP23017_ADDR[i]); //Light 8
        pinMode(1, INPUT,MCP23017_ADDR[i]); //BUTTON 1
        pinMode(2, INPUT,MCP23017_ADDR[i]); //Button 2
        pinMode(3, INPUT,MCP23017_ADDR[i]); //Button 3
        pinMode(4, INPUT,MCP23017_ADDR[i]); //Button 4
        pinMode(5, INPUT,MCP23017_ADDR[i]); //Button 5
        pinMode(6, INPUT,MCP23017_ADDR[i]); //Button 6
        pinMode(7, INPUT,MCP23017_ADDR[i]); //Button 7
        pinMode(8, INPUT,MCP23017_ADDR[i]); //Button 8
    }
}

/*
needs work
*/
void Pick2Light::testConnection(void){
    byte error, address;
    int nDevices;
    
    Serial.println(F("Scanning I2C bus (7-bit addresses) ..."));
    
    nDevices = 0;
    for(address = 1; address < 127; address++ )
    {
        // The i2c_scanner uses the return value of
        // the Write.endTransmisstion to see if
        // a device did acknowledge to the address.
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
        
        if (error == 0)
        {
            Serial.print(F("I2C device found at address 0x"));
            if (address<16)
            Serial.print(F("0"));
            Serial.print(address,HEX);
            Serial.println(F("  !"));
    
            nDevices++;
        }
        else if (error==4)
        {
            Serial.print(F("Unknow error at address 0x"));
            if (address<16)
            Serial.print("0");
            Serial.println(address,HEX);
        }    
    }
    if (nDevices == 0)
    Serial.println("No I2C devices found\n");
    else 
    Serial.println("done\n");
}

/*
Functions for 7 segment control
*/

void Pick2Light::turnOnAllOscilators(void){
    for(int i=0;i<8;i++){
        i2c0.beginTransmission(Display_i2c_addr[i]);
        i2c0.write(0x21);
        i2c0.endTransmission();
        
        i2c1.beginTransmission(Display_i2c_addr[i]);
        i2c0.write(0x21);
        i2c1.endTransmission();
        
        i2c2.beginTransmission(Display_i2c_addr[i]);
        i2c0.write(0x21);
        i2c2.endTransmission();
    }
}

void Pick2Light::setAllBrightness(uint8_t b){
    if (b > 15) b = 15;//15 max
    for(int i=0;i<8;i++){
        i2c0.beginTransmission(Display_i2c_addr[i]);
        i2c0.write(HT16K33_CMD_BRIGHTNESS | b);
        i2c0.endTransmission();
        
        i2c1.beginTransmission(Display_i2c_addr[i]);
        i2c1.write(HT16K33_CMD_BRIGHTNESS | b);
        i2c1.endTransmission();
        
        i2c2.beginTransmission(Display_i2c_addr[i]);
        i2c2.write(HT16K33_CMD_BRIGHTNESS | b);
        i2c2.endTransmission();
    }
}

void Pick2Light::allBlinkRate(uint8_t b){
    if (b > 3) b = 0; // turn off if not sure
    for(int i=0;i<8;i++){
        i2c0.beginTransmission(Display_i2c_addr[i]);
        i2c0.write(HT16K33_BLINK_CMD | HT16K33_BLINK_DISPLAYON | (b << 1)); 
        i2c0.endTransmission();
        
        i2c1.beginTransmission(Display_i2c_addr[i]);
        i2c0.write(HT16K33_BLINK_CMD | HT16K33_BLINK_DISPLAYON | (b << 1)); 
        i2c0.endTransmission();
        
        i2c2.beginTransmission(Display_i2c_addr[i]);
        i2c0.write(HT16K33_BLINK_CMD | HT16K33_BLINK_DISPLAYON | (b << 1)); 
        i2c0.endTransmission();
    }
}

void Pick2Light::writeDisplay(uint8_t i2c_addr,uint8_t i2cType){
    switch(i2cType){
      case 0:{
          i2c0.beginTransmission(i2c_addr);
          i2c0.write((uint8_t)0x00); // start at address $00
          
          for (uint8_t i=0; i<8; i++) {
              i2c0.write(displaybuffer[i] & 0xFF);    
              i2c0.write(displaybuffer[i] >> 8);    
          }
          i2c0.endTransmission(); 
          break;
      }
      case 1:{
          i2c1.beginTransmission(i2c_addr);
          i2c1.write((uint8_t)0x00); // start at address $00
          
          for (uint8_t i=0; i<8; i++) {
              i2c1.write(displaybuffer[i] & 0xFF);    
              i2c1.write(displaybuffer[i] >> 8);    
          }
          i2c1.endTransmission(); 
          break;
      }
      case 2:{
          i2c2.beginTransmission(i2c_addr);
          i2c2.write((uint8_t)0x00); // start at address $00
          
          for (uint8_t i=0; i<8; i++) {
              i2c2.write(displaybuffer[i] & 0xFF);    
              i2c2.write(displaybuffer[i] >> 8);    
          }
          i2c2.endTransmission(); 
          break;
      }
      default:{
          Wire.beginTransmission(i2c_addr);
          Wire.write((uint8_t)0x00); // start at address $00
          
          for (uint8_t i=0; i<8; i++) {
              Wire.write(displaybuffer[i] & 0xFF);    
              Wire.write(displaybuffer[i] >> 8);    
          }
          Wire.endTransmission(); 
          break;
      }
  }
}

//clears display buffer need writeDisplay afterwards
void Pick2Light::clear(void){
    for (uint8_t i=0; i<8; i++) {
        displaybuffer[i] = 0;
    }
}
/*
7 segment only control
*/
void Pick2Light::print(unsigned long n, int base){
  if (base == 0) write(n);
  else printNumber(n, base);
}

void Pick2Light::print(char c, int base){
  print((long) c, base);
}

void Pick2Light::print(unsigned char b, int base){
  print((unsigned long) b, base);
}

void Pick2Light::print(int n, int base){
  print((long) n, base);
}

void Pick2Light::print(unsigned int n, int base){
  print((unsigned long) n, base);
}

void  Pick2Light::println(void) {
  position = 0;
}

void  Pick2Light::println(char c, int base){
  print(c, base);
  println();
}

void  Pick2Light::println(unsigned char b, int base){
  print(b, base);
  println();
}

void  Pick2Light::println(int n, int base){
  print(n, base);
  println();
}

void Pick2Light::println(unsigned int n, int base){
  print(n, base);
  println();
}

void  Pick2Light::println(long n, int base){
  print(n, base);
  println();
}

void  Pick2Light::println(unsigned long n, int base){
  print(n, base);
  println();
}

void  Pick2Light::println(double n, int digits){
  print(n, digits);
  println();
}

void  Pick2Light::print(double n, int digits){
  printFloat(n, digits);
}

size_t Pick2Light::write(uint8_t c) {

  uint8_t r = 0;

  if (c == '\n') position = 0;
  if (c == '\r') position = 0;

  if ((c >= '0') && (c <= '9')) {
    writeDigitNum(position, c-'0');
    r = 1;
  }

  position++;
  if (position == 2) position++;

  return r;
}

void Pick2Light::writeDigitRaw(uint8_t d, uint8_t bitmask) {
  if (d > 4) return;
  displaybuffer[d] = bitmask;
}

void Pick2Light::drawColon(boolean state) {
  if (state)
    displaybuffer[2] = 0x2;
  else
    displaybuffer[2] = 0;
}

void Pick2Light::writeColon(uint8_t i2c_addr,uint8_t i2cType) {
    switch(i2cType){
      case 0:{
          i2c0.beginTransmission(i2c_addr);
          i2c0.write((uint8_t)0x04); // start at address $02
          i2c0.write(displaybuffer[2] & 0xFF);
          i2c0.write(displaybuffer[2] >> 8);
          i2c0.endTransmission();
      }
      case 1:{
          i2c1.beginTransmission(i2c_addr);
          i2c1.write((uint8_t)0x04); // start at address $02
          i2c1.write(displaybuffer[2] & 0xFF);
          i2c1.write(displaybuffer[2] >> 8);
          i2c1.endTransmission();
      }
      case 2:{
          i2c2.beginTransmission(i2c_addr);
          i2c2.write((uint8_t)0x04); // start at address $02
          i2c2.write(displaybuffer[2] & 0xFF);
          i2c2.write(displaybuffer[2] >> 8);
          i2c2.endTransmission();
      }
      default:{  
          Wire.beginTransmission(i2c_addr);
          Wire.write((uint8_t)0x04); // start at address $02
          Wire.write(displaybuffer[2] & 0xFF);
          Wire.write(displaybuffer[2] >> 8);
          Wire.endTransmission();
      }
    }
}

void Pick2Light::writeDigitNum(uint8_t d, uint8_t num, boolean dot) {
  if (d > 4) return;

  writeDigitRaw(d, numbertable[num] | (dot << 7));
}

void Pick2Light::print(long n, int base){
  printNumber(n, base);
}

void Pick2Light::printNumber(long n, uint8_t base){
    printFloat(n, 0, base);
}

void Pick2Light::printFloat(double n, uint8_t fracDigits, uint8_t base) { 
  uint8_t numericDigits = 4;   // available digits on display
  boolean isNegative = false;  // true if the number is negative
  
  // is the number negative?
  if(n < 0) {
    isNegative = true;  // need to draw sign later
    --numericDigits;    // the sign will take up one digit
    n *= -1;            // pretend the number is positive
  }
  
  // calculate the factor required to shift all fractional digits
  // into the integer part of the number
  double toIntFactor = 1.0;
  for(int i = 0; i < fracDigits; ++i) toIntFactor *= base;
  
  // create integer containing digits to display by applying
  // shifting factor and rounding adjustment
  uint32_t displayNumber = n * toIntFactor + 0.5;
  
  // calculate upper bound on displayNumber given
  // available digits on display
  uint32_t tooBig = 1;
  for(int i = 0; i < numericDigits; ++i) tooBig *= base;
  
  // if displayNumber is too large, try fewer fractional digits
  while(displayNumber >= tooBig) {
    --fracDigits;
    toIntFactor /= base;
    displayNumber = n * toIntFactor + 0.5;
  }
  
  // did toIntFactor shift the decimal off the display?
  if (toIntFactor < 1) {
    printError();
  } else {
    // otherwise, display the number
    int8_t displayPos = 4;
    
    if (displayNumber)  //if displayNumber is not 0
    {
      for(uint8_t i = 0; displayNumber || i <= fracDigits; ++i) {
        boolean displayDecimal = (fracDigits != 0 && i == fracDigits);
        writeDigitNum(displayPos--, displayNumber % base, displayDecimal);
        if(displayPos == 2) writeDigitRaw(displayPos--, 0x00);
        displayNumber /= base;
      }
    }
    else {
      writeDigitNum(displayPos--, 0, false);
    }
  
    // display negative sign if negative
    if(isNegative) writeDigitRaw(displayPos--, 0x40);
  
    // clear remaining display positions
    while(displayPos >= 0) writeDigitRaw(displayPos--, 0x00);
  }
}

void Pick2Light::printError(void) {
  for(uint8_t i = 0; i < SEVENSEG_DIGITS; ++i) {
    writeDigitRaw(i, (i == 2 ? 0x00 : 0x40));
  }
}

/**
 * Bit number associated to a give Pin
 */
uint8_t Pick2Light::bitForPin(uint8_t pin){
	return pin%8;
}

/**
 * Register address, port dependent, for a given PIN
 */
uint8_t Pick2Light::regForPin(uint8_t pin, uint8_t portAaddr, uint8_t portBaddr){
	return(pin<8) ?portAaddr:portBaddr;
}

/**
 * Reads a given register
 */
uint8_t Pick2Light::readRegister(uint8_t addr,uint8_t i2caddr){
	// read the current GPINTEN
    i2c0.beginTransmission(MCP23017_ADDRESS | i2caddr);
    i2c0.write(addr);
    i2c0.endTransmission();
    i2c0.requestFrom(MCP23017_ADDRESS | i2caddr, 1);
    return i2c0.read();
}


/**
 * Writes a given register
 */
void Pick2Light::writeRegister(uint8_t regAddr, uint8_t regValue, uint8_t i2caddr){
    i2c0.beginTransmission(MCP23017_ADDRESS | i2caddr);
    i2c0.write(regAddr);
    i2c0.write(regValue);
    i2c0.endTransmission();
    
}

/**
 * Helper to update a single bit of an A/B register.
 * - Reads the current register value
 * - Writes the new register value
 */
void Pick2Light::updateRegisterBit(uint8_t pin, uint8_t pValue, uint8_t portAaddr, uint8_t portBaddr, uint8_t i2caddr) {
	uint8_t regValue;
	uint8_t regAddr=regForPin(pin,portAaddr,portBaddr);
	uint8_t bit=bitForPin(pin);
	regValue = readRegister(regAddr, i2caddr);

	// set the value for the particular bit
	bitWrite(regValue,bit,pValue);

	writeRegister(regAddr,regValue,i2caddr);
}

/**
 * Sets the pin mode to either INPUT or OUTPUT
 */
void Pick2Light::pinMode(uint8_t p, uint8_t d, uint8_t i2caddr) {
	updateRegisterBit(p,(d==INPUT),MCP23017_IODIRA,MCP23017_IODIRB, i2caddr);
}

/**
 * Reads all 16 pins (port A and B) into a single 16 bits variable.
 */
uint16_t Pick2Light::readGPIOAB(uint8_t i2caddr) {
	uint16_t ba = 0;
	uint8_t a;
    
    i2c0.beginTransmission(MCP23017_ADDRESS | i2caddr);
    i2c0.write(MCP23017_GPIOA);
    i2c0.endTransmission();
    i2c0.requestFrom(MCP23017_ADDRESS | i2caddr, 2);
    a  = i2c0.read();
    ba = i2c0.read();
	// read the current GPIO output latches
	
	ba <<= 8;
	ba |= a;

	return ba;
}

/**
 * Read a single port, A or B, and return its current 8 bit value.
 * Parameter b should be 0 for GPIOA, and 1 for GPIOB.
 */
uint8_t Pick2Light::readGPIO(uint8_t b, uint8_t i2caddr) {
    
    i2c0.beginTransmission(MCP23017_ADDRESS | i2caddr);
    if (b == 0)
        i2c0.write(MCP23017_GPIOA);
    else 
        i2c0.write(MCP23017_GPIOB);
    i2c0.endTransmission();
    i2c0.requestFrom(MCP23017_ADDRESS | i2caddr, 1);
    return i2c0.read();
	// read the current GPIO output latches
}

/**
 * Writes all the pins in one go. This method is very useful if you are implementing a multiplexed matrix and want to get a decent refresh rate.
 */
void Pick2Light::writeGPIOAB(uint16_t ba, uint8_t i2caddr) {
    i2c0.beginTransmission(MCP23017_ADDRESS | i2caddr);
    i2c0.write(MCP23017_GPIOA);
    i2c0.write((uint8_t)(ba & 0xFF));
    i2c0.write((uint8_t)(ba >> 8));
    i2c0.endTransmission();
}

void Pick2Light::digitalWrite(uint8_t pin, uint8_t d, uint8_t i2caddr) {
	uint8_t gpio;
	uint8_t bit=bitForPin(pin);
    
    
	// read the current GPIO output latches
	uint8_t regAddr=regForPin(pin,MCP23017_OLATA,MCP23017_OLATB);
	gpio = readRegister(regAddr,i2caddr);

	// set the pin and direction
	bitWrite(gpio,bit,d);

	// write the new GPIO
	regAddr=regForPin(pin,MCP23017_GPIOA,MCP23017_GPIOB);
	writeRegister(regAddr,gpio,i2caddr);
}

void Pick2Light::pullUp(uint8_t p, uint8_t d, uint8_t i2caddr) {
	updateRegisterBit(p,d,MCP23017_GPPUA,MCP23017_GPPUB,i2caddr);
}

uint8_t Pick2Light::digitalRead(uint8_t pin, uint8_t i2caddr) {
	uint8_t bit=bitForPin(pin);
	uint8_t regAddr=regForPin(pin,MCP23017_GPIOA,MCP23017_GPIOB);
	return (readRegister(regAddr,i2caddr) >> bit) & 0x1;
}