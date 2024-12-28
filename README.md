# M5PaperS3-Stuff

## Hints 
- To install the epdiy library, just clone it into your arduino IDE libraries directory.

## Arduino IDE: M5PaperS3 Simple Badge.

Simple demo to display a badge on the PaperS3.

I tried using SPIFFS and drawJpegFile but could not get it to work. I had this problem with the M5StickC2 Nixie Watch as well. The workaround is to compile in the images with .h files. Not so bad with small images, but huge bloat with bigger ones. Luckily, for an E-Ink display, monochrome works best, so an XBM file image is about 1/3 the size of a full color JPG. Bloated, but manageable.

This version uses drawXBitmap which luckily works because reverse
engineering the XBM file format is tedious. Create your badge in GIMP as an image with size 540x960 and export it in XBM file format. Tweak macro names (which can't start with a number.)

At least in the Arduino IDE, gcc header files seem to need to end in .h.

At this point in time, using M5Unified for PaperS3 is a work in progress.
My call to M5Begin() just put the device in a crash/reboot loop. 

After the program starts, a dot in the lower right of the screen will blink
to let you know the device is powered on. While the dot is TFT_WHITE, 
double click the power button to power it off.





