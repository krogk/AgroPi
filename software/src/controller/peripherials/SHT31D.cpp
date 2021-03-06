/**
* @file
* @author Kamil Rog
* @version 0.1
*
*
* @section DESCRIPTION
* 
* This file contains the functions for SHT31D class.
*
*/

/*
 *
 * https://www.kernel.org/doc/Documentation/i2c/dev-interface
 * https://github.com/adafruit/Adafruit_SHT31
 * https://www.sensirion.com/fileadmin/user_upload/customers/sensirion/Dokumente/Humidity_and_Temperature_Sensors/Sensirion_Humidity_and_Temperature_Sensors_SHT3x_Datasheet_digital.pdf
 *
 * This depends on i2c dev lib
 * sudo apt-get install libi2c-dev
 *
 * Below is also a good one to have, but be careful i2cdump from the below cause the sht31 interface to become unstable for me
 * and requires a hard-reset to recover correctly.
 * sudo apt-get install i2c-tools
 *
 * on PI make sure below 2 commands are in /boot/config.txt
 * dtparam=i2c_arm=on
 * dtparam=i2c1_baudrate=10000
 * I know we are slowing down the baurate from optimal, but it seems to be the most stable setting in my testing.
 * add another 0 to the above baudrate for max setting, ie dtparam=i2c1_baudrate=100000
 */
 
 
#include "SHT31D.h"
#include <stdint.h>
#include <linux/i2c-dev.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <elf.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>



/*
 * delay:
 *	Wait for some number of milliseconds
 *********************************************************************************
 */

void delay (unsigned int howLong)
{
  struct timespec sleeper, dummy ;

  sleeper.tv_sec  = (time_t)(howLong / 1000) ;
  sleeper.tv_nsec = (long)(howLong % 1000) * 1000000 ;

  nanosleep (&sleeper, &dummy) ;
}

/*
*
* CRC-8 formula from page 14 of SHT spec pdf
*
* Test data 0xBE, 0xEF should yield 0x92
*
* Initialization data 0xFF
* Polynomial 0x31 (x8 + x5 +x4 +1)
* Final XOR 0x00
*/
uint8_t crc8(const uint8_t *data, int len)
{
  const uint8_t POLYNOMIAL = 0x31;
  uint8_t crc = 0xFF;
  int j;
  int i;
  
  for (j = len; j; --j ) {
    crc ^= *data++;

    for ( i = 8; i; --i ) {
      crc = ( crc & 0x80 )
            ? (crc << 1) ^ POLYNOMIAL
            : (crc << 1);
    }
  }
  return crc;
}

/*
 * sht31_open:
 *	Open a file pointer to the appropiate I2C buss and sht31 address
 *********************************************************************************
 */
int sht31_open(int i2c_address, uint8_t sht31_address)
{
  char filename[20];
  int fp;
  
  snprintf(filename, 19, "/dev/i2c-%d", i2c_address);
  fp = open(filename, O_RDWR);
  if (fp < 0) {
    return fp;
  }

  if (ioctl(fp, I2C_SLAVE, sht31_address) < 0) {
    close(fp);
    return -1;
  }
  
  // Do an itial read & write of basically nothing.
  // Still working on this, but without it the first command issued failes, these will also usually fail
#ifdef SHT31D_FIX_INITIAL_FAIL
  uint8_t buf = 0x00;
  if (write(fp, &buf, 1) != 1) {}
  if ( read(fp, &buf, 1) != 1) {} 
#endif
  
  return fp;
}

int sht31_close(int fp)
{
  return close(fp);
}

/*
 * writeandread:
 *	Write I2C command and read return.  Pass 0 for readsize if you only want to write
 *********************************************************************************
 */

SHT31_Return writeandread(int fp, uint16_t sndword, uint8_t *buffer, int readsize)
{
  int rtn;
  int sendsize = 2;
  uint8_t snd[sendsize];
  
  // big-endian - Split the 16bit word into two 8 bits that are flipped.
  snd[0]=(sndword >> 8) & 0xff;
  snd[1]=sndword & 0xff;

  rtn = write(fp, snd, sendsize);
  if ( rtn != sendsize ) {
    //printf("ERROR sending command %d :- %s\n",rtn, strerror (errno));
    return SHT31_WRITE_FAILED;
  } 

  if (readsize > 0) {
    delay(10);
    rtn = read(fp, buffer, readsize);
    if ( rtn < readsize) {
      return SHT31_READ_FAILED;
    }
  }
  
  return SHT31_OK;
}

/*
 * getserialnum:
 *	gets the serial number of the sht31
 *********************************************************************************
 */
SHT31_Return getserialnum(int file, uint32_t *serialNo)
{
  uint8_t buf[10];
  int rtn;

  rtn = writeandread(file, SHT31_READ_SERIALNO, buf, 6);
  if (rtn != SHT31_OK)
    return SHT31_READ_FAILED;
  else {
    *serialNo = ((uint32_t)buf[0] << 24)
              | ((uint32_t)buf[1] << 16)
              | ((uint32_t)buf[3] << 8)
              | (uint32_t)buf[4];
    if (buf[2] != crc8(buf, 2) || buf[5] != crc8(buf+3, 2))
      return SHT31_CRC_CHECK_FAILED;
  }
  
  return SHT31_OK;
}

/*
 * getserialnum:
 *	gets temperature and humidity values
 *********************************************************************************
 */
SHT31_Return gettempandhumidity(int file, float *temp, float *hum)
{
  uint8_t buf[10];
  int rtn;
  
  rtn = writeandread(file, SHT32_DEFAULT_READ, buf, 6);
  
  if (rtn != SHT31_OK)
    return SHT31_READ_FAILED;
  else {
    uint16_t ST, SRH;
    ST = buf[0];
    ST <<= 8;
    ST |= buf[1];
    
    SRH = buf[3];
    SRH <<= 8;
    SRH |= buf[4];

    *temp = -45.0 + (175.0 * ((float) ST / (float) 0xFFFF));
    *hum = 100.0 * ((float) SRH / (float) 0xFFFF);
 
    if ( buf[2] != crc8(buf, 2) || buf[5] != crc8(buf+3, 2))
      return SHT31_CRC_CHECK_FAILED;
  }
  
  return SHT31_OK;
}

/*
 * getserialnum:
 *	gets status
 *********************************************************************************
 */
SHT31_Return getstatus(int file, uint16_t *rtnbuf)
{
  uint8_t buf[10];
  int rtn = writeandread(file, SHT31_READSTATUS, buf, 3);
 
  if (rtn != SHT31_OK)
    return SHT31_READ_FAILED;
  else { 
    *rtnbuf = buf[0];
    *rtnbuf <<= 8;
    *rtnbuf |= buf[1];
   
    if ( buf[2] != crc8(buf, 2) )
      return SHT31_CRC_CHECK_FAILED;
  }
  
  return SHT31_OK;
}

/*
 * clearstatus:
 *	clear all status sht31.
 *********************************************************************************
 */
SHT31_Return clearstatus(int file)
{
  if( writeandread(file, SHT31_CLEARSTATUS, NULL, 0) != 0)
    return SHT31_BAD;
  else 
    return SHT31_OK;
}

/*
 * softreset:
 *	reset sht31.
 *********************************************************************************
 */
SHT31_Return softreset(int file)
{
  if( writeandread(file, SHT31_SOFTRESET, NULL, 0) != 0)
    return SHT31_BAD;
  else 
    return SHT31_OK;	
}

/*
 * enableheater:
 *	turns on heater.
 *********************************************************************************
 */
SHT31_Return enableheater(int file)
{
  if( writeandread(file, SHT31_HEATER_ENABLE, NULL, 0) != 0)
    return SHT31_BAD;
  else 
    return SHT31_OK;
}

/*
 * disableheater:
 *	turns off heater.
 *********************************************************************************
 */
SHT31_Return disableheater(int file)
{
  if( writeandread(file, SHT31_HEATER_DISABLE, NULL, 0) != 0)
    return SHT31_BAD;
  else 
    return SHT31_OK;
}




