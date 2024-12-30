// This version uses drawXBitmap which luckily works because reverse
// engineering XBM file format was tedious. Create your badge in GIMP, output
// with XBM file format, tweak macro names to not start with number.
// gcc header files seem to need to end with .h.

// After the program starts, a dot in the lower right of the scren will blink
// to let you know the device is powered on. While the dot is TFT_WHITE, 
// double click the power button to power it off.

// We tried unsing M5Unified and M5.begin() to set up the display but it did not work.

#include <epdiy.h>
#include <M5GFX.h>
#include <M5Unified.h>
#include "IMG_0573.h"

M5GFX display;
int pixel[3];
char *data;
int color = 0;


void setup(void)
{
  display.init();
  display.setTextSize(5.0);
  if (display.isEPD())
  {
    display.setEpdMode(epd_mode_t::epd_fastest);
  }
  // eyelet at top
  display.setRotation(display.getRotation() ^ 2);
  // Crashes here, do not use: M5.begin();
  //M5.Speaker.setVolume(255);
  //M5.Speaker.tone(2000, 100); 
  display.println("I RUN");
  
  display.startWrite();
  display.fillScreen(TFT_WHITE);
  display.drawXBitmap(0, 0, xbm_bits, xbm_width, xbm_height, TFT_BLACK);
  display.endWrite();
}

void loop(void)
{
  display.startWrite();
  if (color == 0)
  {
     display.fillCircle(500,910,20,TFT_WHITE);
  }
  else
  {
     display.fillCircle(500,910,20,TFT_BLACK);
  }
  display.endWrite();
  color = (color + 1) % 2;
  sleep(3);
}
