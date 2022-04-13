//
// Created by User on 26.09.2021.
//

#ifndef PRIZMSVOEXPANSION_H
#define PRIZMSVOEXPANSION_H

#include "Prizm_Expansion.h"
#include "Prizm_Utils.h"

#define PRIZMSVOEXPANSION_SETSERVOSPEED1 (0x28)
#define PRIZMSVOEXPANSION_SETSERVOSPEED2 (0x29)
#define PRIZMSVOEXPANSION_SETSERVOSPEED3 (0x2A)
#define PRIZMSVOEXPANSION_SETSERVOSPEED4 (0x2B)
#define PRIZMSVOEXPANSION_SETSERVOSPEED5 (0x2C)
#define PRIZMSVOEXPANSION_SETSERVOSPEED6 (0x2D)
#define PRIZMSVOEXPANSION_SETSERVOSPEEDS (0x2E)
#define PRIZMSVOEXPANSION_SETSERVOPOSITION1 (0x2F)
#define PRIZMSVOEXPANSION_SETSERVOPOSITION2 (0x30)
#define PRIZMSVOEXPANSION_SETSERVOPOSITION3 (0x31)
#define PRIZMSVOEXPANSION_SETSERVOPOSITION4 (0x32)
#define PRIZMSVOEXPANSION_SETSERVOPOSITION5 (0x33)
#define PRIZMSVOEXPANSION_SETSERVOPOSITION6 (0x34)
#define PRIZMSVOEXPANSION_SETSERVOPOSITIONS (0x35)
#define PRIZMSVOEXPANSION_SETCRSERVOSTATE1 (0x36)
#define PRIZMSVOEXPANSION_SETCRSERVOSTATE2 (0x37)
#define PRIZMSVOEXPANSION_READSERVOPOSITION1 (0x2F)
#define PRIZMSVOEXPANSION_READSERVOPOSITION2 (0x30)
#define PRIZMSVOEXPANSION_READSERVOPOSITION3 (0x31)
#define PRIZMSVOEXPANSION_READSERVOPOSITION4 (0x32)
#define PRIZMSVOEXPANSION_READSERVOPOSITION5 (0x33)
#define PRIZMSVOEXPANSION_READSERVOPOSITION6 (0x34)


class PrizmServoExpansion : public PrizmExpansion {

    using PrizmExpansion::PrizmExpansion;

private:

    uint8_t  last_position_1 = 90;        // these hold the current 'last' positions of each servo channel
    uint8_t  last_position_2 = 90;
    uint8_t  last_position_3 = 90;
    uint8_t  last_position_4 = 90;
    uint8_t  last_position_5 = 90;
    uint8_t  last_position_6 = 90;

public:

    void setServoSpeed(uint8_t  channel, uint8_t  servospeed);

    void setServoSpeeds(uint8_t  servospeed1, uint8_t  servospeed2, uint8_t  servospeed3, uint8_t  servospeed4, uint8_t  servospeed5, uint8_t  servospeed6);

    void setServoPosition(uint8_t  channel, uint8_t  servoposition);

    void setServoPositions(uint8_t  servoposition1, uint8_t  servoposition2, uint8_t  servoposition3, uint8_t  servoposition4, uint8_t  servoposition5, uint8_t  servoposition6);

    void setCRServoState(uint8_t  channel, uint8_t  servospeed);

    int16_t readServoPosition(uint8_t channel);
};


#endif //PRIZMSVOEXPANSION_H
