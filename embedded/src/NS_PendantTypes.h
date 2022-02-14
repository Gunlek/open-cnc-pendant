//
// Created by Fabien Aubret on 29/01/2022.
//

enum PendantState {
    STATE_STARTING              =   0x00,
    STATE_AXIS_CONTROL          =   0x01,
    STATE_SPEED_SETTING         =   0x02,
    STATE_ERMERGENCY_STOP       =   0x03,
    STATE_SPINDLE_CONTROL       =   0x04,
    STATE_MOVE_MODE_SETTING     =   0x05,
    STATE_COOLANT_SETTING       =   0x06,
    STATE_RT_FEEDRATE_SETTING   =   0x07,
    STATE_RT_SPINDLE_SETTING    =   0x08,
    STATE_ERROR                 =   0xFF
};

enum JobState {
    JOB_PENDING     =   0x00,
    JOB_STARTING    =   0x01,
    JOB_PAUSED      =   0x02,
    JOB_STOPPED     =   0x03,
    JOB_ERROR       =   0xFF
};

enum Axis {
    AXIS_X          =   0x01,
    AXIS_Y          =   0x02,
    AXIS_Z          =   0x03
};

enum Step {
    STEP_0_1        =   1,
    STEP_1          =   10,
    STEP_10         =   100,
    STEP_100        =   1000
};

