//You need to connect a composite TV input cable to the pins specified below.
//cc by-sa 4.0 license
//Martin-Laclaustra
/*
    CONNECTION

    A) voltageDivider = false; B) voltageDivider = true

       55 shades                  179 shades

    ESP32        TV            ESP32                       TV     
    -----+                     -----+    ____ 100 ohm
        G|-                        G|---|____|+          
    pin25|--------- Comp       pin25|---|____|+--------- Comp    
    pin26|-                    pin26|-        150 ohm
         |                          |
         |                          |
    -----+                     -----+                              

    Connect pin 25 or 26
  
    C) R-2R resistor ladder; D) unequal rungs ladder

       55 shades                  up to 254 shades?

    ESP32        TV           ESP32                       TV
    -----+                    -----+    ____ 
        G|-+_____                 G|---|____|
    pinA0|-| R2R |- Comp      pinA0|---|____|+--------- Comp
    pinA1|-|     |            pinA1|---|____|
    pinA2|-|     |              ...|
      ...|-|_____|                 |
    -----+                    -----+

    Connect pins of your choice (A0...A8=any pins).
    Custom ladders can be used by tweaking colorMinValue and colorMaxValue
*/

#include <ESP32Lib.h>
#include <Ressources/CodePage437_8x8.h>
#include <Composite/CompMode.h>

//pin configuration for DAC
const int outputPin = 25;

CompositeColorDAC display;
//CompositeColorLadder display;

void setup()
{
  //initializing composite at the specified pins
  //output pin and boolean for voltage divider can be omitted
  //see Composite/CompMode.h for other modes
  display.init(CompMode::MODENTSCColor240P, 25, false);
  //display.init(CompMode::MODEPALColor288P, 25, false);
  //use these for the ladder hardware configuration
  //display.init(CompMode::MODENTSCColor240P, display.XPlayer);
  //This PAL mode did not work with the ladder
  //display.init(CompMode::MODEPALColor288P, display.XPlayer);
  //But this PAL mode works
  //display.init(ModeComposite(10, 30, 48, 312,  1,  6, 5, 5,  15, 288, 0, 0, 0, 0, 1, 6244533,5,16,4433619,true), display.XPlayer);
  //NOTE: PAL color only works for CRT TVs, not LDC TVs


  display.fillCircle(25 + 55, 50, 1 + 50 / 4, display.RGB(96, 0, 0));
  display.fillCircle(25 + 55+30, 50, 1 + 50 / 4, display.RGB(0, 96, 0));
  display.fillCircle(25 + 55+60, 50, 1 + 50 / 4, display.RGB(0, 0, 96));

  display.fillCircle(100 + 25 + 55, 50, 1 + 50 / 4, display.RGB(255, 0, 0));
  display.fillCircle(100 + 25 + 55+30, 50, 1 + 50 / 4, display.RGB(0, 255, 0));
  display.fillCircle(100 + 25 + 55+60, 50, 1 + 50 / 4, display.RGB(0, 0, 255));

  display.fillCircle(200 + 25 + 55, 50, 1 + 50 / 4, display.RGB(96, 96, 0));
  display.fillCircle(200 + 25 + 55+30, 50, 1 + 50 / 4, display.RGB(0, 96, 96));
  display.fillCircle(200 + 25 + 55+60, 50, 1 + 50 / 4, display.RGB(96, 0, 96));

  display.fillCircle(300 + 25 + 55, 50, 1 + 50 / 4, display.RGB(255, 255, 0));
  display.fillCircle(300 + 25 + 55+30, 50, 1 + 50 / 4, display.RGB(0, 255, 255));
  display.fillCircle(300 + 25 + 55+60, 50, 1 + 50 / 4, display.RGB(255, 0, 255));



  //selecting the font
  display.setFont(CodePage437_8x8);
  //displaying the test pattern
  display.fillRect(8+30-4, 88-2, (2*255)+5+8, 40+4+4, display.RGB(127,127,127));
  display.fillRect(8+30, 88, (2*255)+5, 40+4, display.RGB(0,0,0));
  display.setTextColor(display.RGB(192,192,192));
  for(int x = 0; x < 256*2; x+=2)
  {
    display.fillRect(8+x + 32, 90, 2, 40, display.RGB(x/2,x/2,x/2));
    if(x % 32 == 0)
    {
      display.fillRect(8+x + 32, 85, 4, 4, display.RGB(255,255,255));
      display.setCursor(8+x + 32 - 4, 78 - 4);
      display.print(x/2,HEX);
    }
  }
}

void loop()
{
}
