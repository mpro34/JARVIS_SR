/*
  BitVoicer.h - Implements serial communication with the BitVoicer.
  Created by BitSophia Software Ltd., December 03, 2012.
  Realeased into public domain.
*/

#ifndef BitVoicer11_h
#define BitVoicer11_h

#include "Arduino.h"

//Internal BitVoicerSerial buffer
#define BUFFER_SIZE = 64;

//Analog reference constants
#define BV_DEFAULT 3
#define BV_EXTERNAL 1

//Defines BitVoicer constants
#define BV_UNDEFINED 0
#define BV_CHAR 1
#define BV_INT 2
#define BV_BYTE 3
#define BV_STR 4
#define BV_COMMAND 254
#define BV_STATUS 255
#define BV_STARTSAMPLING 1
#define BV_STOPSAMPLING 0
#define BV_ENGINESTOPPED 0
#define BV_ENGINERUNNING 1


//Defines all elements of the class
class BitVoicerSerial
{
  public:
    //Class constructor
    BitVoicerSerial();
    //Method that retrieves data from serial port
    byte getData();
    //Method that sends a start/stop listening signal to BitVoicer
    void startStopListening();
    //BitVoicer's audio processing method
    void processAudio(unsigned int wait);
    //Method that sets up the audio input
    void setAudioInput(uint8_t pin);
    //Sets the analog voltage reference
    void setAnalogReference(uint8_t mode);
    //Method that sets Arduino back to its original input settings
    void undoAudioInput();
    //Sends a byte to BitVoicer
    void sendToBV(uint8_t b);
    //Sends a char to BitVoicer
    void sendToBV(char c);
    //Sends a int to BitVoicer
    void sendToBV(int n);
    //Sends a String object to BitVoicer
    void sendToBV(String s);
    //Stores byte data
    byte byteData;
    //Stores char data
    char charData;
    //Stores int data
    int intData;
    //Stores string data
    String strData;
    //Stores command data
    byte cmdData;
    //Stores engine status
    boolean engineRunning;
  private:
    //Stores temporary data read from the serial port
    byte _data[64];
    //Sets the public variables with the correct data
    //from last read
    void setData(byte dataType, int dataLength);
    //Stores the analog voltage reference
    uint8_t _bvAnalogReference;
};

#endif