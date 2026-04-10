//============================================================================
// Here you can define you call and LoRa SSID.
// This will transfer across all boards, just define you "CALL.h" file in settings.
// 
//============================================================================
//Settings based on TBTracker-ESP32 by Roel Kroes.

 //ENTER YOU CALLSIGN: (For all modes except Horus and LoRa.)
#define YOUR_CALL "yourcall"

//LoRa Setup:
#define YOUR_LORA_CALL "YOURCALL-L" //Differen setup because it needs the SSID in it. (For now.)
#define LORA_APRS_SSID "-11"

//Horus setup:
#define PAYLOAD_ID_V1 0              // For Horus V1. See above. Set to 0 if you do not have a payload ID
#define PAYLOAD_ID_V2 256            // For Horus V2. See above. Set to 256 if you do not have a payload ID
#define HORUS_V3_CALLSIGN "N0CALL"   // Horus V3 callsign and is free to choose but keep it AS SHORT AS POSSIBLE (adding V3 in the call is not necessary and not recommended)


