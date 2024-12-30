// This version uses drawXBitmap which luckily works because reverse
// engineering XBM file format was tedious. Edit badge in GIMP, output
// with XBM file format, tweak macro names to not start with number.
// gcc header files seem to need to end with .h.

// ToDo: RTC, date display 

#include <epdiy.h>
#include <M5Unified.h>
#include "IMG_0573.h"

int pixel[3];
char *data;
int color = 0;
int w;
static constexpr const char* const wd[7] = {"Sun","Mon","Tue","Wed","Thr","Fri","Sat"};
// Dont forget the null!
char datestring[] = "XXX MM/YY/DDDD                          ";

void setup(void)
{
  auto cfg = M5.config();
  M5.begin(cfg);
  M5.Imu.sleep();
  M5.Display.setTextSize(4.0);
  if (M5.Display.isEPD())
  {
    M5.Display.setEpdMode(epd_mode_t::epd_quality);
  }
  // eyelet at top
  M5.Display.setRotation(M5.Display.getRotation() ^ 2);
  M5.Speaker.setVolume(255);
  M5.Speaker.tone(1000, 1000); 
  M5.Display.startWrite();
  M5.Display.fillScreen(TFT_BLACK);
  M5.Display.endWrite();
  sleep(1);
  M5.Display.startWrite();
  M5.Display.fillScreen(TFT_WHITE);
  M5.Display.endWrite();
  sleep(1);
  M5.Display.startWrite();
  M5.Display.drawXBitmap(0, 0, xbm_bits, xbm_width, xbm_height, TFT_BLACK);

  // Print the date
  auto t = time(nullptr);
  setenv("TZ","PST8PDT",1);
  tzset();
  auto tm = localtime(&t);
  sprintf(datestring, "%3s %02d/%02d/%04d",
      wd[tm->tm_wday], tm->tm_mon+1, tm->tm_mday, tm->tm_year+1900);
  M5.Display.setFont(&fonts::DejaVu12);
  w = M5.Display.textWidth(datestring);
  M5.Display.drawString(datestring,(540-w)/2,900);
  M5.Display.endWrite();
  M5.Power.timerSleep(7200);
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

