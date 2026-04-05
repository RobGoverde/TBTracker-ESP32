//============================================================================
// Here you can make custom presets to enable setting up for different boards 
// without changing all the pins.
//============================================================================
//Settings based on TBTracker-ESP32 by Roel Kroes.

  //SPI:
  #define SCK 47
  #define MISO 14
  #define MOSI 21
  #define CS 1
  
  //Radio:
  #define PIN_NSS 1
  #define PIN_DIO0 -1
  #define PIN_BUSY 41     
  #define PIN_RESET 42
  #define PIN_DIO1 20
  #define PIN_DIO2 -1  
  #define USE_TCXO 0.0
  #define USE_SX1280 //Chose: USE_SX127X, USE_RF69, USE_SX1262, USE_SX1268, USE_LLCC68, USE_SX1280, USE_SX1280PA
  
//GPS:
static const int Rx = -1, Tx = 8;     // This will probably be different for your board
static const uint32_t GPSBaud = 9600;  // modern devices are 9600 baud. some are 4800 baud.
  
//Sensors:
  // Comment the five lines below out if you do not use a voltage divider
  //============================================================================
  // #define USE_VOLTAGE_INFO          // Uncomment this if you use a voltage divider
  // #define VOLTAGE_IN_PIN 3          // Pin number to which the voltage divider is connected
  // #define VOLTAGE_DIVIDER_R1 100000 // in Ohm 100K is a good value for voltage between 2 and 6 volts
  // #define VOLTAGE_DIVIDER_R2 100000 // in Ohm 100K is a good value for voltage between 2 and 6 volts
  // #define VOLTAGE_DEVIATION  0.0    // Will be added as an error offset to the calculated result of the voltage divider.In a perfect world this should be 0.00.
  // #define USE_VOLTAGE_IN_APRS     // If you uncomment this, the voltage information will be added to the APRS comment field
  // #define SDA_PIN 46  // your SDA pin for the I2C protocol (needed for BME280 sensor)
  // #define SCL_PIN 2  // your SCL pin for the I2C protocol (needed for BME280 sensor) 
  
  
//Modulation:
 
//Lora
#define LORA_ENABLED true        // Set to true if you want LoRa transmissions
#define RECEIVING_ENABLED false  // Set to true if you want the tracker to listen on the LoRa frequency for incoming packets
#define LORA_PAYLOAD_ID YOUR_LORA_CALL   // This will show on Sondehub. Payload ID for LoRa protocol. CHANGE THIS!
#define LORA_FREQUENCY 2400.0    // in MHz
#define LORA_MODE 24              // Mode 2 is usually used for simple telemetry data
#define LORA_REPEATS 1           // number of LoRa transmits during a cycle
#define LORA_LOOPTIME 40         // Transmit LoRa every xx seconds
#define LORA_FREQ_OFFSET 0.0     // Frequency deviation in MHz. Will be added to the LoRa frequency. Should be a float and can be negative.
#define LORA_BANDWIDTH 125.0  // Do not change, change LORA_MODE instead
#define LORA_SPREADFACTOR 9   // Do not change, change LORA_MODE instead
#define LORA_CODERATE 7       // Do not change, change LORA_MODE instead
#define LORA_PREFIX "$$"      // Prefix for "Telemetry". Some older LoRa software does not accept a prefix of more than 2x "$"
#define LORA_SYNCWORD 0x12    // Default syncword
#define LORA_POWER 2         // in dBm between 2 and 17. 10 = 10mW (recommended)
#define LORA_CURRENTLIMIT 100
#define LORA_PREAMBLELENGTH 8
#define LORA_GAIN 0

//LoRa APRS
#define LORA_APRS_ENABLED false          // Set to true if you want LORA-APRS transmissions at all, also select (multiple) APRS frequencies below
#define LORA_APRS_WORLD_ENABLED true     // Set to true if you want LORA-APRS transmissions on the world frequency 433.775 (LORA_APRS_ENABLED must be set to true)
#define LORA_APRS_PL_ENABLED true        // Set to True if you want LORA-APRS transmissions on the Poland frequency 434.855 (LORA_APRS_ENABLED must be set to true)
#define LORA_APRS_UK_ENABLED true        // Set to True if you want LORA-APRS transmissions on the UK frequency 439.9125 (LORA_APRS_ENABLED must be set to true)
#define LORA_APRS_PAYLOAD_ID YOUR_CALL    // CHANGE THIS. This will show on Sondehub. For LORA-APRS this should be a HAM call without SSID.
#define LORA_APRS_SSID "-11"             // 11 is the symbol for balloon. Use quotes like this: "-11"
#define LORA_APRS_MODE 99                // Do not change
#define LORA_APRS_MODE_PL 98             // Do not change
#define LORA_APRS_MODE_UK 97             // Do not change
#define LORA_APRS_FREQUENCY 433.775      // LORA-APRS is worldwide on 433.775 MHz at about 300bd, do not change
#define LORA_APRS_FREQUENCY_PL 434.855   // LORA-APRS used in Poland on 434.855 at about 1200bd
#define LORA_APRS_FREQUENCY_UK 439.9125  // LORA-APRS used in the UK on 439.9125 at about 300bd
#define LORA_APRS_LOOPTIME 180           // Set this rather high (>120s), so you won't be flagged for misusing the APRS network
#define LORA_APRS_FREQ_OFFSET 0.0        // Frequency deviation in MHz. Will be added to the LoRa APRS frequency. Should be a float and can be negative.
#define LORA_APRS_CUSTOM_MESSAGE "BALLOON" // Custom message that will be added to the LoRa APRS telemetry and will be visible on APRS and Sondehub. Use quotes.

//Horus:
// HORUS V3 is currently the preferred mode.
//============================================================================
#define HORUS_V1_ENABLED false       // Set to true if you want HorusBinary V1 transmissions (you can do V1, V2 and V3 transmissions on the same tracker)
#define HORUS_V2_ENABLED false       // Set to true if you want HorusBinary V2 transmissions
#define HORUS_V3_ENABLED false       // Set to true if you want HorusBinary V3 transmissions (recommended Horus mode)
#define HORUS_V3_CALLSIGN YOUR_CALL   // Horus V3 callsign and is free to choose but keep it AS SHORT AS POSSIBLE (adding V3 in the call is not necessary and not recommended)
#define HORUS_V3_CUSTOM_FIELDS       // if defined will include custom fields into the Horus transmission
                                     // two fields have been already added as custom fields in this code:
                                     // 1. gps speed (currently set to 'do not show' in TBTracker-ESP32.ini)
                                     // 2. RF chip
                                     // You can change this in the code or leave it as is
                                     // Note that including custom fields will SIGNIFICANTLY increase transmission length!
                                     // Just comment the line out if you do not want custom fields
#define PAYLOAD_ID_V1 0              // For Horus V1. See above. Set to 0 if you do not have a payload ID
#define PAYLOAD_ID_V2 256            // For Horus V2. See above. Set to 256 if you do not have a payload ID
#define HORUS_FREQUENCY_1 437.600    // Horus can transmit on two frequencies (434.714, 437.600 is kind of standard in Europe )
#define HORUS_FREQUENCY_2 434.714    // Just set to 0.0 if you only want 1 frequency
#define HORUS_POWER 13               // In dBm. Valid values +2 to +17 dBm. 10dBm = 10mW, 13dBm=20mW (recommended)
#define HORUS_BAUD 100               // recommended 50 (8MHz processor) or 100 baud (16MHz, better processor or esp32)
#define HORUS_SPACING 270            // NOTE: This results in a shift of 244 Hz on the sx127x and RF69 due to the PLL Resolution of those chips is 61Hz
#define HORUS_LOOPTIME 40            // Transmit Horus every xx seconds
#define HORUS_FREQ_OFFSET 0.0        // Frequency deviation in MHz. This will be added to HORUS_FREQUENCY

//AFSK:
#define APRS_AFSK_ENABLED false      // Set this to true if you want APRS transmissions
#define APRS_AFSK_CALLSIGN YOUR_CALL  // CHANGE THIS and use quotation marks. This will show on Sondehub. For APRS this should be a HAM call without SSID.
#define APRS_AFSK_LOOPTIME 180       // Transmit APRS every xx seconds. Set this to something >= 120 seconds
#define APRS_AFSK_SSID 11            // SSID. You can use 11 for a HAM balloon
#define APRS_AFSK_PREAMBLE 100       // I got good results with 100 but you can go as low as 8
#define APRS_AFSK_POWER 13           // In dBm. Valid values +2 to +17 dBm. 10dBm = 10mW, 13dBm=20mW
#define APRS_AFSK_FREQUENCY 432.500  // 70cm APRS frequency. Seems still experimental
#define APRS_AFSK_FREQ_OFFSET 0.0    // Frequency deviation in MHz. This will be added to APRS_AFSK_FREQUENCY

//FSK
#define FSK_FREQUENCY 434.0
#define FSK_BITRATE 4.8
#define FSK_FREQDEV 5.0
#define FSK_RXBANDWIDTH_sx127 125.0
#define FSK_RXBANDWIDTH_sx126 156.2 
#define FSK_POWER 10  // default power setting in dBm between 2 and 17. 10 = 10mW. Sets also RTTY power
#define FSK_PREAMBLELENGTH 16
#define FSK_ENABLEOOK false
#define FSK_DATASHAPING 0.5
#define FSK_USERREGULATORLDO false
#define SENTENCE_LENGTH 100  // Maximum length of telemetry line to send

 //RTTY
#define RTTY_ENABLED false        // Set to true if you want RTTY transmissions
#define RTTY_PAYLOAD_ID YOUR_CALL  // This will show on Sondehub. Payload ID for RTTY protocol. CHANGE THIS!
#define RTTY_FREQUENCY 437.600    // in MHz
#define RTTY_SHIFT 610            // 610 is usually a good value. 
#define RTTY_BAUD 100             // Baud rate. You should set this to 50 or 100 usually
#define RTTY_STOPBITS 2           // Usually leave this at 2
#define RTTY_PREFIX "$$$$$$"      // As RTTY with the sx12xx series chips is challenging, prefix with at least 4x$
#define RTTY_REPEATS 1            // number of RTTY transmits during a cycle, usually set to 1
#define RTTY_LOOPTIME 40          // Transmit RTTY every xx seconds
#define RTTY_IDLE_TIME 4000       // Idle carrier in ms before sending actual RTTY string. \
                                  // Set to a low value (i.e. 1000 or lower) if you have a very frequency stable signal 
                                  // Set to a high value (i.e. 5000 or even higher) if you have a hard time to tune and decode the signal
#define RTTY_ASCII 0           // 7 data bits
#define RTTY_ASCII_EXTENDED 1  // 8 data bits
#define RTTY_ITA2 2            // Baudot

// SSDV 
// Uncomment below to activate SSDV:
#define USE_SSDV   
#define CAMERA_MODEL_ESP32S3_EYE  //See list in TBTracker.
#define FLIP_HORIZONTAL true      // Camera is usually mounted in selfie mode. Set to true if the picture needs mirroring hotizontally
#define FLIP_VERTICAL false       // Set to true if the picture needs mirroring vertically (usually not the case)

// High res settings (save to SD)
#define SSDV_HIGHRES false         // Set to true if you want to take high res pictures and save those to SD card 
#define SSDVHIGHRES_LOOPTIME 30   // take a high res picture and save to SD every xx seconds 
#define HIGHRES_RESOLUTION  4     // 1 = 1600x1200 (all sensors, OV2640, OV3660 and OV5640)
                                  // 2 = 1920x1080 (3MP and 5MP sensors, OV3660 and OV5640) 
                                  // 3 = 2048x1536 (3MP and 5MP sensors, OV3660 and OV5640) 
                                  // 4 = 2560x1440 (5MP sensors, OV5640)  2K
#define HIGHRES_QUALITY 10        // 0..63 with 0=best, 63=worst. 10 is very good quality.                                  

// Low res settings (send over LoRa)
#define SSDV_LOWRES  true        // Set to true if you want to send low res images over LoRa Mode 1
#define SSDV_LOWRES_SAVE false   // Set to true if you want the low res pictures saved to SD card, false if not
#define SSDVLOWRES_LOOPTIME 10   // take a low res picture, transmit the picture, wait SSDVLOWRES_LOOPTIME seconds, take the next lowres picture 
#define CALLSIGN_SSDV YOUR_CALL   // max 6 chars!
#define LOWRES_RESOLUTION 2      // 1=320x240, 2=640x480, 3=800x600, 4=1024x768
#define LOWRES_QUALITY 4         // 0..7 with 7=best. Above 4 the improvements were not detectable