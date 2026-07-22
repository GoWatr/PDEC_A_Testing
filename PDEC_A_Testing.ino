//====================================================
// MAIN.ino
// ATmega2560 HVAC AUTOMATION
// BEDROOM + HALL AUTOMATION
//====================================================

#include "Sensors.h"
#include "RelayFunctions.h"

//====================================================
// STATE VARIABLES
//====================================================

bool Bedroom_State = false;
bool Hall_State = false;

bool RainDetected = false;

//====================================================
// ACTION FLAGS
//====================================================

bool Rain_Action_Done = false;

bool Bedroom_AC_ON_Done = false;
bool Bedroom_AC_OFF_Done = false;

bool Hall_AC_ON_Done = false;
bool Hall_AC_OFF_Done = false;

//====================================================
// TIMER VARIABLES
//====================================================

unsigned long sensorMillis = 0;

const unsigned long sensorInterval = 1000;

//====================================================
// SENSOR VALUES
//====================================================

int16_t bedroomAC = -1;
int16_t hallAC = -1;
int16_t rain = -1;

//====================================================
// DAMPER CONTROL FUNCTION
//====================================================

void UpdateDamper()
{
  //--------------------------------------------------
  // BOTH AC ON
  //--------------------------------------------------

  if (bedroomAC > 55 && hallAC > 55)
  {
    digitalWrite(Topdamper, HIGH);
    digitalWrite(Beddamper, HIGH);
    digitalWrite(Halldamper, HIGH);

    Serial.println("BOTH AC ON -> ALL DAMPERS CLOSE");
  }

  //--------------------------------------------------
  // BEDROOM AC ON ONLY
  //--------------------------------------------------

  else if (bedroomAC > 55 && hallAC < 44)
  {
    digitalWrite(Topdamper, LOW);
    digitalWrite(Beddamper, HIGH);
    digitalWrite(Halldamper, LOW);

    Serial.println("BEDROOM AC ON ONLY");
  }

  //--------------------------------------------------
  // HALL AC ON ONLY
  //--------------------------------------------------

  else if (hallAC > 55 && bedroomAC < 44)
  {
    digitalWrite(Topdamper, LOW);
    digitalWrite(Beddamper, LOW);
    digitalWrite(Halldamper, HIGH);

    Serial.println("HALL AC ON ONLY");
  }

  //--------------------------------------------------
  // BOTH AC OFF
  //--------------------------------------------------

  else if (bedroomAC < 44 && hallAC < 44)
  {
    digitalWrite(Topdamper, LOW);
    digitalWrite(Beddamper, LOW);
    digitalWrite(Halldamper, LOW);

    Serial.println("BOTH AC OFF -> ALL DAMPERS OPEN");
  }
}

//====================================================
// CLOSE ALL DEVICES
//====================================================

void CloseAllDevices()
{
  Serial.println("Close All Devices");

  //--------------------------------------------------
  // BEDROOM
  //--------------------------------------------------

  BedroomWindowOFF();

  BedroomCurtain1OFF();
  BedroomCurtain2OFF();

  //--------------------------------------------------
  // HALL
  //--------------------------------------------------

  HallWindowOFF();

  HallCurtain1OFF();
  HallCurtain2OFF();

  //--------------------------------------------------
  // ALL DAMPERS CLOSE
  //--------------------------------------------------

  digitalWrite(Topdamper, HIGH);
  digitalWrite(Beddamper, HIGH);
  digitalWrite(Halldamper, HIGH);

  //--------------------------------------------------
  // RESET STATES
  //--------------------------------------------------

  Bedroom_State = false;
  Hall_State = false;
}

//====================================================
// SETUP
//====================================================

void setup()
{
  Serial.begin(115200);

  SensorInit();

  RelayInit();

  Serial.println("SYSTEM STARTED");
}

//====================================================
// LOOP
//====================================================

void loop()
{
  //--------------------------------------------------
  // SENSOR READ TIMER
  //--------------------------------------------------

  if (millis() - sensorMillis >= sensorInterval)
  {
    sensorMillis = millis();

    Serial.println("Loop Running");

    //--------------------------------------------------
    // READ SENSORS
    //--------------------------------------------------

    bedroomAC = Read_Bedroom_AC();

    hallAC = Read_Hall_AC();

    rain = Read_RainSensor();

    //--------------------------------------------------
    // SERIAL PRINT
    //--------------------------------------------------

    Serial.print("Bedroom AC : ");
    Serial.println(bedroomAC);

    Serial.print("Hall AC : ");
    Serial.println(hallAC);

    Serial.print("Rain : ");
    Serial.println(rain);

    //==================================================
    // RAIN DETECTION
    //==================================================

    if (rain == 1)
    {
      RainDetected = true;

      if (Rain_Action_Done == false)
      {
        Serial.println("RAIN DETECTED");

        CloseAllDevices();

        Rain_Action_Done = true;
      }

      return;
    }
    else
    {
      //------------------------------------------------
      // RAIN STOPPED
      //------------------------------------------------

      if (RainDetected == true)
      {
        Serial.println("RAIN STOPPED");

        Bedroom_AC_ON_Done = false;
        Bedroom_AC_OFF_Done = false;

        Hall_AC_ON_Done = false;
        Hall_AC_OFF_Done = false;
      }

      RainDetected = false;

      Rain_Action_Done = false;
    }

    //==================================================
    // BEDROOM AC ON
    //==================================================

    if (bedroomAC > 15)
    {
      if (Bedroom_AC_ON_Done == false)
      {
        Serial.println("BEDROOM AC ON");

        //------------------------------------------------
        // CLOSE WINDOW + CURTAINS
        //------------------------------------------------
        BedroomWindowOFF();

        BedroomCurtain1OFF();
        BedroomCurtain2OFF();

        Bedroom_State = true;

        //------------------------------------------------
        // UPDATE DAMPER
        //------------------------------------------------

        UpdateDamper();

        //------------------------------------------------
        // FLAG UPDATE
        //------------------------------------------------

        Bedroom_AC_ON_Done = true;
        Bedroom_AC_OFF_Done = false;
      }
    }

    //==================================================
    // BEDROOM AC OFF
    //==================================================

    else if (bedroomAC < 10 && bedroomAC >= 0)
    {
      if (Bedroom_AC_OFF_Done == false)
      {
        Serial.println("BEDROOM AC OFF");

        //------------------------------------------------
        // OPEN WINDOW + CURTAINS
        //------------------------------------------------

        BedroomWindowON();

        BedroomCurtain1ON();
        BedroomCurtain2ON();

        Bedroom_State = false;

        //------------------------------------------------
        // UPDATE DAMPER
        //------------------------------------------------

        UpdateDamper();

        //------------------------------------------------
        // FLAG UPDATE
        //------------------------------------------------

        Bedroom_AC_OFF_Done = true;
        Bedroom_AC_ON_Done = false;
      }
    }

    //==================================================
    // HALL AC ON
    //==================================================

    if (hallAC > 55)
    {
      if (Hall_AC_ON_Done == false)
      {
        Serial.println("HALL AC ON");

        //------------------------------------------------
        // CLOSE WINDOW + CURTAINS
        //------------------------------------------------

        HallCurtain1OFF();
        HallCurtain2OFF();

        HallWindowOFF();

        Hall_State = true;

        //------------------------------------------------
        // UPDATE DAMPER
        //------------------------------------------------

        UpdateDamper();

        //------------------------------------------------
        // FLAG UPDATE
        //------------------------------------------------

        Hall_AC_ON_Done = true;
        Hall_AC_OFF_Done = false;
      }
    }

    //==================================================
    // HALL AC OFF
    //==================================================

    else if (hallAC < 44 && hallAC >= 0)
    {
      if (Hall_AC_OFF_Done == false)
      {
        Serial.println("HALL AC OFF");

        //------------------------------------------------
        // OPEN WINDOW + CURTAINS
        //------------------------------------------------

        HallWindowON();

        HallCurtain1ON();
        HallCurtain2ON();

        Hall_State = false;

        //------------------------------------------------
        // UPDATE DAMPER
        //------------------------------------------------

        UpdateDamper();

        //------------------------------------------------
        // FLAG UPDATE
        //------------------------------------------------

        Hall_AC_OFF_Done = true;
        Hall_AC_ON_Done = false;
      }
    }
  }
}