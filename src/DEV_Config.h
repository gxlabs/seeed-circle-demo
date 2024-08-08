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
#ifndef _DEV_CONFIG_H_
#define _DEV_CONFIG_H_

#include <stdint.h>
#include <stdio.h>
#include <SPI.h>
#include <Arduino.h> 
#include <Wire.h>
#include "Debug.h"



#define UBYTE   uint8_t
#define UWORD   uint16_t
#define UDOUBLE uint32_t

/**
 * GPIO config
**/

// #define PIN_MOSI D10
// #define PIN_MISO D9
// #define PIN_SCK D8
// // LCD
// #define PIN_LCD_CS D7
// #define PIN_LCD_DC D6
// #define PIN_LCD_RST D5
// #define PIN_LCD_BL D4
// // TOUCH
// #define PIN_TOUCH_SDA D3
// #define PIN_TOUCH_SCL D2
// #define PIN_TOUCH_INT D1
// #define PIN_TOUCH_RST D0

#define DEV_CS_PIN  D7
#define DEV_DC_PIN  D6
#define DEV_RST_PIN D3
#define DEV_BL_PIN  A2

#define TP_RST_PIN D0
#define TP_INT_PIN D1

/**
 * GPIO read and write
**/
#define DEV_Digital_Write(_pin, _value) digitalWrite(_pin, _value == 0? LOW:HIGH)
#define DEV_Digital_Read(_pin) digitalRead(_pin)


/**
 * SPI
**/
#define DEV_SPI_WRITE(_dat)   SPI.transfer(_dat)

/**
 * delay x ms
**/
#define DEV_Delay_ms(__xms)    delay(__xms)

/**
 * PWM_BL
**/
 #define  DEV_Set_BL(_Pin, _Value)  analogWrite(_Pin, _Value)

/*-----------------------------------------------------------------------------*/
void Config_Init();
uint8_t DEV_I2C_Read_Byte(uint8_t DevAddr, uint8_t RegAddr);
void DEV_I2C_Write_Byte(uint8_t DevAddr, uint8_t RegAddr, uint8_t value);
void DEV_I2C_Read_nByte(UBYTE DevAddr,UBYTE Cmd, UBYTE *data, UBYTE num);

#endif

