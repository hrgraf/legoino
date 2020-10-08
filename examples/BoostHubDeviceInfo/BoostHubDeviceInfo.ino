/**
 * A BoostHub basic example to connect a boost hub and try to get the
 * hub device infos like battery level, Rssi and firmwar version
 * 
 * (c) Copyright 2019 - Cornelius Munz
 * Released under MIT License
 * 
 */


//  Connected to: 00:16:53:b9:fa:73
//  RSSI: -76
//  Activate tilt sensor
//  Firmware Version: 2-0-0-23
//  Hardware Version: 0-4-0-0
//  Rssi: -82, BatteryLevel [%]: 95, Tilt [x/y]: 1/-87
//  Rssi: -80, BatteryLevel [%]: 95, Tilt [x/y]: 1/-87
//  Rssi: -78, BatteryLevel [%]: 95, Tilt [x/y]: 1/-87
//  Rssi: -78, BatteryLevel [%]: 95, Tilt [x/y]: 1/-87
//  Rssi: -77, BatteryLevel [%]: 95, Tilt [x/y]: 1/-87
//  Rssi: -76, BatteryLevel [%]: 95, Tilt [x/y]: 1/-87
//  Rssi: -76, BatteryLevel [%]: 95, Tilt [x/y]: 1/-87
//  Rssi: -75, BatteryLevel [%]: 95, Tilt [x/y]: 1/-87
//  Rssi: -75, BatteryLevel [%]: 95, Tilt [x/y]: 1/-87
//  Rssi: -75, BatteryLevel [%]: 95, Tilt [x/y]: 1/-87
//  Shut down

#include "BoostHub.h"

// create a hub instance
BoostHub myBoostHub;

void setup() 
{
  Serial.begin(115200);
  Serial.println("Scan for Lego BoostHub...");
  myBoostHub.init(10); // scan for 10s
  delay(1000);
} 


// main loop
void loop() 
{
  static int count = 0;

  // connect flow. Search for BLE services and try to connect if the uuid of the hub is found
  if (myBoostHub.isConnecting()) 
  {
    myBoostHub.connectHub();
    if (myBoostHub.isConnected()) 
    {
      Serial.println("Activate tilt sensor");
      myBoostHub.activatePortDevice(0x3A, 40); // Tilt-Sensor
    } 
    else 
    {
      Serial.println("Failed to connect");
    }

    delay(1000);
  }

  // if connected, show some info
  if (myBoostHub.isConnected()) 
  {
    if (count == 0)
    {
      Serial.print("Firmware Version: ");
      Serial.print(myBoostHub.getFirmwareVersionMajor(), DEC);
      Serial.print("-");
      Serial.print(myBoostHub.getFirmwareVersionMinor(), DEC);
      Serial.print("-");
      Serial.print(myBoostHub.getFirmwareVersionBugfix(), DEC);
      Serial.print("-");
      Serial.println(myBoostHub.getFirmwareVersionBuild(), DEC);
  
      Serial.print("Hardware Version: ");
      Serial.print(myBoostHub.getHardwareVersionMajor(), DEC);
      Serial.print("-");
      Serial.print(myBoostHub.getHardwareVersionMinor(), DEC);
      Serial.print("-");
      Serial.print(myBoostHub.getHardwareVersionBugfix(), DEC);
      Serial.print("-");
      Serial.println(myBoostHub.getHardwareVersionBuild(), DEC);

      myBoostHub.setLedColor(GREEN);
    }

    Serial.print("Rssi: ");
    Serial.print(myBoostHub.getRssi(), DEC);
    Serial.print(", BatteryLevel [%]: ");
    Serial.print(myBoostHub.getBatteryLevel(), DEC);
    Serial.print(", Tilt [x/y]: ");
    Serial.print(myBoostHub.getTiltX(), DEC);
    Serial.print("/");
    Serial.println(myBoostHub.getTiltY(), DEC);

    count++;
  }
  else
  {
    count = 0;
  }
  
  if (count == 10) 
  {
    Serial.println("Shut down");
    myBoostHub.shutDownHub();
  }

  delay(1000);
} // End of loop
