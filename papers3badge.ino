// This version uses drawXBitmap which luckily works because reverse
// engineering XBM file format was tedious. Create your badge in GIMP, output
// with XBM file format, tweak macro names to not start with number.
// gcc header files seem to need to end with .h.

// After the program starts, a dot in the lower right of the scren will blink
// to let you know the device is powered on. While the dot is TFT_WHITE, 
// double click the power button to power it off.

#include <M5Unified.h>
#include "IMG_0573.h"

int pixel[3];
char *data;
int color = 0;


void setup(void)
{
  auto cfg = M5.config();
  cfg.serial_baudrate = 115200;
  M5.begin(cfg);

  M5.Display.setTextSize(5.0);
  if (M5.Display.isEPD())
  {
    M5.Display.setEpdMode(epd_mode_t::epd_fastest);
  }
  // eyelet at top
  M5.Display.setRotation(M5.Display.getRotation() ^ 2);
  // For later - try tone, etc.
  //M5.Speaker.setVolume(255);
  //M5.Speaker.tone(2000, 100); 
  M5.Display.println("I RUN");
  
  M5.Display.startWrite();
  M5.Display.fillScreen(TFT_WHITE);
  M5.Display.drawXBitmap(0, 0, xbm_bits, xbm_width, xbm_height, TFT_BLACK);
  M5.Display.endWrite();
}

void loop(void)
{
  M5.Display.startWrite();
  if (color == 0)
  {
     M5.Display.fillCircle(500,910,20,TFT_WHITE);
  }
  else
  {
     M5.Display.fillCircle(500,910,20,TFT_BLACK);
  }
  M5.Display.endWrite();
  color = (color + 1) % 2;
  sleep(3);
}

