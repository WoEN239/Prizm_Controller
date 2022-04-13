//
// Created by User on 26.09.2021.
//

#ifndef PRIZMEXPANSION_H
#define PRIZMEXPANSION_H

#include <Arduino.h>
#include <Wire.h>

#define PRIZMEXPANSION_WDTSTOP (0x23)
#define PRIZMEXPANSION_ENABLE (0x25)
#define PRIZMEXPANSION_RESET (0x27)
#define PRIZMEXPANSION_SETID (0x24)
#define PRIZMEXPANSION_READFW (0x26)
#define PRIZMEXPANSION_READVOLTAGE (0x53)


class PrizmExpansion {

protected:
    uint8_t address;
public:

    explicit PrizmExpansion(uint8_t address = 0);

    void WDT_STOP() const;
    void controllerEnable() const;
    void controllerReset() const;
    void setID(uint8_t newID);
    uint8_t readID();
    int16_t readFirmware() const;
    int16_t readBatteryVoltage() const;

};


#endif //PRIZMEXPANSION_H
