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

#include <M5Stack.h>
#include "HexRGB.h"

#define NUM_HEX     3
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

int hex_ids[]={2,1};

HexRGB hexRGB(NUM_HEX,BRIGTHNESS);

void setup() {
  M5.begin();             //Init M5Stack.
  M5.Power.begin();       //Init power 

  hexRGB.show();
}

uint8_t i=0;
uint8_t sinBeat;

void loop(){  

/*
  EVERY_N_MILLISECONDS( 100 ) 
  {
    hexRGB.fadeToBlack( 0, 80);
    hexRGB.led(0,hexRGB.browse(2,i),CRGB::Red);
        
    i++;
    if (i>=hexRGB.HEXRGB_NUM_LEDS)
    {
      i=0;
    }
    hexRGB.show();

  }

  EVERY_N_MILLISECONDS( 100 ) 
  {
    hexRGB.fadeToBlack( 0, 20);
    int pos = random8(37);
    hexRGB.led(0,pos,CRGB::Green);
    hexRGB.show();
  } 
*/
  

  EVERY_N_MILLISECONDS( 10 ) 
  {
    sinBeat=beatsin8(30,0,6,0,0);
    hexRGB.color(0,CRGB::Black);
    hexRGB.line(0, CRGB::Red,sinBeat);
    hexRGB.show();
  } 
/*  
  hexRGB.border(0, CRGB::Blue,0);
  hexRGB.border(0, CRGB::Blue,3);
  hexRGB.border(1, CRGB::Blue,1);
  hexRGB.border(2, CRGB::Blue,2);
  hexRGB.line(2, CRGB::Red,0);
  
  hexRGB.show();
  
  
  EVERY_N_MILLISECONDS( 50 ) 
  {     
    hexRGB.color(1, CRGB::Blue);
    hexRGB.border_gradient(0, wave_gp,0,i*256/18);
    hexRGB.border_gradient(0, wave_gp,1,i*256/18);
    hexRGB.border_gradient(0, wave_gp,2,i*256/18);
    hexRGB.border_gradient(0, wave_gp,3,i*256/18);
    hexRGB.border_gradient(1, heatmap_gp,0,i*256/18);
    hexRGB.gradient(2, b_w_gp,3,i*256/37);
    i++;
    if (i>36)
    {
      i=0; 
    }
    hexRGB.show();
  } 
  */
}
