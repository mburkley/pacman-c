/* Memory map table.  Starts at flat map but replace with specific locations as
 * they are discovered */

// Video : https://www.walkofmind.com/programming/pie/video_memory.htm

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
#define SPRITES memory.mem.block.sprites
#define INTENABLE memory.regs.write.intEnable
#define COINCOUNTER memory.regs.write.coinCounter
#define COINLOCKOUT memory.regs.write.coinLockout
#define REGSWRITE memory.regs.write
#define SOUNDENABLE memory.regs.write.soundEnable

#define IN0_UP          (memory.regs.read.in0 & 0x01)
#define IN0_LEFT        (memory.regs.read.in0 & 0x02)
#define IN0_RIGHT       (memory.regs.read.in0 & 0x04)
#define IN0_DOWN        (memory.regs.read.in0 & 0x08)
#define IN0_TEST        (memory.regs.read.in0 & 0x10)
#define IN0_COIN1       (memory.regs.read.in0 & 0x20)
#define IN0_COIN2       (memory.regs.read.in0 & 0x40)
#define IN0_COIN3       (memory.regs.read.in0 & 0x80)

#define IN1_UP          (memory.regs.read.in0 & 0x01)
#define IN1_LEFT        (memory.regs.read.in0 & 0x02)
#define IN1_RIGHT       (memory.regs.read.in0 & 0x04)
#define IN1_DOWN        (memory.regs.read.in0 & 0x08)
#define IN1_SERVICE     (memory.regs.read.in0 & 0x10)
#define IN1_START1      (memory.regs.read.in0 & 0x20)
#define IN1_START2      (memory.regs.read.in0 & 0x40)
#define IN1_CABINET     (memory.regs.read.in0 & 0x80)

#define SWAP16(int addr1, int addr2)\
{ \
    uint8_t tmp1, tmp2; \
    tmp1 = MEM(addr1); tmp2 = MEM(addr1+1); \
    MEM(addr1) = MEM(addr2); MEM(addr1+1) = MEM(addr2+1); \
    MEM(addr2) = tmp1; MEM(addr2+1) = tmp2; \
}

