#include "Arduino.h"
#include "Encoder.h"
#include "CL_PendantLCD/CL_PendantLCD.h"

Encoder stepEncoder(12, 13);
Encoder axisEncoder(4, 5);
Encoder mainEncoder(2, 3);

Step availableSteps[4] = { Step::STEP_0_1, Step::STEP_1, Step::STEP_10, STEP_100 };
int currentStepIndex = 0;

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

    // TODO: Create a class to send control commands to GRBL
    // TODO: Add all the menus
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
    if(stepEncoder.read() / 4 != stepEncoderLastPosition){
        int encStepVariation = (int)(stepEncoder.read() / 4 - stepEncoderLastPosition);

        currentStepIndex += encStepVariation;
        if(currentStepIndex < 0){
            currentStepIndex = 0;
        }
        if(currentStepIndex > 3){
            currentStepIndex = 3;
        }

        controlStep = availableSteps[currentStepIndex];

        lcd.refreshMenu();
        stepEncoderLastPosition = stepEncoder.read() / 4;
    }
}