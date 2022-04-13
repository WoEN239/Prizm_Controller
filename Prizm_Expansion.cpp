//
// Created by User on 26.09.2021.
//

#include "Prizm_Expansion.h"
#include "Prizm_Utils.h"

PrizmExpansion::PrizmExpansion(uint8_t address) {
    this->address = address;
}

void PrizmExpansion::WDT_STOP() const {
    send8(address, PRIZMEXPANSION_WDTSTOP, 50);
}

void PrizmExpansion::controllerReset() const {
    send8(address, PRIZMEXPANSION_RESET, 25);
}

void PrizmExpansion::setID(uint8_t newID) {
    if (uint8_t oldID = readID()) {// No other I2C devices can be connected to sensor ports when executing this command.

        send2x8(oldID, PRIZMEXPANSION_SETID, newID);

        pinMode(6, OUTPUT);                //===== RED LED is on pin 6
        digitalWrite(6, HIGH);                // Flash PRIZM Red LED when finished
        delay(100);
        digitalWrite(6, LOW);
        delay(100);
        digitalWrite(6, HIGH);
        delay(100);
        digitalWrite(6, LOW);
        address = newID;
    }
}

void PrizmExpansion::controllerEnable() const {
    send8(address, PRIZMEXPANSION_ENABLE, 25);
}

uint8_t PrizmExpansion::readID() {
    uint8_t ID;                      // All other I2C devices must also be disconnected from sensor ports when using this function

    for (uint8_t i = 1; i < 120 && !ID; i++) {            // Spin up I2C addresses from 1 - 120

        Wire.beginTransmission(i);

        if ((Wire.endTransmission() == 0) &&
            ((i < 5) || (i > 6))) // Capture response from expansion controller (ignore 5 and 6 - they are used by PRIZM)
        {
            ID = i;
            address = ID;
            delay(50);
        }
    }

    return ID;
}

int16_t PrizmExpansion::readFirmware() const {

    send8(address, PRIZMEXPANSION_READFW);
    Wire.requestFrom(address, (uint8_t) 1);
    int16_t DCversion = Wire.read();
    delay(PRIZMUTILS_DEFAULT_I2C_DELAY);
    return DCversion;
}

int16_t PrizmExpansion::readBatteryVoltage() const {
    send8(address, PRIZMEXPANSION_READVOLTAGE);
    Wire.requestFrom(address, (uint8_t) 2);
    byte byte1 = Wire.read();
    int16_t Bvoltage = byte1 * 256 + Wire.read();
    delay(PRIZMUTILS_DEFAULT_I2C_DELAY);
    return Bvoltage;
}
