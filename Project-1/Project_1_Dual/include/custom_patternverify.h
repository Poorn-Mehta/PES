/*
 * custom_patternverify.h
 *
 *  Created on: Oct 31, 2018
 *      Author: poorn
 */

#ifndef CUSTOM_PATTERNVERIFY_H_
#define CUSTOM_PATTERNVERIFY_H_

#include "custom_main.h"

extern float random_number, seed;
extern uint32_t max, range, random_value;
extern ptr_type *pattern_original;
extern uint8_t verification_flag, verification_counter;

void gen_verify(void);
void patternverify(void);

#endif /* CUSTOM_PATTERNVERIFY_H_ */
