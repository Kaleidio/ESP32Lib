/*
	Author: Martin-Laclaustra 2020
	License: 
	Creative Commons Attribution ShareAlike 4.0
	https://creativecommons.org/licenses/by-sa/4.0/
	
	For further details check out: 
		https://github.com/bitluni
*/
#include "CompMode.h"

//ModeComposite arguments order:
//==============================
//Horizontal pixels (in order):
//   hFront,hSync,hBack,hRes,
//Vertical lines or half-lines (in order):
//   vFront,vPreEqHL,vSyncHL,vPostEqHL,vBack,vActive,
//Vertical half-lines specific of odd(first) or even(second) fields:
//   vOPreRegHL,vOPostRegHL,vEPreRegHL,vEPostRegHL,
//Vertical resolution reduction:
//   vDiv,
//Pixel rate in Hz:
//   pixelClock,
//Color encoding data:
//   burstStart,burstLength,colorClock,phaseAlternating
//Graphical adjustment of aspect ratio:
//   aspect


//=========
//PAL MODES
//=========
//625 lines/frame, 25 frames/s, h 15625 Hz, v 50 Hz, visible horizontal proportion 0.812
//color burst: ((1135/4) + (1/625)) * 15625 = 4433618.75 Hz +/- 5 Hz
//line: 64 us = 1.65 us + 4.7 us + 5.5 us + 52.15 us

const ModeComposite CompMode::MODEPAL288P(12, 38, 62, 400,  1,  6, 5, 5,  15, 288, 0, 0, 0, 0, 1, 8000000);
//312 line / 50 frame
//288 active lines

//125 ns/pix
//512 pix/line, 64 us/line, 15.625 kHz hSync, 4.75 us hSync
//312 lines/field-progressiveframe, 19.968 ms/field, 50.080 Hz vSync


const ModeComposite CompMode::MODEPAL576I(12, 38, 62, 400,  1,  5, 5, 5,  15, 288, 1, 0, 2, 1, 1, 8000000);
//625 line / 25 frame
//576 active lines

// every field has 1 half-line less (vPreEqHL 6->5) and 4 half-lines (1+2+0+1) are added to vsync part

//125 ns/pix
//512 pix/line, 64 us/line, 15.625 kHz hSync, 4.75 us hSync
//312.5 lines/field, 20 ms/field, 50 Hz vSync


const ModeComposite CompMode::MODEPAL288Pmax(20, 64, 88, 704,  1,  6, 5, 5,  15, 288, 0, 0, 0, 0, 1, 13333333);
//312 line / 50 frame
//288 active lines

//75 ns/pix
//856 pix/line, 64.200 us/line, 15.576324 kHz hSync, 4.8 us hSync
//312 lines/field-progressiveframe, 20.0304 ms/field, 49.924 Hz vSync


const ModeComposite CompMode::MODEPAL288Pmin(2, 5, 5, 52,  1,  6, 5, 5,  15, 288, 0, 0, 0, 0, 1, 1000000);
//312 line / 50 frame
//288 active lines

//1000 ns/pix
//64 pix/line, 64 us/line, 15.625 kHz hSync, 5 us hSync
//312 lines/field-progressiveframe, 19.968 ms/field, 50.080 Hz vSync


const ModeComposite CompMode::MODEPAL576Imin(2, 5, 5, 52,  1,  5, 5, 5,  15, 288, 1, 0, 2, 1, 1, 1000000);
//625 line / 25 frame
//576 active lines

//1000 ns/pix
//64 pix/line, 64 us/line, 15.625 kHz hSync, 5 us hSync
//312.5 lines/field, 20 ms/field, 50 Hz vSync


const ModeComposite CompMode::MODEPAL576Idiv3(12, 38, 62, 400,  1,  5, 5, 5,  15, 288, 1, 0, 2, 1, 3, 8000000);
//625 line / 25 frame
//576 active lines

//125 ns/pix
//512 pix/line, 64 us/line, 15.625 kHz hSync, 4.75 us hSync
//312.5 lines/field, 20 ms/field, 50 Hz vSync



//==========
//NTSC MODES
//==========
//525 lines/frame, 30 frames/s, h 15750 Hz, v 60 Hz, visible horizontal proportion 0.812
//color burst: 3579545 Hz

//525 lines/frame, 30 * 1000 / 1001 = 29.97 frames/s, h (5*1000000*63/88)*2/455 = 15734.2657 Hz = 4.5 * 1000000 / 286, v 59.94 Hz, visible horizontal proportion 0.812
//color burst: 5*1000000*63/88 = 3579545.4545 Hz +/- 10 Hz
//line: 63.5555 us = 1.5 us + 4.7 us + 4.5 us + 52.8555 us

const ModeComposite CompMode::MODENTSC240P(12, 38, 58, 400,  1,  6, 6, 6,  12, 240, 0, 0, 0, 0, 1, 8000000);
//262 line / 60 frame
//240 active lines

//125 ns/pix
//508 pix/line, 63.5 us/line, 15.74803 kHz hSync, 4.75 us hSync
//262 lines/field-progressiveframe, 16.637 ms/field, 60.107 Hz vSync


const ModeComposite CompMode::MODENTSC480I(12, 38, 58, 400,  1,  6, 6, 6,  12, 240, 0, 0, 1, 1, 1, 8000000);
//525 line / 30 frame
//480 active lines

//125 ns/pix
//508 pix/line, 63.5 us/line, 15.74803 kHz hSync, 4.75 us hSync
//262.5 lines/field, 16.668750 ms/field, 59.9925 Hz vSync


const ModeComposite CompMode::MODENTSC240Pmax(20, 64, 76, 688,  1,  6, 6, 6,  12, 240, 0, 0, 0, 0, 1, 13333333);
//262 line / 60 frame
//240 active lines

//75 ns/pix
//848 pix/line, 63.6 us/line, 15.72327 kHz hSync, 4.8 us hSync
//262 lines/field-progressiveframe, 16.6632 ms/field, 60.0125 Hz vSync


//===========
//COLOR MODES
//===========
const ModeComposite CompMode::MODEPALColor288P(18, 56, 94, 604,  1+78,  6, 5, 5,  15+10, 288-88, 0, 0, 0, 0, 1, 12051950,10,25,4433619,true);
const ModeComposite CompMode::MODENTSCColor240P(20, 56, 72, 652,  1+36,  6, 6, 6,  12+4, 240-40, 0, 0, 0, 0, 1, 12560000,13,32,3579545,false);


//===========
//OLD MODES
//===========
const ModeComposite CompMode::MODE400x300(32, 76, 380, 8, 8, 24, 278, 2, 1, 16, 8000000);
//1136 per line 
//920 visible
//84 sync
//132 front
//312 total lines

//856
const ModeComposite CompMode::MODEPAL312P(64, 96, 640, 56, 8, 23, 272, 9, 1, 32, 13333333, 70, 38, 4433619);
//const ModeComposite Composite::MODEPAL312P(84, 152, 840, 60, 8, 23, 272, 9, 1, 42, 17734475, 99, 40, 4433619);
//const ModeComposite   Composite::MODEPAL312P(44, 76, 420, 28, 8, 23, 272, 9, 1, 20, 8867238, 50, 20, 4433619);
//const ModeComposite Composite::MODENTSC312P(64, 96, 640, 56, 8, 23, 272, 9, 1, 32, 13333333, 70, 38, 4433619);

//4.43361875 * 4
