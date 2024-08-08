/*****************************************************************************
* | File        :   DEV_Config.c
* | Author      :   Waveshare team
* | Function    :   Hardware underlying interface
* | Info        :
*                Used to shield the underlying layers of each master 
*                and enhance portability
*----------------
* | This version:   V1.0
* | Date        :   2018-11-22
* | Info        :

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include "DEV_Config.h"

void GPIO_Init()
{
  pinMode(DEV_CS_PIN, OUTPUT);
  pinMode(DEV_RST_PIN, OUTPUT);
  pinMode(DEV_DC_PIN, OUTPUT);
  pinMode(DEV_BL_PIN, OUTPUT);
  pinMode(TP_RST_PIN, OUTPUT);
  analogWrite(DEV_BL_PIN,140);
 }

 void Config_Init()
 {

  GPIO_Init();
  
  //Serial
  Serial.begin(115200);
  
  //spi
  SPI.setDataMode(SPI_MODE3);
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  SPI.begin();

  //i2c
  Wire.setPins(D4, D5);
  Wire.begin();

  }

UBYTE DEV_I2C_Read_Byte(UBYTE DevAddr, UBYTE RegAddr)
{
  UBYTE value;

  Wire.beginTransmission(DevAddr);
  Wire.write((byte)RegAddr);
  Wire.endTransmission();

  Wire.requestFrom(DevAddr, (byte)1);
  value = Wire.read();

  return value;
}

void DEV_I2C_Read_nByte(UBYTE DevAddr,UBYTE Cmd, UBYTE *data, UBYTE num)
{

	Wire.beginTransmission(DevAddr);
	Wire.write(Cmd);
	// Wire.endTransmission();
	Wire.requestFrom(DevAddr, num);

	UBYTE i = 0;
	for(i = 0; i < num; i++) {
		data[i] =  Wire.read();
	}
	Wire.endTransmission();

}

void DEV_I2C_Write_Byte(UBYTE DevAddr, UBYTE RegAddr, UBYTE value)
{
  Wire.beginTransmission(DevAddr);
  Wire.write(RegAddr);
  Wire.write(value);
  Wire.endTransmission();
}

