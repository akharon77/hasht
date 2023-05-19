#ifndef CONFIG_LAB_H
#define CONFIG_LAB_H

const uint32_t LAB_SIZE = 330;
const uint32_t LAB_CNT  = 1000000;
const uint32_t LAB_SEED = 13;
#ifdef _MEASURE
const uint32_t LAB_AVG  = 300;
#else
const uint32_t LAB_AVG  = 1;
#endif  // _MEASURE

#endif  // CONFIG_LAB_H
