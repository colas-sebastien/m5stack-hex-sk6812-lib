/*
  
*/
#ifndef HexRGB_h
#define HexRGB_h

#include "FastLED.h"

#define HEXRGB_PIN            26  // Port B
/*                                  
 *  M5Core    Port A  Pin 21
 *            Port B  Pin 26
 *            Port C  Pin 17
 *            
 *  M5Atom    Port    Pin 26
 *  
 *  M5Stick   Port    Pin 32
 */
                                  


class HexRGB
{
  public:

    // Usesfull values to control the Hex
    const uint8_t HEXRGB_NUM_LEDS      = 37;
    const uint8_t HEXRGB_NUM_LINES     =  7;
    const uint8_t HEXRGB_NUM_DIAGONALS = 13;

    // Contructor
    HexRGB(int number_hex,int brightness);
    
    void    led            (int hex_id, int pixel_id, CRGB color);
    void    color          (int hex_id, CRGB color);
    void    border         (int hex_id, CRGB color, int border_id);
    void    border_gradient(int hex_id, CRGBPalette16 palette,int border_id,int index);
    void    line           (int hex_id, CRGB color, int line_id);    
    void    diagonal       (int hex_id, CRGB color, int diagonal_id);    
    void    triangle       (int hex_id, CRGB color);    
    void    rotation       (int hex_id, int rotation_id);
    void    gradient       (int hex_id, CRGBPalette16 palette, int direction,int index);
    void    gradient       (int hex_ids[],int nb_hex, CRGBPalette16 palette, int direction,int index, int gap);
    void    fadeToBlack    (int hex_id, uint8_t fadeBy);
    uint8_t browse         (int model,uint8_t index);
    void show();
    void led_array(int hex_id, CRGB color, uint8_t *led_array,int led_array_size);
    
  private:
    CRGB *tmpLeds;
    CRGB *leds;   

    uint8_t HexRotation[37] = { 3, 8,14,21, 2, 7,13,20,27, 1, 6,12,19,26,32, 0, 5,11,18,25,31,36, 4,10,17,24,30,35, 9,16,23,29,34,15,22,28,33};
    
    uint8_t HexBorderA[18] = { 0, 1, 2, 3, 8,14,21,27,32,36,35,34,33,28,22,15, 9, 4};
    uint8_t HexBorderB[12] = { 5, 6, 7,13,20,26,31,30,29,23,16,10};
    uint8_t HexBorderC[ 6] = {11,12,19,25,24,17};
    uint8_t HexBorderD[ 1] = {18};
    
    uint8_t HexLineA[ 4] = { 0, 1, 2, 3};
    uint8_t HexLineB[ 5] = { 4, 5, 6, 7, 8};
    uint8_t HexLineC[ 6] = { 9,10,11,12,13,14};
    uint8_t HexLineD[ 7] = {15,16,17,18,19,20,21};
    uint8_t HexLineE[ 6] = {22,23,24,25,26,27};
    uint8_t HexLineF[ 5] = {28,29,30,31,32};
    uint8_t HexLineG[ 4] = {33,34,35,36};
    
    uint8_t HexDiagonalA[ 1] = {0};
    uint8_t HexDiagonalB[ 2] = {4,1};
    uint8_t HexDiagonalC[ 3] = {9,5,2};
    uint8_t HexDiagonalD[ 4] = {15,10,6,3};
    uint8_t HexDiagonalE[ 3] = {16,11,7};
    uint8_t HexDiagonalF[ 4] = {22,17,12,8};
    uint8_t HexDiagonalG[ 3] = {23,18,13};
    uint8_t HexDiagonalH[ 4] = {28,24,19,14};
    uint8_t HexDiagonalI[ 3] = {29,25,20};
    uint8_t HexDiagonalJ[ 4] = {33,30,26,21};
    uint8_t HexDiagonalK[ 3] = {34,31,27};
    uint8_t HexDiagonalL[ 2] = {35,32};
    uint8_t HexDiagonalM[ 1] = {36};     
    
    uint8_t HexBrowse1[37] = {0,1,2,3,8,14,21,27,32,36,35,34,33,28,22,15,9,4,5,6,7,13,20,26,31,30,29,23,16,10,11,12,19,25,24,17,18};   
};

#endif           
