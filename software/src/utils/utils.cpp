/**
* @file utils.cpp
* @author Kamil Rog
* @version 0.1
* 
* This file contains the utilities functions used in the project.
*
*/

#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


/**
* Cyclic redundancy check, Calculates 8-Bit checksum with following parameters
* Specified on page 14 of SHT31D Application Note & Also applies to SGP30
* Initial value:          0xFF
* Polynomial:             0x31 (x^8 + x^5 + x^4 + 1)
* XOR Result by:          0x00
*
*
* @param data    Data to perform CRC8 on
* @param datalen length of the data in bytes
* 
* @return Byte CRC Checksum 
*
* @todo: Modify to pass in polynomial, initial value and XOR factor
*/
uint8_t CRC8(uint8_t *data, uint8_t datalen) {
  const uint8_t POLYNOMIAL = 0x31;
  uint8_t crc = 0xFF;

  // Modulo-2 division, a byte at a time
  for (uint8_t i = 0; i < datalen; i++) {
    // XOR
    crc ^= data[i];
    // For each bit
    for (uint8_t b = 0; b < 8; b++) {
      // If top bit is set
      if (crc & 0x80)
        //XOR the previous remainder with the polynomnial
        crc = (crc << 1) ^ POLYNOMIAL;
      else
       // Shift next bit of the message
        crc <<= 1;
    }
  }
  return crc;
}




