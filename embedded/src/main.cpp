#include "Arduino.h"
#include "Encoder.h"
#include "CL_PendantLCD/CL_PendantLCD.h"

Encoder stepEncoder(12, 13);
Encoder axisEncoder(4, 5);
Encoder mainEncoder(2, 3);

Step availableSteps[4] = { Step::STEP_0_1, Step::STEP_1, Step::STEP_10, STEP_100 };

PendantState state = PendantState::STATE_STARTING;
Axis controlledAxis = Axis::AXIS_X;
Step controlStep = Step::STEP_10;

CL_PendantLCD lcd(6, 7, 8, 9, 10, 11);

long position = -999;

long stepEncoderLastPosition = 0;
long axisEncoderLastPosition = 0;

void readAxisEncoderValue();
void readStepEncoderValue();

void setup() {
    lcd.setParameters(state, controlledAxis, controlStep);
    lcd.begin(16, 2);

    Serial.begin(9600);

    state = PendantState::STATE_AXIS_CONTROL;
}

void loop() {
    lcd.showMenu();

    readAxisEncoderValue();
    readStepEncoderValue();

    // TODO: Use the Axis encoder to define the currently controlled axis
    // TODO: Create a class to send control commands to GRBL
    // TODO: And sooooo moore !
}

void readAxisEncoderValue(){
    if(axisEncoder.read() != axisEncoderLastPosition){
        int encAxisValue = (int)(axisEncoder.read() / 4);
        encAxisValue = encAxisValue % 3 + 1;
        controlledAxis = (Axis)encAxisValue;

        lcd.refreshMenu();
        axisEncoderLastPosition = axisEncoder.read();
    }
}

void readStepEncoderValue(){
    if(stepEncoder.read() != stepEncoderLastPosition){
        int encStepValue = (int)(stepEncoder.read() / 4);
        encStepValue = encStepValue % 6 - 1;
        if(encStepValue < 0){
            encStepValue = 0;
        }
        if(encStepValue > 3){
            encStepValue = 3;
        }
        controlStep = availableSteps[encStepValue];

        lcd.refreshMenu();
        stepEncoderLastPosition = stepEncoder.read();
    }
}