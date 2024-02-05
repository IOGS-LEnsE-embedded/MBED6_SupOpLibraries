/**
 * FILENAME :        TCS34725.cpp          
 *
 * DESCRIPTION :
 *       RGB Sensor TCS34725 classes
 *
 * NOTES :
 *       Developped by Villou / LEnsE
 **
 * AUTHOR :    Julien VILLEMEJANE        START DATE :    05/feb/2024
 *
 *       LEnsE / Institut d'Optique Graduate School
 *          http://lense.institutoptique.fr/
 */

#include "TCS34725.h"

TCS34725::TCS34725(I2C *_i2c){
    /* Initialisation of i2c module */
    if (_i2c){ delete this->__i2c; }
    this->__i2c=_i2c;
    this->__i2c->frequency(TCS34725_FREQ);
    wait_us(100);
}

bool TCS34725::init(void){
    char cmd[2];

    // Init TCS
    cmd[0] =    TCS34725_CMD_BIT | TCS34725_ID;
    int ack = this->__i2c->write(TCS34725_ADD << 1, cmd, 1, true);
    if(DEBUG_TCS)   printf("A_ID = %d\r\n", ack);
    ack = this->__i2c->read(TCS34725_ADD << 1, cmd, 1);
    if(DEBUG_TCS)   printf("A_ID_read = %d / Val = %d\r\n", ack, cmd[0]);
    if(cmd[0] == 0x44){
        this->_tcs34725Initialised = true;
        return true;
    }
    else
        return false;    
}


bool TCS34725::setIntegrationTime(uint8_t it){
    if (!_tcs34725Initialised)
        return false;
    char cmd[2];
    cmd[0] =    TCS34725_CMD_BIT | TCS34725_ATIME;
    cmd[1] =    it;
    this->_tcs34725IntegrationTime = it;
    int ack = this->__i2c->write(TCS34725_ADD << 1, cmd, 2);
    if(ack == 0)
        return true;
    else
        return false;
}

bool TCS34725::setGain(tcs34725Gain_t gain){
    if (!_tcs34725Initialised)
        return false;
    char cmd[2];
    cmd[0] =    TCS34725_CMD_BIT | TCS34725_CONTROL;
    cmd[1] =    gain;
    this->_tcs34725Gain = gain;
    int ack = this->__i2c->write(TCS34725_ADD << 1, cmd, 2);
    if(ack == 0)
        return true;
    else
        return false;
}

bool TCS34725::enable(){
    if (!_tcs34725Initialised)
        return false;
    char cmd[2];
    cmd[0] =    TCS34725_CMD_BIT | TCS34725_ENABLE;
    cmd[1] =    TCS34725_ENABLE_PON;
    int ack = this->__i2c->write(TCS34725_ADD << 1, cmd, 2);
    wait_us(30000);
    cmd[0] =    TCS34725_CMD_BIT | TCS34725_ENABLE;
    cmd[1] =    TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN;
    ack += this->__i2c->write(TCS34725_ADD << 1, cmd, 2);
    if(ack == 0)
        return true;
    else
        return false;
}

bool TCS34725::disable(){
    /* Turn the device off to save power */
    char cmd[2];
    cmd[0] =    TCS34725_CMD_BIT | TCS34725_ENABLE;
    int ack = this->__i2c->write(TCS34725_ADD << 1, cmd, 1, true);
    ack += this->__i2c->read(TCS34725_ADD << 1, cmd, 1);
    char reg = cmd[0];
    
    cmd[0] =    TCS34725_CMD_BIT | TCS34725_ENABLE;
    cmd[1] =    reg &  ~(TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN);
    ack += this->__i2c->read(TCS34725_ADD << 1, cmd, 1);
    if(ack == 0)
        return true;
    else
        return false;
}


bool TCS34725::getRawData(uint16_t *r, uint16_t *g, uint16_t *b, uint16_t *c) {
    if (!_tcs34725Initialised)
        return false;
    char cmd[2];
    /// Collect Clear value
    cmd[0] =    TCS34725_CMD_BIT | TCS34725_CDATAL;
    int ack = this->__i2c->write(TCS34725_ADD << 1, cmd, 1, true);
    ack += this->__i2c->read(TCS34725_ADD << 1, cmd, 2);
    *c = (uint16_t(cmd[1]) << 8) | (uint16_t(cmd[0]) & 0xFF);
    /// Collect Red Value
    cmd[0] =    TCS34725_CMD_BIT | TCS34725_RDATAL;
    ack += this->__i2c->write(TCS34725_ADD << 1, cmd, 1, true);
    ack += this->__i2c->read(TCS34725_ADD << 1, cmd, 2);
    *r = (uint16_t(cmd[1]) << 8) | (uint16_t(cmd[0]) & 0xFF);
    /// Collect Blue Value
    cmd[0] =    TCS34725_CMD_BIT | TCS34725_BDATAL;
    ack += this->__i2c->write(TCS34725_ADD << 1, cmd, 1, true);
    ack += this->__i2c->read(TCS34725_ADD << 1, cmd, 2);
    *b = (uint16_t(cmd[1]) << 8) | (uint16_t(cmd[0]) & 0xFF);
    /// Collect Green Value
    cmd[0] =    TCS34725_CMD_BIT | TCS34725_GDATAL;
    ack += this->__i2c->write(TCS34725_ADD << 1, cmd, 1, true);
    ack += this->__i2c->read(TCS34725_ADD << 1, cmd, 2);
    *g = (uint16_t(cmd[1]) << 8) | (uint16_t(cmd[0]) & 0xFF);

    if(ack == 0)
        return true;
    else
        return false;
}
