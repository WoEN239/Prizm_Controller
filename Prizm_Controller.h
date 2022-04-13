#include <Arduino.h>

#ifndef PRIZM_H
#define PRIZM_H

#include "Prizm_Expansion.h"
#include "Prizm_DC_Expansion.h"
#include "Prizm_Servo_Expansion.h"

#define PRIZM_INTEGRATEDDC_ID (5)
#define PRIZM_INTEGRATEDSVO_ID (6)
#define PRIZM_BATTERYVOLTAGE (0)
#define PRIZM_GREENLED (7)
#define PRIZM_REDLED (6)
#define PRIZM_STARTBTN (8)
#define PRIZM_MAX_CONTROLLER_COUNT (6)

class Prizm {

public:
    PrizmDCExpansion integrated_DC;
    PrizmServoExpansion integrated_servo;

    Prizm() : integrated_DC(PRIZM_INTEGRATEDDC_ID), integrated_servo(PRIZM_INTEGRATEDSVO_ID) {}

    static uint8_t readLineSensor(uint8_t pin);
    static uint32_t readSonicSensorCM(uint8_t pin);
    static int16_t readBatteryVoltage();
    static void prizmBegin();
    static void prizmBegin(boolean waitForStartButton);

    [[noreturn]] static void prizmEnd();
    static void setGreenLED(uint8_t state);
    static void setRedLED(uint8_t state);
    static uint8_t readStartButton();

private:
};

extern Prizm prizm;

#endif







