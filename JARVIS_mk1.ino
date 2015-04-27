#include <BitVoicer11.h>

//Instantiates the BitVoicerSerial class
BitVoicerSerial bvSerial = BitVoicerSerial();

//Stores true if the Audio Streaming Calibration tool
//is running
boolean sampleTest = false;
//Stores the data type retrieved by getData()
byte dataType = 0;
//Sets up the pins and default variables
int pinR = 3;
int pinY = 5;
int pinG = 6;
int lightLevel = 0;

void setup()
{
  //Sets the analog reference to external (AREF pin)
  //WARNING!!! If anything is conected to the AREF pin,
  //this function MUST be called first. Otherwise, it will
  //damage the board.
  bvSerial.setAnalogReference(BV_EXTERNAL);
  //Sets up the microcontroller to perform faster analog reads
  //on the specified pin
  bvSerial.setAudioInput(0);
  //Starts serial communication at 115200 bps
  Serial.begin(115200);
  //Sets up the pinModes
  pinMode(pinR, OUTPUT);
  pinMode(pinY, OUTPUT);
  pinMode(pinG, OUTPUT);
}

void loop()
{
  //Captures audio and sends it to BitVoicer if the Audio
  //Streaming Calibration Tool is running
  if (sampleTest == true)
  {
    //The value passed to the function is the time
    //(in microseconds) that the function has to wait before
    //performing the reading. It is used to achieve about
    //8000 readings per second.
    bvSerial.processAudio(46);
  }
 
  //Captures audio and sends it to BitVoicer if the Speech
  //Recognition Engine is running
  if (bvSerial.engineRunning)
  {
    //The value passed to the function is the time
    //(in microseconds) that the function has to wait before
    //performing the reading. It is used to achieve about
    //8000 readings per second.
    bvSerial.processAudio(46);
  }
}

//This function runs every time serial data is available
//in the serial buffer after a loop
void serialEvent()
{
  //Reads the serial buffer and stores the received data type
  dataType = bvSerial.getData();
 
  //Changes the value of sampleTest if the received data was
  //the start/stop sampling command
  if (dataType == BV_COMMAND)
      sampleTest = bvSerial.cmdData;
 
  //Signals BitVoicer's Speech Recognition Engine to start
  //listening to audio streams after the engineRunning status
  //was received
  if (dataType == BV_STATUS && bvSerial.engineRunning == true)
    bvSerial.startStopListening();
 
  //Checks if the data type is the same as the one in the
  //Voice Schema
  if (dataType == BV_STR)
    setLEDs();
}

//Performs the LED changes according to the value in
//bvSerial.strData
void setLEDs()
{
  if (bvSerial.strData == "wake")
  {
    digitalWrite(pinR, LOW);
    digitalWrite(pinY, LOW);
    digitalWrite(pinG, LOW);
    digitalWrite(pinR, HIGH);
    digitalWrite(pinY, HIGH);
    digitalWrite(pinG, HIGH);
    delay(200);
    digitalWrite(pinR, LOW);
    digitalWrite(pinY, LOW);
    digitalWrite(pinG, LOW);
    delay(200);
    digitalWrite(pinR, HIGH);
    digitalWrite(pinY, HIGH);
    digitalWrite(pinG, HIGH);
    delay(200);
    digitalWrite(pinR, LOW);
    digitalWrite(pinY, LOW);
    digitalWrite(pinG, LOW);
    delay(200);
    digitalWrite(pinR, HIGH);
    digitalWrite(pinY, HIGH);
    digitalWrite(pinG, HIGH);
    delay(200);
    digitalWrite(pinR, LOW);
    digitalWrite(pinY, LOW);
    digitalWrite(pinG, LOW);
    lightLevel = 0;
  }
  else if (bvSerial.strData == "sleep")
  {
    digitalWrite(pinR, LOW);
    digitalWrite(pinY, LOW);
    digitalWrite(pinG, LOW);
    digitalWrite(pinR, HIGH);
    digitalWrite(pinY, HIGH);
    digitalWrite(pinG, HIGH);
    delay(200);
    digitalWrite(pinR, LOW);
    digitalWrite(pinY, LOW);
    digitalWrite(pinG, LOW);
    delay(200);
    digitalWrite(pinR, HIGH);
    digitalWrite(pinY, HIGH);
    digitalWrite(pinG, HIGH);
    delay(200);
    digitalWrite(pinR, LOW);
    digitalWrite(pinY, LOW);
    digitalWrite(pinG, LOW);
    lightLevel = 0;
  }
  else if (bvSerial.strData == "RH")
  {
    digitalWrite(pinR, HIGH);
    lightLevel = 255;
  }
  else if (bvSerial.strData == "RL")
  {
    digitalWrite(pinR, LOW);
    lightLevel = 0;
  }
  else if (bvSerial.strData == "YH")
  {
    digitalWrite(pinY, HIGH);
    lightLevel = 255;
  }
  else if (bvSerial.strData == "YL")
  {
    digitalWrite(pinY, LOW);
    lightLevel = 0;
  }
  else if (bvSerial.strData == "GH")
  {
    digitalWrite(pinG, HIGH);
    lightLevel = 255;
  }
  else if (bvSerial.strData == "GL")
  {
    digitalWrite(pinG, LOW);
    lightLevel = 0;
  }
  else if (bvSerial.strData == "ALLON")
  {
    digitalWrite(pinR, HIGH);
    digitalWrite(pinY, HIGH);
    digitalWrite(pinG, HIGH);
    lightLevel = 255;
  }
  else if (bvSerial.strData == "ALLOFF")
  {
    digitalWrite(pinR, LOW);
    digitalWrite(pinY, LOW);
    digitalWrite(pinG, LOW);
    lightLevel = 0;
  }
  else if (bvSerial.strData == "brighter")
  {
    if (lightLevel < 255)
    {
      lightLevel += 85;
      analogWrite(pinR, lightLevel);
      analogWrite(pinY, lightLevel);
      analogWrite(pinG, lightLevel);
    }
  }
  else if (bvSerial.strData == "darker")
  {
    if (lightLevel > 0)
    {
      lightLevel -= 85;
      analogWrite(pinR, lightLevel);
      analogWrite(pinY, lightLevel);
      analogWrite(pinG, lightLevel);
    }
  }
  else
  {
    bvSerial.startStopListening();
    bvSerial.sendToBV("ERROR:" + bvSerial.strData);
    bvSerial.startStopListening();
  }
}

