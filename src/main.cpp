#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#include "LCD_Driver.h"
#include "Touch_Driver.h"
#include "GUI_Paint.h"
#include "image.h"

UBYTE flag = 0, flgh = 0;
UWORD x, y, l = 0;

void Touch_INT_callback()
{
    flag = TOUCH_IRQ;
    Serial.println("Touch interrupt!");
}

void I2C_Scanner()
{
    Serial.println("Scanning I2C bus...");
    byte count = 0;
    for (byte i = 1; i < 127; i++)
    {
        Wire.beginTransmission(i);
        if (Wire.endTransmission() == 0)
        {
            Serial.print("Found I2C device at address 0x");
            if (i < 16)
                Serial.print("0");
            Serial.print(i, HEX);
            Serial.println(" !");
            count++;
            delay(1);
        }
    }
    Serial.print("Found ");
    Serial.print(count, DEC);
    Serial.println(" device(s).");
}

void setup()
{
    Serial.begin(115200);
    delay(2000);

    I2C_Scanner(); // Scan for I2C devices
    delay(2000);

    Touch_1IN28_XY XY;
    XY.mode = 0;
    XY.x_point = 0;
    XY.y_point = 0;
    Config_Init();
    delay(2000);
    LCD_Init();
    delay(2000);

    if (Touch_1IN28_init(XY.mode) == true)
        Serial.println("Touch controller detected!");
    else
        Serial.println("Error: Not Detected CST816T!");

    LCD_SetBacklight(1000);
    Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, BLACK);
    Paint_Clear(WHITE);
    attachInterrupt(1, Touch_INT_callback, LOW);
    pinMode(TP_INT_PIN, INPUT_PULLUP);
    Paint_DrawString_EN(35, 90, "Gesture test", &Font20, BLACK, WHITE);
    Paint_DrawString_EN(10, 120, "Complete as prompted", &Font16, BLACK, WHITE);
    DEV_Delay_ms(500);
}

void loop()
{
    Paint_ClearWindows(10, 90, 230, 137, WHITE);
    Paint_DrawString_EN(105, 100, "Up", &Font24, 0X647C, WHITE);
    while (XY.Gesture != Down)
    {
        if (flag == TOUCH_IRQ)
        {
            XY.Gesture = DEV_I2C_Read_Byte(address, 0x01);
            flag = TOUCH_DRAW;
        }
        DEV_Delay_ms(10);
    }

    Paint_ClearWindows(105, 100, 160, 155, WHITE);
    Paint_DrawString_EN(85, 100, "Down", &Font24, 0X647C, WHITE);
    while (XY.Gesture != UP)
    {
        if (flag == TOUCH_IRQ)
        {
            XY.Gesture = DEV_I2C_Read_Byte(address, 0x01);
            flag = TOUCH_DRAW;
        }
        DEV_Delay_ms(10);
    }
}