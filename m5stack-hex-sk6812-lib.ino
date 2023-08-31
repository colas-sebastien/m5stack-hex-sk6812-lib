/*
*******************************************************************************
* Library to control M5Stack Hex SK6812
* based on the official code:
* https://github.com/m5stack/M5Stack/tree/master/examples/Unit/HEX_SK6812
*******************************************************************************
*
* Depending of you controller:
* - Please connect your M5Stack on port B
* - Please connect your M5Atom on the only port available
* - Please connect your M5Stick on the only port available and change the value of HEXRGB_PIN to 32 into the HexRGB.h file  
*/

/*******************************************/
/* Comment/Uncomment depending your device */
// #include <M5Stack.h>
#include <M5Atom.h>
/*******************************************/

/*******************************************
 * Set HEXRGB_PIN to your port number:
 * 
 *  M5Core    Port A  Pin 21
 *            Port B  Pin 26
 *            Port C  Pin 17
 *            
 *  M5Atom    Port    Pin 26
 *  
 *  M5Stick   Port    Pin 32 */
// #define HEXRGB_PIN  26 
/*  If not specified Pin 26 will be used
 ******************************************/

#include "HexRGB.h"

#define NUM_HEX     7
#define BRIGTHNESS  5


DEFINE_GRADIENT_PALETTE( heatmap_gp )
{
    0,  255,    0,    0,  // red
  128,  255,  255,    0,  // bright yellow
  255,  255,    0,    0   // red
};

DEFINE_GRADIENT_PALETTE( wave_gp )
{
    0,    9,    9,  121,  // cyan
   90,   11,   11,   70,  // blue
  120,   11,   11,   70,  // blue
  255,    9,    9,  121   // cyan
};


DEFINE_GRADIENT_PALETTE( b_w_gp )
{
    0,    0,    0,    0,  // black
  100,    0,    0,    0,
  110,  255,  255,  255,  // white
  120,  255,  255,  255,  // white
  130,    0,    0,    0,
  255,    0,    0,    0   // black
};

HexRGB hexRGB(NUM_HEX,BRIGTHNESS);

void setup() {
  M5.begin();             //Init M5Stack.

  for (int hex_id=0; hex_id<NUM_HEX; hex_id ++)
  {
    hexRGB.color(hex_id, CRGB::Red);
  }
  hexRGB.show();
}

uint8_t i_0=0;
uint8_t i_1=0;
uint8_t i_2=0;
uint8_t sinBeat;
uint8_t demo_id=0;

CRGB color=CRGB::Red;

void loop(){  
  
  EVERY_N_MILLISECONDS( 100 ) 
  {    
    for (int hex_id=0; hex_id<NUM_HEX; hex_id ++)
    {    
      switch (demo_id)
      {
        case 0:
          hexRGB.border_gradient(hex_id, heatmap_gp,0,i_0*256/sizeof(HexRGB::HexBorderA));                      
          break;
        case 1:
          hexRGB.border_gradient(hex_id, heatmap_gp,0,i_0*256/sizeof(HexRGB::HexBorderA));
          hexRGB.border_gradient(hex_id, heatmap_gp,1,i_0*256/sizeof(HexRGB::HexBorderA));
          hexRGB.border_gradient(hex_id, heatmap_gp,2,i_0*256/sizeof(HexRGB::HexBorderA));
          hexRGB.border_gradient(hex_id, heatmap_gp,3,i_0*256/sizeof(HexRGB::HexBorderA));
          break;          
        case 2:
          hexRGB.color(hex_id,CRGB::Red);
          hexRGB.line(hex_id, CRGB::Yellow,beatsin8(30,0,6,0,0));
          break;
        case 3:
          hexRGB.fadeToBlack( hex_id, 10);
          hexRGB.led(hex_id,random8(HexRGB::HEXRGB_NUM_LEDS),CRGB::Red);
          break;
        case 4:
          hexRGB.color(hex_id,CRGB::Black);
          hexRGB.line(hex_id, CRGB::Red,3);
          hexRGB.rotation(hex_id, i_1);          
          break;
        case 5:
          color.setHue(i_2);
          hexRGB.color(hex_id,color); 
          break;          
        default:                  
          break;     
      }      
    }
    i_0=(i_0+1)%sizeof(HexRGB::HexBorderA);
    i_1=(i_1+1)%7;
    i_2+=5;
    
    hexRGB.show();
    M5.update();
    #ifdef _M5ATOM_H_
    if (M5.Btn.wasPressed()) 
    #else
    if (M5.BtnA.wasPressed()) 
    #endif
    {
        demo_id=(demo_id+1)%6;
        for (int hex_id=0; hex_id<NUM_HEX; hex_id ++)
        {
          hexRGB.color(hex_id, CRGB::Red);  
        }        
    }    
  }     
}
