/**
* @file
* @author Kamil Rog
* @version 0.1
*
*
* @section DESCRIPTION
* 
* This file contains the class for the VEML7700 A light sensor
*
*/
#ifndef VEML7700_H
#define VEML7700_H

#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include "I2CDriver.h"

/**
* @brief VEML7700 class
* @author Kamil Rog
*
* This is class is responsilbe for the VEML7700 light sensor.
* 
* @section PROTOCOL
* 
* I2C
*
* @section Registers
*
* CONFIGURATION REGISTER #0
*
*   BIT	  	|				REGISTER NAME				|				DESCRIPTION
* 15 : 13		|		      Reserved					|				  Set 000b 
* 12 : 11		|					ALS_GAIN			  	|         See Enums for options
*   10	  	|					Reserved					| 				Set 0b             
*  9 : 6  	|				   ALS_IT						|					See Enums for options
*  3 : 2		|					Reserved					|				  Set 00b           
*    1	  	|				 ALS_INT_EN					| 			  See Enums for options
*    0	  	|					 ALS_SD	  				| 				See Enums for options
*
*
* COMMAND REGISTER 
*/
class VEML7700 {
	
public:
	VEML7700(void) {
		
	}

  /**
   * Gain Setting Enumeration
   */
	enum ALS_GAIN_T {
		ALS_GAIN_x1 = 0x0,  /// x 1
		ALS_GAIN_x2 = 0x1,  /// x 2
		ALS_GAIN_d8 = 0x2,  /// x 1/8
		ALS_GAIN_d4 = 0x3   /// x 1/4
	};
		
  /**
   * Integration time Enumeration
   */
  enum ALS_INTEGRTATION_TIME_T {
		ALS_INTEGRATION_25ms = 0xc,   /// 25 mS
		ALS_INTEGRATION_50ms = 0x8,   /// 50 mS
		ALS_INTEGRATION_100ms = 0x0,  /// 100 mS
		ALS_INTEGRATION_200ms = 0x1,  /// 200 mS
		ALS_INTEGRATION_400ms = 0x2,  /// 400 mS
		ALS_INTEGRATION_800ms = 0x3   /// 800 mS
  };
	
	/**
	* Integration time Enumeration
	*/	
	enum ALS_PERSISTENCE_T {
		ALS_PERSISTENCE_1 = 0x0,  ///
		ALS_PERSISTENCE_2 = 0x1,  ///
		ALS_PERSISTENCE_4 = 0x2,  ///
		ALS_PERSISTENCE_8 = 0x3   ///
	};

	/**
	* Power Enumeration
	*/		
	enum ALS_POWERMODE_T { 
		ALS_POWER_MODE_1 = 0x0,  /// 
		ALS_POWER_MODE_2 = 0x1,  ///
		ALS_POWER_MODE_3 = 0x2,  ///
		ALS_POWER_MODE_4 = 0x3   ///
	};

	/**
	* Status Enumeration
	*/		
	enum {
		STATUS_OK = 0, 
		STATUS_ERROR = -1
	};	

	/**
	* Initialize VEML7700 with basic settings.
	*
	*/	
	void Initialize();

	// High Level Commands

	/**
	* Read Current Lux without chaning any VEML7700 settings.
	*
  * @param lux Address of the variable to update with current measurement of light intenstity in lux.
  * 
	* @return  
	*/
	uint8_t Get_ALS_Lux(float& lux);
	uint8_t Get_White_Lux(float& white);


private:

	// Device commands

	uint8_t Get_ALS(uint16_t& als);
  uint8_t Get_White(uint16_t& white); 
	
	// Address
	enum { I2C_ADDRESS = 0x10 };
	// Command Enumerations
	// Gain selection 
	enum { COMMAND_ALS_SM = 0x00, ALS_SM_MASK = 0x1800, ALS_SM_SHIFT = 11 };
	// Integration time 
	enum { COMMAND_ALS_IT = 0x00, ALS_IT_MASK = 0x03c0, ALS_IT_SHIFT = 6 };
	// ALS persistence protect number setting 
	enum { COMMAND_ALS_PERS = 0x00, ALS_PERS_MASK = 0x0030, ALS_PERS_SHIFT = 4 };
	// ALS interrupt enable setting
	enum { COMMAND_ALS_INT_EN = 0x00, ALS_INT_EN_MASK = 0x0002, ALS_INT_EN_SHIFT = 1 };
	// ALS shut down setting
	enum { COMMAND_ALS_SD = 0x00,  ALS_SD_MASK = 0x0001, ALS_SD_SHIFT = 0 };
	// ALS high threshold window setting
	enum { COMMAND_ALS_WH = 0x01 };
	// ALS low threshold window setting (MSB)
	enum { COMMAND_ALS_WL = 0x02 };
	// Power saving mode setting
	enum { COMMAND_PSM = 0x03, PSM_MASK = 0x0006, PSM_SHIFT = 1 };
	// Power saving mode enable setting
	enum { COMMAND_PSM_EN = 0x03, PSM_EN_MASK = 0x0001, PSM_EN_SHIFT = 0 };
	// Get Data - High precision ALS
	enum { COMMAND_ALS = 0x04 };
	// Get Data - White ALS command
	enum { COMMAND_WHITE = 0x05 };
  // Read Interrupt ALS INT trigger event
	enum { COMMAND_ALS_IF_L = 0x06, ALS_IF_L_MASK = 0x8000, ALS_IF_L_SHIFT = 15 };
	enum { COMMAND_ALS_IF_H = 0x06, ALS_IF_H_MASK = 0x4000, ALS_IF_H_SHIFT = 14 };

  // Config Regsiter
  uint16_t registerVEML7700[4];

  // Gain Set & Get commands
  uint8_t Set_Gain(ALS_GAIN_T gain);
  uint8_t Get_Gain(ALS_GAIN_T &gain);
   
  // Integration Time Set & Get commands
  uint8_t Set_Integration_Time(ALS_INTEGRTATION_TIME_T integrationTime);
  uint8_t Get_Integration_Time(ALS_INTEGRTATION_TIME_T& integrationTime);

  // Integration Time Set & Get commands
  void Compute_Lux(uint16_t raw_counts, float& lux);

  // I2C Object instance class
  I2CDriver i2cdriv;
  int fd;


};


#endif
