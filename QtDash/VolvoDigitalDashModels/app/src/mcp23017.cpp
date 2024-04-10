#include <mcp23017.h>

extern "C" {
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
}

static inline __s32 i2c_smbus_access(int file, char read_write, __u8 command,
                                     int size, union i2c_smbus_data *data)
{
    struct i2c_smbus_ioctl_data args;
    args.read_write = read_write;
    args.command = command;
    args.size = size;
    args.data = data;

    return ioctl(file,I2C_SMBUS,&args);
}

static inline __s32 i2c_smbus_read_byte_data(int file, __u8 command)
{
    union i2c_smbus_data data;
    if (i2c_smbus_access(file,I2C_SMBUS_READ,command,
                         I2C_SMBUS_BYTE_DATA,&data)) {
        return -1;
    } else {
        return 0x0FF & data.byte;
    }
}

Mcp23017::Mcp23017(uint8_t bus, uint8_t addr) : mAddr(addr), mBus(bus) {
}

bool Mcp23017::openDevice() {
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

bool Mcp23017::closeDevice() {
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

uint8_t Mcp23017::read(RegisterAddr reg) {
    if (!mIsOpen) {
        printf("read failed: device not open\n");
        return -1;
    }

    int ret = i2c_smbus_read_byte_data(mFd, (uint8_t) reg);

    if (ret < 0) {
        printf("i2c-%d device @0x%02X register addr: 0x%02X read failed: %d\n", mBus, (unsigned int)mAddr, (unsigned int)reg, errno);
        return -1;
    }
    return ret;
}
