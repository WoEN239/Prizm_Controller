//
// Created by User on 26.09.2021.
//

#include "Prizm_DС_Expansion.h"


void PrizmDCExpansion::setMotorPower(uint8_t channel, int16_t power) {
    uint8_t byte = power < -100 ? -100 : power > 100 ? 100 : power;
    if (channel == 1) {
        byte = (!byte) && brake_on_zero_1 ? PRIZMDCEXPANSION_BRAKEMOTOR : byte;
        if (byte != last_power_1) {
            send2x8(address, PRIZMDCEXPANSION_SETPOWER1, byte);
            last_power_1 = byte;
        }
    }   // DC channel 1
    if (channel == 2) {
        byte = (!byte) && brake_on_zero_2 ? PRIZMDCEXPANSION_BRAKEMOTOR : byte;
        if (byte != last_power_2) {
            send2x8(address, PRIZMDCEXPANSION_SETPOWER2, byte);
            last_power_2 = byte;
        }
    }   // DC channel 2

}

void PrizmDCExpansion::setMotorPowers(int16_t power1, int16_t power2) {
    uint8_t byte1 = power1 < -100 ? -100 : power1 > 100 ? 100 : power1 == 0 && brake_on_zero_1 ? PRIZMDCEXPANSION_BRAKEMOTOR : power1;
    uint8_t byte2 = power2 < -100 ? -100 : power2 > 100 ? 100 : power2 == 0 && brake_on_zero_2 ? PRIZMDCEXPANSION_BRAKEMOTOR : power2;
    if (byte1 != last_power_1 || byte2 != last_power_2) {
        send3x8(address, PRIZMDCEXPANSION_SETPOWERS, byte1, byte2);
        last_power_1 = byte1;
        last_power_2 = byte2;
    }
}

void PrizmDCExpansion::setMotorSpeed(uint8_t channel, int16_t Mspeed) {
    if (channel == 1) { channel = PRIZMDCEXPANSION_SETSPEED1; }   // DC channel 1
    if (channel == 2) { channel = PRIZMDCEXPANSION_SETSPEED2; }
    send8and16(address, channel, Mspeed);
}

void PrizmDCExpansion::setMotorSpeeds(int16_t Mspeed1, int16_t Mspeed2) {
    send8and2x16(address, PRIZMDCEXPANSION_SETSPEEDS, Mspeed1, Mspeed2);
}

void PrizmDCExpansion::setMotorTarget(uint8_t channel, int16_t Mspeed, int32_t Mtarget) {
    if (channel == 1) { channel = PRIZMDCEXPANSION_SETTARGET1; }   // DC channel 1
    if (channel == 2) { channel = PRIZMDCEXPANSION_SETTARGET2; }
    send8and16and32(address, channel, Mspeed, Mtarget);
}

void PrizmDCExpansion::setMotorTargets(int16_t Mspeed1, int32_t Mtarget1, int16_t Mspeed2, int32_t Mtarget2) {
    send8and2x16and32(address, PRIZMDCEXPANSION_SETTARGETS, Mspeed1, Mtarget1, Mspeed2, Mtarget2);
}

void PrizmDCExpansion::setMotorInvert(uint8_t channel, uint8_t invertMotor, bool invertEncoder) {
    if (channel == 1) {
        channel = PRIZMDCEXPANSION_SETINVERT1;
        invert_encoder_1 = invertEncoder;
    }   // DC channel 1
    else if (channel == 2) {
        channel = PRIZMDCEXPANSION_SETINVERT2;
        invert_encoder_2 = invertEncoder;
    }
    send2x8(address, channel, invertMotor);
}

void PrizmDCExpansion::setMotorBraking(uint8_t channel, bool brakeOnZero) {
    if (channel == 1)
        brake_on_zero_1 = brakeOnZero;
    else if (channel == 2)
        brake_on_zero_2 = brakeOnZero;
}

int16_t PrizmDCExpansion::readMotorBusy(uint8_t channel) {
    if (channel == 1) { channel = PRIZMDCEXPANSION_READBUSY1; }   // DC channel 1
    if (channel == 2) { channel = PRIZMDCEXPANSION_READBUSY2; }
    send8(address, channel);
    Wire.requestFrom(address, (uint8_t) 1);
    int16_t byte1 = Wire.read();
    delay(PRIZMUTILS_DEFAULT_I2C_DELAY);
    return byte1;
}

int16_t PrizmDCExpansion::readMotorCurrent(uint8_t channel) {
    if (channel == 1) { channel = PRIZMDCEXPANSION_READCURRENT1; }   // DC channel 1
    if (channel == 2) { channel = PRIZMDCEXPANSION_READCURRENT2; }
    send8(address, channel);
    Wire.requestFrom(address, (uint8_t) 2);
    byte byte1 = Wire.read();
    int16_t MotorCurrent = byte1 * 256 + Wire.read();
    delay(PRIZMUTILS_DEFAULT_I2C_DELAY);
    return MotorCurrent;
}

int32_t PrizmDCExpansion::readEncoderCount(uint8_t channel) {
    int8_t sign = 0;
    if (channel == 1) {
        channel = PRIZMDCEXPANSION_READENCODER1;
        sign = invert_encoder_1 ? -1 : 1;
    }
    if (channel == 2) {
        channel = PRIZMDCEXPANSION_READENCODER2;
        sign = invert_encoder_2 ? -1 : 1;
    }
    send8(address, channel);

    Wire.requestFrom(address, (uint8_t) 4);
    byte byte1 = Wire.read();
    byte byte2 = Wire.read();
    byte byte3 = Wire.read();
    //uint32_t eCount = (((((byte1 * 256) + byte2) * 256) + byte3) * 256) + Wire.read(); // idk why this does not work
    uint32_t eCount = byte1;
    eCount = (eCount * 256) + byte2;
    eCount = (eCount * 256) + byte3;
    eCount = (eCount * 256) + Wire.read();
    delay(PRIZMUTILS_DEFAULT_I2C_DELAY);
    return sign * eCount;
}

void PrizmDCExpansion::resetEncoder(uint8_t channel) {
    if (channel == 1) { channel = PRIZMDCEXPANSION_RESETENCODER1; }
    if (channel == 2) { channel = PRIZMDCEXPANSION_RESETENCODER2; }
    send8(address, channel);
}

void PrizmDCExpansion::resetEncoders() {
    send8(address, PRIZMDCEXPANSION_RESETENCODERS);
}

void PrizmDCExpansion::setMotorSpeedPID(uint8_t P, uint8_t I, uint8_t D) {
    send4x8(address, PRIZMDCEXPANSION_SETSPEEDPID, P, I, D);
}

void PrizmDCExpansion::setMotorTargetPID(uint8_t P, uint8_t I, uint8_t D) {
    send4x8(address, PRIZMDCEXPANSION_SETTARGETPID, P, I, D);
}

void PrizmDCExpansion::setMotorInvert(uint8_t channel, uint8_t invertMotor) {
    setMotorInvert(channel, invertMotor, invertMotor);
}

