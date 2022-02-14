#include "Arduino.h"
#include "Encoder.h"
#include "CL_PendantLCD/CL_PendantLCD.h"

Encoder enc1(12, 13);
Encoder enc2(4, 5);
Encoder mainEncoder(2, 3);

PendantState state = PendantState::STATE_STARTING;
Axis controlledAxis = Axis::AXIS_X;

CL_PendantLCD lcd(6, 7, 8, 9, 10, 11);

long position = -999;

void setup() {
    lcd.setParameters(state, controlledAxis);
    lcd.begin(16, 2);

    Serial.begin(9600);

    state = PendantState::STATE_AXIS_CONTROL;
}

void loop() {
    lcd.showMenu();

    // TODO: Use the Axis encoder to define the currently controlled axis
    // TODO: Create a class to send control commands to GRBL
    // TODO: And sooooo moore !
}