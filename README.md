# M5PaperS3-Stuff

## Hints 
- To install the epdiy library, I just cloned it into my Arduino IDE "libraries" directory. No further configuration was required.

## Arduino IDE: M5PaperS3 Simple Badge.

Simple demo to display a badge on the PaperS3.

I tried using SPIFFS and drawJpegFile but could not get it to work. I had this problem with the M5StickC2 Nixie Watch as well. The workaround is to compile in the images with .h files. Not so bad with small images, but huge bloat with bigger ones. Luckily, for an E-Ink display, monochrome works best, so an XBM file image is about 1/3 the size of a full color JPG. Bloated, but manageable.

This version uses drawXBitmap which luckily works because reverse
engineering the XBM file format is tedious. Create your badge in GIMP as an image with size 540x960 and export it in XBM file format. Tweak macro names (which can't start with a number.)

At least in the Arduino IDE, gcc header files seem to need to end in .h.

Features from M5United
- M5.Imu.sleep call hopefully saves some power - hard to tell if it's working.
- Draw local time in PST8PDT timezone at bottom of screen. RTC must be previously set to UTC.
- Use M5.Power.timerSleep to sleep device and then wake it up every hour to update the date.

If the timerSLeep call is removed or fails, a dot in the lower right of the screen will blink
to let you know the device is still powered on. While the dot is TFT_WHITE, 
double click the power button to power it off.





