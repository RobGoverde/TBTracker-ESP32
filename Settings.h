/*
Preset experiment through seperate .h files per board in subfolder "preset".
Here you can chose a board specific preset or make you own.

10-04-2026:
Also added a preset file for the call info so I dont have to erase my data every time I commit to GitHub after testing.
The CALL_PD7BOR call below is a Git Ignore file, so make sure you enter you own.

Rob Goverde - PD7BOR
============================================================================*/
//Chose callsign presets
#include "presets/CALL_PD7BOR.h" //Edit the CALL.h file in the "preset" folder with your own call or make a copy of it with an added _YOURCALL.

//Chose board specific preset file:
//Uncomment one to select:

//#include "presets/C3_Supermini_1278.h"     //Custom build.
//#include "presets/D0WDQ6_Devboard_1278.h"  //Custom build.
//#include "presets/HT62.h"                  //Heltec HT62. Build tutorial see: https://www.robgoverde.nl/ct62-balloon-tracker-how-to-english/
//#include "presets/S2_Mini_1278.h"          //For use with HAB tracker board by Jan PE1ANS (SK).
#include "presets/S3_Burst.h"              //Custom build on devboard for burstcontrol tesing.
//#include "presets/S3_Dev_SSDV_1280.h"      //Custom build, SSDV on 2.4GHz with a SX1280 radio.
//#include "presets/T3S3_SX1280PA.h"         //For the Lilygo T3S3 with SX1280PA (Out of the box use.)
