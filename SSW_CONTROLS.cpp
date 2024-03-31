// Automated Seatbelt Restraint System - SSW CONTROLS
// Code Written by Jose Puga
// Senior Design Project - ME195B 


#include <Arduino.h> 
#include <Nextion.h> 
#include <AccelStepper.h> 

void StartMotor() {

// Insert motor control parameters here 

}

// Declaring Nextion Objects - Page ID, Component ID, Component Name 

// Register a button object to the touch event list. 
NexTouch *nex_listen_list[] = { 

}; 

// When the START button is released, the Motor turns on and the state text changes 

void bOnPopCallback (void *ptr) { 
    tState.setText("START")
    // Insert Move Forward Member Function here 
}

// When the STOP button is released, the MOTOR turns off and the state text changes

void bOffPopCallback(void *ptr) { 
tState.setText("STOP")
// Insert Stop Member Function here
}

void setup () {

Serial.begin(38400); 

// StartMotor()

nexInit(); 

bOn.attachPop(bOnPopCallback, &bOn); 
bOff.attachPop(bOffPopCallback, &bOff); 

}

void loop () {

  // Check if data is available on the serial port
  if (Serial.available() > 0) {
    state = Serial.read(); // Read the incoming byte

    if (state == '0') {
      StartMotor(false); // Turn the motor off
      Serial.println("Motor Is Off"); // Send feedback to the phone
    } 
    else if (state == '1') {
      StartMotor(true); // Turn the motor on
      Serial.println("Motor Is On"); // Send feedback to the phone
    }

    // Process Nextion display events or commands
    // Assuming 'nex_listen_list' is correctly defined and initialized elsewhere
    nexLoop(nex_listen_list);
  }
}

