// RelayFunctions.h

#ifndef RELAYFUNCTIONS_H
#define RELAYFUNCTIONS_H

#include <Arduino.h>

//--------------------------------------------------
// PIN DEFINITIONS
//--------------------------------------------------

//---------- BED ROOM --------
#define BedW_ON        10
#define BedW_OFF       11

//---------- LIVING ROOM --------
#define HallW_ON       12
#define HallW_OFF      13

//---------- BED ROOM CURTAINS --------
#define BDCurt1_ON     47
#define BDCurt1_OFF    49

#define BDCurt2_ON     51
#define BDCurt2_OFF    53

//---------- HALL CURTAINS --------
#define HallCurt1_ON   39
#define HallCurt1_OFF  41

#define HallCurt2_ON   43
#define HallCurt2_OFF  45

#define Topdamper 5
#define Beddamper 4
#define Halldamper 3
//--------------------------------------------------
// RELAY INITIALIZATION
//--------------------------------------------------
void RelayInit()
{
  // Window
  pinMode(BedW_ON, OUTPUT);
  pinMode(BedW_OFF, OUTPUT);

  pinMode(HallW_ON, OUTPUT);
  pinMode(HallW_OFF, OUTPUT);

  // Bedroom Curtain
  pinMode(BDCurt1_ON, OUTPUT);
  pinMode(BDCurt1_OFF, OUTPUT);

  pinMode(BDCurt2_ON, OUTPUT);
  pinMode(BDCurt2_OFF, OUTPUT);

  // Hall Curtain
  pinMode(HallCurt1_ON, OUTPUT);
  pinMode(HallCurt1_OFF, OUTPUT);

  pinMode(HallCurt2_ON, OUTPUT);
  pinMode(HallCurt2_OFF, OUTPUT);
  
  // Damper or Lower
  pinMode(Topdamper, OUTPUT);
  pinMode(Beddamper, OUTPUT);
  pinMode(Halldamper, OUTPUT);
  
  // Relay OFF initially (Active LOW)
  digitalWrite(BedW_ON, HIGH);
  digitalWrite(BedW_OFF, HIGH);

  digitalWrite(HallW_ON, HIGH);
  digitalWrite(HallW_OFF, HIGH);

  digitalWrite(BDCurt1_ON, HIGH);
  digitalWrite(BDCurt1_OFF, HIGH);

  digitalWrite(BDCurt2_ON, HIGH);
  digitalWrite(BDCurt2_OFF, HIGH);

  digitalWrite(HallCurt1_ON, HIGH);
  digitalWrite(HallCurt1_OFF, HIGH);

  digitalWrite(HallCurt2_ON, HIGH);
  digitalWrite(HallCurt2_OFF, HIGH);

  digitalWrite(Topdamper, HIGH);
  digitalWrite(Beddamper, HIGH);
  digitalWrite(Halldamper, HIGH);
}


//--------------------------------------------------
// BED ROOM WINDOW
//--------------------------------------------------
void BedroomWindowON()
{
  Serial.println("BedroomWindowON");
  digitalWrite(BedW_ON, LOW);
  delay(5000);
  digitalWrite(BedW_ON, HIGH);
}

void BedroomWindowOFF()
{
  Serial.println("BedroomWindowOFF");
  digitalWrite(BedW_OFF, LOW);
  delay(5000);
  digitalWrite(BedW_OFF, HIGH);
}

//--------------------------------------------------
// HALL WINDOW
//--------------------------------------------------
void HallWindowON()
{
  Serial.println("HallWindowON");
  digitalWrite(HallW_ON, LOW);
  delay(2000);
  digitalWrite(HallW_ON, HIGH);
}

void HallWindowOFF()
{
  Serial.println("HallWindowOFF");
  digitalWrite(HallW_OFF, LOW);
  delay(2000);
  digitalWrite(HallW_OFF, HIGH);
}

//--------------------------------------------------
// BED ROOM CURTAIN 1
//--------------------------------------------------
void BedroomCurtain1ON()
{
  Serial.println("BedroomCurtain1ON");
  digitalWrite(BDCurt1_ON, LOW);
  delay(20000);
  digitalWrite(BDCurt1_ON, HIGH);
}

void BedroomCurtain1OFF()
{
  Serial.println("BedroomCurtain1OFF");
  digitalWrite(BDCurt1_OFF, LOW);
  delay(20000);
  digitalWrite(BDCurt1_OFF, HIGH);
}

//--------------------------------------------------
// BED ROOM CURTAIN 2
//--------------------------------------------------
void BedroomCurtain2ON()
{
  Serial.println("BedroomCurtain2ON");
  digitalWrite(BDCurt2_ON, LOW);
  delay(20000);
  digitalWrite(BDCurt2_ON, HIGH);
}

void BedroomCurtain2OFF()
{
  Serial.println("BedroomCurtain2OFF");
  digitalWrite(BDCurt2_OFF, LOW);
  delay(20000);
  digitalWrite(BDCurt2_OFF, HIGH);
}

//--------------------------------------------------
// HALL CURTAIN 1
//--------------------------------------------------
void HallCurtain1ON()
{
  Serial.println("HallCurtain1ON");
  digitalWrite(HallCurt1_ON, LOW);
  delay(20000);
  digitalWrite(HallCurt1_ON, HIGH);
}

void HallCurtain1OFF()
{
  Serial.println("HallCurtain1OFF");
  digitalWrite(HallCurt1_OFF, LOW);
  delay(20000);
  digitalWrite(HallCurt1_OFF, HIGH);
}

//--------------------------------------------------
// HALL CURTAIN 2
//--------------------------------------------------
void HallCurtain2ON()
{
  Serial.println("HallCurtain2ON");
  digitalWrite(HallCurt2_ON, LOW);
  delay(20000);
  digitalWrite(HallCurt2_ON, HIGH);
}

void HallCurtain2OFF()
{
  Serial.println("HallCurtain2OFF");
  digitalWrite(HallCurt2_OFF, LOW);
  delay(20000);
  digitalWrite(HallCurt2_OFF, HIGH);
}

#endif