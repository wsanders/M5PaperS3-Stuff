// This version uses drawXBitmap which luckily works because reverse
// engineering XBM file format was tedious. Edit badge in GIMP, output
// with XBM file format, tweak macro names to not start with number.
// gcc header files seem to need to end with .h.

// ToDo: RTC, date display 

#include <epdiy.h>
#include <M5Unified.h>
#include "IMG_0573.h"
#include "bat0.h"
#include "bat1.h"
#include "bat2.h"
#include "bat3.h"
#include "bat4.h"

int pixel[3];
char *data;
int color = 0;
static constexpr const char* const wd[7] = {"Sun","Mon","Tue","Wed","Thr","Fri","Sat"};
// Dont forget the null!
char datestring[] = "XXX MM/YY/DDDD                          ";

void setup(void)
{
  int w,b;
  Serial.begin(921600);
  Serial.println(sizeof(int));  // size in bytes
  Serial.printf("size of int: %d\n",sizeof(int)); // max value an int can hold
  Serial.printf("INT_MAX: %d\n",INT_MAX); // max value an int can hold

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
  // A bit of screen clearing Fu to clear afterimages
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

  // I have no idea why this works but it does:
  auto t = time(nullptr);
  setenv("TZ","PST8PDT",1);
  tzset();
  auto tm = localtime(&t);

  sprintf(datestring, "%3s %02d/%02d/%04d",
      wd[tm->tm_wday], tm->tm_mon+1, tm->tm_mday, tm->tm_year+1900);
  // If you resize the font (even to 1.0x) it will look good
  M5.Display.setFont(&fonts::Font4);
  M5.Display.setTextSize(2.0);
  w = M5.Display.textWidth(datestring);
  M5.Display.drawString(datestring,(540-w)/2,900);

  // Battery 
  b = M5.Power.getBatteryLevel();
  if (b > 80) { 
    M5.Display.drawXBitmap(25, 20, bat4_bits, bat4_width, bat4_height, TFT_BLACK);
  } 
  else if (b > 60) { 
    M5.Display.drawXBitmap(25, 20, bat3_bits, bat3_width, bat3_height, TFT_BLACK);
  }
  else if (b > 40) { 
    M5.Display.drawXBitmap(25, 20, bat2_bits, bat2_width, bat2_height, TFT_BLACK);
  }
  else if (b > 20) { 
    M5.Display.drawXBitmap(25, 20, bat1_bits, bat1_width, bat1_height, TFT_BLACK);
  } 
  else { 
    M5.Display.drawXBitmap(25, 20, bat0_bits, bat0_width, bat0_height, TFT_BLACK);
  }

  M5.Display.endWrite();
  //seconds until midnight
  w = 3600*(23 - tm->tm_hour) + 60*(60 - tm->tm_min) + tm->tm_sec + 10;
  //M5.Display.fillScreen(TFT_WHITE);
  //M5.Display.setCursor(100,300);
  //M5.Display.setFont(&fonts::Font8x8C64);
  Serial.printf("SLEEP %d SEC  %2d  %2d  %2d \n", w, tm->tm_hour, tm->tm_min, tm->tm_sec);
  M5.Display.printf("SLEEP %d SEC: %2d:%2d:%2d \n", w, tm->tm_hour, tm->tm_min, tm->tm_sec);
  // sleep a while to make it easier to upload
  sleep(240);
  M5.Power.timerSleep(w);
  
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

