/**
 * FILENAME :        TFmini.h          
 *
 * DESCRIPTION :
 *      TF Mini - Lidar TF-MINI-S from Benewake.
 *      
 *
 *      Distance measurement from 0.1 to 12 meters 
 *      Time-Of-Flight 
 *
 * NOTES :
 *       Developped by Villou / LEnsE
 **
 * AUTHOR :    Julien VILLEMEJANE        START DATE :    02/feb/2024
 *
 *       LEnsE / Institut d'Optique Graduate School
 */

#ifndef __TFMINI_HEADER_H__
#define __TFMINI_HEADER_H__

#include <mbed.h>

/** Constant definition */
#define TFMINI_BAUDRATE   115200
#define TFMINI_DEBUGMODE  0

// The frame size is nominally 9 characters, but we don't include the first two 0x59's marking the start of the frame
#define TFMINI_FRAME_SIZE                 7

// Timeouts
#define TFMINI_MAXBYTESBEFOREHEADER       30
#define TFMINI_MAX_MEASUREMENT_ATTEMPTS   10

// States
#define READY                             0
#define ERROR_SERIAL_NOHEADER             1
#define ERROR_SERIAL_BADCHECKSUM          2
#define ERROR_SERIAL_TOOMANYTRIES         3
#define MEASUREMENT_OK                    10

/**
 * @class TFMini
 * @brief Control TFMini Lidar
 * @details     TFMini module is a Lidar that permits to measure
 *  distance from 0.1 to 12 meters. 
 *  Communication is RS232 protocol at 115200bauds.
 */

class TFMini {
    private:
        /// Serial interface 
        UnbufferedSerial _ser;
        /// State of the data transfer
        int state;
        /// Last collected distance in meters
        uint16_t distance;
        /// Last collected strength of the communication
        uint16_t strength;
    
        // Low-level communication
        void setStandardOutputMode();
        /// 
        int takeMeasurement();

    public:
        /**
        * @brief Simple constructor of the TFMini class.
        * @details Create a TFMini object based on a Serial communication port
        *    Serial communication will be initialized at 115200 bds
        * @param TX Transmit pin of the serial communication
        * @param RX Receive pin of the serial communication
        */
        TFMini(PinName TX, PinName RX); 
       
        /**
        * @brief Get distance value measured by the Lidar
        * @return distance in meters (int)
        */
        uint16_t getDistance();

        /**
        * @brief Get signal strength measured by the Lidar
        * @return strength
        */
        uint16_t getRecentSignalStrength();
};


#endif