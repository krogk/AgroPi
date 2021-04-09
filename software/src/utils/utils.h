/**
* @file utils.h
* @author Kamil Rog
* @version 0.1
*
* 
* This is a header file for utility functions
* This file only contains the function prototypes
* 
*/
#ifndef UTILS_H
#define UTILS_H

#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint8_t CRC8(uint8_t *data, uint8_t datalen);

#endif