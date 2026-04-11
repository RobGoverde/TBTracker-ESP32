//============================================================================
// All SSDV related procedures
//  
//============================================================================
#if defined(USE_SSDV)

#include "camera_pins.h"
#include "FS.h"                // SD Card ESP32
#include "SD_MMC.h"            // SD Card ESP32
#include "soc/soc.h"           // Brownout preventie
#include "soc/rtc_cntl_reg.h"
#include "ssdv.h"
#include "fb_gfx.h"
#include "img_converters.h"

#define IMG_BUFF_SIZE 128   // size of the buffer feeding SSDV process
#define LORA_BUFFER  255   // size of the lora packet buffer

//============================================================================
// Globals
//============================================================================

const unsigned char font8x8_basic[] = {
    // Space (index 0)
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    // (index 1-10)
    0x3C, 0x46, 0x4A, 0x52, 0x62, 0x3C, 0x00, 0x00, // 0
    0x18, 0x28, 0x08, 0x08, 0x08, 0x3E, 0x00, 0x00, // 1
    0x3C, 0x42, 0x02, 0x3C, 0x40, 0x7E, 0x00, 0x00, // 2
    0x3C, 0x42, 0x0C, 0x02, 0x42, 0x3C, 0x00, 0x00, // 3
    0x08, 0x18, 0x28, 0x48, 0x7E, 0x08, 0x00, 0x00, // 4
    0x7E, 0x40, 0x7C, 0x02, 0x42, 0x3C, 0x00, 0x00, // 5
    0x3C, 0x40, 0x7C, 0x42, 0x42, 0x3C, 0x00, 0x00, // 6
    0x7E, 0x02, 0x04, 0x08, 0x10, 0x10, 0x00, 0x00, // 7
    0x3C, 0x42, 0x3C, 0x42, 0x42, 0x3C, 0x00, 0x00, // 8
    0x3C, 0x42, 0x42, 0x3E, 0x02, 0x3C, 0x00, 0x00, // 9
    // (index 11-13)
    0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x00, // . 
    0x00, 0x0C, 0x0C, 0x00, 0x0C, 0x0C, 0x00, 0x00, // : 
    0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00, // - 
    // (index 14-39)
    0x00, 0x00, 0x38, 0x04, 0x3C, 0x44, 0x3A, 0x00, // a
    0x00, 0x40, 0x7C, 0x42, 0x42, 0x42, 0x7C, 0x00, // b
    0x00, 0x00, 0x3C, 0x40, 0x40, 0x42, 0x3C, 0x00, // c
    0x00, 0x02, 0x3E, 0x42, 0x42, 0x42, 0x3E, 0x00, // d
    0x00, 0x00, 0x3C, 0x42, 0x7E, 0x40, 0x3C, 0x00, // e
    0x00, 0x1C, 0x22, 0x78, 0x20, 0x20, 0x70, 0x00, // f
    0x00, 0x00, 0x3E, 0x42, 0x42, 0x3E, 0x02, 0x3C, // g
    0x00, 0x40, 0x7C, 0x42, 0x42, 0x42, 0x42, 0x00, // h
    0x00, 0x08, 0x00, 0x18, 0x08, 0x08, 0x1C, 0x00, // i
    0x00, 0x04, 0x00, 0x0C, 0x04, 0x04, 0x44, 0x38, // j
    0x00, 0x40, 0x44, 0x48, 0x70, 0x48, 0x44, 0x00, // k
    0x00, 0x18, 0x08, 0x08, 0x08, 0x08, 0x1C, 0x00, // l
    0x00, 0x00, 0x6C, 0x92, 0x92, 0x92, 0x92, 0x00, // m
    0x00, 0x00, 0x7C, 0x42, 0x42, 0x42, 0x42, 0x00, // n
    0x00, 0x00, 0x3C, 0x42, 0x42, 0x42, 0x3C, 0x00, // o
    0x00, 0x00, 0x7C, 0x42, 0x42, 0x7C, 0x40, 0x40, // p
    0x00, 0x00, 0x3E, 0x42, 0x42, 0x3E, 0x02, 0x02, // q
    0x00, 0x00, 0x3C, 0x42, 0x40, 0x40, 0x40, 0x00, // r
    0x00, 0x00, 0x3E, 0x40, 0x3C, 0x02, 0x7C, 0x00, // s
    0x00, 0x20, 0x70, 0x20, 0x20, 0x22, 0x1C, 0x00, // t
    0x00, 0x00, 0x42, 0x42, 0x42, 0x42, 0x3E, 0x00, // u
    0x00, 0x00, 0x42, 0x42, 0x42, 0x24, 0x18, 0x00, // v
    0x00, 0x00, 0x92, 0x92, 0x92, 0x92, 0x6C, 0x00, // w
    0x00, 0x00, 0x42, 0x24, 0x18, 0x24, 0x42, 0x00, // x
    0x00, 0x00, 0x42, 0x42, 0x42, 0x3E, 0x02, 0x3C, // y
    0x00, 0x00, 0x7E, 0x04, 0x18, 0x40, 0x7E, 0x00  // z
};

uint16_t ssdvPacketCount = 0;
ssdv_t ssdv;
uint16_t imageID = 0;
uint8_t imgBuff[IMG_BUFF_SIZE];
uint8_t loraBuff[LORA_BUFFER + 1];

//============================================================================
// Function to color one single pixel in BGR colors
//============================================================================
void drawPixel(uint8_t *buf, int x, int y, int w, uint8_t r, uint8_t g, uint8_t b) {
    int idx = (y * w + x) * 3;
    buf[idx + 0] = b;
    buf[idx + 1] = g;
    buf[idx + 2] = r;
}

//============================================================================
// Function to draw a filled rectangle
//============================================================================
void drawRect(uint8_t *buf, int x, int y, int rw, int rh, int w, uint8_t r, uint8_t g, uint8_t b) {
    for (int i = y; i < y + rh; i++) {
        for (int j = x; j < x + rw; j++) {
            drawPixel(buf, j, i, w, r, g, b);
        }
    }
}

//============================================================================
// Function to draw one single scalable white character
//============================================================================
void drawSimpleChar(uint8_t *buf, int x, int y, char c, int w, int scale) {
    int fontIdx = 0; // Space

    // calculate the index in the font array
    if (c >= '0' && c <= '9') {
        fontIdx = 1 + (c - '0'); // digits 0-9
    } else if (c == '.') {
        fontIdx = 11;
    } else if (c == ':') {
        fontIdx = 12;
    } else if (c == '-') {
        fontIdx = 13;
    } else if (c >= 'a' && c <= 'z') {
        fontIdx = 14 + (c - 'a'); // lower case
    } else if (c >= 'A' && c <= 'Z') {
        // Force lower case
        fontIdx = 14 + (c - 'A'); 
    }

    // Teken het 8x8 bitmap raster
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            // Indexering in de 1D font array (karakter_index * 8 bytes + rij_index)
            if (font8x8_basic[fontIdx * 8 + i] & (1 << (7 - j))) {
                // Schaalfactor toepassen
                for(int sy=0; sy<scale; sy++) {
                    for(int sx=0; sx<scale; sx++) {
                        // Teken de pixel (Wit)
                        drawPixel(buf, x + (j*scale) + sx, y + (i*scale) + sy, w, 255, 255, 255);
                    }
                }
            }
        }
    }
}

//============================================================================
// Function to draw a String of scalable text
//============================================================================
void drawSimpleText(uint8_t *buf, int x, int y, String text, int w, int scale) {
    for (int i = 0; i < text.length(); i++) {
        // 8 pixels width per char * scale + 1 pixel space
        drawSimpleChar(buf, x + (i * (8 * scale + scale/2)), y, text[i], w, scale);
    }
}

//============================================================================
// Setup the camera and the SD card
//============================================================================
void setupSSDV() {

  // Camera config
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.frame_size = FRAMESIZE_UXGA; // Resolutie: UXGA (1600x1200)
  config.pixel_format = PIXFORMAT_JPEG; 
  config.grab_mode = CAMERA_GRAB_LATEST;
  config.fb_location = CAMERA_FB_IN_PSRAM;
  config.jpeg_quality = 10;
  config.fb_count = 2;

  // Camera initialis
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) 
  {
    toSerialConsole("Could not initialized camera error code: 0x");
    toSerialConsole(err);
    toSerialConsole("\n");
    return;
  }
  else
  {
    toSerialConsole("Camera succesfully initialized.\n");
  }

  // SD-card initialise
  if(! SD_MMC.setPins(39, 38, 40))
  {
    toSerialConsole("Could not remap pins for SD-card\n");
    return;
  }


  if(!SD_MMC.begin("/sdcard",true)) 
  {
    toSerialConsole("Could not initialize SD-card\n");
    return;
  }
  else
  {
    toSerialConsole("SD-card succesfully initialized\n");
  }

  // Set all the auto functions for exposure, contrast and brightness, using the internal ISP of the camera
  sensor_t * s = esp_camera_sensor_get();
  s->set_whitebal(s, 1);       // 1 = enable Auto White Balance
  s->set_awb_gain(s, 1);       // 1 = enable AWB Gain
  s->set_wb_mode(s, 0);        // 0 = Auto modus (1=Sunny, 2=Cloudy, enz.)
  s->set_exposure_ctrl(s, 1);  // 1 = enable Auto Exposure Control
  s->set_aec2(s, 1);           // 1 = enable AEC sensor DSP
  s->set_ae_level(s, 0);       // exposure correction: -2 to 2 (0 is standard)
  s->set_gain_ctrl(s, 1);      // 1 = enable Auto Gain Control
  s->set_agc_gain(s, 0);       // 0 tot 30
  s->set_gainceiling(s, (gainceiling_t)0); // 0 = 2x gain, 6 = 128x gain
  // image improvement
  s->set_brightness(s, 0);     // -2 to 2
  s->set_contrast(s, 0);       // -2 to 2
  s->set_saturation(s, 0);     // -2 to 2
  s->set_bpc(s, 1);            // Black Pixel Cancellation
  s->set_wpc(s, 1);            // White Pixel Cancellation
  s->set_raw_gma(s, 1);        // Gamma correctie aan

  if (FLIP_HORIZONTAL)
  {
    s->set_hmirror(s, 1);     
  }
  else
  {
    s->set_hmirror(s, 0);
  }

  if (FLIP_VERTICAL)
  {
    s->set_vflip(s, 1);     
  }
  else
  {
    s->set_vflip(s, 0);
  }


  // CRUCIAL: Give the sensor time to adjust and measure
  delay(1500);
}

//============================================================================
// Take a high res picture and save it to SD
// File name is a combination of Date/Time/Location/Altitude
//============================================================================
void SaveHighResPhoto()
{
  // Get the latest GPS
  processGPSData();
  
  // Set the resolution of the sensor
  sensor_t * s = esp_camera_sensor_get();
  switch(HIGHRES_RESOLUTION)
  {
   case 1: {s->set_framesize(s,FRAMESIZE_UXGA);} break;
   case 2: {s->set_framesize(s,FRAMESIZE_FHD);} break;
   case 3: {s->set_framesize(s,FRAMESIZE_QXGA);} break;
   case 4: {s->set_framesize(s,FRAMESIZE_QHD);} break;
   case 5: {s->set_framesize(s,FRAMESIZE_5MP);} break;
   default: {s->set_framesize(s,FRAMESIZE_UXGA);} break; 
  }
  // Set the JPG quality
  int qual = HIGHRES_QUALITY;
  if ( (qual < 0) || (qual > 63)) {qual = 10;}
  s->set_quality(s,qual);
  
  // Let the sensor stabilize
  delay(1000);

  // Take the picture
  toSerialConsole("Taking High Res picture....");
  camera_fb_t * fb = esp_camera_fb_get();  
  if(!fb) 
  {
    toSerialConsole("Error taking picture\n");
    return;
  }
 
  // Create file name
  // Filename should be: YYDDMM-HHMMSS-longitude-latitude-altitude-randomstring-hires.jpg
  String lFolder = "/" + getSDFolderName();
  String picture_path = lFolder + "/";
  picture_path += getTimeLocationString(); 
  // Add an random string for pictures when there is no GPS lock
  picture_path += generateRandomString(8);

  picture_path += "_HIRES.jpg"; 
  fs::FS &fs = SD_MMC;
  if(!fs.exists(lFolder))
  {
    fs.mkdir(lFolder);
  }
  File file = fs.open(picture_path.c_str(), FILE_WRITE);  
  if(!file)
  {
    toSerialConsole("Could not open file for writing on SD card\n");
    // Free the memory
    esp_camera_fb_return(fb);
    return;
  }

  // Write the file 
  file.write(fb->buf, fb->len); 
  toSerialConsole("Photo saved: ");
  toSerialConsole(picture_path.c_str());
  toSerialConsole("\n");
  file.close();
  
  // Free the memory
  esp_camera_fb_return(fb);
}


//============================================================================
// Take a low res picture and send it over LoRa
//============================================================================
void TakeandSendLowResPhoto()
{
  uint8_t * rgb_buf;
  // Set the resolution of the sensor 
  // according to what is in settings.h
  sensor_t * s = esp_camera_sensor_get();
  switch(LOWRES_RESOLUTION)
  {
    case 1: {s->set_framesize(s, FRAMESIZE_QVGA);} break;
    case 2: {s->set_framesize(s, FRAMESIZE_VGA);} break;
    case 3: {s->set_framesize(s, FRAMESIZE_SVGA);} break;
    case 4: {s->set_framesize(s, FRAMESIZE_XGA);} break;
    default: {s->set_framesize(s, FRAMESIZE_QVGA);} break;
  }
  // Set the quality always to 10
  s->set_quality(s,10);
  // Let the sensor stabilize
  delay(1000);

  // Take the picture
  toSerialConsole("Taking Low Res picture....");
  camera_fb_t * fb = esp_camera_fb_get();  
  if(!fb) 
  {
    toSerialConsole("Error taking picture\n");
    esp_camera_fb_return(fb);
    return;
  }
  toSerialConsole(imageID); toSerialConsole("\n");

  // Save to SD if selected in Settings.h
  if (SSDV_LOWRES_SAVE)
  {
    // Create file name
    // Filename should be: YYDDMM-HHMMSS-longitude-latitude-altitude-randomstring-lowres.jpg
    String lFolder = "/" + getSDFolderName();
    String picture_path = lFolder + "/";
    picture_path += getTimeLocationString(); 
    // Add an random string for pictures when there is no GPS lock
    picture_path += generateRandomString(8);

    picture_path += "_LOWRES.jpg"; 
    fs::FS &fs = SD_MMC;
    if(!fs.exists(lFolder))
    {
      fs.mkdir(lFolder);
    }
  
    File file = fs.open(picture_path.c_str(), FILE_WRITE);  
    if(!file)
    {
      toSerialConsole("Could not open file for writing on SD card\n");
      // Free the memory
      esp_camera_fb_return(fb);
      return;
    }

    // Write the picture to the SD
    file.write(fb->buf, fb->len); 
    toSerialConsole("Photo saved: ");
    toSerialConsole(picture_path.c_str());
    toSerialConsole("\n");
    file.close();
  }  


  if (SSDV_LOWRES_TEXT)
  {
     // Now create a text overlay with GPS info on the top of the picture 
     // 1. Convert to RGB888 to be able to write on picture
     // Very memory intensive 
     toSerialConsole("Converting image to RGB888\n");
    
     rgb_buf = (uint8_t *)ps_malloc(fb->width * fb->height * 3); 
     toSerialConsole("Memory allocated\n");

     if (fmt2rgb888(fb->buf, fb->len, fb->format, rgb_buf))
     {
        toSerialConsole("Image converted\n");
        
        // Write the GPS info
        String lGPSText = getJPGOverlayString();
        // Draw a black rectangle on the picture 
        drawRect(rgb_buf, 10, 10, fb->width-20, 30, fb->width, 0, 0, 0);
        drawSimpleText(rgb_buf, 20, 14, CUSTOM_LINE, fb->width, 1);
        drawSimpleText(rgb_buf, 20, 29, lGPSText, fb->width, 1);
        
        // Convert back to JPG
        uint8_t *jpg_buf = NULL;
        size_t jpg_len = 0;
        fb_data_t out_fb;
        out_fb.width  = fb->width;
        out_fb.height = fb->height;
        out_fb.data   = rgb_buf;    
        out_fb.format = FB_BGR888;  
        // out_fb.data contains the RGB888 pixels
        // out_fb.width * out_fb.height * 3 is size of the RGB buffer
        if (fmt2jpg(out_fb.data, out_fb.width * out_fb.height * 3, 
                 out_fb.width, out_fb.height, 
                 PIXFORMAT_RGB888, 80, &jpg_buf, &jpg_len))
        {
           // Transmit the picture with the added text over LoRa  
           toSerialConsole("Transmitting image with text on it\n");
           process_ssdv(jpg_len,jpg_buf);
           free(jpg_buf);
        }
        else
        {
          toSerialConsole("Could not convert back to JPG\n");
          free(jpg_buf);
        }

     }
     else
     {
        toSerialConsole("Could not convert the image\n");
     }
     free(rgb_buf);
  }
  else
  {
     //transmit the unaltered camera frame
     process_ssdv(fb->len,fb->buf);
  }

  // Free the memory
  esp_camera_fb_return(fb);
}



//============================================================================
// Read camera buffer
//============================================================================
int iread(uint8_t *buffer,int numBytes,size_t fb_len, uint8_t *fb_buf, int fbIndex ){
  int bufSize = 0;
  // have we reached past end of imagebuffer
  if((fbIndex + numBytes ) < fb_len) {
    bufSize = numBytes;
  }  else  {
    bufSize = fb_len - fbIndex;
  }
  // clear the dest buffer
  memset(buffer,0,numBytes);
  memcpy(buffer,&fb_buf[fbIndex],bufSize);
  return bufSize;
}

/*
int iread(uint8_t *buffer,int numBytes,camera_fb_t *fb, int fbIndex ){
  int bufSize = 0;
  // have we reached past end of imagebuffer
  if((fbIndex + numBytes ) < fb->len) {
    bufSize = numBytes;
  }  else  {
    bufSize = fb->len - fbIndex;
  }
  // clear the dest buffer
  memset(buffer,0,numBytes);
  memcpy(buffer,&fb->buf[fbIndex],bufSize);
  return bufSize;
}
*/

//============================================================================
// Process the camera buffer
//============================================================================
void process_ssdv(size_t fb_len, uint8_t *fb_buf)
{
  int index = 0, c = 0;
  ssdvPacketCount = 0;
  
  // initialise ssdv config structure
  ssdv_enc_init(&ssdv, SSDV_TYPE_NOFEC, CALLSIGN_SSDV, imageID++, LOWRES_QUALITY);
  // set the output lora packet buffer for ssdv where the final ssdv packet will end up
  ssdv_enc_set_buffer(&ssdv, loraBuff);

  while (1)   
  {
    toSerialConsole("Initialize SSDV\n");
    // set the output lora packet buffer for ssdv where the final ssdv packet will end up
    ssdv_enc_set_buffer(&ssdv, loraBuff);
    toSerialConsole("Feeding SSDV\n");
    // Feed the SSDV encoder the image.  Encoder saves it to loraBuff 
    while( (c = ssdv_enc_get_packet(&ssdv)) == SSDV_FEED_ME) 
    {
       // read packet worth of bytes from image buffer
       index += iread(imgBuff, IMG_BUFF_SIZE, fb_len, fb_buf, index);
       toSerialConsole("Feeding SSDV Encoder, index = ");toSerialConsole(index);toSerialConsole("\n");
       ssdv_enc_feed(&ssdv, imgBuff, IMG_BUFF_SIZE); 
    }

    if(c == SSDV_EOI) 
    {
      toSerialConsole("SSDV End of Image\n");
      break;  // break out of the while loop
    }
    else if(c != SSDV_OK)
    {
      toSerialConsole("ERROR: SSDV Error\n");
      break; // break out of the while loop 
    }

    // move lora data backwards 1 byte This seems needed for pits gateway to read it. (TT7)
    for(uint16_t i = 0; i < 256; i++) 
    {
      loraBuff[i] = loraBuff[i+1]; 
    }

    // Now send the packet over the radio
    toSerialConsole("Transmitting packet: ");
    toSerialConsole(ssdvPacketCount);
    toSerialConsole("\n");
    sendLoRaSSDV();
    // Up the packetcounter
    ssdvPacketCount++;

    // Send a telemetry packet every 25 packets to update location (which is about 1 minute)
    if (ssdvPacketCount % 25 == 0)
    {
      // Check the gps for updated location info
      smartDelay(1000);
      CheckGPS();
      // Print the sensor data
      printSensorData();
      CreateTXLine(LORA_PAYLOAD_ID, LoRaCounter++, LORA_PREFIX);
      sendLoRa(Sentence, LORA_MODE);
    }

    if (ssdvPacketCount > 300) 
    {
      toSerialConsole("ERROR: ssdvPacketCount > 300\n");
      break; // incase we get stuck in this loop, for example when the camera isn't on
    }
  } // while(true)
}

//============================================================================
// Send a LoRa SSDV packet
//============================================================================
void sendLoRaSSDV()
{
   char buf[PACKETLEN]; 
   int j;
   int i;

   // Setup the radio for LoRa mode 1
   SetupLoRa(LORA_MODE);
   // Set the transmit buffer to all zero's
   for (j = 0; j < PACKETLEN; j++) { buf[j] = '\0'; }
   // Fill the transmit buffer with SSDV data
   for (i = 0; i < LORA_BUFFER; i++) { buf[i] = loraBuff[i]; }
   Radiolib_assert(radio.transmit((uint8_t*)buf, PACKETLEN));
}


//============================================================================
// Test function for drawing a line without the library
//============================================================================
void drawRedLineDirect(uint8_t *bgr_buf, int width, int height) {
    // We tekenen een dikke lijn door 5 pixels breed te maken
    int lineWidth = 5; 

    // Loop door de hoogte van de afbeelding
    for (int y = 0; y < height; y++) {
        // Bereken de X-positie voor de diagonaal
        int x = (y * width) / height;

        // Maak de lijn een beetje dikker voor betere zichtbaarheid
        for (int lw = 0; lw < lineWidth; lw++) {
            int currentX = x + lw;
            
            // Zorg dat we niet buiten de breedte van de foto tekenen
            if (currentX < width) {
                // Bereken de exacte index in de 1D array
                // Elke pixel is 3 bytes (RGB888)
                int pixelIndex = (y * width + currentX) * 3;

                // Zet de pixel op Rood (255, 0, 0)
                // Let op: controleer of je camera RGB of BGR levert.
                // Als de lijn blauw is, wissel dan index 0 en 2 om.
                bgr_buf[pixelIndex + 0] = 0x00; // blauw
                bgr_buf[pixelIndex + 1] = 0x00; // Groen
                bgr_buf[pixelIndex + 2] = 0xFF; // Rood
            }
        }
    }
    toSerialConsole("Red line drawn on the buffer\n");
}


#endif