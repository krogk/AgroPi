/**
* @file
* @author Kamil Rog
* @version 0.1
*
*
* @section DESCRIPTION
* 
* This file contains the functions for the Relay Board class.
*
*/

#include "RelayBoard.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/**
* Initialize GPIO Pins for using Relay Board.
*
* 
* @return Zero on success
*/
int RelayBoard::Initialize()
{
    return 0; 
}
