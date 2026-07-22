// Sensors.h

#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>

//--------------------------------------------------
// MODBUS SERIAL
//--------------------------------------------------
#define modbus Serial2   // TX2=16, RX2=17

//--------------------------------------------------
// SENSOR VALUES
//--------------------------------------------------
int16_t Bedroom_AC = -1;
int16_t Hall_AC = -1;
int16_t Rainsensor = -1;
int16_t Humidity = -1;

//--------------------------------------------------
// SENSOR INIT
//--------------------------------------------------
void SensorInit()
{
  modbus.begin(9600);
}

//--------------------------------------------------
// CRC16 FUNCTION
//--------------------------------------------------
uint16_t CRC16(uint8_t *data, uint8_t len)
{
  uint16_t crc = 0xFFFF;

  for (int i = 0; i < len; i++)
  {
    crc ^= data[i];

    for (int j = 0; j < 8; j++)
    {
      if (crc & 0x0001)
      {
        crc >>= 1;
        crc ^= 0xA001;
      }
      else
      {
        crc >>= 1;
      }
    }
  }

  return crc;
}

//--------------------------------------------------
// MODBUS READ WITH CRC CHECK
//--------------------------------------------------
int16_t readRegister(uint8_t slaveID, uint16_t regAddr)
{
  uint8_t frame[8] =
  {
    slaveID,
    0x03,
    (uint8_t)(regAddr >> 8),
    (uint8_t)(regAddr & 0xFF),
    0x00,
    0x01,
    0,
    0
  };

  //--------------------------------------------------
  // CALCULATE CRC
  //--------------------------------------------------

  uint16_t crc = CRC16(frame, 6);

  frame[6] = crc & 0xFF;
  frame[7] = (crc >> 8) & 0xFF;

  //--------------------------------------------------
  // CLEAR OLD SERIAL DATA
  //--------------------------------------------------

  while (modbus.available())
  {
    modbus.read();
  }

  //--------------------------------------------------
  // SEND REQUEST
  //--------------------------------------------------

  modbus.write(frame, 8);
  modbus.flush();

  delay(20);

  //--------------------------------------------------
  // RECEIVE RESPONSE
  //--------------------------------------------------

  uint8_t resp[7];

  int index = 0;

  unsigned long start = millis();

  while (millis() - start < 500)
  {
    if (modbus.available())
    {
      resp[index++] = modbus.read();

      if (index >= 7)
      {
        break;
      }
    }
  }

  //--------------------------------------------------
  // RESPONSE CHECK
  //--------------------------------------------------

  if (index == 7)
  {
    //------------------------------------------------
    // CRC CHECK
    //------------------------------------------------

    uint16_t receivedCRC = (resp[6] << 8) | resp[5];

    uint16_t calculatedCRC = CRC16(resp, 5);

    if (receivedCRC == calculatedCRC)
    {
      //------------------------------------------------
      // VALID RESPONSE
      //------------------------------------------------

      if (resp[0] == slaveID && resp[1] == 0x03)
      {
        return (resp[3] << 8) | resp[4];
      }
    }
  }

  //--------------------------------------------------
  // SENSOR TIMEOUT / ERROR
  //--------------------------------------------------

  return -1;
}

//--------------------------------------------------
// BEDROOM AC SENSOR
//--------------------------------------------------
int16_t Read_Bedroom_AC()
{
  modbus.begin(9600);

  delay(50);

  Bedroom_AC = readRegister(0x02, 0x0000);
  // Bedroom_AC = 0;
  return Bedroom_AC;
}

//--------------------------------------------------
// HALL AC SENSOR
//--------------------------------------------------
int16_t Read_Hall_AC()
{
  modbus.begin(9600);

  delay(50);

  Hall_AC = readRegister(0x03, 0x0000);
  //Hall_AC = 23;
  return Hall_AC;
}

//--------------------------------------------------
// RAIN SENSOR
//--------------------------------------------------
int16_t Read_RainSensor()
{
  modbus.begin(4800);

  delay(100);

  //Rainsensor = readRegister(0x01, 0x0001);
  Rainsensor = 0;
  return Rainsensor;
}

//--------------------------------------------------
// HUMIDITY SENSOR
//--------------------------------------------------
int16_t Read_Humidity()
{
  modbus.begin(4800);

  delay(100);

  Humidity = readRegister(0x04, 0x0000);

  return Humidity;
}

#endif