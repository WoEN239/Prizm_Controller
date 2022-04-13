#include <Arduino.h>
#include <avr/wdt.h>
#include <Wire.h>
#include "Prizm_Controller.h"

Prizm prizm;

void Prizm::prizmBegin(boolean waitForStartButton) {  //======= Send a SW reset to all EXPANSION port I2C
    Wire.begin();

    for (uint8_t i = 1; i <= PRIZM_MAX_CONTROLLER_COUNT; i++)
        PrizmExpansion(i).controllerReset();
    delay(400);                        // Give EXPANSION controllers time to reset
    // SW reset on Expansion and DC + Servo chips at addresses 5 and 6 (7 is not used)
    for (uint8_t i = 1; i <= PRIZM_MAX_CONTROLLER_COUNT; i++)
        PrizmExpansion(i).controllerReset();

    unsigned long t_start = millis(); // Battery voltage indication
    for (int16_t i = 0; i < (readBatteryVoltage() - 1050) / 100; i++) {
        setRedLED(HIGH);
        setGreenLED(HIGH);
        delay(100);
        setRedLED(LOW);
        setGreenLED(LOW);
        delay(100);
    }
    setRedLED(LOW);
    setGreenLED(LOW);
    unsigned long t_waited = millis() - t_start;
    unsigned long t_delay = 1000;
    delay(t_delay - (t_waited)>0?t_delay - (t_waited):0); // 1 second delay between time GO button is pushed and program starts gives time for resets

    for (uint8_t i = 1; i <= PRIZM_MAX_CONTROLLER_COUNT; i++)
        PrizmExpansion(i).controllerEnable();

    setGreenLED(HIGH);                    // Turn on when we're reset
    while (readStartButton() == 0 && waitForStartButton) {
        setRedLED(millis() % 3000 < 25);
    }        // wait for the program start (green_value) button pressed
    setRedLED(HIGH);
    t_start = millis();
    while (millis() - t_start < 333 && readStartButton()) {}
    delay(20);
    while (readStartButton())
    setGreenLED(LOW);                    // turn green_value off


}

void Prizm::prizmBegin()
{
    prizmBegin(false);
}

[[noreturn]] void Prizm::prizmEnd() {  //Sent a Reset command to all controllers and reset the controller
    for (uint8_t i = 1; i <= PRIZM_MAX_CONTROLLER_COUNT; i++)
        PrizmExpansion(i).controllerReset();

    wdt_enable(WDTO_15MS);  // set the wdt to timeout after 15ms automatically resets
    for (;;) {}
}

/**
 * Get Battery voltage
 *
 * @return Voltage * 100
 */
int16_t Prizm::readBatteryVoltage() {
    int16_t voltage = analogRead(PRIZM_BATTERYVOLTAGE) * 2;
    return voltage;
}

uint8_t Prizm::readLineSensor(uint8_t pin) {     // Can sense black or white (follow the edge of a black line on a white surface)
    uint8_t BWstate; // black or white
    pinMode(pin, INPUT);
    return digitalRead(pin);
}


/**
 * Read TETRIX or any HC-SR04 - like ultrasonic sensor
 *
 * @param pin Echo/Trig pin (note: those are usually two separate wires, but they can be connected together)
 * @return distance in centimeters
 */
uint32_t Prizm::readSonicSensorCM(uint8_t pin) {   // Returns distance of object from sensor in Centimeters

    delayMicroseconds(1000);  // added in version 2 to help with reading accuracy, can't read sonic sensors very fast
    uint32_t duration;
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    delayMicroseconds(2);
    digitalWrite(pin, HIGH);
    delayMicroseconds(5);
    digitalWrite(pin, LOW);
    pinMode(pin, INPUT);
    duration = pulseIn(pin, HIGH);
    return duration / 29 / 2; // convert time of echo to centimeters distance

}

void Prizm::setGreenLED(uint8_t state) {
    pinMode(PRIZM_GREENLED, OUTPUT); //===== GREEN LED is on pin 7
    digitalWrite(PRIZM_GREENLED, state);
}

void Prizm::setRedLED(uint8_t state) {
    pinMode(PRIZM_REDLED, OUTPUT); //===== RED LED is on pin 6
    digitalWrite(PRIZM_REDLED, state);
}

uint8_t Prizm::readStartButton() {       //============== function returns; unpressed button == 0; pressed button == 1
    pinMode(PRIZM_STARTBTN, INPUT);    // Button is on pin 8; unpressed = high, pressed = low;
    return !digitalRead(PRIZM_STARTBTN);
}


//=========THE END ===========================================================================================================================================================


