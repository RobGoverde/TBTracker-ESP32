/*
Preset experiment through seperate .h files per board in subfolder "preset".
Here you can still enter you general settings.

Select the preset file and enter your callsign here first.
You can either edit an existing preset file or copy and edit a new one in the preset folder.

Rob Goverde - PD7BOR
============================================================================*/

//Chose preset file:
#include "presets/S3_Dev_SSDV_GHz.h" 

//== Personal settings: ==

//ENTER YOU CALLSIGN: (For all modes except Horus and LoRa.)
#define YOUR_CALL "N0CALL"

//LoRa Setup:
#define YOUR_LORA_CALL "N0CALL-11" //Differen setup because it needs the SSID in it. (For now.)
#define LORA_APRS_SSID "-11"

//Horus setup:
#define PAYLOAD_ID_V1 0              // For Horus V1. See above. Set to 0 if you do not have a payload ID
#define PAYLOAD_ID_V2 256            // For Horus V2. See above. Set to 256 if you do not have a payload ID
#define HORUS_V3_CALLSIGN "N0CALL"   // Horus V3 callsign and is free to choose but keep it AS SHORT AS POSSIBLE (adding V3 in the call is not necessary and not recommended)




