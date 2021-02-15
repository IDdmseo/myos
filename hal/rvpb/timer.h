#ifndef HAL_RVPB_TIMER_H_
#define HAL_RVPB_TIMER_H_

typedef union timerxcontrol_t
{
    uint32_t all;
    struct {
        uint32_t oneshot:1;     //0
        uint32_t timersize:1;   //1
        uint32_t timerpre:2;    //3:2
        uint32_t reserved0:1;   //4
        uint32_t intenable:1;   //5
        uint32_t timermode:1;   //6
        uint32_t timeren:1;     //7
        uint32_t reserved1:24;  //31:8
    } bits;
} timerxcontrol_t;

typedef union timerxris_t
{
    uint32_t all;
    struct {
        uint32_t timerxris:1;   //0
        uint32_t reserved:31;   //31:1
    } bits;
} timerxris_t;

typedef union timerxmis_t
{
    uint32_t all;
    struct {
        uint32_t timerxmis:1;   //0
        uint32_t reserved:31;   //31:1
    } bits;
} timerxmis_t;

typedef struct timer_t
{
    uint32_t        timerxload;     // 0x00
    uint32_t        timerxvalue;    // 0x04
    timerxcontrol_t timerxcontrol;  // 0x08
    uint32_t        timerxintclr;   // 0x0C
    timerxris_t     timerxris;      // 0x10
    timerxmis_t     timerxmis;      // 0x14
    uint32_t        timerxbgload;   // 0x18
} timer_t;

#define TIMER_CPU_BASE  0x10011000
#define TIMER_INTERRUPT 36

#define TIMER_FREERUNNING   0
#define TIMER_PERIODIC		1

#define TIMER_16BIT_COUNTER 0
#define TIMER_32BIT_COUNTER 1

#define TIMER_10HZ_INTERVAL       (32768 * 4)

#endif /* HAL_RVPB_TIMER_H_ */
