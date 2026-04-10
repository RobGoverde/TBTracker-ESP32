/*
Preset experiment through seperate .h files per board in subfolder "preset".
Here you can chose a board specific preset or make you own.

10-04-2026:
Also added a preset file for the call info so I dont have to erase my data every time I commit to GitHub after testing.
The CALL_PD7BOR call below is a Git Ignore file, so make sure you enter you own.

Rob Goverde - PD7BOR
============================================================================*/

//Chose board specific preset file:
#include "presets/S3_Burst.h" //Please see the /preset/ folder.

//Chose callsign presets
#include "presets/CALL_PD7BOR.h" //Edit the CALL.h file in the "preset" folder with your own call or make a copy of it with an added _YOURCALL.



