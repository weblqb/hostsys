#ifndef BMP180_H
#define BMP180_H

//i2c address
#define BMP180_Address 0x77

//Operating Modes
#define BMP180_ULTRALOWPOWER    0
#define BMP180_STANDARD         1
#define BMP180_HIGHRES          2
#define BMP180_ULTRAHIGHRES     3

//BMP185 Registers
#define BMP180_CAL_AC1          0xAA  //Calibration data (16 bits)
#define BMP180_CAL_AC2          0xAC  //Calibration data (16 bits)
#define BMP180_CAL_AC3          0xAE  //Calibration data (16 bits)
#define BMP180_CAL_AC4          0xB0  //Calibration data (16 bits)
#define BMP180_CAL_AC5          0xB2  //Calibration data (16 bits)
#define BMP180_CAL_AC6          0xB4  //Calibration data (16 bits)
#define BMP180_CAL_B1           0xB6  //Calibration data (16 bits)
#define BMP180_CAL_B2           0xB8  //Calibration data (16 bits)
#define BMP180_CAL_MB           0xBA  //Calibration data (16 bits)
#define BMP180_CAL_MC           0xBC  //Calibration data (16 bits)
#define BMP180_CAL_MD           0xBE  //Calibration data (16 bits)
#define BMP180_CONTROL          0xF4
#define BMP180_TEMPDATA         0xF6
#define BMP180_PRESSUREDATA     0xF6

//Commands
#define BMP180_READTEMPCMD      0x2E
#define BMP180_READPRESSURECMD  0x34

class BMP180
{
private:
    short AC1,AC2,AC3,B1,B2,MB,MC,MD;
    unsigned short AC4,AC5,AC6;
    int fd;
    char I2C_readByte(int reg);
    unsigned short I2C_readU16(int reg);
    short I2C_readS16(int reg);
    void I2C_writeByte(int reg, int val);
    void load_calibration();
    int read_raw_temp();
    int read_raw_pressure();
public:
    BMP180();
    float read_temperature();
    int read_pressure();
    float read_altitude();
    float read_sealevel_pressure();
};

#endif // BMP180_H
