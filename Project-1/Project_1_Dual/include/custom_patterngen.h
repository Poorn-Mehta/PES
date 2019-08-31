/*
 * custom_patterngen.h
 *
 *  Created on: Oct 31, 2018
 *      Author: poorn
 */

#ifndef CUSTOM_PATTERNGEN_H_
#define CUSTOM_PATTERNGEN_H_

#include "custom_main.h"

extern float random_number, seed;
extern uint32_t max, range, random_value;
extern ptr_type *pattern_original;

void generator(void);
void patterngen(void);

#endif /* CUSTOM_PATTERNGEN_H_ */
