/**
* @file
* @author Kamil Rog
* @version 0.1
*
*
* @section DESCRIPTION
* 
* This file contains the functions for VEML7700 class.
*
*/
#include "VEML7700.h"
#include <cmath>



/**
* Initialize VEML7700 
* Open fd and write 4 16-bit integers to appropriate registers
* Gain                = 01 = x2 
* Integration time    = 0000 = 100 ms
* Persistance         = 00 = 1
* Power mode          = 00 = mode 1
* Refresh Time        = 600 ms
* Resolution (lx/bit) = 0.0288
*
* @return None
*/
void VEML7700::Initialize(I2CDriver &i2c) {
  i2cdriv = i2c;
  // Open fd to VEML7700
  fd = i2cdriv.I2C_Setup_File(I2C_ADDRESS);

	// Formulate initial register configuration setup of VEML7700
	registerVEML7700[0] = ( (uint16_t(ALS_GAIN_x2) << ALS_SM_SHIFT) | (uint16_t(ALS_INTEGRATION_100ms) << ALS_IT_SHIFT) |(uint16_t(ALS_PERSISTENCE_1) << ALS_PERS_SHIFT) | (uint16_t(0) << ALS_INT_EN_SHIFT) | (uint16_t(0) << ALS_SD_SHIFT) );
	registerVEML7700[1] = 0x0000;
	registerVEML7700[2] = 0xffff;
	registerVEML7700[3] = ( (uint16_t(ALS_POWER_MODE_1) << PSM_SHIFT) | (uint16_t(0) << PSM_EN_SHIFT) );

  // Setup VEML7700 with initial setting by writing data to registers.
	for (uint8_t i = 0; i < 4; i++) {
    i2cdriv.I2C_Write_16bitReg(fd, i, registerVEML7700[i]);
	}
	// Datasheet says to wait at least 2.5ms if there are any issues then try puting delay here before any write/reads
}

/**
* Close file descriptor
* 
* @param fd filde descriptor to close.
*
* @return Status of close operation
*/
int VEML7700::Close_Device() {
  //Soft_Reset();
  return close(fd);
}



/**
* Get Lux from VEML7700
*
* @param lux  Addres of lux variable to modify
* 
* @return Status 
*/
uint8_t VEML7700::Get_ALS_Lux(float& lux) {
  uint16_t rawCount;
  // Get raw count 
  uint8_t status = Get_ALS(rawCount);
  // Compute Lux based on the lux value 
  Compute_Lux(rawCount, lux);
  // return status 
  return status;
}


/**
* Get raw ALS count from VEML7700
*
* @param als  Addres of als variable update with read lux value  
* 
* @return Status 
*/
  uint8_t VEML7700::Get_ALS(uint16_t& als) {
  // Read
  als = i2cdriv.I2C_Read_16bitReg(fd, COMMAND_ALS);
  return STATUS_OK;
}


/**
* Get white lux from VEML7700
*
* @param als Addres of white variable update with read white value  
* 
* @return Status 
*/
uint8_t VEML7700::Get_White_Lux(float& white) {   
  uint16_t rawCount;     
  uint8_t status = Get_White(rawCount); 
  Compute_Lux(rawCount, white);     
  return status;   
}   

/**
* Get raw white als count from VEML7700
*
* @param white Addres of als variable update with read raw count 
* 
* @return Status 
*/
uint8_t VEML7700::Get_White(uint16_t& white) {              
  white = i2cdriv.I2C_Read_16bitReg(fd, COMMAND_WHITE); 
  return STATUS_OK;
}                                                  


/**
* Compute Lux base on the raw count
*
* @param rawCount   Raw count from the sensor 
* @param lux        Address of lux variable to update.
* 
* @return None
*/
void VEML7700::Compute_Lux(uint16_t rawCount, float& lux) {
  // Get Gain
  ALS_GAIN_T gain;
  Get_Gain(gain);
  // Get integration time
  ALS_INTEGRTATION_TIME_T integrationTime;
  Get_Integration_Time(integrationTime);

  // Initialize factor variables
  float factor1 = 0.0, factor2 = 0.0;

  // Chose factor1 - appropriate gain
  switch(gain & 0x3){

  case ALS_GAIN_x1:
    factor1 = 1.f;
    break;

  case ALS_GAIN_x2:
    factor1 = 0.5f;
    break;

  case ALS_GAIN_d8:
    factor1 = 8.f;
    break;

  case ALS_GAIN_d4:
    factor1 = 4.f;
    break;

  default:
    factor1 = 1.f;
    break;
  }

  // Chose factor2 - appropriate integration time
  switch(integrationTime) {
    
    case ALS_INTEGRATION_25ms:
      factor2 = 0.2304f;
      break;

    case ALS_INTEGRATION_50ms:
      factor2 = 0.1152f;
      break;

    case ALS_INTEGRATION_100ms:
      factor2 = 0.0576f;
      break;

    case ALS_INTEGRATION_200ms:
      factor2 = 0.0288f;
      break;

    case ALS_INTEGRATION_400ms:
      factor2 = 0.0144f;
      break;

    case ALS_INTEGRATION_800ms:
      factor2 = 0.0072f;
      break;

    default:
      factor2 = 0.2304f;
      break;
  }
  
  // Calculate lux
  lux = rawCount * factor1 * factor2;

  // Apply Correction Lux_calc = 6.0135E-13x^4 - 9.3924E-09x^3 + 8.1488E-05x^2 + 1.0023E+00x See Application note in hardware/VEML7700, page 21 for details 
  float f1 = 0, f2 = 0, f3 = 0, f4 = 0;
  f1 = 6.0135E-13 * pow(lux, 4); 
  f2 = 9.3924E-09 * pow(lux, 3); 
  f3 = 8.1488E-05 * pow(lux, 2); 
  f4 = 1.0023E+00 * lux; 
  lux = f1 + f2 + f3 + f4;
}


/**
* Set Gain for VEML7700 
*
* @param rawCount 
* @param lux          Address of lux variable to update.
* 
* @return             Zero on success else negative errno 
*/
uint8_t VEML7700::Set_Gain(ALS_GAIN_T gain) {
  // Define new register value 
	uint16_t reg = ( (registerVEML7700[COMMAND_ALS_SM] & ~ALS_SM_MASK) | ((uint16_t(gain) << ALS_SM_SHIFT) & ALS_SM_MASK) );
  // Update register cache variable
  registerVEML7700[COMMAND_ALS_SM] = reg;
  // Update register with new value 
	return i2cdriv.I2C_Write_16bitReg(fd, COMMAND_ALS, reg); 
}

/**
* Get current gain from register cache 
*
* @param gain         Address of gain variable to update
* 
* @return             Status
*/
uint8_t VEML7700::Get_Gain(ALS_GAIN_T &gain) {
  // Assing current gain set to for VEML7700
	gain = ALS_GAIN_T((registerVEML7700[COMMAND_ALS_SM] & ALS_SM_MASK) >> ALS_SM_SHIFT );
	return STATUS_OK;
}


/**
* Set Integration time for VEML7700 
*
* @param integrationTime  Integration time enumeration to set
* 
* @return                 Zero on success else negative errno 
*/
uint8_t VEML7700::Set_Integration_Time(ALS_INTEGRTATION_TIME_T integrationTime) {
  // Define new register value using masks and shift new value into it
  uint16_t reg = ( (registerVEML7700[COMMAND_ALS_IT] & ~ALS_IT_MASK) | ((uint16_t(integrationTime) << ALS_IT_SHIFT) & ALS_IT_MASK) );
  // Update register cache variable
  registerVEML7700[COMMAND_ALS_IT] = reg;
  // Update register with new value 
  return i2cdriv.I2C_Write_16bitReg(fd, COMMAND_ALS_IT, reg);
}

/**
* Get current gain from register cache 
*
* @param integrationTime Address of integration time variable to update
* 
* @return Zero on success else negative errno
*/
uint8_t VEML7700::Get_Integration_Time(ALS_INTEGRTATION_TIME_T& integrationTime) {
  // Update the valuee for th
  integrationTime = ALS_INTEGRTATION_TIME_T( (registerVEML7700[COMMAND_ALS_IT] & ALS_IT_MASK) >> ALS_IT_SHIFT );
  return STATUS_OK;
}

