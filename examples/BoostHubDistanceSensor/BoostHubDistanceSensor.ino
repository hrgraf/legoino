/**
 * A BoostHub basic example to connect a boost hub, set the led color of the hub 
 * dependent on the detected distance of the distance/color sensor
 * 
 * (c) Copyright 2019 - Cornelius Munz
 * Released under MIT License
 * 
 */

#include "BoostHub.h"

// create a hub instance
BoostHub myBoostHub;
BoostHub::Port _portC = BoostHub::Port::C;
BoostHub::Port _portD = BoostHub::Port::D;

void setup() {
    Serial.begin(115200);
    myBoostHub.init(10); // scan for 10s
} 


// main loop
void loop() {

  // connect flow. Search for BLE services and try to connect if the uuid of the hub is found
  if (myBoostHub.isConnecting()) {
    myBoostHub.connectHub();
    if (myBoostHub.isConnected()) {
      Serial.println("Connected to HUB");
      // connect color/distance sensor to port c, activate sensor for updates
      myBoostHub.activatePortDevice(_portC, 37);
      // connect boost tacho motor  to port d, activate sensor for updates
      myBoostHub.activatePortDevice(_portD, 38);
    } else {
      Serial.println("Failed to connect to HUB");
    }
  }

  // if connected, get distance
  if (myBoostHub.isConnected()) {
    
    delay(100);
   
    // read distance value of color/distance sensor
    double distance = myBoostHub.getDistance();

    // read color value of sensor
    int color = myBoostHub.getColor();

    // set hub LED color dependent on the distance of the sensor to an object
    // red -- short distance
    // orange -- medium distance
    // green -- large distance 
    if (distance < 50.0) {
      myBoostHub.setLedColor(RED);
    } else if (distance < 100.0) {
      myBoostHub.setLedColor(ORANGE);
    }else {
      myBoostHub.setLedColor(GREEN);
    }
    
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.print(", color: ");
    if (color >= NUM_COLOR)
      Serial.println("unknown");
    else
      Serial.println(COLOR_STRING[color]);
  }
  
} // End of loop
