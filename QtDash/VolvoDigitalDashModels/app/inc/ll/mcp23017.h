#ifndef MCP23017_H
#define MCP23017_H

#include <cstddef>
#include <cstdint>

#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <cstdlib>
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <err.h>
#include <errno.h>

#include <linux/types.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/**
 * @brief MCP23017 i2c i/o expander class
 * uses linux i2c-dev interface to read from
 * the i2c bus.
 *
 * On a pi, this is all assuming that the i2c-bcm2835
 * and i2c-dev modules have been loaded into the kernel.
 */
class Mcp23017
{
public:

    /**
     * @brief MCP23017 register addresses
     */
    enum class RegisterAddr {
        IODIRA      = 0x00,
        IODIRB      = 0x01,
        IPOLA       = 0x02,
        IPOLB       = 0x03,
        GPINTENA    = 0x04,
        GPINTENB    = 0x05,
        DEFVALA     = 0x06,
        DEFVALB     = 0x07,
        INTCONA     = 0x08,
        INTCONB     = 0x09,
        IOCONA      = 0x0A,
        IOCONB      = 0x0B,
        GPPUA       = 0x0C,
        GPPUB       = 0x0D,
        INTFA       = 0x0E,
        INTFB       = 0x0F,
        INTCAPA     = 0x10,
        INTCAPB     = 0x11,
        GPIOA       = 0x12,
        GPIOB       = 0x13,
        OLATA       = 0x14,
        OLATB       = 0x15,
    };

    /**
     * @brief Constructor
     * @param bus: i2c bus -- ex: 1 for i2c-1, 0 for i2c-0
     * @param addr: 8 bit address of device on the bus (use i2cdetect if you don't know)
     */
    Mcp23017(uint8_t bus = 0x01, uint8_t addr = 0x20);

    /**
     * @brief Open I2C device
     * @return true if successful, false on error
     */
    bool openDevice();

    /**
     * @brief Close the I2C device
     * @return true if successful, false on error
     */
    bool closeDevice();

    /**
     * @brief read
     * @param reg
     * @return
     */
    uint8_t read(RegisterAddr reg) const ;

    int getNumChannels() const{
        return 16;
    }
private:
    /**
     * @brief device address
     */
    uint8_t mAddr = 0x20;

    /**
     * @brief i2c bus on which device is located
     */
    uint8_t mBus = 0x01;

    /**
     * @brief /dev file descriptor
     */
    int mFd = -0xff;

    /**
     * @brief is device connected?
     */
    bool mIsOpen = false;
};

#endif // MCP23017_H
