#include <Nextion.h>
#include <AccelStepper.h>

// Define the stepper motor interface type and the pins used
AccelStepper stepper(AccelStepper::DRIVER, 2, 3); // Pin 2 for STEP, Pin 3 for DIR

// Declare the Nextion components
NexButton b0 = NexButton(0, 1, "b0"); // Page 0, ID 1, Button for forward
NexButton b1 = NexButton(0, 2, "b1"); // Page 0, ID 2, Button for backward
NexSlider h0 = NexSlider(0, 3, "h0"); // Page 0, ID 3, Slider for speed

// List of all the touch event listeners
NexTouch *nex_listen_list[] = {
    &b0,
    &b1,
    &h0,
    NULL  // End of list
};

// Forward and backward button events
void b0PopCallback(void *ptr) {
    stepper.moveTo(stepper.currentPosition() + 1000); // Move 1000 steps forward
}

void b1PopCallback(void *ptr) {
    stepper.moveTo(stepper.currentPosition() - 1000); // Move 1000 steps backward
}

// Slider event for speed adjustment
void h0PopCallback(void *ptr) {
    uint32_t speed;
    h0.getValue(&speed);
    stepper.setMaxSpeed(speed); // Set the speed from slider
    stepper.setAcceleration(500); // Set a reasonable acceleration
}

void setup() {
    Serial.begin(9600); // Start serial communication with computer for debugging
    Serial2.begin(9600); // Start serial communication on Serial2 port with Nextion display
    Serial.println("STARTING UP....");

    nexInit(); // Initialize communication with Nextion display

    // Attach the callback functions
    b0.attachPop(b0PopCallback, &b0);
    b1.attachPop(b1PopCallback, &b1);
    h0.attachPop(h0PopCallback, &h0);

    // Setup initial stepper parameters
    stepper.setMaxSpeed(1000);
    stepper.setAcceleration(500);
}

void loop() {
    nexLoop(nex_listen_list); // Process Nextion touch events
    stepper.run(); // Continuously runs the stepper to its target position
}
