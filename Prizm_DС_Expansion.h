//
// Created by User on 26.09.2021.
//

#ifndef PRIZMDCEXPANSION_H
#define PRIZMDCEXPANSION_H

#include "Prizm_Expansion.h"
#include "Prizm_Utils.h"

#define PRIZMDCEXPANSION_SETPOWER1 (0x40)
#define PRIZMDCEXPANSION_SETPOWER2 (0x41)
#define PRIZMDCEXPANSION_SETPOWERS (0x42)
#define PRIZMDCEXPANSION_SETSPEED1 (0x43)
#define PRIZMDCEXPANSION_SETSPEED2 (0x44)
#define PRIZMDCEXPANSION_SETSPEEDS (0x45)
#define PRIZMDCEXPANSION_SETTARGET1 (0x46)
#define PRIZMDCEXPANSION_SETTARGET2 (0x47)
#define PRIZMDCEXPANSION_SETTARGETS (0x48)
#define PRIZMDCEXPANSION_SETINVERT1 (0x51)
#define PRIZMDCEXPANSION_SETINVERT2 (0x52)
#define PRIZMDCEXPANSION_READBUSY1 (0x4F)
#define PRIZMDCEXPANSION_READBUSY2 (0x50)
#define PRIZMDCEXPANSION_READCURRENT1 (0x54)
#define PRIZMDCEXPANSION_READCURRENT2 (0x55)
#define PRIZMDCEXPANSION_READENCODER1 (0x49)
#define PRIZMDCEXPANSION_READENCODER2 (0x4A)
#define PRIZMDCEXPANSION_RESETENCODER1 (0x4C)
#define PRIZMDCEXPANSION_RESETENCODER2 (0x4D)
#define PRIZMDCEXPANSION_RESETENCODERS (0x4E)
#define PRIZMDCEXPANSION_SETSPEEDPID (0X56)
#define PRIZMDCEXPANSION_SETTARGETPID (0x57)
#define PRIZMDCEXPANSION_BRAKEMOTOR (0x7D)

class PrizmDCExpansion : public PrizmExpansion {

    using PrizmExpansion::PrizmExpansion;

private:

    uint8_t last_power_1 = 0;
    uint8_t last_power_2 = 0;

public:

    bool brake_on_zero_1 = false;
    bool brake_on_zero_2 = false;

    bool invert_encoder_1 = false;
    bool invert_encoder_2 = false;

    void setMotorPower(uint8_t channel, int16_t power);

    void setMotorPowers(int16_t power1, int16_t power2);

    void setMotorSpeed(uint8_t channel, int16_t Mspeed);

    void setMotorSpeeds(int16_t Mspeed1, int16_t Mspeed2);

    void setMotorTarget(uint8_t channel, int16_t Mspeed, int32_t Mtarget);

    void setMotorTargets(int16_t Mspeed1, int32_t Mtarget1, int16_t Mspeed2, int32_t Mtarget2);

    void setMotorInvert(uint8_t channel, uint8_t invertMotor);

    void setMotorInvert(uint8_t channel, uint8_t invertMotor, bool invertEncoder);

    void setMotorBraking(uint8_t channel, bool brakeOnZero);

    int16_t readMotorBusy(uint8_t channel);

    int16_t readMotorCurrent(uint8_t channel);

    int32_t readEncoderCount(uint8_t channel);

    void resetEncoder(uint8_t channel);

    void resetEncoders();

    void setMotorSpeedPID(uint8_t P, uint8_t I, uint8_t D);

    void setMotorTargetPID(uint8_t P, uint8_t I, uint8_t D);


private:

};


#endif //PRIZMDCEXPANSION_H
