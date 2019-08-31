/*
 * custom_memwrite.h
 *
 *  Created on: Oct 30, 2018
 *      Author: poorn
 */

#ifndef CUSTOM_MEMWRITE_H_
#define CUSTOM_MEMWRITE_H_

#include "custom_main.h"
#ifdef	FRDM
#include "custom_flash_program.h"
#endif

void memwrite(void);

#endif /* CUSTOM_MEMWRITE_H_ */
