//============================================================================
// Process a received LoRa packet. 
// This function will run if a packet has been received
// You should create your own actions here.
// Be sure to check if a correct packet was received!   //Rob Goverde Remote Burst Mod icw the Burst Controller. >>>EXPERIMENTAL<<<
//============================================================================

//#define BURST_MODE //Uncomment for burst pin activation.
#define REPLY_MODE //Uncomment for CW reply.

void ProcessRXPacket() {
  // Buffer to hold the received data from the radio
  byte buf[PACKETLEN];
  int16_t state;


  // EXAMPLE OF RX ACTION
  toSerialConsole("============================================\n");
  toSerialConsole("PACKET RECEIVED!\n");
  toSerialConsole("============================================\n");

  // Grab the data from the radio module
  switch (LORA_MODE) {
    case 1:  // Implicit header, so tell the radio how many bytes to read
      state = radio.readData(buf, LoRaSettings.implicitHeader);
      break;
    default:
      state = radio.readData(buf, 0);
      break;
  }

  // Packet was successfully received
  if (state == RADIOLIB_ERR_NONE) {
    #if defined(BURST_MODE)
    toSerialConsole("First 10 chars: ");
    // Print the first 10 hex chars of the packet
   char magicword[10];
    toSerialConsole("[RADIO] first 10 hex chars:\t");
    for (int i = 0; i < 10; i++) {
      toSerialConsole(buf[i]);
      magicword[i] = buf[i];
      toSerialConsole(" ");
    }
    toSerialConsole("\n============================================\n");
    toSerialConsole("Character");
    toSerialConsole("\n");
    toSerialConsole(magicword);
    String mw2 = String(magicword);
    toSerialConsole("\n============================================\n");
    if (mw2.indexOf("BURST") >= 0){toSerialConsole(">>>>>>>>>>>>>>> BURST ! <<<<<<<<<<<<<");
     digitalWrite(burstPin, HIGH);
      toSerialConsole("High\t");
      delay(5000);
      digitalWrite(burstPin, LOW);
    }
    else toSerialConsole("!!!> You did'nt say the magic word! <!!!");
    #endif

    #if defined(REPLY_MODE)
    toSerialConsole("Replymode OK\t");
    int statem = radio.beginFSK(FSK_FREQUENCY, FSK_BITRATE, FSK_FREQDEV, FSK_RXBANDWIDTH_sx127, FSK_POWER, FSK_PREAMBLELENGTH, FSK_ENABLEOOK);
    MorseClient morse(&radio);
    statem = morse.begin(437.6);
    morse.print("RR 59");
    #endif

  }


  // Reset the received flag
  receivedFlag = false;
}
