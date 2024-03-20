struct
{
    union
    {
        struct
        {
            uint8_t rom[0x4000]; // starts at 0x0000
            uint8_t video[0x400]; // starts at 0x4000
            uint8_t colour[0x400]; // starts at 0x4400
            uint8_t ram[0x7f0];  // starts at 0x4800
            uint8_t sprites[0x10];  // starts at 0x4ff0
        } block;
        uint8_t addr[0x5000];
    } mem;
    union
    {
        struct
        {
            uint8_t in0; // 0x5000-0x503f
            uint8_t in1; // 0x5040-0x507f
            uint8_t dipSwitches; // 0x5080-0x50bf
        } read;
        struct
        {
            uint8_t intEnable;  // 0x5000
            uint8_t soundEnable; // 0x5001
            uint8_t auxEnable; // 0x5002
            uint8_t flipScreen; // 0x5003
            uint8_t player1Start; // 0x5004
            uint8_t player2Start; // 0x5005
            uint8_t coinLockout; // 0x5006
            uint8_t coinCounter; // 0x5007
            uint8_t soundRegs[0x40]; // 0x5040
            uint8_t spriteCoords[0x10]; // 0x5060
            uint8_t watchdog; // 0x50c0-0x50ff
        } write;
    } regs;
}
memmap;

#define MEM memmap.mem.addr
#define RAM memory.mem.block.ram
#define VIDEO memory.mem.block.video
#define COLOUR memory.mem.block.colour
#define SOUND memory.regs.write.soundRegs
#define INTENABLE (memory.regs.write.intEnable)
#define REGSWRITE (memory.regs.write)
