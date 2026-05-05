# Welcome to my fork of TBTracker-ESP32 by Roel Kroes.

## First of all:
All credits go to the original creator of TBTracker, Roel Koes (PD7R).
Check it out here: https://github.com/RoelKroes/TBTracker-ESP32

The things I do with this fork are build on his work, i'm only tweaking it a bit to some ideas I have.

This is in no way a replacement of the original and the goal is to keep it up do date with only my tweaks changed.

# Some of the added fork features:

## 2.4 GHz support
This fork adds LoRa 2.4GHz support with a SX1280 radio module to TBTracker-ESP32.
It is developed and tested on a LilyGO T3-S3 SX1280PA board but future tracker builds are on the way.
The main idea of this 2.4 GHz LoRa usage is to get more transfer speed on SSDV images, but also just to give the opertunity to experiment with 2.4 GHz RF.
The SSDV transfer is still in development but telemetry transfer with a edited version of TBTracker-RX was already successful.
To account for the different capabilitys of the SX1280 I have created a lora mode "24" as the SX1280 is not capable of transmitting/receiving on the regular LoRa settings, mainly the bandwidth.

Note that the SX1280 does not support 4FSK and is not tested on other modes other than LoRa at this moment.
Use it only with LoRa. Dont forget to change the frequency if needed. 

Make sure to select the right pins and board (Uncomment "#define USE_SX1280") and set the right frequency. As well as your call.
You can add GPS by using pin 38 on the S3-T3, this might be different on another board.

**The board I used to test this code has a Power Amplifier (PA), notes from the manufacturer:**

Note: In this version of the board, the LoRa chip has a Power Amplifier (PA). The software setting for the transmitting power cannot exceed 5dBm, or the chip will be damaged. Every setting between 2-5dBm will result in an output power of 20dBm, so we recommend to be on the lower side of this range and to set the transmitting power to 2dBm or 3dBm.

Note: Not all countries allow LoRa signals to be transmitted on 2.4GHz with a power of 20dBm (100mW). In the Netherlands, for example, this maximum is 10dBm (10mW). Therefore, set the maximum transmission power in such a way that it complies with local laws and regulations.

This is still very much experimental.

## Presets
I used to have a lot of copy's of TBTracker-ESP32 on my computer, different versions, different boards.
The idea of presets is to have only one copy of TBTracker and multiple presets you can easily activate for different boards and setups.
This way its easier to keep TBT at its latest version (not having to update all the copy's of TBT) and easier to set up, especcialy when the board you use is already in the existing presets folder.
It also serves as a hardware cheatsheet of where to connect the pins for the specific board you are using.

The idea is to make this preset folder a database of different setups that keeps on growing over time as more boards are added.

## Wiki
I also want to create a easy to read Wiki that is also applicable to the original version of TBTracker ESP32.
Covering everything from the basic hardware to actually launching a amateur balloon.
My goal is to make it a light read and not go full serious-technical, it is a hobby afterall.

## Remote Burst
This idea came when taling about the recovery of SSDV balloons. The idea is to remotely send a (safeword secured) LoRa command to drop the payload.
For this I have made a very basic "Burst Controller" that sends this word. This is still very much in development.
A feature I have added recently is a Reply Mode, where instead of actually dropping the payload it sends a "RR 59" in CW on the 437.600MHz frequency.

