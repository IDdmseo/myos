#include "stdint.h"
#include "stdbool.h"
#include "haltimer.h"

void delay(uint32_t ms)
{
    uint32_t goal = hal_timer_get_1ms_counter() + ms;

    while(goal != hal_timer_get_1ms_counter());
}
