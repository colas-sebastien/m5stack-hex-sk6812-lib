/*

*/

#include "HexRGB.h"
#include "FastLED.h"


HexRGB::HexRGB(int number_hex,int brightness)
{
  leds   =new CRGB[HEXRGB_NUM_LEDS*number_hex];
  tmpLeds=new CRGB[HEXRGB_NUM_LEDS];
  
  FastLED.addLeds<WS2811,HEXRGB_PIN,GRB>(leds, HEXRGB_NUM_LEDS*number_hex).setCorrection(TypicalLEDStrip);
  for (int i=0; i<HEXRGB_NUM_LEDS*number_hex; i++)
  {
    leds[i]=CRGB::Black;
  } 
  FastLED.setBrightness(brightness); //set the LED brightness to 5.  
}

void HexRGB::color(int hex_id, CRGB color)
{
  for (int i=0; i<HEXRGB_NUM_LEDS; i++)
  {
    leds[i+HEXRGB_NUM_LEDS*hex_id]=color;
  } 
}

void HexRGB::led_array(int hex_id, CRGB color,uint8_t *led_array,int led_array_size)
{
  for (int i=0;i<led_array_size;i++)
  {
    leds[led_array[i]+HEXRGB_NUM_LEDS*hex_id]=color;
  }  
}

void HexRGB::border(int hex_id, CRGB color, int border_id)
{  
  switch (border_id) {
    case 0: HexRGB::led_array(hex_id,color,HexBorderA,sizeof(HexBorderA)); break;
    case 1: HexRGB::led_array(hex_id,color,HexBorderB,sizeof(HexBorderB)); break;
    case 2: HexRGB::led_array(hex_id,color,HexBorderC,sizeof(HexBorderC)); break;
    case 3: HexRGB::led_array(hex_id,color,HexBorderD,sizeof(HexBorderD)); break;
    default: return; break;
  }
}

void HexRGB::line(int hex_id, CRGB color, int line_id)
{ 
  switch (line_id) {
    case 0: HexRGB::led_array(hex_id,color,HexLineA,sizeof(HexLineA)); break;    
    case 1: HexRGB::led_array(hex_id,color,HexLineB,sizeof(HexLineB)); break;
    case 2: HexRGB::led_array(hex_id,color,HexLineC,sizeof(HexLineC)); break;
    case 3: HexRGB::led_array(hex_id,color,HexLineD,sizeof(HexLineD)); break;
    case 4: HexRGB::led_array(hex_id,color,HexLineE,sizeof(HexLineE)); break;
    case 5: HexRGB::led_array(hex_id,color,HexLineF,sizeof(HexLineF)); break;
    case 6: HexRGB::led_array(hex_id,color,HexLineG,sizeof(HexLineG)); break;    
    default: return; break;
  }  
}

void HexRGB::diagonal(int hex_id, CRGB color, int diagonal_id)
{  
  switch (diagonal_id) {
    case  0: HexRGB::led_array(hex_id,color,HexDiagonalA,sizeof(HexDiagonalA)); break;
    case  1: HexRGB::led_array(hex_id,color,HexDiagonalB,sizeof(HexDiagonalB)); break;
    case  2: HexRGB::led_array(hex_id,color,HexDiagonalC,sizeof(HexDiagonalC)); break;
    case  3: HexRGB::led_array(hex_id,color,HexDiagonalD,sizeof(HexDiagonalD)); break;
    case  4: HexRGB::led_array(hex_id,color,HexDiagonalE,sizeof(HexDiagonalE)); break;
    case  5: HexRGB::led_array(hex_id,color,HexDiagonalF,sizeof(HexDiagonalF)); break;
    case  6: HexRGB::led_array(hex_id,color,HexDiagonalG,sizeof(HexDiagonalG)); break;
    case  7: HexRGB::led_array(hex_id,color,HexDiagonalH,sizeof(HexDiagonalH)); break;
    case  8: HexRGB::led_array(hex_id,color,HexDiagonalI,sizeof(HexDiagonalI)); break;
    case  9: HexRGB::led_array(hex_id,color,HexDiagonalJ,sizeof(HexDiagonalJ)); break;
    case 10: HexRGB::led_array(hex_id,color,HexDiagonalK,sizeof(HexDiagonalK)); break;
    case 11: HexRGB::led_array(hex_id,color,HexDiagonalL,sizeof(HexDiagonalL)); break;
    case 12: HexRGB::led_array(hex_id,color,HexDiagonalM,sizeof(HexDiagonalM)); break;                                                
    default: return; break;
  }  
}

void HexRGB::triangle(int hex_id, CRGB color)
{
  uint8_t triangle[] = {0,1,2,3,5,6,7,11,12,18};
  HexRGB::led_array(hex_id,color,triangle,sizeof(triangle));  
}

void HexRGB::rotation(int hex_id, int rotation_id)
{  
  int new_index;
  
  for (int i=0;i<HEXRGB_NUM_LEDS; i++)
  {
    tmpLeds[i]=leds[i+HEXRGB_NUM_LEDS*hex_id];
  }
  
  for (int i=0;i<HEXRGB_NUM_LEDS; i++)
  {
    new_index=i;
    for (int j=0;j<rotation_id%6;j++)
    {
      new_index=HexRotation[new_index];
    }
    leds[i+HEXRGB_NUM_LEDS*hex_id]=tmpLeds[new_index];
  }  
}

void HexRGB::gradient(int hex_id, CRGBPalette16 palette, int direction,int index)
{
  CRGB color;
  if (direction == 0)
  {
    for (int i=0;i<HEXRGB_NUM_LINES;i++)
    {
      color=ColorFromPalette(palette, index+i*256/HEXRGB_NUM_LINES);
      HexRGB::line(hex_id, color, i);
    }    
  }
  if (direction == 1)
  {
    for (int i=0;i<HEXRGB_NUM_DIAGONALS;i++)
    {
      color=ColorFromPalette(palette, index+i*256/HEXRGB_NUM_DIAGONALS);
      HexRGB::diagonal(hex_id, color, i);
    }    
  }    
  if (direction == 2)
  {
    for (int i=0;i<HEXRGB_NUM_LEDS;i++)
    {
      color=ColorFromPalette(palette, index+i*256/HEXRGB_NUM_LEDS);
      leds[i+HEXRGB_NUM_LEDS*hex_id]=color;
    }    
  }
  if (direction == 3)
  {
    for (int i=0;i<HEXRGB_NUM_LEDS;i++)
    {
      color=ColorFromPalette(palette, index+i*256/HEXRGB_NUM_LEDS);
      leds[HexBrowse1[i]+HEXRGB_NUM_LEDS*hex_id]=color;
    }    
  }  
}

void HexRGB::border_gradient(int hex_id, CRGBPalette16 palette,int border_id,int index)
{
  CRGB color;
  int nb_leds;
  uint8_t *border;

  switch (border_id) {
    case 0: border=HexBorderA;nb_leds=sizeof(HexBorderA);break;
    case 1: border=HexBorderB;nb_leds=sizeof(HexBorderB);break;
    case 2: border=HexBorderC;nb_leds=sizeof(HexBorderC);break;
    case 3: border=HexBorderD;nb_leds=sizeof(HexBorderD); break;
    default: return; break;
  }  
  
  for (int i=0;i<nb_leds;i++) 
  {
    color=ColorFromPalette(palette, index+i*256/nb_leds);
    leds[border[i]+HEXRGB_NUM_LEDS*hex_id]=color;    
  }        
}

void HexRGB::gradient(int hex_ids[], int nb_hex, CRGBPalette16 palette, int direction,int index,int gap)
{
  CRGB color;

  if (direction == 0)
  {
    int nb_lines=HEXRGB_NUM_LINES*nb_hex+(nb_hex-1)*gap;
    for (int hex=0;hex<nb_hex;hex ++)
    {
      for (int i=0;i<HEXRGB_NUM_LINES;i++)
      {
        color=ColorFromPalette(palette, (index+256/nb_lines*(i+(gap+HEXRGB_NUM_LINES)*hex))%256);
        
        HexRGB::line(hex_ids[hex], color, i);
      }    
    }
  }/*
  if (direction == 1)
  {
    for (int i=0;i<HEXRGB_NUM_DIAGONALS;i++)
    {
      color=ColorFromPalette(palette, index+i*256/HEXRGB_NUM_DIAGONALS);
      HexRGB::diagonal(hex_id, color, i);
    }    
  }    */
}

void HexRGB::led(int hex_id, int pixel_id, CRGB color)
{
  leds[pixel_id+HEXRGB_NUM_LEDS*hex_id]=color;
}

void HexRGB::fadeToBlack  (int hex_id, uint8_t fadeBy)
{
  CRGB *hex_leds;
  hex_leds=&leds[HEXRGB_NUM_LEDS*hex_id];
  fadeToBlackBy(hex_leds, HEXRGB_NUM_LEDS, fadeBy);
}

uint8_t HexRGB::browse(int model,uint8_t index)
{
  uint8_t browse_index=index;
  
  switch (model) {
    case 1:browse_index=HexBrowse1[index];break;
    case 2:browse_index=HexBrowse1[HEXRGB_NUM_LEDS-1-index];break;
    default: break;
  }    
  return browse_index;
}

void HexRGB::show()
{
  FastLED.show();
}
