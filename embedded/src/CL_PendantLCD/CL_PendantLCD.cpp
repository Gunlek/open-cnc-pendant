//
// Created by fabie on 14/02/2022.
//

#include "CL_PendantLCD.h"

/**
 * Create an instance of CL_PendantLCD
 * Input parameters are the same as LiquidCrystal declaration
 * @param rs
 * @param enable
 * @param d0
 * @param d1
 * @param d2
 * @param d3
 */
CL_PendantLCD::CL_PendantLCD(int rs, int enable, int d0, int d1, int d2, int d3):
    m_lcd(rs, enable, d0, d1, d2, d3)
{

}

/**
 * Define the references for the parameters that will be used in the rest of the program
 * @param i_state               The current state of the pendant
 * @param i_controlledAxis      The currently controlled axis
 */
void CL_PendantLCD::setParameters(PendantState &i_state, Axis &i_controlledAxis) {
    this->m_state = &i_state;
    this->m_controlledAxis = &i_controlledAxis;
}

/**
 * Initialize an LCD with a fixed number of columns and rows
 * @param i_cols The number of columns on the LCD
 * @param i_rows The number of rows on the LCD
 */
void CL_PendantLCD::begin(int i_cols, int i_rows) {
    this->m_cols = i_cols;
    this->m_rows = i_rows;

    this->m_lcd.begin(this->m_cols, this->m_rows);
}

/**
 * Show the menu that corresponds to the current active state
 */
void CL_PendantLCD::showMenu() {
    switch(*this->m_state){
        case PendantState::STATE_STARTING:
            this->m_lcd.setCursor(0, 0);
            this->m_lcd.print("Booting...");
            break;

        case PendantState::STATE_AXIS_CONTROL:
            if(m_previousShowMenuState != PendantState::STATE_AXIS_CONTROL) {
                this->m_lcd.clear();

                this->m_lcd.setCursor(0, 0);
                this->m_lcd.print("Axis: ");
                this->m_lcd.print(this->currentAxisToString());

                this->m_lcd.setCursor(0, 1);
                this->m_lcd.print("Step: ");
                this->m_lcd.print(this->m_controlStep);
            }

            this->m_previousShowMenuState = *this->m_state;
            break;

        default:
            for(int r = 0; r < this->m_rows; r++) {
                for(int c = 0; c < this->m_cols; c++) {
                    this->m_lcd.setCursor(c, r);
                    this->m_lcd.print("#");
                }
            }
            break;
    }
}

void CL_PendantLCD::refreshMenu(){
    this->m_previousShowMenuState = PendantState::STATE_ERROR;
}

/**
 * Translate the current axis to string
 * @return A string, X, Y or Z depending on the enum value
 */
char *CL_PendantLCD::currentAxisToString() {
    return m_axisToString[*this->m_controlledAxis];
}




