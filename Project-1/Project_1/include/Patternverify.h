#ifndef __Patternverify_h__
#define __Patternverify_h__

#include "Main.h"

extern float random_number, seed;
extern uint32_t max, range, random_value, *pattern_original;
extern uint8_t verification_flag, verification_counter;

void gen_verify(void);
void patternverify(void);

#endif
