//
// Created by fabie on 14/02/2022.
//

#ifndef EMBEDDED_CL_PENDANTLCD_H
#define EMBEDDED_CL_PENDANTLCD_H


#include "LiquidCrystal.h"
#include "NS_PendantTypes.h"

class CL_PendantLCD {
    public:
        CL_PendantLCD(int rs, int enable, int d0, int d1, int d2, int d3);
        void setParameters(PendantState & i_state, Axis & i_controlledAxis, Step & i_controlStep);
        void begin(int i_cols, int i_rows);

        void refreshMenu();

        void showMenu();

    private:
        PendantState * m_state;
        Axis * m_controlledAxis;
        Step * m_controlStep;

        LiquidCrystal m_lcd;

        PendantState m_previousShowMenuState;

        int m_cols;
        int m_rows;

        char* m_axisToString[4] = {(char*)"", (char*)"X", (char*)"Y", (char*)"Z"};
        char* currentAxisToString();

        double currentRealControlStep();
};


#endif //EMBEDDED_CL_PENDANTLCD_H
