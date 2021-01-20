#include "OLEDType_SSD1306.h"  //include driver file
#include "OLED_GFX.h"
#include "OLED_SSD1306.h"
#include "hello_world.h"

OLED_SSD1306 display;                                                              // instantiation  OLED_SSD1306

const unsigned char rpi_2[128] = { /* 0X00,0X01,0X1A,0X00,0X20,0X00, */           //binary file of picture
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X07,0XC1,0XF0,0X00,0X18,0X32,0X06,0X00,
0X10,0X0C,0X02,0X00,0X11,0X0C,0X02,0X00,0X10,0X4C,0X84,0X00,0X08,0X2D,0X04,0X00,
0X0C,0X1E,0X08,0X00,0X06,0X3F,0X10,0X00,0X03,0XE1,0XF0,0X00,0X04,0X40,0X18,0X00,
0X08,0XC0,0X88,0X00,0X09,0XFF,0XE4,0X00,0X0F,0X1C,0X34,0X00,0X1E,0X0C,0X1E,0X00,
0X24,0X0C,0X12,0X00,0X24,0X0C,0X01,0X00,0X24,0X0C,0X11,0X00,0X26,0X1E,0X19,0X00
0X2F,0XE1,0XFB,0X00,0X1B,0XC0,0XE6,0X00,0X10,0XC0,0XC6,0X00,0X10,0XC0,0X84,0X00,
0X08,0X40,0X84,0X00,0X08,0X73,0X0C,0X00,0X06,0X7F,0X98,0X00,0X01,0XC0,0XE0,0X00,
0X00,0XC0,0XC0,0X00,0X00,0X33,0X00,0X00,0X00,0X0C,0X00,0X00,0X00,0X00,0X00,0X00,
};

unsigned char rpi_3[128] = { /* 0X00,0X01,0X1A,0X00,0X20,0X00, */               //binary file of picture
0XFF,0XFF,0XFF,0XC0,0XFF,0XFF,0XFF,0XC0,0XF8,0X3E,0X0F,0XC0,0XE7,0XCD,0XF9,0XC0,
0XEF,0XFB,0XFD,0XC0,0XEE,0XF3,0XFD,0XC0,0XEF,0XB3,0X7B,0XC0,0XF7,0XD2,0XFB,0XC0,
0XFF,0XE1,0XFF,0XC0,0XFD,0XC0,0XEF,0XC0,0XFC,0X1E,0X0F,0XC0,0XFB,0XBF,0XE7,0XC0,
0XF7,0X3F,0X77,0XC0,0XF6,0X00,0X1B,0XC0,0XF0,0XE3,0XCB,0XC0,0XE1,0XF3,0XE1,0XC0,
0XDB,0XF7,0XFD,0XC0,0XDB,0XF3,0XFE,0XC0,0XDB,0XF3,0XEE,0XC0,0XD9,0XE1,0XE6,0XC0,
0XD0,0X1E,0X04,0XC0,0XE4,0X3F,0X19,0XC0,0XEF,0X3F,0X39,0XC0,0XFF,0XBF,0X7B,0XC0,
0XF7,0XBF,0X7B,0XC0,0XF7,0X8C,0XF3,0XC0,0XF9,0X80,0X67,0XC0,0XFE,0X3F,0X1F,0XC0,
0XFF,0X3F,0X3F,0XC0,0XFF,0XDC,0XFF,0XC0,0XFF,0XF3,0XFF,0XC0,0XFF,0XFF,0XFF,0XC0,
};

unsigned char hand_map[130] = { /* 0X00,0X01,0X1A,0X00,0X20,0X00, */               //binary file of picture
  0x42, 0x4d, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x28, 0x00, 
  0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0xe0, 0x1c, 
  0x00, 0x00, 0xdf, 0xec, 0x00, 0x00, 0xbf, 0xf4, 0x00, 0x00, 0xbf, 0x74, 0x00, 0x00, 0x7c, 0x38, 
  0x00, 0x00, 0x7b, 0xf8, 0x00, 0x00, 0x73, 0xf8, 0x00, 0x00, 0x6c, 0x04, 0x00, 0x00, 0x6d, 0xb4, 
  0x00, 0x00, 0x6d, 0xb4, 0x00, 0x00, 0x6d, 0xb4, 0x00, 0x00, 0x62, 0x34, 0x00, 0x00, 0x6f, 0xb4, 
  0x00, 0x00, 0x6f, 0xb4, 0x00, 0x00, 0x6f, 0xb4, 0x00, 0x00, 0x6f, 0xb4, 0x00, 0x00, 0x9f, 0xcc, 
  0x00, 0x00,
};

int main(int argc, char **argv)
{
        if ( !display.init(OLED_I2C_RESET,OLED_OLED_I2C_128x32) )       //initiate the I2C interface screen ,otherwise ,exit
                exit(EXIT_FAILURE);
        display.begin();                                                //start display
        display.clearDisplay();                                         //clear screen
        display.drawBitmap(0,0,rpi_2,32,32,1);                          //picture display location X:0,Y:0,picture file :RPI_2,picture high:32,picture with:32,font:black
        display.drawBitmap(96,0,rpi_2,32,32,1);                         //picture display location X:96,Y:0,picture file :RPI_2,picture high:32,picture with:32,font:black
        display.drawRect(0,0,128,32,0);                                 //display white
        display.setTextSize(1);                                         //set font size one
        display.setTextColor(WHITE);                                    //set font color white
        display.setCursor(29,0);                                        //set character display location X:29,:Y:0
        display.print("Hello World");                                   //set display content Hello World
        display.setCursor(29,16);                                       //set ddisplay location X:29,Y:16
        display.print("www.52pi.cn");                                   //set display ccontent www.52pi.cn
        display.display();                                              //start display
        usleep(10000);                                                  //delay

        try {
            // Block of code to try
            hand hand_image;
            display.begin();                                                //start display
            display.clearDisplay();                                         //clear screen
            display.drawBitmap(0,0,hand_image.data,32,32,1);                          //picture display location X:0,Y:0,picture file :RPI_2,picture high:32,picture with:32,font:black
            display.display();                                              //start display
        }
        catch () {
          std::cout "ERROR FUCKTARD";
        }

        usleep(10000);                                                  //delay
}

