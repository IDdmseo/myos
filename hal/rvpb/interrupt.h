#ifndef HAL_RVPB_INTERRUPT_H_
#define HAL_RVPB_INTERRUPT_H_

typedef union cpucontrol_t
{
    uint32_t all;
    struct {
        uint32_t enable:1;          // 0
        uint32_t reserved:31;
    } bits;
} cpucontrol_t;

typedef union prioritymask_t
{
    uint32_t all;
    struct {
        uint32_t reserved0:4;        // 3:0
        uint32_t prioritymask:4;    // 7:4
        uint32_t reserved1:24;
    } bits;
} prioritymask_t;

typedef union binaryPoint_t
{
    uint32_t all;
    struct {
        uint32_t binarypoint:3;     // 2:0
        uint32_t reserved:29;
    } bits;
} binarypoint_t;

typedef union interruptAck_t
{
    uint32_t all;
    struct {
        uint32_t interruptid:10;    // 9:0
        uint32_t cpusourceid:3;     // 12:10
        uint32_t reserved:19;
    } bits;
} interruptack_t;

typedef union endofinterrupt_t
{
    uint32_t all;
    struct {
        uint32_t interruptid:10;    // 9:0
        uint32_t cpusourceid:3;     // 12:10
        uint32_t reserved:19;
    } bits;
} endofinterrupt_t;

typedef union runninginterrupt_t
{
    uint32_t all;
    struct {
        uint32_t reserved0:4;        // 3:0
        uint32_t priority:4;        // 7:4
        uint32_t reserved1:24;
    } bits;
} runninginterrupt_t;

typedef union highestpendinter_t
{
    uint32_t all;
    struct {
        uint32_t interruptid:10;    // 9:0
        uint32_t cpusourceid:3;     // 12:10
        uint32_t reserved:19;
    } bits;
} highestpendinter_t;

typedef union distributorctrl_t
{
    uint32_t all;
    struct {
        uint32_t enable:1;          // 0
        uint32_t reserved:31;
    } bits;
} distributorctrl_t;

typedef union controllertype_t
{
    uint32_t all;
    struct {
        uint32_t idlinesnumber:5;   // 4:0
        uint32_t cpunumber:3;       // 7:5
        uint32_t reserved:24;
    } bits;
} controllertype_t;

typedef struct ciccput_t
{
    cpucontrol_t       cpucontrol;        //0x000
    prioritymask_t     prioritymask;      //0x004
    binarypoint_t      binarypoint;       //0x008
    interruptack_t     interruptack;      //0x00C
    endofinterrupt_t   endofinterrupt;    //0x010
    runninginterrupt_t runninginterrupt;  //0x014
    highestpendinter_t highestpendinter;  //0x018
} giccput_t;

typedef struct gicdist_t
{
    distributorctrl_t   distributorctrl;    //0x000
    controllertype_t    controllertype;     //0x004
    uint32_t            reserved0[62];      //0x008-0x0FC
    uint32_t            reserved1;          //0x100
    uint32_t            setenable1;         //0x104
    uint32_t            setenable2;         //0x108
    uint32_t            reserved2[29];      //0x10C-0x17C
    uint32_t            reserved3;          //0x180
    uint32_t            clearenable1;       //0x184
    uint32_t            clearenable2;       //0x188
} gicdist_t;

#define GIC_CPU_BASE  0x1E000000  //CPU interface
#define GIC_DIST_BASE 0x1E001000  //distributor

#define GIC_PRIORITY_MASK_NONE  0xF

#define GIC_IRQ_START           32
#define GIC_IRQ_END             95

#endif /* HAL_RVPB_INTERRUPT_H_ */
