#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h>
// Utility Macros
#define FAN_SIZE 8       // How many pixels per fan
#define NUM_FANS 1       // Number of fans in the strans
#define LED_FAN_OFFSET 0 // How far from 12 o'clock first pixel is  IE HOW FAR TO ROTATE FAN TO GET 0 TO BE BOTTOM
#define NUM_LEDS (FAN_SIZE * NUM_FANS)

extern CRGBArray</*NUM_STRIPS*/ NUM_FANS * FAN_SIZE> g_LEDs;

static const int FanPixelsVertical[FAN_SIZE] =
{
  4, 5, 3, 6, 2, 7, 1, 0
};
static const int FanPixelsHorizontal[FAN_SIZE] =
{
  2, 3, 1, 4, 0 , 5, 7, 6
};
enum PixelOrder
{
  Sequential = 0,
  Reverse    = 1,
  BottomUp   = 2,
  TopDown    = 4,
  LeftRight  = 8,
  RightLeft  = 16
};

int GetFanPixelOrder(int iPos, PixelOrder order = Sequential)
{
  while (iPos < 0)
    iPos += FAN_SIZE;

  int offset = (iPos + LED_FAN_OFFSET) % FAN_SIZE;  // Offset within this fan
  int roffset = (iPos + FAN_SIZE - LED_FAN_OFFSET) % FAN_SIZE;  // Offset within this fan

  int fanBase = iPos - (iPos % FAN_SIZE);           // Round down to previous multiple of FAN_SIZE
  
  switch (order)
  {
    case BottomUp:
      return fanBase + FAN_SIZE - 1 - (FanPixelsVertical[iPos % FAN_SIZE] + LED_FAN_OFFSET) % FAN_SIZE;
    
    case TopDown:
      return NUM_LEDS - 1 - (fanBase + (FanPixelsVertical[FAN_SIZE - 1 - (iPos % FAN_SIZE)] + LED_FAN_OFFSET) % FAN_SIZE);

    case LeftRight:
      return fanBase + (FanPixelsHorizontal[ iPos % FAN_SIZE ] + LED_FAN_OFFSET - 1) % FAN_SIZE;
    
    case RightLeft:
      return fanBase + (FanPixelsHorizontal[FAN_SIZE - 1 - (iPos % FAN_SIZE) ] + LED_FAN_OFFSET - 1) % FAN_SIZE;

   case Reverse:
      return fanBase + FAN_SIZE - 1 - roffset;

    case Sequential:
    default:
      return fanBase + offset;
  }
}

void DrawFanPixels(float fPos, float count, CRGB color, PixelOrder order = Sequential, int iFan = 0)
{
  fPos += iFan * FAN_SIZE;
  int remaining = count;
  int iPos = fPos;
  while(remaining>0)
  {
    g_LEDs[GetFanPixelOrder(iPos++, order)] = color;
    remaining--;
  }
   
}
