#ifndef MCP23017_H

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

extern "C" {
    #include <linux/i2c.h>
    #include <linux/i2c-dev.h>
    //#include <i2c/smbus.h>
}

static inline __s32 i2c_smbus_access(int file, char read_write, __u8 command,
                                     int size, union i2c_smbus_data *data)
{
    struct i2c_smbus_ioctl_data args;
    args.read_write = read_write;
    args.command = command;
    args.size = size;
    args.data = data;

    //printf("r/w: %d\tcmd: 0x%02x\tsz: %d\tdata: %d\n", args.read_write, args.command, args.size, args.data);

    return ioctl(file,I2C_SMBUS,&args);
}

static inline __s32 i2c_smbus_read_byte_data(int file, __u8 command)
{
    union i2c_smbus_data data;
    if (i2c_smbus_access(file,I2C_SMBUS_READ,command,
                         I2C_SMBUS_BYTE_DATA,&data))
        return -1;
    else
        return 0x0FF & data.byte;
}

class mcp23017
{
public:

    enum class RegisterAddr{
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

    mcp23017(uint8_t bus = 0x01, uint8_t addr = 0x27) : mAddr(addr), mBus(bus) {

    }

    bool openDevice() {
        char fname[32];
        snprintf(fname, 32, "/dev/i2c-%d", mBus);
        mFd = open(fname, O_RDWR);

        if (mFd < 0) {
            printf("Error opening /dev/i2c-%d: %d\n", mBus, errno);
            return false;
        }

        if (ioctl(mFd, I2C_SLAVE, mAddr) < 0) {
            printf("Error opening device on bus i2c-%d: %d\n", mBus, errno);
            return false;
        }

        mIsOpen = true;
        return true;
    }

    bool closeDevice() {
        if (mFd > 0) {
            if (close(mFd) != 0) {
                printf("Error closing device i2c-%d: %d\n", mBus, errno);
                mFd = -0xff;
                return false;
            }

            mIsOpen = false;
            return true;
        }

        return false;
    }

    uint8_t read(RegisterAddr reg) {
        if (!mIsOpen) {
            printf("read failed: device not open\n");
            return -1;
        }

        int ret = i2c_smbus_read_byte_data(mFd, (uint8_t) reg);

        if (ret < 0) {
            printf("i2c-%d device @0x%02X register addr: 0x%02X read failed: %d\n", mBus, mAddr, reg, errno);
            return -1;
        }

        //printf("i2c-%d device @0x%02X register addr: 0x%02X read success: 0x%02X\n", mBus, mAddr, reg, ret);
        return ret;
    }
private:
    uint8_t mAddr = 0x27;
    uint8_t mBus = 0x01;
    int mFd = -0xff;
    bool mIsOpen = false;
};

#endif // MCP23017_H
