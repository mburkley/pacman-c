// 	;; 4e66 last state coin inputs shifted left by 1
// 	;; COINS_PER_CREDIT #coins per #credits
// 	;; partialCredit #left over coins (partial credits)
// 	;; CREDITS_PER_COIN	#credits per #coins
// 	;; coinCredits #credits
// 	;; LIVES_PER_GAME #lives per game
// 
// 	;; 4e80-4e83 P1 score
uint32_t p1Score;
// 	;; 4e84-4e87 P2 score
uint32_t p2Score;
// 	;; 4e88-4e8b High score
uint32_t highScore;
// 	
// 	;; 4370 #players (0=1, 1=2)
// 	
// 	Starting address: 0
//   Ending address: 16383
//      Output file: (none)
// Pass 1 of 1
// 0000  f3        di			; Disable interrupts
// 0001  3e3f      ld      a,#3f
// 0003  ed47      ld      i,a		; Interrupt page = 0x3f
// 0005  c30b23    jp      #230b		; Run startup tests
// 
// 	;; Fill "hl" to "hl+b" with "a"
// 0008  77        ld      (hl),a
// 0009  23        inc     hl
// 000a  10fc      djnz    #0008           ; (-4)
// 000c  c9        ret     
// 000d  c30e07    jp      #070e

// 	;; hl = hl + a, (hl) -> a
// 0010  85        add     a,l		
// 0011  6f        ld      l,a		
// 0012  3e00      ld      a,#00
// 0014  8c        adc     a,h		
// 0015  67        ld      h,a
// 0016  7e        ld      a,(hl)
// 0017  c9        ret     
// 
// 	;; Some sort of table lookup
// 	;; hl = hl + 2*b,  (hl) -> e, (++hl) -> d, de -> hl
// 	;; (Used to add up scores!)
// 0018  78        ld      a,b		; b -> a 
// 0019  87        add     a,a		; 2*a -> a 
// 001a  d7        rst     #10
// 001b  5f        ld      e,a
// 001c  23        inc     hl
// 001d  56        ld      d,(hl)
// 001e  eb        ex      de,hl
// 001f  c9        ret     
// 
// 0020  e1        pop     hl
// 0021  87        add     a,a
// 0022  d7        rst     #10
// 0023  5f        ld      e,a
// 0024  23        inc     hl
// 0025  56        ld      d,(hl)
// 0026  eb        ex      de,hl
// 0027  e9        jp      (hl)
// 
// 0028  e1        pop     hl
// 0029  46        ld      b,(hl)
// 002a  23        inc     hl
// 002b  4e        ld      c,(hl)
// 002c  23        inc     hl
// 002d  e5        push    hl
// 002e  1812      jr      #0042           ; (18)
// 
// 0030  11904c    ld      de,#4c90
// 0033  0610      ld      b,#10
// 0035  c35100    jp      #0051
// 
// 	;; Loop waiting for interrupt?
// 0038  af        xor     a
// 0039  320050    ld      (#5000),a
// 003c  320750    ld      (#5007),a
// 003f  c33800    jp      #0038
// 
// 	;; Weird routine
// 	;; (#4c80) spins through 4cc0 to 4cff
// 	;; bc -> ((#4c80)),  (#4c80++)
// 0042  2a804c    ld      hl,(#4c80)
// 0045  70        ld      (hl),b
// 0046  2c        inc     l
// 0047  71        ld      (hl),c
// 0048  2c        inc     l
// 0049  2002      jr      nz,#004d        ; (2)
// 004b  2ec0      ld      l,#c0
// 004d  22804c    ld      (#4c80),hl
// 0050  c9        ret     
// 
// 	;; Jump from rst 0x30
// 0051  1a        ld      a,(de)
// 0052  a7        and     a
// 0053  2806      jr      z,#005b         ; (6)
// 0055  1c        inc     e
// 0056  1c        inc     e
// 0057  1c        inc     e
// 0058  10f7      djnz    #0051           ; (-9)
// 005a  c9        ret     
// 
// 005b  e1        pop     hl
// 005c  0603      ld      b,#03
// 005e  7e        ld      a,(hl)
// 005f  12        ld      (de),a
// 0060  23        inc     hl
// 0061  1c        inc     e
// 0062  10fa      djnz    #005e           ; (-6)
// 0064  e9        jp      (hl)
// 0065  c32d20    jp      #202d
// 0068  00        nop     
// 0069  010203    ld      bc,#0302
// 006c  04        inc     b
// 006d  05        dec     b
// 006e  0607      ld      b,#07
// 0070  08        ex      af,af'
// 0071  09        add     hl,bc
// 0072  0a        ld      a,(bc)
// 0073  0b        dec     bc
// 0074  0c        inc     c
// 0075  0d        dec     c
// 0076  0e0f      ld      c,#0f
// 0078  1011      djnz    #008b           ; (17)
// 007a  12        ld      (de),a
// 007b  13        inc     de
// 007c  14        inc     d
// 007d  010304    ld      bc,#0403
// 0080  0607      ld      b,#07
// 0082  08        ex      af,af'
// 0083  09        add     hl,bc
// 0084  0a        ld      a,(bc)
// 0085  0b        dec     bc
// 0086  0c        inc     c
// 0087  0d        dec     c
// 0088  0e0f      ld      c,#0f
// 008a  1011      djnz    #009d           ; (17)
// 008c  14        inc     d
// 
// 	;; Non-test mode interrupt routine
// 008d  f5        push    af
kickWatchdog();
// 0091  af        xor     a
// 0092  320050    ld      (#5000),a	; Disable interrupts (hardware) 
// 0095  f3        di			; Disable interrupts (CPU) 
// 0096  c5        push    bc
// 0097  d5        push    de
// 0098  e5        push    hl
// 0099  dde5      push    ix
// 009b  fde5      push    iy
// 	
// 009d  218c4e    ld      hl,#4e8c	; Write freq/volume for sound regs 
// 00a0  115050    ld      de,#5050
// 00a3  011000    ld      bc,#0010
// 00a6  edb0      ldir
// 	
// 00a8  3acc4e    ld      a,(#4ecc)	; Useless read 
// 00ab  a7        and     a
// 
// 	;; Write sound waveforms
// 00ac  3acf4e    ld      a,(#4ecf)
// 00af  2003      jr      nz,#00b4        ; (3)
// 00b1  3a9f4e    ld      a,(#4e9f)
// 00b4  324550    ld      (#5045),a
// 00b7  3adc4e    ld      a,(#4edc)
// 00ba  a7        and     a
// 00bb  3adf4e    ld      a,(#4edf)
// 00be  2003      jr      nz,#00c3        ; (3)
// 00c0  3aaf4e    ld      a,(#4eaf)
// 00c3  324a50    ld      (#504a),a
// 00c6  3aec4e    ld      a,(#4eec)
// 00c9  a7        and     a
// 00ca  3aef4e    ld      a,(#4eef)
// 00cd  2003      jr      nz,#00d2        ; (3)
// 00cf  3abf4e    ld      a,(#4ebf)
// 00d2  324f50    ld      (#504f),a
// 	
// 00d5  21024c    ld      hl,#4c02
// 00d8  11224c    ld      de,#4c22
// 00db  011c00    ld      bc,#001c
// 00de  edb0      ldir
// 
// 00e0  dd21204c  ld      ix,#4c20
// 00e4  dd7e02    ld      a,(ix+#02)
// 00e7  07        rlca    
// 00e8  07        rlca    
// 00e9  dd7702    ld      (ix+#02),a
// 00ec  dd7e04    ld      a,(ix+#04)
// 00ef  07        rlca    
// 00f0  07        rlca    
// 00f1  dd7704    ld      (ix+#04),a
// 00f4  dd7e06    ld      a,(ix+#06)
// 00f7  07        rlca    
// 00f8  07        rlca    
// 00f9  dd7706    ld      (ix+#06),a
// 00fc  dd7e08    ld      a,(ix+#08)
// 00ff  07        rlca    
// 0100  07        rlca    
// 0101  dd7708    ld      (ix+#08),a
// 0104  dd7e0a    ld      a,(ix+#0a)
// 0107  07        rlca    
// 0108  07        rlca    
// 0109  dd770a    ld      (ix+#0a),a
// 010c  dd7e0c    ld      a,(ix+#0c)
// 010f  07        rlca    
// 0110  07        rlca    
// 0111  dd770c    ld      (ix+#0c),a
// 0114  3ad14d    ld      a,(#4dd1)
// 0117  fe01      cp      #01
// 0119  2038      jr      nz,#0153        ; (56)
// 011b  dd21204c  ld      ix,#4c20
// 011f  3aa44d    ld      a,(#4da4)
// 0122  87        add     a,a
// 0123  5f        ld      e,a
// 0124  1600      ld      d,#00
// 0126  dd19      add     ix,de
// 0128  2a244c    ld      hl,(#4c24)
// 012b  ed5b344c  ld      de,(#4c34)
// 012f  dd7e00    ld      a,(ix+#00)
// 0131  32244c    ld      (#4c24),a
// 0135  dd7e01    ld      a,(ix+#01)
// 0138  32254c    ld      (#4c25),a
// 013b  dd7e10    ld      a,(ix+#10)
// 013e  32344c    ld      (#4c34),a
// 0141  dd7e11    ld      a,(ix+#11)
// 0144  32354c    ld      (#4c35),a
// 0147  dd7500    ld      (ix+#00),l
// 014a  dd7401    ld      (ix+#01),h
// 014d  dd7310    ld      (ix+#10),e
// 0150  dd7211    ld      (ix+#11),d
// 0153  3aa64d    ld      a,(#4da6)
// 0156  a7        and     a
// 0157  ca7601    jp      z,#0176
// 015a  ed4b224c  ld      bc,(#4c22)
// 015e  ed5b324c  ld      de,(#4c32)
// 0162  2a2a4c    ld      hl,(#4c2a)
// 0165  22224c    ld      (#4c22),hl
// 0168  2a3a4c    ld      hl,(#4c3a)
// 016b  22324c    ld      (#4c32),hl
// 016e  ed432a4c  ld      (#4c2a),bc
// 0172  ed533a4c  ld      (#4c3a),de
// 0176  21224c    ld      hl,#4c22
// 0179  11f24f    ld      de,#4ff2
// 017c  010c00    ld      bc,#000c
// 017f  edb0      ldir    
// 0181  21324c    ld      hl,#4c32
// 0184  116250    ld      de,#5062
// 0187  010c00    ld      bc,#000c
// 018a  edb0      ldir    
// 018c  cddc01    call    #01dc
// 018f  cd2102    call    #0221
// 0192  cdc803    call    #03c8
// 0195  3a004e    ld      a,(#4e00)
// 0198  a7        and     a
// 0199  2812      jr      z,#01ad         ; (18)
// 019b  cd9d03    call    #039d
// 019e  cd9014    call    #1490
// 01a1  cd1f14    call    #141f
// 01a4  cd6702    call    #0267
// 01a7  cdad02    call    #02ad
// 01aa  cdfd02    call    #02fd
// 01ad  3a004e    ld      a,(#4e00)
// 01b0  3d        dec     a
// 01b1  2006      jr      nz,#01b9        ; (6)
// 01b3  32ac4e    ld      (#4eac),a
// 01b6  32bc4e    ld      (#4ebc),a
// 01b9  cd0c2d    call    #2d0c
// 01bc  cdc12c    call    #2cc1
// 01bf  fde1      pop     iy
// 01c1  dde1      pop     ix
// 01c3  e1        pop     hl
// 01c4  d1        pop     de
// 01c5  c1        pop     bc
// 01c6  3a004e    ld      a,(#4e00)
// 01c9  a7        and     a
// 01ca  2808      jr      z,#01d4         ; (8)
// 
// 01cc  3a4050    ld      a,(#5040)	; Check test switch 
// 01cf  e610      and     #10
// 01d1  ca0000    jp      z,#0000		; Reset if test
// 	 
// 01d4  3e01      ld      a,#01		; Enable interrupts (hardware) 
// 01d6  320050    ld      (#5000),a
// 01d9  fb        ei			; Enable interrupts (CPU) 
// 01da  f1        pop     af
// 01db  c9        ret     
// 
// 	
// 01dc  21844c    ld      hl,#4c84
// 01df  34        inc     (hl)
// 01e0  23        inc     hl
// 01e1  35        dec     (hl)
// 01e2  23        inc     hl
// 01e3  111902    ld      de,#0219
// 01e6  010104    ld      bc,#0401
// 01e9  34        inc     (hl)
// 01ea  7e        ld      a,(hl)
// 01eb  e60f      and     #0f
// 01ed  eb        ex      de,hl
// 01ee  be        cp      (hl)
// 01ef  2013      jr      nz,#0204        ; (19)
// 01f1  0c        inc     c
// 01f2  1a        ld      a,(de)
// 01f3  c610      add     a,#10
// 01f5  e6f0      and     #f0
// 01f7  12        ld      (de),a
// 01f8  23        inc     hl
// 01f9  be        cp      (hl)
// 01fa  2008      jr      nz,#0204        ; (8)
// 01fc  0c        inc     c
// 01fd  eb        ex      de,hl
// 01fe  3600      ld      (hl),#00
// 0200  23        inc     hl
// 0201  13        inc     de
// 0202  10e5      djnz    #01e9           ; (-27)
// 0204  218a4c    ld      hl,#4c8a
// 0207  71        ld      (hl),c
// 0208  2c        inc     l
// 0209  7e        ld      a,(hl)
// 020a  87        add     a,a
// 020b  87        add     a,a
// 020c  86        add     a,(hl)
// 020d  3c        inc     a
// 020e  77        ld      (hl),a
// 020f  2c        inc     l
// 0210  7e        ld      a,(hl)
// 0211  87        add     a,a
// 0212  86        add     a,(hl)
// 0213  87        add     a,a
// 0214  87        add     a,a
// 0215  86        add     a,(hl)
// 0216  3c        inc     a
// 0217  77        ld      (hl),a
// 0218  c9        ret     
// 
// 0219  06a0      ld      b,#a0
// 021b  0a        ld      a,(bc)
// 021c  60        ld      h,b
// 021d  0a        ld      a,(bc)
// 021e  60        ld      h,b
// 021f  0a        ld      a,(bc)
// 0220  a0        and     b
// 0221  21904c    ld      hl,#4c90
// 0224  3a8a4c    ld      a,(#4c8a)
// 0227  4f        ld      c,a
// 0228  0610      ld      b,#10
// 022a  7e        ld      a,(hl)
// 022b  a7        and     a
// 022c  282f      jr      z,#025d         ; (47)
// 022e  e6c0      and     #c0
// 0230  07        rlca    
// 0231  07        rlca    
// 0232  b9        cp      c
// 0233  3028      jr      nc,#025d        ; (40)
// 0235  35        dec     (hl)
// 0236  7e        ld      a,(hl)
// 0237  e63f      and     #3f
// 0239  2022      jr      nz,#025d        ; (34)
// 023b  77        ld      (hl),a
// 023c  c5        push    bc
// 023d  e5        push    hl
// 023e  2c        inc     l
// 023f  7e        ld      a,(hl)
// 0240  2c        inc     l
// 0241  46        ld      b,(hl)
// 0242  215b02    ld      hl,#025b
// 0245  e5        push    hl
// 0246  e7        rst     #20
// 0247  94        sub     h
// 0248  08        ex      af,af'
// 0249  a3        and     e
// 024a  068e      ld      b,#8e
// 024c  05        dec     b
// 024d  72        ld      (hl),d
// 024e  12        ld      (de),a
// 024f  00        nop     
// 0250  100b      djnz    #025d           ; (11)
// 0252  1063      djnz    #02b7           ; (99)
// 0254  02        ld      (bc),a
// 0255  2b        dec     hl
// 0256  21f021    ld      hl,#21f0
// 0259  b9        cp      c
// 025a  22e1c1    ld      (#c1e1),hl
// 025d  2c        inc     l
// 025e  2c        inc     l
// 025f  2c        inc     l
// 0260  10c8      djnz    #022a           ; (-56)
// 0262  c9        ret     
// 
// 0263  ef        rst     #28
// 0264  1c        inc     e
// 0265  86        add     a,(hl)
// 0266  c9        ret     
// 
// 0267  3a6e4e    ld      a,(#coinCredits)
// 026a  fe99      cp      #99
// 026c  17        rla     
// 026d  320650    ld      (#5006),a
// 0270  1f        rra     
// 0271  d0        ret     nc
// 
// 	;; Check/debounce coin inputs
// 0272  3a0050    ld      a,(#5000)
// 0275  47        ld      b,a
// 0276  cb00      rlc     b
// 0278  3a664e    ld      a,(#4e66)
// 027b  17        rla     
// 027c  e60f      and     #0f
// 027e  32664e    ld      (#4e66),a
// 0281  d60c      sub     #0c
// 0283  ccdf02    call    z,#02df			; Add Coin
// 0286  cb00      rlc     b
// 0288  3a674e    ld      a,(#4e67)
// 028b  17        rla     
// 028c  e60f      and     #0f
// 028e  32674e    ld      (#4e67),a
// 0291  d60c      sub     #0c
// 0293  c29a02    jp      nz,#029a
// 0296  21694e    ld      hl,#4e69
// 0299  34        inc     (hl)
// 029a  cb00      rlc     b
// 029c  3a684e    ld      a,(#4e68)
// 029f  17        rla     
// 02a0  e60f      and     #0f
// 02a2  32684e    ld      (#4e68),a
// 02a5  d60c      sub     #0c
// 02a7  c0        ret     nz
// 
// 02a8  21694e    ld      hl,#4e69
// 02ab  34        inc     (hl)
// 02ac  c9        ret     
// 
// 02ad  3a694e    ld      a,(#4e69)
// 02b0  a7        and     a
// 02b1  c8        ret     z
// 
// 02b2  47        ld      b,a
// 02b3  3a6a4e    ld      a,(#4e6a)
// 02b6  5f        ld      e,a
// 02b7  fe00      cp      #00
// 02b9  c2c402    jp      nz,#02c4
// 02bc  3e01      ld      a,#01
// 02be  320750    ld      (#5007),a
// 02c1  cddf02    call    #02df
// 02c4  7b        ld      a,e
// 02c5  fe08      cp      #08
// 02c7  c2ce02    jp      nz,#02ce
// 02ca  af        xor     a
// 02cb  320750    ld      (#5007),a
// 02ce  1c        inc     e
// 02cf  7b        ld      a,e
// 02d0  326a4e    ld      (#4e6a),a
// 02d3  d610      sub     #10
// 02d5  c0        ret     nz
// 
// 02d6  326a4e    ld      (#4e6a),a
// 02d9  05        dec     b
// 02da  78        ld      a,b
// 02db  32694e    ld      (#4e69),a
// 02de  c9        ret     
// 
// 	;; Coins -> credits routine
// 02df  3a6b4e    ld      a,(#COINS_PER_CREDIT)		; #coins per #credits 
// 02e2  216c4e    ld      hl,#partialCredit		; #leftover coins 
// 02e5  34        inc     (hl)			; add 1 
// 02e6  96        sub     (hl)
// 02e7  c0        ret     nz			; not enough coins for credit 
// 
// 02e8  77        ld      (hl),a			; store leftover coins 
// 02e9  3a6d4e    ld      a,(#CREDITS_PER_COIN)		; #credits per #coins 
// 02ec  216e4e    ld      hl,#coinCredits		; #credits 
// 02ef  86        add     a,(hl)			; add # credits 
// 02f0  27        daa     
// 02f1  d2f602    jp      nc,#02f6
// 02f4  3e99      ld      a,#99
// 02f6  77        ld      (hl),a			; store #credits, max 99 
// 02f7  219c4e    ld      hl,#4e9c
// 02fa  cbce      set     1,(hl)			; set bit 1 of 4e9c 
// 02fc  c9        ret     
// 
// 02fd  21ce4d    ld      hl,#4dce
// 0300  34        inc     (hl)
// 0301  7e        ld      a,(hl)
// 0302  e60f      and     #0f
// 0304  201f      jr      nz,#0325        ; (31)
// 0306  7e        ld      a,(hl)
// 0307  0f        rrca    
// 0308  0f        rrca    
// 0309  0f        rrca    
// 030a  0f        rrca    
// 030b  47        ld      b,a
// 030c  3ad64d    ld      a,(#4dd6)
// 030f  2f        cpl     
// 0310  b0        or      b
// 0311  4f        ld      c,a
// 0312  3a6e4e    ld      a,(#coinCredits)
// 0315  d601      sub     #01
// 0317  3002      jr      nc,#031b        ; (2)
// 0319  af        xor     a
// 031a  4f        ld      c,a
// 031b  2801      jr      z,#031e         ; (1)
// 031d  79        ld      a,c
// 031e  320550    ld      (#5005),a
// 0321  79        ld      a,c
// 0322  320450    ld      (#5004),a
// 0325  dd21d843  ld      ix,#43d8
// 0329  fd21c543  ld      iy,#43c5
// 032d  3a004e    ld      a,(#4e00)
// 0330  fe03      cp      #03
// 0332  ca4403    jp      z,#0344
// 0335  3a034e    ld      a,(#4e03)
// 0338  fe02      cp      #02
// 033a  d24403    jp      nc,#0344
// 033d  cd6903    call    #0369
// 0340  cd7603    call    #0376
// 0343  c9        ret     
// 
// 0344  3a094e    ld      a,(#4e09)
// 0347  a7        and     a
// 0348  3ace4d    ld      a,(#4dce)
// 034b  c25903    jp      nz,#0359
// 034e  cb67      bit     4,a
// 0350  cc6903    call    z,#0369
// 0353  c48303    call    nz,#0383
// 0356  c36103    jp      #0361
// 0359  cb67      bit     4,a
// 035b  cc7603    call    z,#0376
// 035e  c49003    call    nz,#0390
// 0361  3a704e    ld      a,(#4e70)
// 0364  a7        and     a
// 0365  cc9003    call    z,#0390
// 0368  c9        ret     
// 
// 0369  dd360050  ld      (ix+#00),#50
// 036d  dd360155  ld      (ix+#01),#55
// 0371  dd360231  ld      (ix+#02),#31
// 0375  c9        ret     
// 
// 0376  fd360050  ld      (iy+#00),#50
// 037a  fd360155  ld      (iy+#01),#55
// 037e  fd360232  ld      (iy+#02),#32
// 0382  c9        ret     
// 
// 0383  dd360040  ld      (ix+#00),#40
// 0387  dd360140  ld      (ix+#01),#40
// 038b  dd360240  ld      (ix+#02),#40
// 038f  c9        ret     
// 
// 0390  fd360040  ld      (iy+#00),#40
// 0394  fd360140  ld      (iy+#01),#40
// 0398  fd360240  ld      (iy+#02),#40
// 039c  c9        ret     
// 
// 039d  3a064e    ld      a,(#4e06)
// 03a0  d605      sub     #05
// 03a2  d8        ret     c
// 
// 03a3  2a084d    ld      hl,(#4d08)
// 03a6  0608      ld      b,#08
// 03a8  0e10      ld      c,#10
// 03aa  7d        ld      a,l
// 03ab  32064d    ld      (#4d06),a
// 03ae  32d24d    ld      (#4dd2),a
// 03b1  91        sub     c
// 03b2  32024d    ld      (#4d02),a
// 03b5  32044d    ld      (#4d04),a
// 03b8  7c        ld      a,h
// 03b9  80        add     a,b
// 03ba  32034d    ld      (#4d03),a
// 03bd  32074d    ld      (#4d07),a
// 03c0  91        sub     c
// 03c1  32054d    ld      (#4d05),a
// 03c4  32d34d    ld      (#4dd3),a
// 03c7  c9        ret     
// 
// 03c8  3a004e    ld      a,(#4e00)
// 03cb  e7        rst     #20
// 03cc  d403fe    call    nc,#fe03
// 03cf  03        inc     bc
// 03d0  e5        push    hl
// 03d1  05        dec     b
// 03d2  be        cp      (hl)
// 03d3  063a      ld      b,#3a
// 03d5  014ee7    ld      bc,#e74e
// 03d8  dc030c    call    c,#0c03
// 03db  00        nop     
// 03dc  ef        rst     #28
// 03dd  00        nop     
// 03de  00        nop     
// 03df  ef        rst     #28
// 03e0  0600      ld      b,#00
// 03e2  ef        rst     #28
// 03e3  0100ef    ld      bc,#ef00
// 03e6  14        inc     d
// 03e7  00        nop     
// 03e8  ef        rst     #28
// 03e9  1800      jr      #03eb           ; (0)
// 03eb  ef        rst     #28
// 03ec  04        inc     b
// 03ed  00        nop     
// 03ee  ef        rst     #28
// 03ef  1e00      ld      e,#00
// 03f1  ef        rst     #28
// 03f2  07        rlca    
// 03f3  00        nop     
// 03f4  21014e    ld      hl,#4e01
// 03f7  34        inc     (hl)
// 03f8  210150    ld      hl,#5001
// 03fb  3601      ld      (hl),#01
// 03fd  c9        ret     
// 
// 	;; Can't find a jump to here?!
// 03fe  cda12b    call    #2ba1			; Write # credits on screen
// 0401  3a6e4e    ld      a,(#coinCredits)
// 0404  a7        and     a
// 0405  280c      jr      z,#0413			; No credits -> 0x13
// 0407  af        xor     a
// 0408  32044e    ld      (#4e04),a
// 040b  32024e    ld      (#4e02),a
// 040e  21004e    ld      hl,#4e00
// 0411  34        inc     (hl)
// 0412  c9        ret     
// 
// 0413  3a024e    ld      a,(#4e02)
// 0416  e7        rst     #20
// 0417  5f        ld      e,a
// 0418  04        inc     b
// 0419  0c        inc     c
// 041a  00        nop     
// 041b  71        ld      (hl),c
// 041c  04        inc     b
// 041d  0c        inc     c
// 041e  00        nop     
// 041f  7f        ld      a,a
// 0420  04        inc     b
// 0421  0c        inc     c
// 0422  00        nop     
// 0423  85        add     a,l
// 0424  04        inc     b
// 0425  0c        inc     c
// 0426  00        nop     
// 0427  8b        adc     a,e
// 0428  04        inc     b
// 0429  0c        inc     c
// 042a  00        nop     
// 042b  99        sbc     a,c
// 042c  04        inc     b
// 042d  0c        inc     c
// 042e  00        nop     
// 042f  9f        sbc     a,a
// 0430  04        inc     b
// 0431  0c        inc     c
// 0432  00        nop     
// 0433  a5        and     l
// 0434  04        inc     b
// 0435  0c        inc     c
// 0436  00        nop     
// 0437  b3        or      e
// 0438  04        inc     b
// 0439  0c        inc     c
// 043a  00        nop     
// 043b  b9        cp      c
// 043c  04        inc     b
// 043d  0c        inc     c
// 043e  00        nop     
// 043f  bf        cp      a
// 0440  04        inc     b
// 0441  0c        inc     c
// 0442  00        nop     
// 0443  cd040c    call    #0c04
// 0446  00        nop     
// 0447  d304      out     (#04),a
// 0449  0c        inc     c
// 044a  00        nop     
// 044b  d8        ret     c
// 
// 044c  04        inc     b
// 044d  0c        inc     c
// 044e  00        nop     
// 044f  e0        ret     po
// 
// 0450  04        inc     b
// 0451  0c        inc     c
// 0452  00        nop     
// 0453  1c        inc     e
// 0454  05        dec     b
// 0455  4b        ld      c,e
// 0456  05        dec     b
// 0457  56        ld      d,(hl)
// 0458  05        dec     b
// 0459  61        ld      h,c
// 045a  05        dec     b
// 045b  6c        ld      l,h
// 045c  05        dec     b
// 045d  7c        ld      a,h
// 045e  05        dec     b
// 045f  ef        rst     #28
// 0460  00        nop     
// 0461  01ef01    ld      bc,#01ef
// 0464  00        nop     
// 0465  ef        rst     #28
// 0466  04        inc     b
// 0467  00        nop     
// 0468  ef        rst     #28
// 0469  1e00      ld      e,#00
// 046b  0e0c      ld      c,#0c
// 046d  cd8505    call    #0585
// 0470  c9        ret     
// 
// 0471  210443    ld      hl,#4304
// 0474  3e01      ld      a,#01
// 0476  cdbf05    call    #05bf
// 0479  0e0c      ld      c,#0c
// 047b  cd8505    call    #0585
// 047e  c9        ret     
// 
// 047f  0e14      ld      c,#14
// 0481  cd9305    call    #0593
// 0484  c9        ret     
// 
// 0485  0e0d      ld      c,#0d
// 0487  cd9305    call    #0593
// 048a  c9        ret     
// 
// 048b  210743    ld      hl,#4307
// 048e  3e03      ld      a,#03
// 0490  cdbf05    call    #05bf
// 0493  0e0c      ld      c,#0c
// 0495  cd8505    call    #0585
// 0498  c9        ret     
// 
// 0499  0e16      ld      c,#16
// 049b  cd9305    call    #0593
// 049e  c9        ret     
// 
// 049f  0e0f      ld      c,#0f
// 04a1  cd9305    call    #0593
// 04a4  c9        ret     
// 
// 04a5  210a43    ld      hl,#430a
// 04a8  3e05      ld      a,#05
// 04aa  cdbf05    call    #05bf
// 04ad  0e0c      ld      c,#0c
// 04af  cd8505    call    #0585
// 04b2  c9        ret     
// 
// 04b3  0e33      ld      c,#33
// 04b5  cd9305    call    #0593
// 04b8  c9        ret     
// 
// 04b9  0e2f      ld      c,#2f
// 04bb  cd9305    call    #0593
// 04be  c9        ret     
// 
// 04bf  210d43    ld      hl,#430d
// 04c2  3e07      ld      a,#07
// 04c4  cdbf05    call    #05bf
// 04c7  0e0c      ld      c,#0c
// 04c9  cd8505    call    #0585
// 04cc  c9        ret     
// 
// 04cd  0e35      ld      c,#35
// 04cf  cd9305    call    #0593
// 04d2  c9        ret     
// 
// 04d3  0e31      ld      c,#31
// 04d5  c38005    jp      #0580
// 04d8  ef        rst     #28
// 04d9  1c        inc     e
// 04da  110e12    ld      de,#120e
// 04dd  c38505    jp      #0585
// 04e0  0e13      ld      c,#13
// 04e2  cd8505    call    #0585
// 04e5  cd7908    call    #0879
// 04e8  35        dec     (hl)
// 04e9  ef        rst     #28
// 04ea  1100ef    ld      de,#ef00
// 04ed  05        dec     b
// 04ee  01ef10    ld      bc,#10ef
// 04f1  14        inc     d
// 04f2  ef        rst     #28
// 04f3  04        inc     b
// 04f4  013e01    ld      bc,#013e
// 04f7  32144e    ld      (#4e14),a
// 04fa  af        xor     a
// 04fb  32704e    ld      (#4e70),a
// 04fe  32154e    ld      (#4e15),a
// 0501  213243    ld      hl,#4332
// 0504  3614      ld      (hl),#14
// 0506  3efc      ld      a,#fc
// 0508  112000    ld      de,#0020
// 050b  061c      ld      b,#1c
// 050d  dd214040  ld      ix,#4040
// 0511  dd7711    ld      (ix+#11),a
// 0514  dd7713    ld      (ix+#13),a
// 0517  dd19      add     ix,de
// 0519  10f6      djnz    #0511           ; (-10)
// 051b  c9        ret     
// 
// 051c  21a04d    ld      hl,#4da0
// 051f  0621      ld      b,#21
// 0521  3a3a4d    ld      a,(#4d3a)
// 0524  90        sub     b
// 0525  2005      jr      nz,#052c        ; (5)
// 0527  3601      ld      (hl),#01
// 0529  c38e05    jp      #058e
// 052c  cd1710    call    #1017
// 052f  cd1710    call    #1017
// 0532  cd230e    call    #0e23
// 0535  cd0d0c    call    #0c0d
// 0538  cdd60b    call    #0bd6
// 053b  cda505    call    #05a5
// 053e  cdfe1e    call    #1efe
// 0541  cd251f    call    #1f25
// 0544  cd4c1f    call    #1f4c
// 0547  cd731f    call    #1f73
// 054a  c9        ret     
// 
// 054b  21a14d    ld      hl,#4da1
// 054e  0620      ld      b,#20
// 0550  3a324d    ld      a,(#4d32)
// 0553  c32405    jp      #0524
// 0556  21a24d    ld      hl,#4da2
// 0559  0622      ld      b,#22
// 055b  3a324d    ld      a,(#4d32)
// 055e  c32405    jp      #0524
// 0561  21a34d    ld      hl,#4da3
// 0564  0624      ld      b,#24
// 0566  3a324d    ld      a,(#4d32)
// 0569  c32405    jp      #0524
// 056c  3ad04d    ld      a,(#4dd0)
// 056f  47        ld      b,a
// 0570  3ad14d    ld      a,(#4dd1)
// 0573  80        add     a,b
// 0574  fe06      cp      #06
// 0576  ca8e05    jp      z,#058e
// 0579  c32c05    jp      #052c
// 057c  cdbe06    call    #06be
// 057f  c9        ret     
// 
// 0580  3a754e    ld      a,(#4e75)
// 0583  81        add     a,c
// 0584  4f        ld      c,a
// 0585  061c      ld      b,#1c
// 0587  cd4200    call    #0042
// 058a  f7        rst     #30
// 058b  4a        ld      c,d
// 058c  02        ld      (bc),a
// 058d  00        nop     
// 058e  21024e    ld      hl,#4e02
// 0591  34        inc     (hl)
// 0592  c9        ret     
// 
// 0593  3a754e    ld      a,(#4e75)
// 0596  81        add     a,c
// 0597  4f        ld      c,a
// 0598  061c      ld      b,#1c
// 059a  cd4200    call    #0042
// 059d  f7        rst     #30
// 059e  45        ld      b,l
// 059f  02        ld      (bc),a
// 05a0  00        nop     
// 05a1  cd8e05    call    #058e
// 05a4  c9        ret     
// 
// 05a5  3ab54d    ld      a,(#4db5)
// 05a8  a7        and     a
// 05a9  c8        ret     z
// 
// 05aa  af        xor     a
// 05ab  32b54d    ld      (#4db5),a
// 05ae  3a304d    ld      a,(#4d30)
// 05b1  ee02      xor     #02
// 05b3  323c4d    ld      (#4d3c),a
// 05b6  47        ld      b,a
// 05b7  21ff32    ld      hl,#32ff
// 05ba  df        rst     #18
// 05bb  22264d    ld      (#4d26),hl
// 05be  c9        ret     
// 
// 05bf  36b1      ld      (hl),#b1
// 05c1  2c        inc     l
// 05c2  36b3      ld      (hl),#b3
// 05c4  2c        inc     l
// 05c5  36b5      ld      (hl),#b5
// 05c7  011e00    ld      bc,#001e
// 05ca  09        add     hl,bc
// 05cb  36b0      ld      (hl),#b0
// 05cd  2c        inc     l
// 05ce  36b2      ld      (hl),#b2
// 05d0  2c        inc     l
// 05d1  36b4      ld      (hl),#b4
// 05d3  110004    ld      de,#0400
// 05d6  19        add     hl,de
// 05d7  77        ld      (hl),a
// 05d8  2d        dec     l
// 05d9  77        ld      (hl),a
// 05da  2d        dec     l
// 05db  77        ld      (hl),a
// 05dc  a7        and     a
// 05dd  ed42      sbc     hl,bc
// 05df  77        ld      (hl),a
// 05e0  2d        dec     l
// 05e1  77        ld      (hl),a
// 05e2  2d        dec     l
// 05e3  77        ld      (hl),a
// 05e4  c9        ret     
// 
// 05e5  3a034e    ld      a,(#4e03)
// 05e8  e7        rst     #20
// 05e9  f3        di      
// 05ea  05        dec     b
// 05eb  1b        dec     de
// 05ec  0674      ld      b,#74
// 05ee  060c      ld      b,#0c
// 05f0  00        nop     
// 05f1  a8        xor     b
// 05f2  06cd      ld      b,#cd
// 05f4  a1        and     c
// 05f5  2b        dec     hl
// 05f6  ef        rst     #28
// 05f7  00        nop     
// 05f8  01ef01    ld      bc,#01ef
// 05fb  00        nop     
// 05fc  ef        rst     #28
// 05fd  1c        inc     e
// 05fe  07        rlca    
// 05ff  ef        rst     #28
// 0600  1c        inc     e
// 0601  0b        dec     bc
// 0602  ef        rst     #28
// 0603  1e00      ld      e,#00
// 0605  21034e    ld      hl,#4e03
// 0608  34        inc     (hl)
// 0609  3e01      ld      a,#01
// 060b  32d64d    ld      (#4dd6),a
// 060e  3a714e    ld      a,(#4e71)
// 0611  feff      cp      #ff
// 0613  c8        ret     z
// 
// 0614  ef        rst     #28
// 0615  1c        inc     e
// 0616  0a        ld      a,(bc)
// 0617  ef        rst     #28
// 0618  1f        rra     
// 0619  00        nop     
// 061a  c9        ret     
// 
// 	;; Can't find a jump to here!
// 	;; Display 1/2 player and check start buttons
// 061b  cda12b    call    #2ba1
// 061e  3a6e4e    ld      a,(#coinCredits)	; Credits
// 0621  fe01      cp      #01
// 0623  0609      ld      b,#09		; MSG #9
// 0625  2002      jr      nz,#0629	; >2 credits
// 0627  0608      ld      b,#08		; MSG #8
// 0629  cd5e2c    call    #2c5e
// 062c  3a6e4e    ld      a,(#coinCredits)
// 062f  fe01      cp      #01
// 0631  3a4050    ld      a,(#5040)
// 0634  280c      jr      z,#0642         ; Don't check P2 w/ 1 credit
// 0636  cb77      bit     6,a
// 0638  2008      jr      nz,#0642        ; (8)
// 063a  3e01      ld      a,#01
// 063c  32704e    ld      (#4e70),a
// 063f  c34906    jp      #0649
// 0642  cb6f      bit     5,a
// 0644  c0        ret     nz
// 
// 0645  af        xor     a
// 0646  32704e    ld      (#4e70),a
// 0649  3a6b4e    ld      a,(#COINS_PER_CREDIT)
// 064c  a7        and     a
// 064d  2815      jr      z,#0664         ; (21)
// 064f  3a704e    ld      a,(#4e70)
// 0652  a7        and     a
// 0653  3a6e4e    ld      a,(#coinCredits)
// 0656  2803      jr      z,#065b         ; (3)
// 0658  c699      add     a,#99
// 065a  27        daa     
// 065b  c699      add     a,#99
// 065d  27        daa     
// 065e  326e4e    ld      (#coinCredits),a
// 0661  cda12b    call    #2ba1
// 0664  21034e    ld      hl,#4e03
// 0667  34        inc     (hl)
// 0668  af        xor     a
// 0669  32d64d    ld      (#4dd6),a
// 066c  3c        inc     a
// 066d  32cc4e    ld      (#4ecc),a
// 0670  32dc4e    ld      (#4edc),a
// 0673  c9        ret     
// 
// 0674  ef        rst     #28
// 0675  00        nop     
// 0676  01ef01    ld      bc,#01ef
// 0679  01ef02    ld      bc,#02ef
// 067c  00        nop     
// 067d  ef        rst     #28
// 067e  12        ld      (de),a
// 067f  00        nop     
// 0680  ef        rst     #28
// 0681  03        inc     bc
// 0682  00        nop     
// 0683  ef        rst     #28
// 0684  1c        inc     e
// 0685  03        inc     bc
// 0686  ef        rst     #28
// 0687  1c        inc     e
// 0688  06ef      ld      b,#ef
// 068a  1800      jr      #068c           ; (0)
// 068c  ef        rst     #28
// 068d  1b        dec     de
// 068e  00        nop     
// 068f  af        xor     a
// 0690  32134e    ld      (#4e13),a
// 0693  3a6f4e    ld      a,(#LIVES_PER_GAME)
// 0696  32144e    ld      (#4e14),a
// 0699  32154e    ld      (#4e15),a
// 069c  ef        rst     #28
// 069d  1a        ld      a,(de)
// 069e  00        nop     
// 069f  f7        rst     #30
// 06a0  57        ld      d,a
// 06a1  010021    ld      bc,#2100
// 06a4  03        inc     bc
// 06a5  4e        ld      c,(hl)
// 06a6  34        inc     (hl)
// 06a7  c9        ret     
// 
// 06a8  21154e    ld      hl,#4e15
// 06ab  35        dec     (hl)
// 06ac  cd6a2b    call    #2b6a
// 06af  af        xor     a
// 06b0  32034e    ld      (#4e03),a
// 06b3  32024e    ld      (#4e02),a
// 06b6  32044e    ld      (#4e04),a
// 06b9  21004e    ld      hl,#4e00
// 06bc  34        inc     (hl)
// 06bd  c9        ret     
// 
// 06be  3a044e    ld      a,(#4e04)
// 06c1  e7        rst     #20
// 06c2  79        ld      a,c
// 06c3  08        ex      af,af'
// 06c4  99        sbc     a,c
// 06c5  08        ex      af,af'
// 06c6  0c        inc     c
// 06c7  00        nop     
// 06c8  cd080d    call    #0d08
// 06cb  09        add     hl,bc
// 06cc  0c        inc     c
// 06cd  00        nop     
// 06ce  40        ld      b,b
// 06cf  09        add     hl,bc
// 06d0  0c        inc     c
// 06d1  00        nop     
// 06d2  72        ld      (hl),d
// 06d3  09        add     hl,bc
// 06d4  88        adc     a,b
// 06d5  09        add     hl,bc
// 06d6  0c        inc     c
// 06d7  00        nop     
// 06d8  d209d8    jp      nc,#d809
// 06db  09        add     hl,bc
// 06dc  0c        inc     c
// 06dd  00        nop     
// 06de  e8        ret     pe
// 
// 06df  09        add     hl,bc
// 06e0  0c        inc     c
// 06e1  00        nop     
// 06e2  fe09      cp      #09
// 06e4  0c        inc     c
// 06e5  00        nop     
// 06e6  02        ld      (bc),a
// 06e7  0a        ld      a,(bc)
// 06e8  0c        inc     c
// 06e9  00        nop     
// 06ea  04        inc     b
// 06eb  0a        ld      a,(bc)
// 06ec  0c        inc     c
// 06ed  00        nop     
// 06ee  060a      ld      b,#0a
// 06f0  0c        inc     c
// 06f1  00        nop     
// 06f2  08        ex      af,af'
// 06f3  0a        ld      a,(bc)
// 06f4  0c        inc     c
// 06f5  00        nop     
// 06f6  0a        ld      a,(bc)
// 06f7  0a        ld      a,(bc)
// 06f8  0c        inc     c
// 06f9  00        nop     
// 06fa  0c        inc     c
// 06fb  0a        ld      a,(bc)
// 06fc  0c        inc     c
// 06fd  00        nop     
// 06fe  0e0a      ld      c,#0a
// 0700  0c        inc     c
// 0701  00        nop     
// 0702  2c        inc     l
// 0703  0a        ld      a,(bc)
// 0704  0c        inc     c
// 0705  00        nop     
// 0706  7c        ld      a,h
// 0707  0a        ld      a,(bc)
// 0708  a0        and     b
// 0709  0a        ld      a,(bc)
// 070a  0c        inc     c
// 070b  00        nop     
// 070c  a3        and     e
// 070d  0a        ld      a,(bc)
// 070e  78        ld      a,b
// 070f  a7        and     a
// 0710  2004      jr      nz,#0716        ; (4)
// 0712  2a0a4e    ld      hl,(#4e0a)
// 0715  7e        ld      a,(hl)
// 0716  dd219607  ld      ix,#0796
// 071a  47        ld      b,a
// 071b  87        add     a,a
// 071c  87        add     a,a
// 071d  80        add     a,b
// 071e  80        add     a,b
// 071f  5f        ld      e,a
// 0720  1600      ld      d,#00
// 0722  dd19      add     ix,de
// 0724  dd7e00    ld      a,(ix+#00)
// 0727  87        add     a,a
// 0728  47        ld      b,a
// 0729  87        add     a,a
// 072a  87        add     a,a
// 072b  4f        ld      c,a
// 072c  87        add     a,a
// 072d  87        add     a,a
// 072e  81        add     a,c
// 072f  80        add     a,b
// 0730  5f        ld      e,a
// 0731  1600      ld      d,#00
// 0733  210f33    ld      hl,#330f
// 0736  19        add     hl,de
// 0737  cd1408    call    #0814
// 073a  dd7e01    ld      a,(ix+#01)
// 073d  32b04d    ld      (#4db0),a
// 0740  dd7e02    ld      a,(ix+#02)
// 0743  47        ld      b,a
// 0744  87        add     a,a
// 0745  80        add     a,b
// 0746  5f        ld      e,a
// 0747  1600      ld      d,#00
// 0749  214308    ld      hl,#0843
// 074c  19        add     hl,de
// 074d  cd3a08    call    #083a
// 0750  dd7e03    ld      a,(ix+#03)
// 0753  87        add     a,a
// 0754  5f        ld      e,a
// 0755  1600      ld      d,#00
// 0757  fd214f08  ld      iy,#084f
// 075b  fd19      add     iy,de
// 075d  fd6e00    ld      l,(iy+#00)
// 0760  fd6601    ld      h,(iy+#01)
// 0763  22bb4d    ld      (#4dbb),hl
// 0766  dd7e04    ld      a,(ix+#04)
// 0769  87        add     a,a
// 076a  5f        ld      e,a
// 076b  1600      ld      d,#00
// 076d  fd216108  ld      iy,#0861
// 0771  fd19      add     iy,de
// 0773  fd6e00    ld      l,(iy+#00)
// 0776  fd6601    ld      h,(iy+#01)
// 0779  22bd4d    ld      (#4dbd),hl
// 077c  dd7e05    ld      a,(ix+#05)
// 077f  87        add     a,a
// 0780  5f        ld      e,a
// 0781  1600      ld      d,#00
// 0783  fd217308  ld      iy,#0873
// 0787  fd19      add     iy,de
// 0789  fd6e00    ld      l,(iy+#00)
// 078c  fd6601    ld      h,(iy+#01)
// 078f  22954d    ld      (#4d95),hl
// 0792  cdea2b    call    #2bea
// 0795  c9        ret     
// 
// 0796  03        inc     bc
// 0797  010100    ld      bc,#0001
// 079a  02        ld      (bc),a
// 079b  00        nop     
// 079c  04        inc     b
// 079d  010201    ld      bc,#0102
// 07a0  03        inc     bc
// 07a1  00        nop     
// 07a2  04        inc     b
// 07a3  010302    ld      bc,#0203
// 07a6  04        inc     b
// 07a7  010402    ld      bc,#0204
// 07aa  03        inc     bc
// 07ab  02        ld      (bc),a
// 07ac  05        dec     b
// 07ad  010500    ld      bc,#0005
// 07b0  03        inc     bc
// 07b1  02        ld      (bc),a
// 07b2  0602      ld      b,#02
// 07b4  05        dec     b
// 07b5  010303    ld      bc,#0303
// 07b8  03        inc     bc
// 07b9  02        ld      (bc),a
// 07ba  05        dec     b
// 07bb  02        ld      (bc),a
// 07bc  03        inc     bc
// 07bd  03        inc     bc
// 07be  0602      ld      b,#02
// 07c0  05        dec     b
// 07c1  02        ld      (bc),a
// 07c2  03        inc     bc
// 07c3  03        inc     bc
// 07c4  0602      ld      b,#02
// 07c6  05        dec     b
// 07c7  00        nop     
// 07c8  03        inc     bc
// 07c9  04        inc     b
// 07ca  07        rlca    
// 07cb  02        ld      (bc),a
// 07cc  05        dec     b
// 07cd  010304    ld      bc,#0403
// 07d0  03        inc     bc
// 07d1  02        ld      (bc),a
// 07d2  05        dec     b
// 07d3  02        ld      (bc),a
// 07d4  03        inc     bc
// 07d5  04        inc     b
// 07d6  0602      ld      b,#02
// 07d8  05        dec     b
// 07d9  02        ld      (bc),a
// 07da  03        inc     bc
// 07db  05        dec     b
// 07dc  07        rlca    
// 07dd  02        ld      (bc),a
// 07de  05        dec     b
// 07df  00        nop     
// 07e0  03        inc     bc
// 07e1  05        dec     b
// 07e2  07        rlca    
// 07e3  02        ld      (bc),a
// 07e4  05        dec     b
// 07e5  02        ld      (bc),a
// 07e6  03        inc     bc
// 07e7  05        dec     b
// 07e8  05        dec     b
// 07e9  02        ld      (bc),a
// 07ea  05        dec     b
// 07eb  010306    ld      bc,#0603
// 07ee  07        rlca    
// 07ef  02        ld      (bc),a
// 07f0  05        dec     b
// 07f1  02        ld      (bc),a
// 07f2  03        inc     bc
// 07f3  0607      ld      b,#07
// 07f5  02        ld      (bc),a
// 07f6  05        dec     b
// 07f7  02        ld      (bc),a
// 07f8  03        inc     bc
// 07f9  0608      ld      b,#08
// 07fb  02        ld      (bc),a
// 07fc  05        dec     b
// 07fd  02        ld      (bc),a
// 07fe  03        inc     bc
// 07ff  0607      ld      b,#07
// 0801  02        ld      (bc),a
// 0802  05        dec     b
// 0803  02        ld      (bc),a
// 0804  03        inc     bc
// 0805  07        rlca    
// 0806  08        ex      af,af'
// 0807  02        ld      (bc),a
// 0808  05        dec     b
// 0809  02        ld      (bc),a
// 080a  03        inc     bc
// 080b  07        rlca    
// 080c  08        ex      af,af'
// 080d  02        ld      (bc),a
// 080e  0602      ld      b,#02
// 0810  03        inc     bc
// 0811  07        rlca    
// 0812  08        ex      af,af'
// 0813  02        ld      (bc),a
// 0814  11464d    ld      de,#4d46
// 0817  011c00    ld      bc,#001c
// 081a  edb0      ldir    
// 081c  010c00    ld      bc,#000c
// 081f  a7        and     a
// 0820  ed42      sbc     hl,bc
// 0822  edb0      ldir    
// 0824  010c00    ld      bc,#000c
// 0827  a7        and     a
// 0828  ed42      sbc     hl,bc
// 082a  edb0      ldir    
// 082c  010c00    ld      bc,#000c
// 082f  a7        and     a
// 0830  ed42      sbc     hl,bc
// 0832  edb0      ldir    
// 0834  010e00    ld      bc,#000e
// 0837  edb0      ldir    
// 0839  c9        ret     
// 
// 083a  11b84d    ld      de,#4db8
// 083d  010300    ld      bc,#0003
// 0840  edb0      ldir    
// 0842  c9        ret     
// 
// 0843  14        inc     d
// 0844  1e46      ld      e,#46
// 0846  00        nop     
// 0847  1e3c      ld      e,#3c
// 0849  00        nop     
// 084a  00        nop     
// 084b  320000    ld      (#0000),a
// 084e  00        nop     
// 084f  14        inc     d
// 0850  0a        ld      a,(bc)
// 0851  1e0f      ld      e,#0f
// 0853  2814      jr      z,#0869         ; (20)
// 0855  32193c    ld      (#3c19),a
// 0858  1e50      ld      e,#50
// 085a  2864      jr      z,#08c0         ; (100)
// 085c  32783c    ld      (#3c78),a
// 085f  8c        adc     a,h
// 0860  46        ld      b,(hl)
// 0861  c0        ret     nz
// 
// 0862  03        inc     bc
// 0863  48        ld      c,b
// 0864  03        inc     bc
// 0865  d0        ret     nc
// 
// 0866  02        ld      (bc),a
// 0867  58        ld      e,b
// 0868  02        ld      (bc),a
// 0869  e0        ret     po
// 
// 086a  016801    ld      bc,#0168
// 086d  f0        ret     p
// 
// 086e  00        nop     
// 086f  78        ld      a,b
// 0870  00        nop     
// 0871  0100f0    ld      bc,#f000
// 0874  00        nop     
// 0875  f0        ret     p
// 
// 0876  00        nop     
// 0877  b4        or      h
// 0878  00        nop     


// 0879  21094e    ld      hl,#4e09
// 087c  af        xor     a
// 087d  060b      ld      b,#0b
// 087f  cf        rst     #8
memset (0x4e09, 0, 8);

// 0880  cdc924    call    #24c9
// 0883  2a734e    ld      hl,(#4e73)
// 0886  220a4e    ld      (#4e0a),hl
// 0889  210a4e    ld      hl,#4e0a
// 088c  11384e    ld      de,#4e38
// 088f  012e00    ld      bc,#002e
// 0892  edb0      ldir    
// 0894  21044e    ld      hl,#4e04
// 0897  34        inc     (hl)
// 0898  c9        ret     
// 
// 0899  3a004e    ld      a,(#4e00)
// 089c  3d        dec     a
// 089d  2006      jr      nz,#08a5        ; (6)
// 089f  3e09      ld      a,#09
// 08a1  32044e    ld      (#4e04),a
// 08a4  c9        ret     
// 
// 08a5  ef        rst     #28
// 08a6  1100ef    ld      de,#ef00
// 08a9  1c        inc     e
// 08aa  83        add     a,e
// 08ab  ef        rst     #28
// 08ac  04        inc     b
// 08ad  00        nop     
// 08ae  ef        rst     #28
// 08af  05        dec     b
// 08b0  00        nop     
// 08b1  ef        rst     #28
// 08b2  1000      djnz    #08b4           ; (0)
// 08b4  ef        rst     #28
// 08b5  1a        ld      a,(de)
// 08b6  00        nop     
// 08b7  f7        rst     #30
// 08b8  54        ld      d,h
// 08b9  00        nop     
// 08ba  00        nop     
// 08bb  f7        rst     #30
// 08bc  54        ld      d,h
// 08bd  0600      ld      b,#00
// 08bf  3a724e    ld      a,(#4e72)
// 08c2  47        ld      b,a
// 08c3  3a094e    ld      a,(#4e09)
// 08c6  a0        and     b
// 08c7  320350    ld      (#5003),a
// 08ca  c39408    jp      #0894
// 08cd  3a0050    ld      a,(#5000)
// 08d0  cb67      bit     4,a
// 08d2  c2de08    jp      nz,#08de
// 08d5  21044e    ld      hl,#4e04
// 08d8  360e      ld      (hl),#0e
// 08da  ef        rst     #28
// 08db  13        inc     de
// 08dc  00        nop     
// 08dd  c9        ret     
// 
// 08de  3a0e4e    ld      a,(#4e0e)
// 08e1  fef4      cp      #f4
// 08e3  2006      jr      nz,#08eb        ; (6)
// 08e5  21044e    ld      hl,#4e04
// 08e8  360c      ld      (hl),#0c
// 08ea  c9        ret     
// 
// 08eb  cd1710    call    #1017
// 08ee  cd1710    call    #1017
// 08f1  cddd13    call    #13dd
// 08f4  cd420c    call    #0c42
// 08f7  cd230e    call    #0e23
// 08fa  cd360e    call    #0e36
// 08fd  cdc30a    call    #0ac3
// 0900  cdd60b    call    #0bd6
// 0903  cd0d0c    call    #0c0d
// 0906  cd6c0e    call    #0e6c
// 0909  cdad0e    call    #0ead
// 090c  c9        ret     
// 
// 090d  3e01      ld      a,#01
// 090f  32124e    ld      (#4e12),a
// 0912  cd8724    call    #2487
// 0915  21044e    ld      hl,#4e04
// 0918  34        inc     (hl)
// 0919  3a144e    ld      a,(#4e14)
// 091c  a7        and     a
// 091d  201f      jr      nz,#093e        ; (31)
// 091f  3a704e    ld      a,(#4e70)
// 0922  a7        and     a
// 0923  2819      jr      z,#093e         ; (25)
// 0925  3a424e    ld      a,(#4e42)
// 0928  a7        and     a
// 0929  2813      jr      z,#093e         ; (19)
// 092b  3a094e    ld      a,(#4e09)
// 092e  c603      add     a,#03
// 0930  4f        ld      c,a
// 0931  061c      ld      b,#1c
// 0933  cd4200    call    #0042
// 0936  ef        rst     #28
// 0937  1c        inc     e
// 0938  05        dec     b
// 0939  f7        rst     #30
// 093a  54        ld      d,h
// 093b  00        nop     
// 093c  00        nop     
// 093d  c9        ret     
// 
// 093e  34        inc     (hl)
// 093f  c9        ret     
// 
// 0940  3a704e    ld      a,(#4e70)
// 0943  a7        and     a
// 0944  2806      jr      z,#094c         ; (6)
// 0946  3a424e    ld      a,(#4e42)
// 0949  a7        and     a
// 094a  2015      jr      nz,#0961        ; (21)
// 094c  3a144e    ld      a,(#4e14)
// 094f  a7        and     a
// 0950  201a      jr      nz,#096c        ; (26)
// 0952  cda12b    call    #2ba1
// 0955  ef        rst     #28
// 0956  1c        inc     e
// 0957  05        dec     b
// 0958  f7        rst     #30
// 0959  54        ld      d,h
// 095a  00        nop     
// 095b  00        nop     
// 095c  21044e    ld      hl,#4e04
// 095f  34        inc     (hl)
// 0960  c9        ret     
// 
// 0961  cda60a    call    #0aa6
// 0964  3a094e    ld      a,(#4e09)
// 0967  ee01      xor     #01
// 0969  32094e    ld      (#4e09),a
// 096c  3e09      ld      a,#09
// 096e  32044e    ld      (#4e04),a
// 0971  c9        ret     
// 
// 0972  af        xor     a
// 0973  32024e    ld      (#4e02),a
// 0976  32044e    ld      (#4e04),a
// 0979  32704e    ld      (#4e70),a
// 097c  32094e    ld      (#4e09),a
// 097f  320350    ld      (#5003),a
// 0982  3e01      ld      a,#01
// 0984  32004e    ld      (#4e00),a
// 0987  c9        ret     
// 
// 0988  ef        rst     #28
// 0989  00        nop     
// 098a  01ef01    ld      bc,#01ef
// 098d  01ef02    ld      bc,#02ef
// 0990  00        nop     
// 0991  ef        rst     #28
// 0992  1100ef    ld      de,#ef00
// 0995  13        inc     de
// 0996  00        nop     
// 0997  ef        rst     #28
// 0998  03        inc     bc
// 0999  00        nop     
// 099a  ef        rst     #28
// 099b  04        inc     b
// 099c  00        nop     
// 099d  ef        rst     #28
// 099e  05        dec     b
// 099f  00        nop     
// 09a0  ef        rst     #28
// 09a1  1000      djnz    #09a3           ; (0)
// 09a3  ef        rst     #28
// 09a4  1a        ld      a,(de)
// 09a5  00        nop     
// 09a6  ef        rst     #28
// 09a7  1c        inc     e
// 09a8  063a      ld      b,#3a
// 09aa  00        nop     
// 09ab  4e        ld      c,(hl)
// 09ac  fe03      cp      #03
// 09ae  2806      jr      z,#09b6         ; (6)
// 09b0  ef        rst     #28
// 09b1  1c        inc     e
// 09b2  05        dec     b
// 09b3  ef        rst     #28
// 09b4  1d        dec     e
// 09b5  00        nop     
// 09b6  f7        rst     #30
// 09b7  54        ld      d,h
// 09b8  00        nop     
// 09b9  00        nop     
// 09ba  3a004e    ld      a,(#4e00)
// 09bd  3d        dec     a
// 09be  2804      jr      z,#09c4         ; (4)
// 09c0  f7        rst     #30
// 09c1  54        ld      d,h
// 09c2  0600      ld      b,#00
// 09c4  3a724e    ld      a,(#4e72)
// 09c7  47        ld      b,a
// 09c8  3a094e    ld      a,(#4e09)
// 09cb  a0        and     b
// 09cc  320350    ld      (#5003),a
// 09cf  c39408    jp      #0894
// 09d2  3e03      ld      a,#03
// 09d4  32044e    ld      (#4e04),a
// 09d7  c9        ret     
// 
// 09d8  f7        rst     #30
// 09d9  54        ld      d,h
// 09da  00        nop     
// 09db  00        nop     
// 09dc  21044e    ld      hl,#4e04
// 09df  34        inc     (hl)
// 09e0  af        xor     a
// 09e1  32ac4e    ld      (#4eac),a
// 09e4  32bc4e    ld      (#4ebc),a
// 09e7  c9        ret     
// 
// 09e8  0e02      ld      c,#02
// 09ea  0601      ld      b,#01
// 09ec  cd4200    call    #0042
// 09ef  f7        rst     #30
// 09f0  42        ld      b,d
// 09f1  00        nop     
// 09f2  00        nop     
// 09f3  210000    ld      hl,#0000
// 09f6  cd7e26    call    #267e
// 09f9  21044e    ld      hl,#4e04
// 09fc  34        inc     (hl)
// 09fd  c9        ret     
// 
// 09fe  0e00      ld      c,#00
// 0a00  18e8      jr      #09ea           ; (-24)
// 0a02  18e4      jr      #09e8           ; (-28)
// 0a04  18f8      jr      #09fe           ; (-8)
// 0a06  18e0      jr      #09e8           ; (-32)
// 0a08  18f4      jr      #09fe           ; (-12)
// 0a0a  18dc      jr      #09e8           ; (-36)
// 0a0c  18f0      jr      #09fe           ; (-16)
// 0a0e  ef        rst     #28
// 0a0f  00        nop     
// 0a10  01ef06    ld      bc,#06ef
// 0a13  00        nop     
// 0a14  ef        rst     #28
// 0a15  1100ef    ld      de,#ef00
// 0a18  13        inc     de
// 0a19  00        nop     
// 0a1a  ef        rst     #28
// 0a1b  04        inc     b
// 0a1c  01ef05    ld      bc,#05ef
// 0a1f  01ef10    ld      bc,#10ef
// 0a22  13        inc     de
// 0a23  f7        rst     #30
// 0a24  43        ld      b,e
// 0a25  00        nop     
// 0a26  00        nop     
// 0a27  21044e    ld      hl,#4e04
// 0a2a  34        inc     (hl)
// 0a2b  c9        ret     
// 
// 0a2c  af        xor     a
// 0a2d  32ac4e    ld      (#4eac),a
// 0a30  32bc4e    ld      (#4ebc),a
// 0a33  3e02      ld      a,#02
// 0a35  32cc4e    ld      (#4ecc),a
// 0a38  32dc4e    ld      (#4edc),a
// 0a3b  3a134e    ld      a,(#4e13)
// 0a3e  fe14      cp      #14
// 0a40  3802      jr      c,#0a44         ; (2)
// 0a42  3e14      ld      a,#14
// 0a44  e7        rst     #20
// 0a45  6f        ld      l,a
// 0a46  0a        ld      a,(bc)
// 0a47  08        ex      af,af'
// 0a48  216f0a    ld      hl,#0a6f
// 0a4b  6f        ld      l,a
// 0a4c  0a        ld      a,(bc)
// 0a4d  9e        sbc     a,(hl)
// 0a4e  216f0a    ld      hl,#0a6f
// 0a51  6f        ld      l,a
// 0a52  0a        ld      a,(bc)
// 0a53  6f        ld      l,a
// 0a54  0a        ld      a,(bc)
// 0a55  97        sub     a
// 0a56  226f0a    ld      (#0a6f),hl
// 0a59  6f        ld      l,a
// 0a5a  0a        ld      a,(bc)
// 0a5b  6f        ld      l,a
// 0a5c  0a        ld      a,(bc)
// 0a5d  97        sub     a
// 0a5e  226f0a    ld      (#0a6f),hl
// 0a61  6f        ld      l,a
// 0a62  0a        ld      a,(bc)
// 0a63  6f        ld      l,a
// 0a64  0a        ld      a,(bc)
// 0a65  97        sub     a
// 0a66  226f0a    ld      (#0a6f),hl
// 0a69  6f        ld      l,a
// 0a6a  0a        ld      a,(bc)
// 0a6b  6f        ld      l,a
// 0a6c  0a        ld      a,(bc)
// 0a6d  6f        ld      l,a
// 0a6e  0a        ld      a,(bc)
// 0a6f  21044e    ld      hl,#4e04
// 0a72  34        inc     (hl)
// 0a73  34        inc     (hl)
// 0a74  af        xor     a
// 0a75  32cc4e    ld      (#4ecc),a
// 0a78  32dc4e    ld      (#4edc),a
// 0a7b  c9        ret     
// 
// 0a7c  af        xor     a
// 0a7d  32cc4e    ld      (#4ecc),a
// 0a80  32dc4e    ld      (#4edc),a
*(0x4ecc) = 0;
*(0x4edc) = 0;

// 0a83  0607      ld      b,#07
// 0a85  210c4e    ld      hl,#4e0c
// 0a88  cf        rst     #8
memset (0x4e0c, 0, 7);

// 0a89  cdc924    call    #24c9
// 0a8c  21044e    ld      hl,#4e04
// 0a8f  34        inc     (hl)
// 0a90  21134e    ld      hl,#4e13
// 0a93  34        inc     (hl)
// 0a94  2a0a4e    ld      hl,(#4e0a)
// 0a97  7e        ld      a,(hl)
// 0a98  fe14      cp      #14
// 0a9a  c8        ret     z
// 
// 0a9b  23        inc     hl
// 0a9c  220a4e    ld      (#4e0a),hl
// 0a9f  c9        ret     
// 
// 0aa0  c38809    jp      #0988
// 0aa3  c3d209    jp      #09d2
// 0aa6  062e      ld      b,#2e
// 0aa8  dd210a4e  ld      ix,#4e0a
// 0aac  fd21384e  ld      iy,#4e38
// 0ab0  dd5600    ld      d,(ix+#00)
// 0ab3  fd5e00    ld      e,(iy+#00)
// 0ab6  fd7200    ld      (iy+#00),d
// 0ab9  dd7300    ld      (ix+#00),e
// 0abc  dd23      inc     ix
// 0abe  fd23      inc     iy
// 0ac0  10ee      djnz    #0ab0           ; (-18)
// 0ac2  c9        ret     
// 
// 0ac3  3aa44d    ld      a,(#4da4)
// 0ac6  a7        and     a
// 0ac7  c0        ret     nz
// 
// 0ac8  dd21004c  ld      ix,#4c00
// 0acc  fd21c84d  ld      iy,#4dc8
// 0ad0  110001    ld      de,#0100
// 0ad3  fdbe00    cp      (iy+#00)
// 0ad6  c2d20b    jp      nz,#0bd2
// 0ad9  fd36000e  ld      (iy+#00),#0e
// 0add  3aa64d    ld      a,(#4da6)
// 0ae0  a7        and     a
// 0ae1  281b      jr      z,#0afe         ; (27)
// 0ae3  2acb4d    ld      hl,(#4dcb)
// 0ae6  a7        and     a
// 0ae7  ed52      sbc     hl,de
// 0ae9  3013      jr      nc,#0afe        ; (19)
// 0aeb  21ac4e    ld      hl,#4eac
// 0aee  cbfe      set     7,(hl)
// 0af0  3e09      ld      a,#09
// 0af2  ddbe0b    cp      (ix+#0b)
// 0af5  2004      jr      nz,#0afb        ; (4)
// 0af7  cbbe      res     7,(hl)
// 0af9  3e09      ld      a,#09
// 0afb  320b4c    ld      (#4c0b),a
// 0afe  3aa74d    ld      a,(#4da7)
// 0b01  a7        and     a
// 0b02  281d      jr      z,#0b21         ; (29)
// 0b04  2acb4d    ld      hl,(#4dcb)
// 0b07  a7        and     a
// 0b08  ed52      sbc     hl,de
// 0b0a  3027      jr      nc,#0b33        ; (39)
// 0b0c  3e11      ld      a,#11
// 0b0e  ddbe03    cp      (ix+#03)
// 0b11  2807      jr      z,#0b1a         ; (7)
// 0b13  dd360311  ld      (ix+#03),#11
// 0b17  c3330b    jp      #0b33
// 0b1a  dd360312  ld      (ix+#03),#12
// 0b1e  c3330b    jp      #0b33
// 0b21  3e01      ld      a,#01
// 0b23  ddbe03    cp      (ix+#03)
// 0b26  2807      jr      z,#0b2f         ; (7)
// 0b28  dd360301  ld      (ix+#03),#01
// 0b2c  c3330b    jp      #0b33
// 0b2f  dd360301  ld      (ix+#03),#01
// 0b33  3aa84d    ld      a,(#4da8)
// 0b36  a7        and     a
// 0b37  281d      jr      z,#0b56         ; (29)
// 0b39  2acb4d    ld      hl,(#4dcb)
// 0b3c  a7        and     a
// 0b3d  ed52      sbc     hl,de
// 0b3f  3027      jr      nc,#0b68        ; (39)
// 0b41  3e11      ld      a,#11
// 0b43  ddbe05    cp      (ix+#05)
// 0b46  2807      jr      z,#0b4f         ; (7)
// 0b48  dd360511  ld      (ix+#05),#11
// 0b4c  c3680b    jp      #0b68
// 0b4f  dd360512  ld      (ix+#05),#12
// 0b53  c3680b    jp      #0b68
// 0b56  3e03      ld      a,#03
// 0b58  ddbe05    cp      (ix+#05)
// 0b5b  2807      jr      z,#0b64         ; (7)
// 0b5d  dd360503  ld      (ix+#05),#03
// 0b61  c3680b    jp      #0b68
// 0b64  dd360503  ld      (ix+#05),#03
// 0b68  3aa94d    ld      a,(#4da9)
// 0b6b  a7        and     a
// 0b6c  281d      jr      z,#0b8b         ; (29)
// 0b6e  2acb4d    ld      hl,(#4dcb)
// 0b71  a7        and     a
// 0b72  ed52      sbc     hl,de
// 0b74  3027      jr      nc,#0b9d        ; (39)
// 0b76  3e11      ld      a,#11
// 0b78  ddbe07    cp      (ix+#07)
// 0b7b  2807      jr      z,#0b84         ; (7)
// 0b7d  dd360711  ld      (ix+#07),#11
// 0b81  c39d0b    jp      #0b9d
// 0b84  dd360712  ld      (ix+#07),#12
// 0b88  c39d0b    jp      #0b9d
// 0b8b  3e05      ld      a,#05
// 0b8d  ddbe07    cp      (ix+#07)
// 0b90  2807      jr      z,#0b99         ; (7)
// 0b92  dd360705  ld      (ix+#07),#05
// 0b96  c39d0b    jp      #0b9d
// 0b99  dd360705  ld      (ix+#07),#05
// 0b9d  3aaa4d    ld      a,(#4daa)
// 0ba0  a7        and     a
// 0ba1  281d      jr      z,#0bc0         ; (29)
// 0ba3  2acb4d    ld      hl,(#4dcb)
// 0ba6  a7        and     a
// 0ba7  ed52      sbc     hl,de
// 0ba9  3027      jr      nc,#0bd2        ; (39)
// 0bab  3e11      ld      a,#11
// 0bad  ddbe09    cp      (ix+#09)
// 0bb0  2807      jr      z,#0bb9         ; (7)
// 0bb2  dd360911  ld      (ix+#09),#11
// 0bb6  c3d20b    jp      #0bd2
// 0bb9  dd360912  ld      (ix+#09),#12
// 0bbd  c3d20b    jp      #0bd2
// 0bc0  3e07      ld      a,#07
// 0bc2  ddbe09    cp      (ix+#09)
// 0bc5  2807      jr      z,#0bce         ; (7)
// 0bc7  dd360907  ld      (ix+#09),#07
// 0bcb  c3d20b    jp      #0bd2
// 0bce  dd360907  ld      (ix+#09),#07
// 0bd2  fd3500    dec     (iy+#00)
// 0bd5  c9        ret     
// 
// 0bd6  0619      ld      b,#19
// 0bd8  3a024e    ld      a,(#4e02)
// 0bdb  fe22      cp      #22
// 0bdd  c2e20b    jp      nz,#0be2
// 0be0  0600      ld      b,#00
// 0be2  dd21004c  ld      ix,#4c00
// 0be6  3aac4d    ld      a,(#4dac)
// 0be9  a7        and     a
// 0bea  caf00b    jp      z,#0bf0
// 0bed  dd7003    ld      (ix+#03),b
// 0bf0  3aad4d    ld      a,(#4dad)
// 0bf3  a7        and     a
// 0bf4  cafa0b    jp      z,#0bfa
// 0bf7  dd7005    ld      (ix+#05),b
// 0bfa  3aae4d    ld      a,(#4dae)
// 0bfd  a7        and     a
// 0bfe  ca040c    jp      z,#0c04
// 0c01  dd7007    ld      (ix+#07),b
// 0c04  3aaf4d    ld      a,(#4daf)
// 0c07  a7        and     a
// 0c08  c8        ret     z
// 
// 0c09  dd7009    ld      (ix+#09),b
// 0c0c  c9        ret     
// 
// 0c0d  21cf4d    ld      hl,#4dcf
// 0c10  34        inc     (hl)
// 0c11  3e0a      ld      a,#0a
// 0c13  be        cp      (hl)
// 0c14  c0        ret     nz
// 
// 0c15  3600      ld      (hl),#00
// 0c17  3a044e    ld      a,(#4e04)
// 0c1a  fe03      cp      #03
// 0c1c  2015      jr      nz,#0c33        ; (21)
// 0c1e  216444    ld      hl,#4464
// 0c21  3e10      ld      a,#10
// 0c23  be        cp      (hl)
// 0c24  2002      jr      nz,#0c28        ; (2)
// 0c26  3e00      ld      a,#00
// 0c28  77        ld      (hl),a
// 0c29  327844    ld      (#4478),a
// 0c2c  328447    ld      (#4784),a
// 0c2f  329847    ld      (#4798),a
// 0c32  c9        ret     
// 
// 0c33  213247    ld      hl,#4732
// 0c36  3e10      ld      a,#10
// 0c38  be        cp      (hl)
// 0c39  2002      jr      nz,#0c3d        ; (2)
// 0c3b  3e00      ld      a,#00
// 0c3d  77        ld      (hl),a
// 0c3e  327846    ld      (#4678),a
// 0c41  c9        ret     
// 
// 0c42  3aa44d    ld      a,(#4da4)
// 0c45  a7        and     a
// 0c46  c0        ret     nz
// 
// 0c47  3a944d    ld      a,(#4d94)
// 0c4a  07        rlca    
// 0c4b  32944d    ld      (#4d94),a
// 0c4e  d0        ret     nc
// 
// 0c4f  3aa04d    ld      a,(#4da0)
// 0c52  a7        and     a
// 0c53  c2900c    jp      nz,#0c90
// 0c56  dd210533  ld      ix,#3305
// 0c5a  fd21004d  ld      iy,#4d00
// 0c5e  cd0020    call    #2000
// 0c61  22004d    ld      (#4d00),hl
// 0c64  3e03      ld      a,#03
// 0c66  32284d    ld      (#4d28),a
// 0c69  322c4d    ld      (#4d2c),a
// 0c6c  3a004d    ld      a,(#4d00)
// 0c6f  fe64      cp      #64
// 0c71  c2900c    jp      nz,#0c90
// 0c74  212c2e    ld      hl,#2e2c
// 0c77  220a4d    ld      (#4d0a),hl
// 0c7a  210001    ld      hl,#0100
// 0c7d  22144d    ld      (#4d14),hl
// 0c80  221e4d    ld      (#4d1e),hl
// 0c83  3e02      ld      a,#02
// 0c85  32284d    ld      (#4d28),a
// 0c88  322c4d    ld      (#4d2c),a
// 0c8b  3e01      ld      a,#01
// 0c8d  32a04d    ld      (#4da0),a
// 0c90  3aa14d    ld      a,(#4da1)
// 0c93  fe01      cp      #01
// 0c95  cafb0c    jp      z,#0cfb
// 0c98  fe00      cp      #00
// 0c9a  c2c10c    jp      nz,#0cc1
// 0c9d  3a024d    ld      a,(#4d02)
// 0ca0  fe78      cp      #78
// 0ca2  cc2e1f    call    z,#1f2e
// 0ca5  fe80      cp      #80
// 0ca7  cc2e1f    call    z,#1f2e
// 0caa  3a2d4d    ld      a,(#4d2d)
// 0cad  32294d    ld      (#4d29),a
// 0cb0  dd21204d  ld      ix,#4d20
// 0cb4  fd21024d  ld      iy,#4d02
// 0cb8  cd0020    call    #2000
// 0cbb  22024d    ld      (#4d02),hl
// 0cbe  c3fb0c    jp      #0cfb
// 0cc1  dd210533  ld      ix,#3305
// 0cc5  fd21024d  ld      iy,#4d02
// 0cc9  cd0020    call    #2000
// 0ccc  22024d    ld      (#4d02),hl
// 0ccf  3e03      ld      a,#03
// 0cd1  322d4d    ld      (#4d2d),a
// 0cd4  32294d    ld      (#4d29),a
// 0cd7  3a024d    ld      a,(#4d02)
// 0cda  fe64      cp      #64
// 0cdc  c2fb0c    jp      nz,#0cfb
// 0cdf  212c2e    ld      hl,#2e2c
// 0ce2  220c4d    ld      (#4d0c),hl
// 0ce5  210001    ld      hl,#0100
// 0ce8  22164d    ld      (#4d16),hl
// 0ceb  22204d    ld      (#4d20),hl
// 0cee  3e02      ld      a,#02
// 0cf0  32294d    ld      (#4d29),a
// 0cf3  322d4d    ld      (#4d2d),a
// 0cf6  3e01      ld      a,#01
// 0cf8  32a14d    ld      (#4da1),a
// 0cfb  3aa24d    ld      a,(#4da2)
// 0cfe  fe01      cp      #01
// 0d00  ca930d    jp      z,#0d93
// 0d03  fe00      cp      #00
// 0d05  c22c0d    jp      nz,#0d2c
// 0d08  3a044d    ld      a,(#4d04)
// 0d0b  fe78      cp      #78
// 0d0d  cc551f    call    z,#1f55
// 0d10  fe80      cp      #80
// 0d12  cc551f    call    z,#1f55
// 0d15  3a2e4d    ld      a,(#4d2e)
// 0d18  322a4d    ld      (#4d2a),a
// 0d1b  dd21224d  ld      ix,#4d22
// 0d1f  fd21044d  ld      iy,#4d04
// 0d23  cd0020    call    #2000
// 0d26  22044d    ld      (#4d04),hl
// 0d29  c3930d    jp      #0d93
// 0d2c  3aa24d    ld      a,(#4da2)
// 0d2f  fe03      cp      #03
// 0d31  c2590d    jp      nz,#0d59
// 0d34  dd21ff32  ld      ix,#32ff
// 0d38  fd21044d  ld      iy,#4d04
// 0d3c  cd0020    call    #2000
// 0d3f  22044d    ld      (#4d04),hl
// 0d42  af        xor     a
// 0d43  322a4d    ld      (#4d2a),a
// 0d46  322e4d    ld      (#4d2e),a
// 0d49  3a054d    ld      a,(#4d05)
// 0d4c  fe80      cp      #80
// 0d4e  c2930d    jp      nz,#0d93
// 0d51  3e02      ld      a,#02
// 0d53  32a24d    ld      (#4da2),a
// 0d56  c3930d    jp      #0d93
// 0d59  dd210533  ld      ix,#3305
// 0d5d  fd21044d  ld      iy,#4d04
// 0d61  cd0020    call    #2000
// 0d64  22044d    ld      (#4d04),hl
// 0d67  3e03      ld      a,#03
// 0d69  322a4d    ld      (#4d2a),a
// 0d6c  322e4d    ld      (#4d2e),a
// 0d6f  3a044d    ld      a,(#4d04)
// 0d72  fe64      cp      #64
// 0d74  c2930d    jp      nz,#0d93
// 0d77  212c2e    ld      hl,#2e2c
// 0d7a  220e4d    ld      (#4d0e),hl
// 0d7d  210001    ld      hl,#0100
// 0d80  22184d    ld      (#4d18),hl
// 0d83  22224d    ld      (#4d22),hl
// 0d86  3e02      ld      a,#02
// 0d88  322a4d    ld      (#4d2a),a
// 0d8b  322e4d    ld      (#4d2e),a
// 0d8e  3e01      ld      a,#01
// 0d90  32a24d    ld      (#4da2),a
// 0d93  3aa34d    ld      a,(#4da3)
// 0d96  fe01      cp      #01
// 0d98  c8        ret     z
// 
// 0d99  fe00      cp      #00
// 0d9b  c2c00d    jp      nz,#0dc0
// 0d9e  3a064d    ld      a,(#4d06)
// 0da1  fe78      cp      #78
// 0da3  cc7c1f    call    z,#1f7c
// 0da6  fe80      cp      #80
// 0da8  cc7c1f    call    z,#1f7c
// 0dab  3a2f4d    ld      a,(#4d2f)
// 0dae  322b4d    ld      (#4d2b),a
// 0db1  dd21244d  ld      ix,#4d24
// 0db5  fd21064d  ld      iy,#4d06
// 0db9  cd0020    call    #2000
// 0dbc  22064d    ld      (#4d06),hl
// 0dbf  c9        ret     
// 
// 0dc0  3aa34d    ld      a,(#4da3)
// 0dc3  fe03      cp      #03
// 0dc5  c2ea0d    jp      nz,#0dea
// 0dc8  dd210333  ld      ix,#3303
// 0dcc  fd21064d  ld      iy,#4d06
// 0dd0  cd0020    call    #2000
// 0dd3  22064d    ld      (#4d06),hl
// 0dd6  3e02      ld      a,#02
// 0dd8  322b4d    ld      (#4d2b),a
// 0ddb  322f4d    ld      (#4d2f),a
// 0dde  3a074d    ld      a,(#4d07)
// 0de1  fe80      cp      #80
// 0de3  c0        ret     nz
// 
// 0de4  3e02      ld      a,#02
// 0de6  32a34d    ld      (#4da3),a
// 0de9  c9        ret     
// 
// 0dea  dd210533  ld      ix,#3305
// 0dee  fd21064d  ld      iy,#4d06
// 0df2  cd0020    call    #2000
// 0df5  22064d    ld      (#4d06),hl
// 0df8  3e03      ld      a,#03
// 0dfa  322b4d    ld      (#4d2b),a
// 0dfd  322f4d    ld      (#4d2f),a
// 0e00  3a064d    ld      a,(#4d06)
// 0e03  fe64      cp      #64
// 0e05  c0        ret     nz
// 
// 0e06  212c2e    ld      hl,#2e2c
// 0e09  22104d    ld      (#4d10),hl
// 0e0c  210001    ld      hl,#0100
// 0e0f  221a4d    ld      (#4d1a),hl
// 0e12  22244d    ld      (#4d24),hl
// 0e15  3e02      ld      a,#02
// 0e17  322b4d    ld      (#4d2b),a
// 0e1a  322f4d    ld      (#4d2f),a
// 0e1d  3e01      ld      a,#01
// 0e1f  32a34d    ld      (#4da3),a
// 0e22  c9        ret     
// 
// 0e23  21c44d    ld      hl,#4dc4
// 0e26  34        inc     (hl)
// 0e27  3e08      ld      a,#08
// 0e29  be        cp      (hl)
// 0e2a  c0        ret     nz
// 
// 0e2b  3600      ld      (hl),#00
// 0e2d  3ac04d    ld      a,(#4dc0)
// 0e30  ee01      xor     #01
// 0e32  32c04d    ld      (#4dc0),a
// 0e35  c9        ret     
// 
// 0e36  3aa64d    ld      a,(#4da6)
// 0e39  a7        and     a
// 0e3a  c0        ret     nz
// 
// 0e3b  3ac14d    ld      a,(#4dc1)
// 0e3e  fe07      cp      #07
// 0e40  c8        ret     z
// 
// 0e41  87        add     a,a
// 0e42  2ac24d    ld      hl,(#4dc2)
// 0e45  23        inc     hl
// 0e46  22c24d    ld      (#4dc2),hl
// 0e49  5f        ld      e,a
// 0e4a  1600      ld      d,#00
// 0e4c  dd21864d  ld      ix,#4d86
// 0e50  dd19      add     ix,de
// 0e52  dd5e00    ld      e,(ix+#00)
// 0e55  dd5601    ld      d,(ix+#01)
// 0e58  a7        and     a
// 0e59  ed52      sbc     hl,de
// 0e5b  c0        ret     nz
// 
// 0e5c  cb3f      srl     a
// 0e5e  3c        inc     a
// 0e5f  32c14d    ld      (#4dc1),a
// 0e62  210101    ld      hl,#0101
// 0e65  22b14d    ld      (#4db1),hl
// 0e68  22b34d    ld      (#4db3),hl
// 0e6b  c9        ret     
// 
// 0e6c  3aa54d    ld      a,(#4da5)
// 0e6f  a7        and     a
// 0e70  2805      jr      z,#0e77         ; (5)
// 0e72  af        xor     a
// 0e73  32ac4e    ld      (#4eac),a
// 0e76  c9        ret     
// 
// 0e77  21ac4e    ld      hl,#4eac
// 0e7a  06e0      ld      b,#e0
// 0e7c  3a0e4e    ld      a,(#4e0e)
// 0e7f  fee4      cp      #e4
// 0e81  3806      jr      c,#0e89         ; (6)
// 0e83  78        ld      a,b
// 0e84  a6        and     (hl)
// 0e85  cbe7      set     4,a
// 0e87  77        ld      (hl),a
// 0e88  c9        ret     
// 
// 0e89  fed4      cp      #d4
// 0e8b  3806      jr      c,#0e93         ; (6)
// 0e8d  78        ld      a,b
// 0e8e  a6        and     (hl)
// 0e8f  cbdf      set     3,a
// 0e91  77        ld      (hl),a
// 0e92  c9        ret     
// 
// 0e93  feb4      cp      #b4
// 0e95  3806      jr      c,#0e9d         ; (6)
// 0e97  78        ld      a,b
// 0e98  a6        and     (hl)
// 0e99  cbd7      set     2,a
// 0e9b  77        ld      (hl),a
// 0e9c  c9        ret     
// 
// 0e9d  fe74      cp      #74
// 0e9f  3806      jr      c,#0ea7         ; (6)
// 0ea1  78        ld      a,b
// 0ea2  a6        and     (hl)
// 0ea3  cbcf      set     1,a
// 0ea5  77        ld      (hl),a
// 0ea6  c9        ret     
// 
// 0ea7  78        ld      a,b
// 0ea8  a6        and     (hl)
// 0ea9  cbc7      set     0,a
// 0eab  77        ld      (hl),a
// 0eac  c9        ret     
// 
// 0ead  3aa54d    ld      a,(#4da5)
// 0eb0  a7        and     a
// 0eb1  c0        ret     nz
// 
// 0eb2  3ad44d    ld      a,(#4dd4)
// 0eb5  a7        and     a
// 0eb6  c0        ret     nz
// 
// 0eb7  3a0e4e    ld      a,(#4e0e)
// 0eba  fe46      cp      #46
// 0ebc  280e      jr      z,#0ecc         ; (14)
// 0ebe  feaa      cp      #aa
// 0ec0  c0        ret     nz
// 
// 0ec1  3a0d4e    ld      a,(#4e0d)
// 0ec4  a7        and     a
// 0ec5  c0        ret     nz
// 
// 0ec6  210d4e    ld      hl,#4e0d
// 0ec9  34        inc     (hl)
// 0eca  1809      jr      #0ed5           ; (9)
// 0ecc  3a0c4e    ld      a,(#4e0c)
// 0ecf  a7        and     a
// 0ed0  c0        ret     nz
// 
// 0ed1  210c4e    ld      hl,#4e0c
// 0ed4  34        inc     (hl)
// 0ed5  219480    ld      hl,#8094
// 0ed8  22d24d    ld      (#4dd2),hl
// 0edb  21fd0e    ld      hl,#0efd
// 0ede  3a134e    ld      a,(#4e13)
// 0ee1  fe14      cp      #14
// 0ee3  3802      jr      c,#0ee7         ; (2)
// 0ee5  3e14      ld      a,#14
// 0ee7  47        ld      b,a
// 0ee8  87        add     a,a
// 0ee9  80        add     a,b
// 0eea  d7        rst     #10
// 0eeb  320c4c    ld      (#4c0c),a
// 0eee  23        inc     hl
// 0eef  7e        ld      a,(hl)
// 0ef0  320d4c    ld      (#4c0d),a
// 0ef3  23        inc     hl
// 0ef4  7e        ld      a,(hl)
// 0ef5  32d44d    ld      (#4dd4),a
// 0ef8  f7        rst     #30
// 0ef9  8a        adc     a,d
// 0efa  04        inc     b
// 0efb  00        nop     
// 0efc  c9        ret     
// 
// 0efd  00        nop     
// 0efe  14        inc     d
// 0eff  0601      ld      b,#01
// 0f01  0f        rrca    
// 0f02  07        rlca    
// 0f03  02        ld      (bc),a
// 0f04  15        dec     d
// 0f05  08        ex      af,af'
// 0f06  02        ld      (bc),a
// 0f07  15        dec     d
// 0f08  08        ex      af,af'
// 0f09  04        inc     b
// 0f0a  14        inc     d
// 0f0b  09        add     hl,bc
// 0f0c  04        inc     b
// 0f0d  14        inc     d
// 0f0e  09        add     hl,bc
// 0f0f  05        dec     b
// 0f10  17        rla     
// 0f11  0a        ld      a,(bc)
// 0f12  05        dec     b
// 0f13  17        rla     
// 0f14  0a        ld      a,(bc)
// 0f15  0609      ld      b,#09
// 0f17  0b        dec     bc
// 0f18  0609      ld      b,#09
// 0f1a  0b        dec     bc
// 0f1b  03        inc     bc
// 0f1c  160c      ld      d,#0c
// 0f1e  03        inc     bc
// 0f1f  160c      ld      d,#0c
// 0f21  07        rlca    
// 0f22  160d      ld      d,#0d
// 0f24  07        rlca    
// 0f25  160d      ld      d,#0d
// 0f27  07        rlca    
// 0f28  160d      ld      d,#0d
// 0f2a  07        rlca    
// 0f2b  160d      ld      d,#0d
// 0f2d  07        rlca    
// 0f2e  160d      ld      d,#0d
// 0f30  07        rlca    
// 0f31  160d      ld      d,#0d
// 0f33  07        rlca    
// 0f34  160d      ld      d,#0d
// 0f36  07        rlca    
// 0f37  160d      ld      d,#0d
// 0f39  07        rlca    
// 0f3a  160d      ld      d,#0d
// 0f3c  00        nop     
// 0f3d  00        nop     
// 0f3e  00        nop     
// 0f3f  00        nop     
// 0f40  00        nop     
// 0f41  00        nop     
// 0f42  00        nop     
// 0f43  00        nop     
// 0f44  00        nop     
// 0f45  00        nop     
// 0f46  00        nop     
// 0f47  00        nop     
// 0f48  00        nop     
// 0f49  00        nop     
// 0f4a  00        nop     
// 0f4b  00        nop     
// 0f4c  00        nop     
// 0f4d  00        nop     
// 0f4e  00        nop     
// 0f4f  00        nop     
// 0f50  00        nop     
// 0f51  00        nop     
// 0f52  00        nop     
// 0f53  00        nop     
// 0f54  00        nop     
// 0f55  00        nop     
// 0f56  00        nop     
// 0f57  00        nop     
// 0f58  00        nop     
// 0f59  00        nop     
// 0f5a  00        nop     
// 0f5b  00        nop     
// 0f5c  00        nop     
// 0f5d  00        nop     
// 0f5e  00        nop     
// 0f5f  00        nop     
// 0f60  00        nop     
// 0f61  00        nop     
// 0f62  00        nop     
// 0f63  00        nop     
// 0f64  00        nop     
// 0f65  00        nop     
// 0f66  00        nop     
// 0f67  00        nop     
// 0f68  00        nop     
// 0f69  00        nop     
// 0f6a  00        nop     
// 0f6b  00        nop     
// 0f6c  00        nop     
// 0f6d  00        nop     
// 0f6e  00        nop     
// 0f6f  00        nop     
// 0f70  00        nop     
// 0f71  00        nop     
// 0f72  00        nop     
// 0f73  00        nop     
// 0f74  00        nop     
// 0f75  00        nop     
// 0f76  00        nop     
// 0f77  00        nop     
// 0f78  00        nop     
// 0f79  00        nop     
// 0f7a  00        nop     
// 0f7b  00        nop     
// 0f7c  00        nop     
// 0f7d  00        nop     
// 0f7e  00        nop     
// 0f7f  00        nop     
// 0f80  00        nop     
// 0f81  00        nop     
// 0f82  00        nop     
// 0f83  00        nop     
// 0f84  00        nop     
// 0f85  00        nop     
// 0f86  00        nop     
// 0f87  00        nop     
// 0f88  00        nop     
// 0f89  00        nop     
// 0f8a  00        nop     
// 0f8b  00        nop     
// 0f8c  00        nop     
// 0f8d  00        nop     
// 0f8e  00        nop     
// 0f8f  00        nop     
// 0f90  00        nop     
// 0f91  00        nop     
// 0f92  00        nop     
// 0f93  00        nop     
// 0f94  00        nop     
// 0f95  00        nop     
// 0f96  00        nop     
// 0f97  00        nop     
// 0f98  00        nop     
// 0f99  00        nop     
// 0f9a  00        nop     
// 0f9b  00        nop     
// 0f9c  00        nop     
// 0f9d  00        nop     
// 0f9e  00        nop     
// 0f9f  00        nop     
// 0fa0  00        nop     
// 0fa1  00        nop     
// 0fa2  00        nop     
// 0fa3  00        nop     
// 0fa4  00        nop     
// 0fa5  00        nop     
// 0fa6  00        nop     
// 0fa7  00        nop     
// 0fa8  00        nop     
// 0fa9  00        nop     
// 0faa  00        nop     
// 0fab  00        nop     
// 0fac  00        nop     
// 0fad  00        nop     
// 0fae  00        nop     
// 0faf  00        nop     
// 0fb0  00        nop     
// 0fb1  00        nop     
// 0fb2  00        nop     
// 0fb3  00        nop     
// 0fb4  00        nop     
// 0fb5  00        nop     
// 0fb6  00        nop     
// 0fb7  00        nop     
// 0fb8  00        nop     
// 0fb9  00        nop     
// 0fba  00        nop     
// 0fbb  00        nop     
// 0fbc  00        nop     
// 0fbd  00        nop     
// 0fbe  00        nop     
// 0fbf  00        nop     
// 0fc0  00        nop     
// 0fc1  00        nop     
// 0fc2  00        nop     
// 0fc3  00        nop     
// 0fc4  00        nop     
// 0fc5  00        nop     
// 0fc6  00        nop     
// 0fc7  00        nop     
// 0fc8  00        nop     
// 0fc9  00        nop     
// 0fca  00        nop     
// 0fcb  00        nop     
// 0fcc  00        nop     
// 0fcd  00        nop     
// 0fce  00        nop     
// 0fcf  00        nop     
// 0fd0  00        nop     
// 0fd1  00        nop     
// 0fd2  00        nop     
// 0fd3  00        nop     
// 0fd4  00        nop     
// 0fd5  00        nop     
// 0fd6  00        nop     
// 0fd7  00        nop     
// 0fd8  00        nop     
// 0fd9  00        nop     
// 0fda  00        nop     
// 0fdb  00        nop     
// 0fdc  00        nop     
// 0fdd  00        nop     
// 0fde  00        nop     
// 0fdf  00        nop     
// 0fe0  00        nop     
// 0fe1  00        nop     
// 0fe2  00        nop     
// 0fe3  00        nop     
// 0fe4  00        nop     
// 0fe5  00        nop     
// 0fe6  00        nop     
// 0fe7  00        nop     
// 0fe8  00        nop     
// 0fe9  00        nop     
// 0fea  00        nop     
// 0feb  00        nop     
// 0fec  00        nop     
// 0fed  00        nop     
// 0fee  00        nop     
// 0fef  00        nop     
// 0ff0  00        nop     
// 0ff1  00        nop     
// 0ff2  00        nop     
// 0ff3  00        nop     
// 0ff4  00        nop     
// 0ff5  00        nop     
// 0ff6  00        nop     
// 0ff7  00        nop     
// 0ff8  00        nop     
// 0ff9  00        nop     
// 0ffa  00        nop     
// 0ffb  00        nop     
// 0ffc  00        nop     
// 0ffd  00        nop     
// 0ffe  48        ld      c,b
// 0fff  36af      ld      (hl),#af
// 1001  32d44d    ld      (#4dd4),a
// 1004  210000    ld      hl,#0000
// 1007  22d24d    ld      (#4dd2),hl
// 100a  c9        ret     
// 
// 100b  ef        rst     #28
// 100c  1c        inc     e
// 100d  9b        sbc     a,e
// 100e  3a004e    ld      a,(#4e00)
// 1011  3d        dec     a
// 1012  c8        ret     z
// 
// 1013  ef        rst     #28
// 1014  1c        inc     e
// 1015  a2        and     d
// 1016  c9        ret     
// 
// 1017  cd9112    call    #1291
// 101a  3aa54d    ld      a,(#4da5)
// 101d  a7        and     a
// 101e  c0        ret     nz
// 
// 101f  cd6610    call    #1066
// 1022  cd9410    call    #1094
// 1025  cd9e10    call    #109e
// 1028  cda810    call    #10a8
// 102b  cdb410    call    #10b4
// 102e  3aa44d    ld      a,(#4da4)
// 1031  a7        and     a
// 1032  ca3910    jp      z,#1039
// 1035  cd3512    call    #1235
// 1038  c9        ret     
// 
// 1039  cd1d17    call    #171d
// 103c  cd8917    call    #1789
// 103f  3aa44d    ld      a,(#4da4)
// 1042  a7        and     a
// 1043  c0        ret     nz
// 
// 1044  cd0618    call    #1806
// 1047  cd361b    call    #1b36
// 104a  cd4b1c    call    #1c4b
// 104d  cd221d    call    #1d22
// 1050  cdf91d    call    #1df9
// 1053  3a044e    ld      a,(#4e04)
// 1056  fe03      cp      #03
// 1058  c0        ret     nz
// 
// 1059  cd7613    call    #1376
// 105c  cd6920    call    #2069
// 105f  cd8c20    call    #208c
// 1062  cdaf20    call    #20af
// 1065  c9        ret     
// 
// 1066  3aab4d    ld      a,(#4dab)
// 1069  a7        and     a
// 106a  c8        ret     z
// 
// 106b  3d        dec     a
// 106c  2008      jr      nz,#1076        ; (8)
// 106e  32ab4d    ld      (#4dab),a
// 1071  3c        inc     a
// 1072  32ac4d    ld      (#4dac),a
// 1075  c9        ret     
// 
// 1076  3d        dec     a
// 1077  2008      jr      nz,#1081        ; (8)
// 1079  32ab4d    ld      (#4dab),a
// 107c  3c        inc     a
// 107d  32ad4d    ld      (#4dad),a
// 1080  c9        ret     
// 
// 1081  3d        dec     a
// 1082  2008      jr      nz,#108c        ; (8)
// 1084  32ab4d    ld      (#4dab),a
// 1087  3c        inc     a
// 1088  32ae4d    ld      (#4dae),a
// 108b  c9        ret     
// 
// 108c  32af4d    ld      (#4daf),a
// 108f  3d        dec     a
// 1090  32ab4d    ld      (#4dab),a
// 1093  c9        ret     
// 
// 1094  3aac4d    ld      a,(#4dac)
// 1097  e7        rst     #20
// 1098  0c        inc     c
// 1099  00        nop     
// 109a  c0        ret     nz
// 
// 109b  10d2      djnz    #106f           ; (-46)
// 109d  103a      djnz    #10d9           ; (58)
// 109f  ad        xor     l
// 10a0  4d        ld      c,l
// 10a1  e7        rst     #20
// 10a2  0c        inc     c
// 10a3  00        nop     
// 10a4  1811      jr      #10b7           ; (17)
// 10a6  2a113a    ld      hl,(#3a11)
// 10a9  ae        xor     (hl)
// 10aa  4d        ld      c,l
// 10ab  e7        rst     #20
// 10ac  0c        inc     c
// 10ad  00        nop     
// 10ae  5c        ld      e,h
// 10af  116e11    ld      de,#116e
// 10b2  8f        adc     a,a
// 10b3  113aaf    ld      de,#af3a
// 10b6  4d        ld      c,l
// 10b7  e7        rst     #20
// 10b8  0c        inc     c
// 10b9  00        nop     
// 10ba  c9        ret     
// 
// 10bb  11db11    ld      de,#11db
// 10be  fc11cd    call    m,#cd11
// 10c1  d8        ret     c
// 
// 10c2  1b        dec     de
// 10c3  2a004d    ld      hl,(#4d00)
// 10c6  116480    ld      de,#8064
// 10c9  a7        and     a
// 10ca  ed52      sbc     hl,de
// 10cc  c0        ret     nz
// 
// 10cd  21ac4d    ld      hl,#4dac
// 10d0  34        inc     (hl)
// 10d1  c9        ret     
// 
// 10d2  dd210133  ld      ix,#3301
// 10d6  fd21004d  ld      iy,#4d00
// 10da  cd0020    call    #2000
// 10dd  22004d    ld      (#4d00),hl
// 10e0  3e01      ld      a,#01
// 10e2  32284d    ld      (#4d28),a
// 10e5  322c4d    ld      (#4d2c),a
// 10e8  3a004d    ld      a,(#4d00)
// 10eb  fe80      cp      #80
// 10ed  c0        ret     nz
// 
// 10ee  212f2e    ld      hl,#2e2f
// 10f1  220a4d    ld      (#4d0a),hl
// 10f4  22314d    ld      (#4d31),hl
// 10f7  af        xor     a
// 10f8  32a04d    ld      (#4da0),a
// 10fb  32ac4d    ld      (#4dac),a
// 10fe  32a74d    ld      (#4da7),a
// 1101  dd21ac4d  ld      ix,#4dac
// 1105  ddb600    or      (ix+#00)
// 1108  ddb601    or      (ix+#01)
// 110b  ddb602    or      (ix+#02)
// 110e  ddb603    or      (ix+#03)
// 1111  c0        ret     nz
// 
// 1112  21ac4e    ld      hl,#4eac
// 1115  cbb6      res     6,(hl)
// 1117  c9        ret     
// 
// 1118  cdaf1c    call    #1caf
// 111b  2a024d    ld      hl,(#4d02)
// 111e  116480    ld      de,#8064
// 1121  a7        and     a
// 1122  ed52      sbc     hl,de
// 1124  c0        ret     nz
// 
// 1125  21ad4d    ld      hl,#4dad
// 1128  34        inc     (hl)
// 1129  c9        ret     
// 
// 112a  dd210133  ld      ix,#3301
// 112e  fd21024d  ld      iy,#4d02
// 1132  cd0020    call    #2000
// 1135  22024d    ld      (#4d02),hl
// 1138  3e01      ld      a,#01
// 113a  32294d    ld      (#4d29),a
// 113d  322d4d    ld      (#4d2d),a
// 1140  3a024d    ld      a,(#4d02)
// 1143  fe80      cp      #80
// 1145  c0        ret     nz
// 
// 1146  212f2e    ld      hl,#2e2f
// 1149  220c4d    ld      (#4d0c),hl
// 114c  22334d    ld      (#4d33),hl
// 114f  af        xor     a
// 1150  32a14d    ld      (#4da1),a
// 1153  32ad4d    ld      (#4dad),a
// 1156  32a84d    ld      (#4da8),a
// 1159  c30111    jp      #1101
// 115c  cd861d    call    #1d86
// 115f  2a044d    ld      hl,(#4d04)
// 1162  116480    ld      de,#8064
// 1165  a7        and     a
// 1166  ed52      sbc     hl,de
// 1168  c0        ret     nz
// 
// 1169  21ae4d    ld      hl,#4dae
// 116c  34        inc     (hl)
// 116d  c9        ret     
// 
// 116e  dd210133  ld      ix,#3301
// 1172  fd21044d  ld      iy,#4d04
// 1176  cd0020    call    #2000
// 1179  22044d    ld      (#4d04),hl
// 117c  3e01      ld      a,#01
// 117e  322a4d    ld      (#4d2a),a
// 1181  322e4d    ld      (#4d2e),a
// 1184  3a044d    ld      a,(#4d04)
// 1187  fe80      cp      #80
// 1189  c0        ret     nz
// 
// 118a  21ae4d    ld      hl,#4dae
// 118d  34        inc     (hl)
// 118e  c9        ret     
// 
// 118f  dd210333  ld      ix,#3303
// 1193  fd21044d  ld      iy,#4d04
// 1197  cd0020    call    #2000
// 119a  22044d    ld      (#4d04),hl
// 119d  3e02      ld      a,#02
// 119f  322a4d    ld      (#4d2a),a
// 11a2  322e4d    ld      (#4d2e),a
// 11a5  3a054d    ld      a,(#4d05)
// 11a8  fe90      cp      #90
// 11aa  c0        ret     nz
// 
// 11ab  212f30    ld      hl,#302f
// 11ae  220e4d    ld      (#4d0e),hl
// 11b1  22354d    ld      (#4d35),hl
// 11b4  3e01      ld      a,#01
// 11b6  322a4d    ld      (#4d2a),a
// 11b9  322e4d    ld      (#4d2e),a
// 11bc  af        xor     a
// 11bd  32a24d    ld      (#4da2),a
// 11c0  32ae4d    ld      (#4dae),a
// 11c3  32a94d    ld      (#4da9),a
// 11c6  c30111    jp      #1101
// 11c9  cd5d1e    call    #1e5d
// 11cc  2a064d    ld      hl,(#4d06)
// 11cf  116480    ld      de,#8064
// 11d2  a7        and     a
// 11d3  ed52      sbc     hl,de
// 11d5  c0        ret     nz
// 
// 11d6  21af4d    ld      hl,#4daf
// 11d9  34        inc     (hl)
// 11da  c9        ret     
// 
// 11db  dd210133  ld      ix,#3301
// 11df  fd21064d  ld      iy,#4d06
// 11e3  cd0020    call    #2000
// 11e6  22064d    ld      (#4d06),hl
// 11e9  3e01      ld      a,#01
// 11eb  322b4d    ld      (#4d2b),a
// 11ee  322f4d    ld      (#4d2f),a
// 11f1  3a064d    ld      a,(#4d06)
// 11f4  fe80      cp      #80
// 11f6  c0        ret     nz
// 
// 11f7  21af4d    ld      hl,#4daf
// 11fa  34        inc     (hl)
// 11fb  c9        ret     
// 
// 11fc  dd21ff32  ld      ix,#32ff
// 1200  fd21064d  ld      iy,#4d06
// 1204  cd0020    call    #2000
// 1207  22064d    ld      (#4d06),hl
// 120a  af        xor     a
// 120b  322b4d    ld      (#4d2b),a
// 120e  322f4d    ld      (#4d2f),a
// 1211  3a074d    ld      a,(#4d07)
// 1214  fe70      cp      #70
// 1216  c0        ret     nz
// 
// 1217  212f2c    ld      hl,#2c2f
// 121a  22104d    ld      (#4d10),hl
// 121d  22374d    ld      (#4d37),hl
// 1220  3e01      ld      a,#01
// 1222  322b4d    ld      (#4d2b),a
// 1225  322f4d    ld      (#4d2f),a
// 1228  af        xor     a
// 1229  32a34d    ld      (#4da3),a
// 122c  32af4d    ld      (#4daf),a
// 122f  32aa4d    ld      (#4daa),a
// 1232  c30111    jp      #1101
// 1235  3ad14d    ld      a,(#4dd1)
// 1238  e7        rst     #20
// 1239  3f        ccf     
// 123a  12        ld      (de),a
// 123b  0c        inc     c
// 123c  00        nop     
// 123d  3f        ccf     
// 123e  12        ld      (de),a
// 123f  21004c    ld      hl,#4c00
// 1242  3aa44d    ld      a,(#4da4)
// 1245  87        add     a,a
// 1246  5f        ld      e,a
// 1247  1600      ld      d,#00
// 1249  19        add     hl,de
// 124a  3ad14d    ld      a,(#4dd1)
// 124d  a7        and     a
// 124e  2027      jr      nz,#1277        ; (39)
// 1250  3ad04d    ld      a,(#4dd0)
// 1253  0627      ld      b,#27
// 1255  80        add     a,b
// 1256  47        ld      b,a
// 1257  3a724e    ld      a,(#4e72)
// 125a  4f        ld      c,a
// 125b  3a094e    ld      a,(#4e09)
// 125e  a1        and     c
// 125f  2804      jr      z,#1265         ; (4)
// 1261  cbf0      set     6,b
// 1263  cbf8      set     7,b
// 1265  70        ld      (hl),b
// 1266  23        inc     hl
// 1267  3618      ld      (hl),#18
// 1269  3e00      ld      a,#00
// 126b  320b4c    ld      (#4c0b),a
// 126e  f7        rst     #30
// 126f  4a        ld      c,d
// 1270  03        inc     bc
// 1271  00        nop     
// 1272  21d14d    ld      hl,#4dd1
// 1275  34        inc     (hl)
// 1276  c9        ret     
// 
// 1277  3620      ld      (hl),#20
// 1279  3e09      ld      a,#09
// 127b  320b4c    ld      (#4c0b),a
// 127e  3aa44d    ld      a,(#4da4)
// 1281  32ab4d    ld      (#4dab),a
// 1284  af        xor     a
// 1285  32a44d    ld      (#4da4),a
// 1288  32d14d    ld      (#4dd1),a
// 128b  21ac4e    ld      hl,#4eac
// 128e  cbf6      set     6,(hl)
// 1290  c9        ret     
// 
// 1291  3aa54d    ld      a,(#4da5)
// 1294  e7        rst     #20
// 1295  0c        inc     c
// 1296  00        nop     
// 1297  b7        or      a
// 1298  12        ld      (de),a
// 1299  b7        or      a
// 129a  12        ld      (de),a
// 129b  b7        or      a
// 129c  12        ld      (de),a
// 129d  b7        or      a
// 129e  12        ld      (de),a
// 129f  cb12      rl      d
// 12a1  f9        ld      sp,hl
// 12a2  12        ld      (de),a
// 12a3  0613      ld      b,#13
// 12a5  0e13      ld      c,#13
// 12a7  1613      ld      d,#13
// 12a9  1e13      ld      e,#13
// 12ab  2613      ld      h,#13
// 12ad  2e13      ld      l,#13
// 12af  3613      ld      (hl),#13
// 12b1  3e13      ld      a,#13
// 12b3  46        ld      b,(hl)
// 12b4  13        inc     de
// 12b5  53        ld      d,e
// 12b6  13        inc     de
// 12b7  2ac54d    ld      hl,(#4dc5)
// 12ba  23        inc     hl
// 12bb  22c54d    ld      (#4dc5),hl
// 12be  117800    ld      de,#0078
// 12c1  a7        and     a
// 12c2  ed52      sbc     hl,de
// 12c4  c0        ret     nz
// 
// 12c5  3e05      ld      a,#05
// 12c7  32a54d    ld      (#4da5),a
// 12ca  c9        ret     
// 
// 12cb  210000    ld      hl,#0000
// 12ce  cd7e26    call    #267e
// 12d1  3e34      ld      a,#34
// 12d3  11b400    ld      de,#00b4
// 12d6  4f        ld      c,a
// 12d7  3a724e    ld      a,(#4e72)
// 12da  47        ld      b,a
// 12db  3a094e    ld      a,(#4e09)
// 12de  a0        and     b
// 12df  2804      jr      z,#12e5         ; (4)
// 12e1  3ec0      ld      a,#c0
// 12e3  b1        or      c
// 12e4  4f        ld      c,a
// 12e5  79        ld      a,c
// 12e6  320a4c    ld      (#4c0a),a
// 12e9  2ac54d    ld      hl,(#4dc5)
// 12ec  23        inc     hl
// 12ed  22c54d    ld      (#4dc5),hl
// 12f0  a7        and     a
// 12f1  ed52      sbc     hl,de
// 12f3  c0        ret     nz
// 
// 12f4  21a54d    ld      hl,#4da5
// 12f7  34        inc     (hl)
// 12f8  c9        ret     
// 
// 12f9  21bc4e    ld      hl,#4ebc
// 12fc  cbe6      set     4,(hl)
// 12fe  3e35      ld      a,#35
// 1300  11c300    ld      de,#00c3
// 1303  c3d612    jp      #12d6
// 1306  3e36      ld      a,#36
// 1308  11d200    ld      de,#00d2
// 130b  c3d612    jp      #12d6
// 130e  3e37      ld      a,#37
// 1310  11e100    ld      de,#00e1
// 1313  c3d612    jp      #12d6
// 1316  3e38      ld      a,#38
// 1318  11f000    ld      de,#00f0
// 131b  c3d612    jp      #12d6
// 131e  3e39      ld      a,#39
// 1320  11ff00    ld      de,#00ff
// 1323  c3d612    jp      #12d6
// 1326  3e3a      ld      a,#3a
// 1328  110e01    ld      de,#010e
// 132b  c3d612    jp      #12d6
// 132e  3e3b      ld      a,#3b
// 1330  111d01    ld      de,#011d
// 1333  c3d612    jp      #12d6
// 1336  3e3c      ld      a,#3c
// 1338  112c01    ld      de,#012c
// 133b  c3d612    jp      #12d6
// 133e  3e3d      ld      a,#3d
// 1340  113b01    ld      de,#013b
// 1343  c3d612    jp      #12d6
// 1346  21bc4e    ld      hl,#4ebc
// 1349  3620      ld      (hl),#20
// 134b  3e3e      ld      a,#3e
// 134d  115901    ld      de,#0159
// 1350  c3d612    jp      #12d6
// 1353  3e3f      ld      a,#3f
// 1355  320a4c    ld      (#4c0a),a
// 1358  2ac54d    ld      hl,(#4dc5)
// 135b  23        inc     hl
// 135c  22c54d    ld      (#4dc5),hl
// 135f  11b801    ld      de,#01b8
// 1362  a7        and     a
// 1363  ed52      sbc     hl,de
// 1365  c0        ret     nz
// 
// 1366  21144e    ld      hl,#4e14
// 1369  35        dec     (hl)
// 136a  21154e    ld      hl,#4e15
// 136d  35        dec     (hl)
// 136e  cd7526    call    #2675
// 1371  21044e    ld      hl,#4e04
// 1374  34        inc     (hl)
// 1375  c9        ret     
// 
// 1376  3aa64d    ld      a,(#4da6)
// 1379  a7        and     a
// 137a  c8        ret     z
// 
// 137b  dd21a74d  ld      ix,#4da7
// 137f  dd7e00    ld      a,(ix+#00)
// 1382  ddb601    or      (ix+#01)
// 1385  ddb602    or      (ix+#02)
// 1388  ddb603    or      (ix+#03)
// 138b  ca9813    jp      z,#1398
// 138e  2acb4d    ld      hl,(#4dcb)
// 1391  2b        dec     hl
// 1392  22cb4d    ld      (#4dcb),hl
// 1395  7c        ld      a,h
// 1396  b5        or      l
// 1397  c0        ret     nz
// 
// 1398  210b4c    ld      hl,#4c0b
// 139b  3609      ld      (hl),#09
// 139d  3aac4d    ld      a,(#4dac)
// 13a0  a7        and     a
// 13a1  c2a713    jp      nz,#13a7
// 13a4  32a74d    ld      (#4da7),a
// 13a7  3aad4d    ld      a,(#4dad)
// 13aa  a7        and     a
// 13ab  c2b113    jp      nz,#13b1
// 13ae  32a84d    ld      (#4da8),a
// 13b1  3aae4d    ld      a,(#4dae)
// 13b4  a7        and     a
// 13b5  c2bb13    jp      nz,#13bb
// 13b8  32a94d    ld      (#4da9),a
// 13bb  3aaf4d    ld      a,(#4daf)
// 13be  a7        and     a
// 13bf  c2c513    jp      nz,#13c5
// 13c2  32aa4d    ld      (#4daa),a
// 13c5  af        xor     a
// 13c6  32cb4d    ld      (#4dcb),a
// 13c9  32cc4d    ld      (#4dcc),a
// 13cc  32a64d    ld      (#4da6),a
// 13cf  32c84d    ld      (#4dc8),a
// 13d2  32d04d    ld      (#4dd0),a
// 13d5  21ac4e    ld      hl,#4eac
// 13d8  cbae      res     5,(hl)
// 13da  cbbe      res     7,(hl)
// 13dc  c9        ret     
// 
// 13dd  219e4d    ld      hl,#4d9e
// 13e0  3a0e4e    ld      a,(#4e0e)
// 13e3  be        cp      (hl)
// 13e4  caee13    jp      z,#13ee
// 13e7  210000    ld      hl,#0000
// 13ea  22974d    ld      (#4d97),hl
// 13ed  c9        ret     
// 
// 13ee  2a974d    ld      hl,(#4d97)
// 13f1  23        inc     hl
// 13f2  22974d    ld      (#4d97),hl
// 13f5  ed5b954d  ld      de,(#4d95)
// 13f9  a7        and     a
// 13fa  ed52      sbc     hl,de
// 13fc  c0        ret     nz
// 
// 13fd  210000    ld      hl,#0000
// 1400  22974d    ld      (#4d97),hl
// 1403  3aa14d    ld      a,(#4da1)
// 1406  a7        and     a
// 1407  f5        push    af
// 1408  cc8620    call    z,#2086
// 140b  f1        pop     af
// 140c  c8        ret     z
// 
// 140d  3aa24d    ld      a,(#4da2)
// 1410  a7        and     a
// 1411  f5        push    af
// 1412  cca920    call    z,#20a9
// 1415  f1        pop     af
// 1416  c8        ret     z
// 
// 1417  3aa34d    ld      a,(#4da3)
// 141a  a7        and     a
// 141b  ccd120    call    z,#20d1
// 141e  c9        ret     
// 
// 141f  3a724e    ld      a,(#4e72)
// 1422  47        ld      b,a
// 1423  3a094e    ld      a,(#4e09)
// 1426  a0        and     b
// 1427  c8        ret     z
// 
// 1428  47        ld      b,a
// 1429  dd21004c  ld      ix,#4c00
// 142d  1e08      ld      e,#08
// 142f  0e08      ld      c,#08
// 1431  1607      ld      d,#07
// 1433  3a004d    ld      a,(#4d00)
// 1436  83        add     a,e
// 1437  dd7713    ld      (ix+#13),a
// 143a  3a014d    ld      a,(#4d01)
// 143d  2f        cpl     
// 143e  82        add     a,d
// 143f  dd7712    ld      (ix+#12),a
// 1442  3a024d    ld      a,(#4d02)
// 1445  83        add     a,e
// 1446  dd7715    ld      (ix+#15),a
// 1449  3a034d    ld      a,(#4d03)
// 144c  2f        cpl     
// 144d  82        add     a,d
// 144e  dd7714    ld      (ix+#14),a
// 1451  3a044d    ld      a,(#4d04)
// 1454  83        add     a,e
// 1455  dd7717    ld      (ix+#17),a
// 1458  3a054d    ld      a,(#4d05)
// 145b  2f        cpl     
// 145c  81        add     a,c
// 145d  dd7716    ld      (ix+#16),a
// 1460  3a064d    ld      a,(#4d06)
// 1463  83        add     a,e
// 1464  dd7719    ld      (ix+#19),a
// 1467  3a074d    ld      a,(#4d07)
// 146a  2f        cpl     
// 146b  81        add     a,c
// 146c  dd7718    ld      (ix+#18),a
// 146f  3a084d    ld      a,(#4d08)
// 1472  83        add     a,e
// 1473  dd771b    ld      (ix+#1b),a
// 1476  3a094d    ld      a,(#4d09)
// 1479  2f        cpl     
// 147a  81        add     a,c
// 147b  dd771a    ld      (ix+#1a),a
// 147e  3ad24d    ld      a,(#4dd2)
// 1481  83        add     a,e
// 1482  dd771d    ld      (ix+#1d),a
// 1485  3ad34d    ld      a,(#4dd3)
// 1488  2f        cpl     
// 1489  81        add     a,c
// 148a  dd771c    ld      (ix+#1c),a
// 148d  c3fe14    jp      #14fe
// 1490  3a724e    ld      a,(#4e72)
// 1493  47        ld      b,a
// 1494  3a094e    ld      a,(#4e09)
// 1497  a0        and     b
// 1498  c0        ret     nz
// 
// 1499  47        ld      b,a
// 149a  1e09      ld      e,#09
// 149c  0e07      ld      c,#07
// 149e  1606      ld      d,#06
// 14a0  dd21004c  ld      ix,#4c00
// 14a4  3a004d    ld      a,(#4d00)
// 14a7  2f        cpl     
// 14a8  83        add     a,e
// 14a9  dd7713    ld      (ix+#13),a
// 14ac  3a014d    ld      a,(#4d01)
// 14af  82        add     a,d
// 14b0  dd7712    ld      (ix+#12),a
// 14b3  3a024d    ld      a,(#4d02)
// 14b6  2f        cpl     
// 14b7  83        add     a,e
// 14b8  dd7715    ld      (ix+#15),a
// 14bb  3a034d    ld      a,(#4d03)
// 14be  82        add     a,d
// 14bf  dd7714    ld      (ix+#14),a
// 14c2  3a044d    ld      a,(#4d04)
// 14c5  2f        cpl     
// 14c6  83        add     a,e
// 14c7  dd7717    ld      (ix+#17),a
// 14ca  3a054d    ld      a,(#4d05)
// 14cd  81        add     a,c
// 14ce  dd7716    ld      (ix+#16),a
// 14d1  3a064d    ld      a,(#4d06)
// 14d4  2f        cpl     
// 14d5  83        add     a,e
// 14d6  dd7719    ld      (ix+#19),a
// 14d9  3a074d    ld      a,(#4d07)
// 14dc  81        add     a,c
// 14dd  dd7718    ld      (ix+#18),a
// 14e0  3a084d    ld      a,(#4d08)
// 14e3  2f        cpl     
// 14e4  83        add     a,e
// 14e5  dd771b    ld      (ix+#1b),a
// 14e8  3a094d    ld      a,(#4d09)
// 14eb  81        add     a,c
// 14ec  dd771a    ld      (ix+#1a),a
// 14ef  3ad24d    ld      a,(#4dd2)
// 14f2  2f        cpl     
// 14f3  83        add     a,e
// 14f4  dd771d    ld      (ix+#1d),a
// 14f7  3ad34d    ld      a,(#4dd3)
// 14fa  81        add     a,c
// 14fb  dd771c    ld      (ix+#1c),a
// 14fe  3aa54d    ld      a,(#4da5)
// 1501  a7        and     a
// 1502  c24b15    jp      nz,#154b
// 1505  3aa44d    ld      a,(#4da4)
// 1508  a7        and     a
// 1509  c2b415    jp      nz,#15b4
// 150c  211c15    ld      hl,#151c
// 150f  e5        push    hl
// 1510  3a304d    ld      a,(#4d30)
// 1513  e7        rst     #20
// 1514  8c        adc     a,h
// 1515  16b1      ld      d,#b1
// 1517  16d6      ld      d,#d6
// 1519  16f7      ld      d,#f7
// 151b  1678      ld      d,#78
// 151d  a7        and     a
// 151e  282b      jr      z,#154b         ; (43)
// 1520  0ec0      ld      c,#c0
// 1522  3a0a4c    ld      a,(#4c0a)
// 1525  57        ld      d,a
// 1526  a1        and     c
// 1527  2005      jr      nz,#152e        ; (5)
// 1529  7a        ld      a,d
// 152a  b1        or      c
// 152b  c34815    jp      #1548
// 152e  3a304d    ld      a,(#4d30)
// 1531  fe02      cp      #02
// 1533  2009      jr      nz,#153e        ; (9)
// 1535  cb7a      bit     7,d
// 1537  2812      jr      z,#154b         ; (18)
// 1539  7a        ld      a,d
// 153a  a9        xor     c
// 153b  c34815    jp      #1548
// 153e  fe03      cp      #03
// 1540  2009      jr      nz,#154b        ; (9)
// 1542  cb72      bit     6,d
// 1544  2805      jr      z,#154b         ; (5)
// 1546  7a        ld      a,d
// 1547  a9        xor     c
// 1548  320a4c    ld      (#4c0a),a
// 154b  21c04d    ld      hl,#4dc0
// 154e  56        ld      d,(hl)
// 154f  3e1c      ld      a,#1c
// 1551  82        add     a,d
// 1552  dd7702    ld      (ix+#02),a
// 1555  dd7704    ld      (ix+#04),a
// 1558  dd7706    ld      (ix+#06),a
// 155b  dd7708    ld      (ix+#08),a
// 155e  0e20      ld      c,#20
// 1560  3aac4d    ld      a,(#4dac)
// 1563  a7        and     a
// 1564  2006      jr      nz,#156c        ; (6)
// 1566  3aa74d    ld      a,(#4da7)
// 1569  a7        and     a
// 156a  2009      jr      nz,#1575        ; (9)
// 156c  3a2c4d    ld      a,(#4d2c)
// 156f  87        add     a,a
// 1570  82        add     a,d
// 1571  81        add     a,c
// 1572  dd7702    ld      (ix+#02),a
// 1575  3aad4d    ld      a,(#4dad)
// 1578  a7        and     a
// 1579  2006      jr      nz,#1581        ; (6)
// 157b  3aa84d    ld      a,(#4da8)
// 157e  a7        and     a
// 157f  2009      jr      nz,#158a        ; (9)
// 1581  3a2d4d    ld      a,(#4d2d)
// 1584  87        add     a,a
// 1585  82        add     a,d
// 1586  81        add     a,c
// 1587  dd7704    ld      (ix+#04),a
// 158a  3aae4d    ld      a,(#4dae)
// 158d  a7        and     a
// 158e  2006      jr      nz,#1596        ; (6)
// 1590  3aa94d    ld      a,(#4da9)
// 1593  a7        and     a
// 1594  2009      jr      nz,#159f        ; (9)
// 1596  3a2e4d    ld      a,(#4d2e)
// 1599  87        add     a,a
// 159a  82        add     a,d
// 159b  81        add     a,c
// 159c  dd7706    ld      (ix+#06),a
// 159f  3aaf4d    ld      a,(#4daf)
// 15a2  a7        and     a
// 15a3  2006      jr      nz,#15ab        ; (6)
// 15a5  3aaa4d    ld      a,(#4daa)
// 15a8  a7        and     a
// 15a9  2009      jr      nz,#15b4        ; (9)
// 15ab  3a2f4d    ld      a,(#4d2f)
// 15ae  87        add     a,a
// 15af  82        add     a,d
// 15b0  81        add     a,c
// 15b1  dd7708    ld      (ix+#08),a
// 15b4  cde615    call    #15e6
// 15b7  cd2d16    call    #162d
// 15ba  cd5216    call    #1652
// 15bd  78        ld      a,b
// 15be  a7        and     a
// 15bf  c8        ret     z
// 
// 15c0  0ec0      ld      c,#c0
// 15c2  3a024c    ld      a,(#4c02)
// 15c5  b1        or      c
// 15c6  32024c    ld      (#4c02),a
// 15c9  3a044c    ld      a,(#4c04)
// 15cc  b1        or      c
// 15cd  32044c    ld      (#4c04),a
// 15d0  3a064c    ld      a,(#4c06)
// 15d3  b1        or      c
// 15d4  32064c    ld      (#4c06),a
// 15d7  3a084c    ld      a,(#4c08)
// 15da  b1        or      c
// 15db  32084c    ld      (#4c08),a
// 15de  3a0c4c    ld      a,(#4c0c)
// 15e1  b1        or      c
// 15e2  320c4c    ld      (#4c0c),a
// 15e5  c9        ret     
// 
// 15e6  3a064e    ld      a,(#4e06)
// 15e9  d605      sub     #05
// 15eb  d8        ret     c
// 
// 15ec  3a094d    ld      a,(#4d09)
// 15ef  e60f      and     #0f
// 15f1  fe0c      cp      #0c
// 15f3  3804      jr      c,#15f9         ; (4)
// 15f5  1618      ld      d,#18
// 15f7  1812      jr      #160b           ; (18)
// 15f9  fe08      cp      #08
// 15fb  3804      jr      c,#1601         ; (4)
// 15fd  1614      ld      d,#14
// 15ff  180a      jr      #160b           ; (10)
// 1601  fe04      cp      #04
// 1603  3804      jr      c,#1609         ; (4)
// 1605  1610      ld      d,#10
// 1607  1802      jr      #160b           ; (2)
// 1609  1614      ld      d,#14
// 160b  dd7204    ld      (ix+#04),d
// 160e  14        inc     d
// 160f  dd7206    ld      (ix+#06),d
// 1612  14        inc     d
// 1613  dd7208    ld      (ix+#08),d
// 1616  14        inc     d
// 1617  dd720c    ld      (ix+#0c),d
// 161a  dd360a3f  ld      (ix+#0a),#3f
// 161e  1616      ld      d,#16
// 1620  dd7205    ld      (ix+#05),d
// 1623  dd7207    ld      (ix+#07),d
// 1626  dd7209    ld      (ix+#09),d
// 1629  dd720d    ld      (ix+#0d),d
// 162c  c9        ret     
// 
// 162d  3a074e    ld      a,(#4e07)
// 1630  a7        and     a
// 1631  c8        ret     z
// 
// 1632  57        ld      d,a
// 1633  3a3a4d    ld      a,(#4d3a)
// 1636  d63d      sub     #3d
// 1638  2004      jr      nz,#163e        ; (4)
// 163a  dd360b00  ld      (ix+#0b),#00
// 163e  7a        ld      a,d
// 163f  fe0a      cp      #0a
// 1641  d8        ret     c
// 
// 1642  dd360232  ld      (ix+#02),#32
// 1646  dd36031d  ld      (ix+#03),#1d
// 164a  fe0c      cp      #0c
// 164c  d8        ret     c
// 
// 164d  dd360233  ld      (ix+#02),#33
// 1651  c9        ret     
// 
// 1652  3a084e    ld      a,(#4e08)
// 1655  a7        and     a
// 1656  c8        ret     z
// 
// 1657  57        ld      d,a
// 1658  3a3a4d    ld      a,(#4d3a)
// 165b  d63d      sub     #3d
// 165d  2004      jr      nz,#1663        ; (4)
// 165f  dd360b00  ld      (ix+#0b),#00
// 1663  7a        ld      a,d
// 1664  fe01      cp      #01
// 1666  d8        ret     c
// 
// 1667  3ac04d    ld      a,(#4dc0)
// 166a  1e08      ld      e,#08
// 166c  83        add     a,e
// 166d  dd7702    ld      (ix+#02),a
// 1670  7a        ld      a,d
// 1671  fe03      cp      #03
// 1673  d8        ret     c
// 
// 1674  3a014d    ld      a,(#4d01)
// 1677  e608      and     #08
// 1679  0f        rrca    
// 167a  0f        rrca    
// 167b  0f        rrca    
// 167c  1e0a      ld      e,#0a
// 167e  83        add     a,e
// 167f  dd770c    ld      (ix+#0c),a
// 1682  3c        inc     a
// 1683  3c        inc     a
// 1684  dd7702    ld      (ix+#02),a
// 1687  dd360d1e  ld      (ix+#0d),#1e
// 168b  c9        ret     
// 
// 168c  3a094d    ld      a,(#4d09)
// 168f  e607      and     #07
// 1691  fe06      cp      #06
// 1693  3805      jr      c,#169a         ; (5)
// 1695  dd360a30  ld      (ix+#0a),#30
// 1699  c9        ret     
// 
// 169a  fe04      cp      #04
// 169c  3805      jr      c,#16a3         ; (5)
// 169e  dd360a2e  ld      (ix+#0a),#2e
// 16a2  c9        ret     
// 
// 16a3  fe02      cp      #02
// 16a5  3805      jr      c,#16ac         ; (5)
// 16a7  dd360a2c  ld      (ix+#0a),#2c
// 16ab  c9        ret     
// 
// 16ac  dd360a2e  ld      (ix+#0a),#2e
// 16b0  c9        ret     
// 
// 16b1  3a084d    ld      a,(#4d08)
// 16b4  e607      and     #07
// 16b6  fe06      cp      #06
// 16b8  3805      jr      c,#16bf         ; (5)
// 16ba  dd360a2f  ld      (ix+#0a),#2f
// 16be  c9        ret     
// 
// 16bf  fe04      cp      #04
// 16c1  3805      jr      c,#16c8         ; (5)
// 16c3  dd360a2d  ld      (ix+#0a),#2d
// 16c7  c9        ret     
// 
// 16c8  fe02      cp      #02
// 16ca  3805      jr      c,#16d1         ; (5)
// 16cc  dd360a2f  ld      (ix+#0a),#2f
// 16d0  c9        ret     
// 
// 16d1  dd360a30  ld      (ix+#0a),#30
// 16d5  c9        ret     
// 
// 16d6  3a094d    ld      a,(#4d09)
// 16d9  e607      and     #07
// 16db  fe06      cp      #06
// 16dd  3808      jr      c,#16e7         ; (8)
// 16df  1e2e      ld      e,#2e
// 16e1  cbfb      set     7,e
// 16e3  dd730a    ld      (ix+#0a),e
// 16e6  c9        ret     
// 
// 16e7  fe04      cp      #04
// 16e9  3804      jr      c,#16ef         ; (4)
// 16eb  1e2c      ld      e,#2c
// 16ed  18f2      jr      #16e1           ; (-14)
// 16ef  fe02      cp      #02
// 16f1  30ec      jr      nc,#16df        ; (-20)
// 16f3  1e30      ld      e,#30
// 16f5  18ea      jr      #16e1           ; (-22)
// 16f7  3a084d    ld      a,(#4d08)
// 16fa  e607      and     #07
// 16fc  fe06      cp      #06
// 16fe  3805      jr      c,#1705         ; (5)
// 1700  dd360a30  ld      (ix+#0a),#30
// 1704  c9        ret     
// 
// 1705  fe04      cp      #04
// 1707  3808      jr      c,#1711         ; (8)
// 1709  1e2f      ld      e,#2f
// 170b  cbf3      set     6,e
// 170d  dd730a    ld      (ix+#0a),e
// 1710  c9        ret     
// 
// 1711  fe02      cp      #02
// 1713  3804      jr      c,#1719         ; (4)
// 1715  1e2d      ld      e,#2d
// 1717  18f2      jr      #170b           ; (-14)
// 1719  1e2f      ld      e,#2f
// 171b  18ee      jr      #170b           ; (-18)
// 171d  0604      ld      b,#04
// 171f  ed5b394d  ld      de,(#4d39)
// 1723  3aaf4d    ld      a,(#4daf)
// 1726  a7        and     a
// 1727  2009      jr      nz,#1732        ; (9)
// 1729  2a374d    ld      hl,(#4d37)
// 172c  a7        and     a
// 172d  ed52      sbc     hl,de
// 172f  ca6317    jp      z,#1763
// 1732  05        dec     b
// 1733  3aae4d    ld      a,(#4dae)
// 1736  a7        and     a
// 1737  2009      jr      nz,#1742        ; (9)
// 1739  2a354d    ld      hl,(#4d35)
// 173c  a7        and     a
// 173d  ed52      sbc     hl,de
// 173f  ca6317    jp      z,#1763
// 1742  05        dec     b
// 1743  3aad4d    ld      a,(#4dad)
// 1746  a7        and     a
// 1747  2009      jr      nz,#1752        ; (9)
// 1749  2a334d    ld      hl,(#4d33)
// 174c  a7        and     a
// 174d  ed52      sbc     hl,de
// 174f  ca6317    jp      z,#1763
// 1752  05        dec     b
// 1753  3aac4d    ld      a,(#4dac)
// 1756  a7        and     a
// 1757  2009      jr      nz,#1762        ; (9)
// 1759  2a314d    ld      hl,(#4d31)
// 175c  a7        and     a
// 175d  ed52      sbc     hl,de
// 175f  ca6317    jp      z,#1763
// 1762  05        dec     b
// 1763  78        ld      a,b
// 1764  32a44d    ld      (#4da4),a
// 1767  32a54d    ld      (#4da5),a
// 176a  a7        and     a
// 176b  c8        ret     z
// 
// 176c  21a64d    ld      hl,#4da6
// 176f  5f        ld      e,a
// 1770  1600      ld      d,#00
// 1772  19        add     hl,de
// 1773  7e        ld      a,(hl)
// 1774  a7        and     a
// 1775  c8        ret     z
// 
// 1776  af        xor     a
// 1777  32a54d    ld      (#4da5),a
// 177a  21d04d    ld      hl,#4dd0
// 177d  34        inc     (hl)
// 177e  46        ld      b,(hl)
// 177f  04        inc     b
// 1780  cd5a2a    call    #2a5a
// 1783  21bc4e    ld      hl,#4ebc
// 1786  cbde      set     3,(hl)
// 1788  c9        ret     
// 
// 1789  3aa44d    ld      a,(#4da4)
// 178c  a7        and     a
// 178d  c0        ret     nz
// 
// 178e  3aa64d    ld      a,(#4da6)
// 1791  a7        and     a
// 1792  c8        ret     z
// 
// 1793  0e04      ld      c,#04
// 1795  0604      ld      b,#04
// 1797  dd21084d  ld      ix,#4d08
// 179b  3aaf4d    ld      a,(#4daf)
// 179e  a7        and     a
// 179f  2013      jr      nz,#17b4        ; (19)
// 17a1  3a064d    ld      a,(#4d06)
// 17a4  dd9600    sub     (ix+#00)
// 17a7  b9        cp      c
// 17a8  300a      jr      nc,#17b4        ; (10)
// 17aa  3a074d    ld      a,(#4d07)
// 17ad  dd9601    sub     (ix+#01)
// 17b0  b9        cp      c
// 17b1  da6317    jp      c,#1763
// 17b4  05        dec     b
// 17b5  3aae4d    ld      a,(#4dae)
// 17b8  a7        and     a
// 17b9  2013      jr      nz,#17ce        ; (19)
// 17bb  3a044d    ld      a,(#4d04)
// 17be  dd9600    sub     (ix+#00)
// 17c1  b9        cp      c
// 17c2  300a      jr      nc,#17ce        ; (10)
// 17c4  3a054d    ld      a,(#4d05)
// 17c7  dd9601    sub     (ix+#01)
// 17ca  b9        cp      c
// 17cb  da6317    jp      c,#1763
// 17ce  05        dec     b
// 17cf  3aad4d    ld      a,(#4dad)
// 17d2  a7        and     a
// 17d3  2013      jr      nz,#17e8        ; (19)
// 17d5  3a024d    ld      a,(#4d02)
// 17d8  dd9600    sub     (ix+#00)
// 17db  b9        cp      c
// 17dc  300a      jr      nc,#17e8        ; (10)
// 17de  3a034d    ld      a,(#4d03)
// 17e1  dd9601    sub     (ix+#01)
// 17e4  b9        cp      c
// 17e5  da6317    jp      c,#1763
// 17e8  05        dec     b
// 17e9  3aac4d    ld      a,(#4dac)
// 17ec  a7        and     a
// 17ed  2013      jr      nz,#1802        ; (19)
// 17ef  3a004d    ld      a,(#4d00)
// 17f2  dd9600    sub     (ix+#00)
// 17f5  b9        cp      c
// 17f6  300a      jr      nc,#1802        ; (10)
// 17f8  3a014d    ld      a,(#4d01)
// 17fb  dd9601    sub     (ix+#01)
// 17fe  b9        cp      c
// 17ff  da6317    jp      c,#1763
// 1802  05        dec     b
// 1803  c36317    jp      #1763
// 1806  219d4d    ld      hl,#4d9d
// 1809  3eff      ld      a,#ff
// 180b  be        cp      (hl)
// 180c  ca1118    jp      z,#1811
// 180f  35        dec     (hl)
// 1810  c9        ret     
// 
// 1811  3aa64d    ld      a,(#4da6)
// 1814  a7        and     a
// 1815  ca2f18    jp      z,#182f
// 1818  2a4c4d    ld      hl,(#4d4c)
// 181b  29        add     hl,hl
// 181c  224c4d    ld      (#4d4c),hl
// 181f  2a4a4d    ld      hl,(#4d4a)
// 1822  ed6a      adc     hl,hl
// 1824  224a4d    ld      (#4d4a),hl
// 1827  d0        ret     nc
// 
// 1828  214c4d    ld      hl,#4d4c
// 182b  34        inc     (hl)
// 182c  c34318    jp      #1843
// 182f  2a484d    ld      hl,(#4d48)
// 1832  29        add     hl,hl
// 1833  22484d    ld      (#4d48),hl
// 1836  2a464d    ld      hl,(#4d46)
// 1839  ed6a      adc     hl,hl
// 183b  22464d    ld      (#4d46),hl
// 183e  d0        ret     nc
// 
// 183f  21484d    ld      hl,#4d48
// 1842  34        inc     (hl)
// 1843  3a0e4e    ld      a,(#4e0e)
// 1846  329e4d    ld      (#4d9e),a
// 1849  3a724e    ld      a,(#4e72)
// 184c  4f        ld      c,a
// 184d  3a094e    ld      a,(#4e09)
// 1850  a1        and     c
// 1851  4f        ld      c,a
// 1852  213a4d    ld      hl,#4d3a
// 1855  7e        ld      a,(hl)
// 1856  0621      ld      b,#21
// 1858  90        sub     b
// 1859  3809      jr      c,#1864         ; (9)
// 185b  7e        ld      a,(hl)
// 185c  063b      ld      b,#3b
// 185e  90        sub     b
// 185f  3003      jr      nc,#1864        ; (3)
// 1861  c3ab18    jp      #18ab
// 1864  3e01      ld      a,#01
// 1866  32bf4d    ld      (#4dbf),a
// 1869  3a004e    ld      a,(#4e00)
// 186c  fe01      cp      #01
// 186e  ca191a    jp      z,#1a19
// 1871  3a044e    ld      a,(#4e04)
// 1874  fe10      cp      #10
// 1876  d2191a    jp      nc,#1a19
// 1879  79        ld      a,c
// 187a  a7        and     a
// 187b  2806      jr      z,#1883         ; (6)
// 187d  3a4050    ld      a,(#5040)
// 1880  c38618    jp      #1886
// 1883  3a0050    ld      a,(#5000)
// 1886  cb4f      bit     1,a
// 1888  c29918    jp      nz,#1899
// 188b  2a0333    ld      hl,(#3303)
// 188e  3e02      ld      a,#02
// 1890  32304d    ld      (#4d30),a
// 1893  221c4d    ld      (#4d1c),hl
// 1896  c35019    jp      #1950
// 1899  cb57      bit     2,a
// 189b  c25019    jp      nz,#1950
// 189e  2aff32    ld      hl,(#32ff)
// 18a1  af        xor     a
// 18a2  32304d    ld      (#4d30),a
// 18a5  221c4d    ld      (#4d1c),hl
// 18a8  c35019    jp      #1950
// 18ab  3a004e    ld      a,(#4e00)
// 18ae  fe01      cp      #01
// 18b0  ca191a    jp      z,#1a19
// 18b3  3a044e    ld      a,(#4e04)
// 18b6  fe10      cp      #10
// 18b8  d2191a    jp      nc,#1a19
// 18bb  79        ld      a,c
// 18bc  a7        and     a
// 18bd  2806      jr      z,#18c5         ; (6)
// 18bf  3a4050    ld      a,(#5040)
// 18c2  c3c818    jp      #18c8
// 18c5  3a0050    ld      a,(#5000)
// 18c8  cb4f      bit     1,a
// 18ca  cac91a    jp      z,#1ac9
// 18cd  cb57      bit     2,a
// 18cf  cad91a    jp      z,#1ad9
// 18d2  cb47      bit     0,a
// 18d4  cae81a    jp      z,#1ae8
// 18d7  cb5f      bit     3,a
// 18d9  caf81a    jp      z,#1af8
// 18dc  2a1c4d    ld      hl,(#4d1c)
// 18df  22264d    ld      (#4d26),hl
// 18e2  0601      ld      b,#01
// 18e4  dd21264d  ld      ix,#4d26
// 18e8  fd21394d  ld      iy,#4d39
// 18ec  cd0f20    call    #200f
// 18ef  e6c0      and     #c0
// 18f1  d6c0      sub     #c0
// 18f3  204b      jr      nz,#1940        ; (75)
// 18f5  05        dec     b
// 18f6  c21619    jp      nz,#1916
// 18f9  3a304d    ld      a,(#4d30)
// 18fc  0f        rrca    
// 18fd  da0b19    jp      c,#190b
// 1900  3a094d    ld      a,(#4d09)
// 1903  e607      and     #07
// 1905  fe04      cp      #04
// 1907  c8        ret     z
// 
// 1908  c34019    jp      #1940
// 190b  3a084d    ld      a,(#4d08)
// 190e  e607      and     #07
// 1910  fe04      cp      #04
// 1912  c8        ret     z
// 
// 1913  c34019    jp      #1940
// 1916  dd211c4d  ld      ix,#4d1c
// 191a  cd0f20    call    #200f
// 191d  e6c0      and     #c0
// 191f  d6c0      sub     #c0
// 1921  202d      jr      nz,#1950        ; (45)
// 1923  3a304d    ld      a,(#4d30)
// 1926  0f        rrca    
// 1927  da3519    jp      c,#1935
// 192a  3a094d    ld      a,(#4d09)
// 192d  e607      and     #07
// 192f  fe04      cp      #04
// 1931  c8        ret     z
// 
// 1932  c35019    jp      #1950
// 1935  3a084d    ld      a,(#4d08)
// 1938  e607      and     #07
// 193a  fe04      cp      #04
// 193c  c8        ret     z
// 
// 193d  c35019    jp      #1950
// 1940  2a264d    ld      hl,(#4d26)
// 1943  221c4d    ld      (#4d1c),hl
// 1946  05        dec     b
// 1947  ca5019    jp      z,#1950
// 194a  3a3c4d    ld      a,(#4d3c)
// 194d  32304d    ld      (#4d30),a
// 1950  dd211c4d  ld      ix,#4d1c
// 1954  fd21084d  ld      iy,#4d08
// 1958  cd0020    call    #2000
// 195b  3a304d    ld      a,(#4d30)
// 195e  0f        rrca    
// 195f  da7519    jp      c,#1975
// 1962  7d        ld      a,l
// 1963  e607      and     #07
// 1965  fe04      cp      #04
// 1967  ca8519    jp      z,#1985
// 196a  da7119    jp      c,#1971
// 196d  2d        dec     l
// 196e  c38519    jp      #1985
// 1971  2c        inc     l
// 1972  c38519    jp      #1985
// 1975  7c        ld      a,h
// 1976  e607      and     #07
// 1978  fe04      cp      #04
// 197a  ca8519    jp      z,#1985
// 197d  da8419    jp      c,#1984
// 1980  25        dec     h
// 1981  c38519    jp      #1985
// 1984  24        inc     h
// 1985  22084d    ld      (#4d08),hl
// 1988  cd1820    call    #2018
// 198b  22394d    ld      (#4d39),hl
// 198e  dd21bf4d  ld      ix,#4dbf
// 1992  dd7e00    ld      a,(ix+#00)
// 1995  dd360000  ld      (ix+#00),#00
// 1999  a7        and     a
// 199a  c0        ret     nz
// 
// 199b  3ad24d    ld      a,(#4dd2)
// 199e  a7        and     a
// 199f  282c      jr      z,#19cd         ; (44)
// 19a1  3ad44d    ld      a,(#4dd4)
// 19a4  a7        and     a
// 19a5  2826      jr      z,#19cd         ; (38)
// 19a7  2a084d    ld      hl,(#4d08)
// 19aa  119480    ld      de,#8094
// 19ad  a7        and     a
// 19ae  ed52      sbc     hl,de
// 19b0  201b      jr      nz,#19cd        ; (27)
// 19b2  0619      ld      b,#19
// 19b4  4f        ld      c,a
// 19b5  cd4200    call    #0042
// 19b8  0e15      ld      c,#15
// 19ba  81        add     a,c
// 19bb  4f        ld      c,a
// 19bc  061c      ld      b,#1c
// 19be  cd4200    call    #0042
// 19c1  cd0410    call    #1004
// 19c4  f7        rst     #30
// 19c5  54        ld      d,h
// 19c6  05        dec     b
// 19c7  00        nop     
// 19c8  21bc4e    ld      hl,#4ebc
// 19cb  cbd6      set     2,(hl)
// 19cd  3eff      ld      a,#ff
// 19cf  329d4d    ld      (#4d9d),a
// 19d2  2a394d    ld      hl,(#4d39)
// 19d5  cd6500    call    #0065
// 19d8  7e        ld      a,(hl)
// 19d9  fe10      cp      #10
// 19db  2803      jr      z,#19e0         ; (3)
// 19dd  fe14      cp      #14
// 19df  c0        ret     nz
// 
// 19e0  dd210e4e  ld      ix,#4e0e
// 19e4  dd3400    inc     (ix+#00)
// 19e7  e60f      and     #0f
// 19e9  cb3f      srl     a
// 19eb  0640      ld      b,#40
// 19ed  70        ld      (hl),b
// 19ee  0619      ld      b,#19
// 19f0  4f        ld      c,a
// 19f1  cb39      srl     c
// 19f3  cd4200    call    #0042
// 19f6  3c        inc     a
// 19f7  fe01      cp      #01
// 19f9  cafd19    jp      z,#19fd
// 19fc  87        add     a,a
// 19fd  329d4d    ld      (#4d9d),a
// 1a00  cd081b    call    #1b08
// 1a03  cd6a1a    call    #1a6a
// 1a06  21bc4e    ld      hl,#4ebc
// 1a09  3a0e4e    ld      a,(#4e0e)
// 1a0c  0f        rrca    
// 1a0d  3805      jr      c,#1a14         ; (5)
// 1a0f  cbc6      set     0,(hl)
// 1a11  cb8e      res     1,(hl)
// 1a13  c9        ret     
// 
// 1a14  cb86      res     0,(hl)
// 1a16  cbce      set     1,(hl)
// 1a18  c9        ret     
// 
// 1a19  211c4d    ld      hl,#4d1c
// 1a1c  7e        ld      a,(hl)
// 1a1d  a7        and     a
// 1a1e  ca2e1a    jp      z,#1a2e
// 1a21  3a084d    ld      a,(#4d08)
// 1a24  e607      and     #07
// 1a26  fe04      cp      #04
// 1a28  ca381a    jp      z,#1a38
// 1a2b  c35c1a    jp      #1a5c
// 1a2e  3a094d    ld      a,(#4d09)
// 1a31  e607      and     #07
// 1a33  fe04      cp      #04
// 1a35  c25c1a    jp      nz,#1a5c
// 1a38  3e05      ld      a,#05
// 1a3a  cdd01e    call    #1ed0
// 1a3d  3803      jr      c,#1a42         ; (3)
// 1a3f  ef        rst     #28
// 1a40  17        rla     
// 1a41  00        nop     
// 1a42  dd21264d  ld      ix,#4d26
// 1a46  fd21124d  ld      iy,#4d12
// 1a4a  cd0020    call    #2000
// 1a4d  22124d    ld      (#4d12),hl
// 1a50  2a264d    ld      hl,(#4d26)
// 1a53  221c4d    ld      (#4d1c),hl
// 1a56  3a3c4d    ld      a,(#4d3c)
// 1a59  32304d    ld      (#4d30),a
// 1a5c  dd211c4d  ld      ix,#4d1c
// 1a60  fd21084d  ld      iy,#4d08
// 1a64  cd0020    call    #2000
// 1a67  c38519    jp      #1985
// 1a6a  3a9d4d    ld      a,(#4d9d)
// 1a6d  fe06      cp      #06
// 1a6f  c0        ret     nz
// 
// 1a70  2abd4d    ld      hl,(#4dbd)
// 1a73  22cb4d    ld      (#4dcb),hl
// 1a76  3e01      ld      a,#01
// 1a78  32a64d    ld      (#4da6),a
// 1a7b  32a74d    ld      (#4da7),a
// 1a7e  32a84d    ld      (#4da8),a
// 1a81  32a94d    ld      (#4da9),a
// 1a84  32aa4d    ld      (#4daa),a
// 1a87  32b14d    ld      (#4db1),a
// 1a8a  32b24d    ld      (#4db2),a
// 1a8d  32b34d    ld      (#4db3),a
// 1a90  32b44d    ld      (#4db4),a
// 1a93  32b54d    ld      (#4db5),a
// 1a96  af        xor     a
// 1a97  32c84d    ld      (#4dc8),a
// 1a9a  32d04d    ld      (#4dd0),a
// 1a9d  dd21004c  ld      ix,#4c00
// 1aa1  dd36021c  ld      (ix+#02),#1c
// 1aa5  dd36041c  ld      (ix+#04),#1c
// 1aa9  dd36061c  ld      (ix+#06),#1c
// 1aad  dd36081c  ld      (ix+#08),#1c
// 1ab1  dd360311  ld      (ix+#03),#11
// 1ab5  dd360511  ld      (ix+#05),#11
// 1ab9  dd360711  ld      (ix+#07),#11
// 1abd  dd360911  ld      (ix+#09),#11
// 1ac1  21ac4e    ld      hl,#4eac
// 1ac4  cbee      set     5,(hl)
// 1ac6  cbbe      res     7,(hl)
// 1ac8  c9        ret     
// 
// 1ac9  2a0333    ld      hl,(#3303)
// 1acc  3e02      ld      a,#02
// 1ace  323c4d    ld      (#4d3c),a
// 1ad1  22264d    ld      (#4d26),hl
// 1ad4  0600      ld      b,#00
// 1ad6  c3e418    jp      #18e4
// 1ad9  2aff32    ld      hl,(#32ff)
// 1adc  af        xor     a
// 1add  323c4d    ld      (#4d3c),a
// 1ae0  22264d    ld      (#4d26),hl
// 1ae3  0600      ld      b,#00
// 1ae5  c3e418    jp      #18e4
// 1ae8  2a0533    ld      hl,(#3305)
// 1aeb  3e03      ld      a,#03
// 1aed  323c4d    ld      (#4d3c),a
// 1af0  22264d    ld      (#4d26),hl
// 1af3  0600      ld      b,#00
// 1af5  c3e418    jp      #18e4
// 1af8  2a0133    ld      hl,(#3301)
// 1afb  3e01      ld      a,#01
// 1afd  323c4d    ld      (#4d3c),a
// 1b00  22264d    ld      (#4d26),hl
// 1b03  0600      ld      b,#00
// 1b05  c3e418    jp      #18e4
// 1b08  3a124e    ld      a,(#4e12)
// 1b0b  a7        and     a
// 1b0c  ca141b    jp      z,#1b14
// 1b0f  219f4d    ld      hl,#4d9f
// 1b12  34        inc     (hl)
// 1b13  c9        ret     
// 
// 1b14  3aa34d    ld      a,(#4da3)
// 1b17  a7        and     a
// 1b18  c0        ret     nz
// 
// 1b19  3aa24d    ld      a,(#4da2)
// 1b1c  a7        and     a
// 1b1d  ca251b    jp      z,#1b25
// 1b20  21114e    ld      hl,#4e11
// 1b23  34        inc     (hl)
// 1b24  c9        ret     
// 
// 1b25  3aa14d    ld      a,(#4da1)
// 1b28  a7        and     a
// 1b29  ca311b    jp      z,#1b31
// 1b2c  21104e    ld      hl,#4e10
// 1b2f  34        inc     (hl)
// 1b30  c9        ret     
// 
// 1b31  210f4e    ld      hl,#4e0f
// 1b34  34        inc     (hl)
// 1b35  c9        ret     
// 
// 1b36  3aa04d    ld      a,(#4da0)
// 1b39  a7        and     a
// 1b3a  c8        ret     z
// 
// 1b3b  3aac4d    ld      a,(#4dac)
// 1b3e  a7        and     a
// 1b3f  c0        ret     nz
// 
// 1b40  cdd720    call    #20d7
// 1b43  2a314d    ld      hl,(#4d31)
// 1b46  01994d    ld      bc,#4d99
// 1b49  cd5a20    call    #205a
// 1b4c  3a994d    ld      a,(#4d99)
// 1b4f  a7        and     a
// 1b50  ca6a1b    jp      z,#1b6a
// 1b53  2a604d    ld      hl,(#4d60)
// 1b56  29        add     hl,hl
// 1b57  22604d    ld      (#4d60),hl
// 1b5a  2a5e4d    ld      hl,(#4d5e)
// 1b5d  ed6a      adc     hl,hl
// 1b5f  225e4d    ld      (#4d5e),hl
// 1b62  d0        ret     nc
// 
// 1b63  21604d    ld      hl,#4d60
// 1b66  34        inc     (hl)
// 1b67  c3d81b    jp      #1bd8
// 1b6a  3aa74d    ld      a,(#4da7)
// 1b6d  a7        and     a
// 1b6e  ca881b    jp      z,#1b88
// 1b71  2a5c4d    ld      hl,(#4d5c)
// 1b74  29        add     hl,hl
// 1b75  225c4d    ld      (#4d5c),hl
// 1b78  2a5a4d    ld      hl,(#4d5a)
// 1b7b  ed6a      adc     hl,hl
// 1b7d  225a4d    ld      (#4d5a),hl
// 1b80  d0        ret     nc
// 
// 1b81  215c4d    ld      hl,#4d5c
// 1b84  34        inc     (hl)
// 1b85  c3d81b    jp      #1bd8
// 1b88  3ab74d    ld      a,(#4db7)
// 1b8b  a7        and     a
// 1b8c  caa61b    jp      z,#1ba6
// 1b8f  2a504d    ld      hl,(#4d50)
// 1b92  29        add     hl,hl
// 1b93  22504d    ld      (#4d50),hl
// 1b96  2a4e4d    ld      hl,(#4d4e)
// 1b99  ed6a      adc     hl,hl
// 1b9b  224e4d    ld      (#4d4e),hl
// 1b9e  d0        ret     nc
// 
// 1b9f  21504d    ld      hl,#4d50
// 1ba2  34        inc     (hl)
// 1ba3  c3d81b    jp      #1bd8
// 1ba6  3ab64d    ld      a,(#4db6)
// 1ba9  a7        and     a
// 1baa  cac41b    jp      z,#1bc4
// 1bad  2a544d    ld      hl,(#4d54)
// 1bb0  29        add     hl,hl
// 1bb1  22544d    ld      (#4d54),hl
// 1bb4  2a524d    ld      hl,(#4d52)
// 1bb7  ed6a      adc     hl,hl
// 1bb9  22524d    ld      (#4d52),hl
// 1bbc  d0        ret     nc
// 
// 1bbd  21544d    ld      hl,#4d54
// 1bc0  34        inc     (hl)
// 1bc1  c3d81b    jp      #1bd8
// 1bc4  2a584d    ld      hl,(#4d58)
// 1bc7  29        add     hl,hl
// 1bc8  22584d    ld      (#4d58),hl
// 1bcb  2a564d    ld      hl,(#4d56)
// 1bce  ed6a      adc     hl,hl
// 1bd0  22564d    ld      (#4d56),hl
// 1bd3  d0        ret     nc
// 
// 1bd4  21584d    ld      hl,#4d58
// 1bd7  34        inc     (hl)
// 1bd8  21144d    ld      hl,#4d14
// 1bdb  7e        ld      a,(hl)
// 1bdc  a7        and     a
// 1bdd  caed1b    jp      z,#1bed
// 1be0  3a004d    ld      a,(#4d00)
// 1be3  e607      and     #07
// 1be5  fe04      cp      #04
// 1be7  caf71b    jp      z,#1bf7
// 1bea  c3361c    jp      #1c36
// 1bed  3a014d    ld      a,(#4d01)
// 1bf0  e607      and     #07
// 1bf2  fe04      cp      #04
// 1bf4  c2361c    jp      nz,#1c36
// 1bf7  3e01      ld      a,#01
// 1bf9  cdd01e    call    #1ed0
// 1bfc  381b      jr      c,#1c19         ; (27)
// 1bfe  3aa74d    ld      a,(#4da7)
// 1c01  a7        and     a
// 1c02  ca0b1c    jp      z,#1c0b
// 1c05  ef        rst     #28
// 1c06  0c        inc     c
// 1c07  00        nop     
// 1c08  c3191c    jp      #1c19
// 1c0b  2a0a4d    ld      hl,(#4d0a)
// 1c0e  cd5220    call    #2052
// 1c11  7e        ld      a,(hl)
// 1c12  fe1a      cp      #1a
// 1c14  2803      jr      z,#1c19         ; (3)
// 1c16  ef        rst     #28
// 1c17  08        ex      af,af'
// 1c18  00        nop     
// 1c19  cdfe1e    call    #1efe
// 1c1c  dd211e4d  ld      ix,#4d1e
// 1c20  fd210a4d  ld      iy,#4d0a
// 1c24  cd0020    call    #2000
// 1c27  220a4d    ld      (#4d0a),hl
// 1c2a  2a1e4d    ld      hl,(#4d1e)
// 1c2d  22144d    ld      (#4d14),hl
// 1c30  3a2c4d    ld      a,(#4d2c)
// 1c33  32284d    ld      (#4d28),a
// 1c36  dd21144d  ld      ix,#4d14
// 1c3a  fd21004d  ld      iy,#4d00
// 1c3e  cd0020    call    #2000
// 1c41  22004d    ld      (#4d00),hl
// 1c44  cd1820    call    #2018
// 1c47  22314d    ld      (#4d31),hl
// 1c4a  c9        ret     
// 
// 1c4b  3aa14d    ld      a,(#4da1)
// 1c4e  fe01      cp      #01
// 1c50  c0        ret     nz
// 
// 1c51  3aad4d    ld      a,(#4dad)
// 1c54  a7        and     a
// 1c55  c0        ret     nz
// 
// 1c56  2a334d    ld      hl,(#4d33)
// 1c59  019a4d    ld      bc,#4d9a
// 1c5c  cd5a20    call    #205a
// 1c5f  3a9a4d    ld      a,(#4d9a)
// 1c62  a7        and     a
// 1c63  ca7d1c    jp      z,#1c7d
// 1c66  2a6c4d    ld      hl,(#4d6c)
// 1c69  29        add     hl,hl
// 1c6a  226c4d    ld      (#4d6c),hl
// 1c6d  2a6a4d    ld      hl,(#4d6a)
// 1c70  ed6a      adc     hl,hl
// 1c72  226a4d    ld      (#4d6a),hl
// 1c75  d0        ret     nc
// 
// 1c76  216c4d    ld      hl,#4d6c
// 1c79  34        inc     (hl)
// 1c7a  c3af1c    jp      #1caf
// 1c7d  3aa84d    ld      a,(#4da8)
// 1c80  a7        and     a
// 1c81  ca9b1c    jp      z,#1c9b
// 1c84  2a684d    ld      hl,(#4d68)
// 1c87  29        add     hl,hl
// 1c88  22684d    ld      (#4d68),hl
// 1c8b  2a664d    ld      hl,(#4d66)
// 1c8e  ed6a      adc     hl,hl
// 1c90  22664d    ld      (#4d66),hl
// 1c93  d0        ret     nc
// 
// 1c94  21684d    ld      hl,#4d68
// 1c97  34        inc     (hl)
// 1c98  c3af1c    jp      #1caf
// 1c9b  2a644d    ld      hl,(#4d64)
// 1c9e  29        add     hl,hl
// 1c9f  22644d    ld      (#4d64),hl
// 1ca2  2a624d    ld      hl,(#4d62)
// 1ca5  ed6a      adc     hl,hl
// 1ca7  22624d    ld      (#4d62),hl
// 1caa  d0        ret     nc
// 
// 1cab  21644d    ld      hl,#4d64
// 1cae  34        inc     (hl)
// 1caf  21164d    ld      hl,#4d16
// 1cb2  7e        ld      a,(hl)
// 1cb3  a7        and     a
// 1cb4  cac41c    jp      z,#1cc4
// 1cb7  3a024d    ld      a,(#4d02)
// 1cba  e607      and     #07
// 1cbc  fe04      cp      #04
// 1cbe  cace1c    jp      z,#1cce
// 1cc1  c30d1d    jp      #1d0d
// 1cc4  3a034d    ld      a,(#4d03)
// 1cc7  e607      and     #07
// 1cc9  fe04      cp      #04
// 1ccb  c20d1d    jp      nz,#1d0d
// 1cce  3e02      ld      a,#02
// 1cd0  cdd01e    call    #1ed0
// 1cd3  381b      jr      c,#1cf0         ; (27)
// 1cd5  3aa84d    ld      a,(#4da8)
// 1cd8  a7        and     a
// 1cd9  cae21c    jp      z,#1ce2
// 1cdc  ef        rst     #28
// 1cdd  0d        dec     c
// 1cde  00        nop     
// 1cdf  c3f01c    jp      #1cf0
// 1ce2  2a0c4d    ld      hl,(#4d0c)
// 1ce5  cd5220    call    #2052
// 1ce8  7e        ld      a,(hl)
// 1ce9  fe1a      cp      #1a
// 1ceb  2803      jr      z,#1cf0         ; (3)
// 1ced  ef        rst     #28
// 1cee  09        add     hl,bc
// 1cef  00        nop     
// 1cf0  cd251f    call    #1f25
// 1cf3  dd21204d  ld      ix,#4d20
// 1cf7  fd210c4d  ld      iy,#4d0c
// 1cfb  cd0020    call    #2000
// 1cfe  220c4d    ld      (#4d0c),hl
// 1d01  2a204d    ld      hl,(#4d20)
// 1d04  22164d    ld      (#4d16),hl
// 1d07  3a2d4d    ld      a,(#4d2d)
// 1d0a  32294d    ld      (#4d29),a
// 1d0d  dd21164d  ld      ix,#4d16
// 1d11  fd21024d  ld      iy,#4d02
// 1d15  cd0020    call    #2000
// 1d18  22024d    ld      (#4d02),hl
// 1d1b  cd1820    call    #2018
// 1d1e  22334d    ld      (#4d33),hl
// 1d21  c9        ret     
// 
// 1d22  3aa24d    ld      a,(#4da2)
// 1d25  fe01      cp      #01
// 1d27  c0        ret     nz
// 
// 1d28  3aae4d    ld      a,(#4dae)
// 1d2b  a7        and     a
// 1d2c  c0        ret     nz
// 
// 1d2d  2a354d    ld      hl,(#4d35)
// 1d30  019b4d    ld      bc,#4d9b
// 1d33  cd5a20    call    #205a
// 1d36  3a9b4d    ld      a,(#4d9b)
// 1d39  a7        and     a
// 1d3a  ca541d    jp      z,#1d54
// 1d3d  2a784d    ld      hl,(#4d78)
// 1d40  29        add     hl,hl
// 1d41  22784d    ld      (#4d78),hl
// 1d44  2a764d    ld      hl,(#4d76)
// 1d47  ed6a      adc     hl,hl
// 1d49  22764d    ld      (#4d76),hl
// 1d4c  d0        ret     nc
// 
// 1d4d  21784d    ld      hl,#4d78
// 1d50  34        inc     (hl)
// 1d51  c3861d    jp      #1d86
// 1d54  3aa94d    ld      a,(#4da9)
// 1d57  a7        and     a
// 1d58  ca721d    jp      z,#1d72
// 1d5b  2a744d    ld      hl,(#4d74)
// 1d5e  29        add     hl,hl
// 1d5f  22744d    ld      (#4d74),hl
// 1d62  2a724d    ld      hl,(#4d72)
// 1d65  ed6a      adc     hl,hl
// 1d67  22724d    ld      (#4d72),hl
// 1d6a  d0        ret     nc
// 
// 1d6b  21744d    ld      hl,#4d74
// 1d6e  34        inc     (hl)
// 1d6f  c3861d    jp      #1d86
// 1d72  2a704d    ld      hl,(#4d70)
// 1d75  29        add     hl,hl
// 1d76  22704d    ld      (#4d70),hl
// 1d79  2a6e4d    ld      hl,(#4d6e)
// 1d7c  ed6a      adc     hl,hl
// 1d7e  226e4d    ld      (#4d6e),hl
// 1d81  d0        ret     nc
// 
// 1d82  21704d    ld      hl,#4d70
// 1d85  34        inc     (hl)
// 1d86  21184d    ld      hl,#4d18
// 1d89  7e        ld      a,(hl)
// 1d8a  a7        and     a
// 1d8b  ca9b1d    jp      z,#1d9b
// 1d8e  3a044d    ld      a,(#4d04)
// 1d91  e607      and     #07
// 1d93  fe04      cp      #04
// 1d95  caa51d    jp      z,#1da5
// 1d98  c3e41d    jp      #1de4
// 1d9b  3a054d    ld      a,(#4d05)
// 1d9e  e607      and     #07
// 1da0  fe04      cp      #04
// 1da2  c2e41d    jp      nz,#1de4
// 1da5  3e03      ld      a,#03
// 1da7  cdd01e    call    #1ed0
// 1daa  381b      jr      c,#1dc7         ; (27)
// 1dac  3aa94d    ld      a,(#4da9)
// 1daf  a7        and     a
// 1db0  cab91d    jp      z,#1db9
// 1db3  ef        rst     #28
// 1db4  0e00      ld      c,#00
// 1db6  c3c71d    jp      #1dc7
// 1db9  2a0e4d    ld      hl,(#4d0e)
// 1dbc  cd5220    call    #2052
// 1dbf  7e        ld      a,(hl)
// 1dc0  fe1a      cp      #1a
// 1dc2  2803      jr      z,#1dc7         ; (3)
// 1dc4  ef        rst     #28
// 1dc5  0a        ld      a,(bc)
// 1dc6  00        nop     
// 1dc7  cd4c1f    call    #1f4c
// 1dca  dd21224d  ld      ix,#4d22
// 1dce  fd210e4d  ld      iy,#4d0e
// 1dd2  cd0020    call    #2000
// 1dd5  220e4d    ld      (#4d0e),hl
// 1dd8  2a224d    ld      hl,(#4d22)
// 1ddb  22184d    ld      (#4d18),hl
// 1dde  3a2e4d    ld      a,(#4d2e)
// 1de1  322a4d    ld      (#4d2a),a
// 1de4  dd21184d  ld      ix,#4d18
// 1de8  fd21044d  ld      iy,#4d04
// 1dec  cd0020    call    #2000
// 1def  22044d    ld      (#4d04),hl
// 1df2  cd1820    call    #2018
// 1df5  22354d    ld      (#4d35),hl
// 1df8  c9        ret     
// 
// 1df9  3aa34d    ld      a,(#4da3)
// 1dfc  fe01      cp      #01
// 1dfe  c0        ret     nz
// 
// 1dff  3aaf4d    ld      a,(#4daf)
// 1e02  a7        and     a
// 1e03  c0        ret     nz
// 
// 1e04  2a374d    ld      hl,(#4d37)
// 1e07  019c4d    ld      bc,#4d9c
// 1e0a  cd5a20    call    #205a
// 1e0d  3a9c4d    ld      a,(#4d9c)
// 1e10  a7        and     a
// 1e11  ca2b1e    jp      z,#1e2b
// 1e14  2a844d    ld      hl,(#4d84)
// 1e17  29        add     hl,hl
// 1e18  22844d    ld      (#4d84),hl
// 1e1b  2a824d    ld      hl,(#4d82)
// 1e1e  ed6a      adc     hl,hl
// 1e20  22824d    ld      (#4d82),hl
// 1e23  d0        ret     nc
// 
// 1e24  21844d    ld      hl,#4d84
// 1e27  34        inc     (hl)
// 1e28  c35d1e    jp      #1e5d
// 1e2b  3aaa4d    ld      a,(#4daa)
// 1e2e  a7        and     a
// 1e2f  ca491e    jp      z,#1e49
// 1e32  2a804d    ld      hl,(#4d80)
// 1e35  29        add     hl,hl
// 1e36  22804d    ld      (#4d80),hl
// 1e39  2a7e4d    ld      hl,(#4d7e)
// 1e3c  ed6a      adc     hl,hl
// 1e3e  227e4d    ld      (#4d7e),hl
// 1e41  d0        ret     nc
// 
// 1e42  21804d    ld      hl,#4d80
// 1e45  34        inc     (hl)
// 1e46  c35d1e    jp      #1e5d
// 1e49  2a7c4d    ld      hl,(#4d7c)
// 1e4c  29        add     hl,hl
// 1e4d  227c4d    ld      (#4d7c),hl
// 1e50  2a7a4d    ld      hl,(#4d7a)
// 1e53  ed6a      adc     hl,hl
// 1e55  227a4d    ld      (#4d7a),hl
// 1e58  d0        ret     nc
// 
// 1e59  217c4d    ld      hl,#4d7c
// 1e5c  34        inc     (hl)
// 1e5d  211a4d    ld      hl,#4d1a
// 1e60  7e        ld      a,(hl)
// 1e61  a7        and     a
// 1e62  ca721e    jp      z,#1e72
// 1e65  3a064d    ld      a,(#4d06)
// 1e68  e607      and     #07
// 1e6a  fe04      cp      #04
// 1e6c  ca7c1e    jp      z,#1e7c
// 1e6f  c3bb1e    jp      #1ebb
// 1e72  3a074d    ld      a,(#4d07)
// 1e75  e607      and     #07
// 1e77  fe04      cp      #04
// 1e79  c2bb1e    jp      nz,#1ebb
// 1e7c  3e04      ld      a,#04
// 1e7e  cdd01e    call    #1ed0
// 1e81  381b      jr      c,#1e9e         ; (27)
// 1e83  3aaa4d    ld      a,(#4daa)
// 1e86  a7        and     a
// 1e87  ca901e    jp      z,#1e90
// 1e8a  ef        rst     #28
// 1e8b  0f        rrca    
// 1e8c  00        nop     
// 1e8d  c39e1e    jp      #1e9e
// 1e90  2a104d    ld      hl,(#4d10)
// 1e93  cd5220    call    #2052
// 1e96  7e        ld      a,(hl)
// 1e97  fe1a      cp      #1a
// 1e99  2803      jr      z,#1e9e         ; (3)
// 1e9b  ef        rst     #28
// 1e9c  0b        dec     bc
// 1e9d  00        nop     
// 1e9e  cd731f    call    #1f73
// 1ea1  dd21244d  ld      ix,#4d24
// 1ea5  fd21104d  ld      iy,#4d10
// 1ea9  cd0020    call    #2000
// 1eac  22104d    ld      (#4d10),hl
// 1eaf  2a244d    ld      hl,(#4d24)
// 1eb2  221a4d    ld      (#4d1a),hl
// 1eb5  3a2f4d    ld      a,(#4d2f)
// 1eb8  322b4d    ld      (#4d2b),a
// 1ebb  dd211a4d  ld      ix,#4d1a
// 1ebf  fd21064d  ld      iy,#4d06
// 1ec3  cd0020    call    #2000
// 1ec6  22064d    ld      (#4d06),hl
// 1ec9  cd1820    call    #2018
// 1ecc  22374d    ld      (#4d37),hl
// 1ecf  c9        ret     
// 
// 1ed0  87        add     a,a
// 1ed1  4f        ld      c,a
// 1ed2  0600      ld      b,#00
// 1ed4  21094d    ld      hl,#4d09
// 1ed7  09        add     hl,bc
// 1ed8  7e        ld      a,(hl)
// 1ed9  fe1d      cp      #1d
// 1edb  c2e31e    jp      nz,#1ee3
// 1ede  363d      ld      (hl),#3d
// 1ee0  c3fc1e    jp      #1efc
// 1ee3  fe3e      cp      #3e
// 1ee5  c2ed1e    jp      nz,#1eed
// 1ee8  361e      ld      (hl),#1e
// 1eea  c3fc1e    jp      #1efc
// 1eed  0621      ld      b,#21
// 1eef  90        sub     b
// 1ef0  dafc1e    jp      c,#1efc
// 1ef3  7e        ld      a,(hl)
// 1ef4  063b      ld      b,#3b
// 1ef6  90        sub     b
// 1ef7  d2fc1e    jp      nc,#1efc
// 1efa  a7        and     a
// 1efb  c9        ret     
// 
// 1efc  37        scf     
// 1efd  c9        ret     
// 
// 1efe  3ab14d    ld      a,(#4db1)
// 1f01  a7        and     a
// 1f02  c8        ret     z
// 
// 1f03  af        xor     a
// 1f04  32b14d    ld      (#4db1),a
// 1f07  21ff32    ld      hl,#32ff
// 1f0a  3a284d    ld      a,(#4d28)
// 1f0d  ee02      xor     #02
// 1f0f  322c4d    ld      (#4d2c),a
// 1f12  47        ld      b,a
// 1f13  df        rst     #18
// 1f14  221e4d    ld      (#4d1e),hl
// 1f17  3a024e    ld      a,(#4e02)
// 1f1a  fe22      cp      #22
// 1f1c  c0        ret     nz
// 
// 1f1d  22144d    ld      (#4d14),hl
// 1f20  78        ld      a,b
// 1f21  32284d    ld      (#4d28),a
// 1f24  c9        ret     
// 
// 1f25  3ab24d    ld      a,(#4db2)
// 1f28  a7        and     a
// 1f29  c8        ret     z
// 
// 1f2a  af        xor     a
// 1f2b  32b24d    ld      (#4db2),a
// 1f2e  21ff32    ld      hl,#32ff
// 1f31  3a294d    ld      a,(#4d29)
// 1f34  ee02      xor     #02
// 1f36  322d4d    ld      (#4d2d),a
// 1f39  47        ld      b,a
// 1f3a  df        rst     #18
// 1f3b  22204d    ld      (#4d20),hl
// 1f3e  3a024e    ld      a,(#4e02)
// 1f41  fe22      cp      #22
// 1f43  c0        ret     nz
// 
// 1f44  22164d    ld      (#4d16),hl
// 1f47  78        ld      a,b
// 1f48  32294d    ld      (#4d29),a
// 1f4b  c9        ret     
// 
// 1f4c  3ab34d    ld      a,(#4db3)
// 1f4f  a7        and     a
// 1f50  c8        ret     z
// 
// 1f51  af        xor     a
// 1f52  32b34d    ld      (#4db3),a
// 1f55  21ff32    ld      hl,#32ff
// 1f58  3a2a4d    ld      a,(#4d2a)
// 1f5b  ee02      xor     #02
// 1f5d  322e4d    ld      (#4d2e),a
// 1f60  47        ld      b,a
// 1f61  df        rst     #18
// 1f62  22224d    ld      (#4d22),hl
// 1f65  3a024e    ld      a,(#4e02)
// 1f68  fe22      cp      #22
// 1f6a  c0        ret     nz
// 
// 1f6b  22184d    ld      (#4d18),hl
// 1f6e  78        ld      a,b
// 1f6f  322a4d    ld      (#4d2a),a
// 1f72  c9        ret     
// 
// 1f73  3ab44d    ld      a,(#4db4)
// 1f76  a7        and     a
// 1f77  c8        ret     z
// 
// 1f78  af        xor     a
// 1f79  32b44d    ld      (#4db4),a
// 1f7c  21ff32    ld      hl,#32ff
// 1f7f  3a2b4d    ld      a,(#4d2b)
// 1f82  ee02      xor     #02
// 1f84  322f4d    ld      (#4d2f),a
// 1f87  47        ld      b,a
// 1f88  df        rst     #18
// 1f89  22244d    ld      (#4d24),hl
// 1f8c  3a024e    ld      a,(#4e02)
// 1f8f  fe22      cp      #22
// 1f91  c0        ret     nz
// 
// 1f92  221a4d    ld      (#4d1a),hl
// 1f95  78        ld      a,b
// 1f96  322b4d    ld      (#4d2b),a
// 1f99  c9        ret     
// 
// 1f9a  00        nop     
// 1f9b  00        nop     
// 1f9c  00        nop     
// 1f9d  00        nop     
// 1f9e  00        nop     
// 1f9f  00        nop     
// 1fa0  00        nop     
// 1fa1  00        nop     
// 1fa2  00        nop     
// 1fa3  00        nop     
// 1fa4  00        nop     
// 1fa5  00        nop     
// 1fa6  00        nop     
// 1fa7  00        nop     
// 1fa8  00        nop     
// 1fa9  00        nop     
// 1faa  00        nop     
// 1fab  00        nop     
// 1fac  00        nop     
// 1fad  00        nop     
// 1fae  00        nop     
// 1faf  00        nop     
// 1fb0  00        nop     
// 1fb1  00        nop     
// 1fb2  00        nop     
// 1fb3  00        nop     
// 1fb4  00        nop     
// 1fb5  00        nop     
// 1fb6  00        nop     
// 1fb7  00        nop     
// 1fb8  00        nop     
// 1fb9  00        nop     
// 1fba  00        nop     
// 1fbb  00        nop     
// 1fbc  00        nop     
// 1fbd  00        nop     
// 1fbe  00        nop     
// 1fbf  00        nop     
// 1fc0  00        nop     
// 1fc1  00        nop     
// 1fc2  00        nop     
// 1fc3  00        nop     
// 1fc4  00        nop     
// 1fc5  00        nop     
// 1fc6  00        nop     
// 1fc7  00        nop     
// 1fc8  00        nop     
// 1fc9  00        nop     
// 1fca  00        nop     
// 1fcb  00        nop     
// 1fcc  00        nop     
// 1fcd  00        nop     
// 1fce  00        nop     
// 1fcf  00        nop     
// 1fd0  00        nop     
// 1fd1  00        nop     
// 1fd2  00        nop     
// 1fd3  00        nop     
// 1fd4  00        nop     
// 1fd5  00        nop     
// 1fd6  00        nop     
// 1fd7  00        nop     
// 1fd8  00        nop     
// 1fd9  00        nop     
// 1fda  00        nop     
// 1fdb  00        nop     
// 1fdc  00        nop     
// 1fdd  00        nop     
// 1fde  00        nop     
// 1fdf  00        nop     
// 1fe0  00        nop     
// 1fe1  00        nop     
// 1fe2  00        nop     
// 1fe3  00        nop     
// 1fe4  00        nop     
// 1fe5  00        nop     
// 1fe6  00        nop     
// 1fe7  00        nop     
// 1fe8  00        nop     
// 1fe9  00        nop     
// 1fea  00        nop     
// 1feb  00        nop     
// 1fec  00        nop     
// 1fed  00        nop     
// 1fee  00        nop     
// 1fef  00        nop     
// 1ff0  00        nop     
// 1ff1  00        nop     
// 1ff2  00        nop     
// 1ff3  00        nop     
// 1ff4  00        nop     
// 1ff5  00        nop     
// 1ff6  00        nop     
// 1ff7  00        nop     
// 1ff8  00        nop     
// 1ff9  00        nop     
// 1ffa  00        nop     
// 1ffb  00        nop     
// 1ffc  00        nop     
// 1ffd  00        nop     
// 1ffe  5d        ld      e,l
// 1fff  e1        pop     hl
// 2000  fd7e00    ld      a,(iy+#00)
// 2003  dd8600    add     a,(ix+#00)
// 2006  6f        ld      l,a
// 2007  fd7e01    ld      a,(iy+#01)
// 200a  dd8601    add     a,(ix+#01)
// 200d  67        ld      h,a
// 200e  c9        ret     
// 
// 200f  cd0020    call    #2000
// 2012  cd6500    call    #0065
// 2015  7e        ld      a,(hl)
// 2016  a7        and     a
// 2017  c9        ret     
// 
// 2018  7d        ld      a,l
// 2019  cb3f      srl     a
// 201b  cb3f      srl     a
// 201d  cb3f      srl     a
// 201f  c620      add     a,#20
// 2021  6f        ld      l,a
// 2022  7c        ld      a,h
// 2023  cb3f      srl     a
// 2025  cb3f      srl     a
// 2027  cb3f      srl     a
// 2029  c61e      add     a,#1e
// 202b  67        ld      h,a
// 202c  c9        ret     
// 
// 202d  f5        push    af
// 202e  c5        push    bc
// 202f  7d        ld      a,l
// 2030  d620      sub     #20
// 2032  6f        ld      l,a
// 2033  7c        ld      a,h
// 2034  d620      sub     #20
// 2036  67        ld      h,a
// 2037  0600      ld      b,#00
// 2039  cb24      sla     h
// 203b  cb24      sla     h
// 203d  cb24      sla     h
// 203f  cb24      sla     h
// 2041  cb10      rl      b
// 2043  cb24      sla     h
// 2045  cb10      rl      b
// 2047  4c        ld      c,h
// 2048  2600      ld      h,#00
// 204a  09        add     hl,bc
// 204b  014040    ld      bc,#4040
// 204e  09        add     hl,bc
// 204f  c1        pop     bc
// 2050  f1        pop     af
// 2051  c9        ret     
// 
// 2052  cd6500    call    #0065
// 2055  110004    ld      de,#0400
// 2058  19        add     hl,de
// 2059  c9        ret     
// 
// 205a  cd5220    call    #2052
// 205d  7e        ld      a,(hl)
// 205e  fe1b      cp      #1b
// 2060  2004      jr      nz,#2066        ; (4)
// 2062  3e01      ld      a,#01
// 2064  02        ld      (bc),a
// 2065  c9        ret     
// 
// 2066  af        xor     a
// 2067  02        ld      (bc),a
// 2068  c9        ret     
// 
// 2069  3aa14d    ld      a,(#4da1)
// 206c  a7        and     a
// 206d  c0        ret     nz
// 
// 206e  3a124e    ld      a,(#4e12)
// 2071  a7        and     a
// 2072  ca7e20    jp      z,#207e
// 2075  3a9f4d    ld      a,(#4d9f)
// 2078  fe07      cp      #07
// 207a  c0        ret     nz
// 
// 207b  c38620    jp      #2086
// 207e  21b84d    ld      hl,#4db8
// 2081  3a0f4e    ld      a,(#4e0f)
// 2084  be        cp      (hl)
// 2085  d8        ret     c
// 
// 2086  3e02      ld      a,#02
// 2088  32a14d    ld      (#4da1),a
// 208b  c9        ret     
// 
// 208c  3aa24d    ld      a,(#4da2)
// 208f  a7        and     a
// 2090  c0        ret     nz
// 
// 2091  3a124e    ld      a,(#4e12)
// 2094  a7        and     a
// 2095  caa120    jp      z,#20a1
// 2098  3a9f4d    ld      a,(#4d9f)
// 209b  fe11      cp      #11
// 209d  c0        ret     nz
// 
// 209e  c3a920    jp      #20a9
// 20a1  21b94d    ld      hl,#4db9
// 20a4  3a104e    ld      a,(#4e10)
// 20a7  be        cp      (hl)
// 20a8  d8        ret     c
// 
// 20a9  3e03      ld      a,#03
// 20ab  32a24d    ld      (#4da2),a
// 20ae  c9        ret     
// 
// 20af  3aa34d    ld      a,(#4da3)
// 20b2  a7        and     a
// 20b3  c0        ret     nz
// 
// 20b4  3a124e    ld      a,(#4e12)
// 20b7  a7        and     a
// 20b8  cac920    jp      z,#20c9
// 20bb  3a9f4d    ld      a,(#4d9f)
// 20be  fe20      cp      #20
// 20c0  c0        ret     nz
// 
// 20c1  af        xor     a
// 20c2  32124e    ld      (#4e12),a
// 20c5  329f4d    ld      (#4d9f),a
// 20c8  c9        ret     
// 
// 20c9  21ba4d    ld      hl,#4dba
// 20cc  3a114e    ld      a,(#4e11)
// 20cf  be        cp      (hl)
// 20d0  d8        ret     c
// 
// 20d1  3e03      ld      a,#03
// 20d3  32a34d    ld      (#4da3),a
// 20d6  c9        ret     
// 
// 20d7  3aa34d    ld      a,(#4da3)
// 20da  a7        and     a
// 20db  c8        ret     z
// 
// 20dc  210e4e    ld      hl,#4e0e
// 20df  3ab64d    ld      a,(#4db6)
// 20e2  a7        and     a
// 20e3  c2f420    jp      nz,#20f4
// 20e6  3ef4      ld      a,#f4
// 20e8  96        sub     (hl)
// 20e9  47        ld      b,a
// 20ea  3abb4d    ld      a,(#4dbb)
// 20ed  90        sub     b
// 20ee  d8        ret     c
// 
// 20ef  3e01      ld      a,#01
// 20f1  32b64d    ld      (#4db6),a
// 20f4  3ab74d    ld      a,(#4db7)
// 20f7  a7        and     a
// 20f8  c0        ret     nz
// 
// 20f9  3ef4      ld      a,#f4
// 20fb  96        sub     (hl)
// 20fc  47        ld      b,a
// 20fd  3abc4d    ld      a,(#4dbc)
// 2100  90        sub     b
// 2101  d8        ret     c
// 
// 2102  3e01      ld      a,#01
// 2104  32b74d    ld      (#4db7),a
// 2107  c9        ret     
// 
// 2108  3a064e    ld      a,(#4e06)
// 210b  e7        rst     #20
// 210c  1a        ld      a,(de)
// 210d  214021    ld      hl,#2140
// 2110  4b        ld      c,e
// 2111  210c00    ld      hl,#000c
// 2114  70        ld      (hl),b
// 2115  217b21    ld      hl,#217b
// 2118  86        add     a,(hl)
// 2119  213a3a    ld      hl,#3a3a
// 211c  4d        ld      c,l
// 211d  d621      sub     #21
// 211f  200f      jr      nz,#2130        ; (15)
// 2121  3c        inc     a
// 2122  32a04d    ld      (#4da0),a
// 2125  32b74d    ld      (#4db7),a
// 2128  cd0605    call    #0506
// 212b  21064e    ld      hl,#4e06
// 212e  34        inc     (hl)
// 212f  c9        ret     
// 
// 2130  cd0618    call    #1806
// 2133  cd0618    call    #1806
// 2136  cd361b    call    #1b36
// 2139  cd361b    call    #1b36
// 213c  cd230e    call    #0e23
// 213f  c9        ret     
// 
// 2140  3a3a4d    ld      a,(#4d3a)
// 2143  d61e      sub     #1e
// 2145  c23021    jp      nz,#2130
// 2148  c32b21    jp      #212b
// 214b  3a324d    ld      a,(#4d32)
// 214e  d61e      sub     #1e
// 2150  c23621    jp      nz,#2136
// 2153  cd701a    call    #1a70
// 2156  af        xor     a
// 2157  32ac4e    ld      (#4eac),a
// 215a  32bc4e    ld      (#4ebc),a
// 215d  cda505    call    #05a5
// 2160  221c4d    ld      (#4d1c),hl
// 2163  3a3c4d    ld      a,(#4d3c)
// 2166  32304d    ld      (#4d30),a
// 2169  f7        rst     #30
// 216a  45        ld      b,l
// 216b  07        rlca    
// 216c  00        nop     
// 216d  c32b21    jp      #212b
// 2170  3a324d    ld      a,(#4d32)
// 2173  d62f      sub     #2f
// 2175  c23621    jp      nz,#2136
// 2178  c32b21    jp      #212b
// 217b  3a324d    ld      a,(#4d32)
// 217e  d63d      sub     #3d
// 2180  c23021    jp      nz,#2130
// 2183  c32b21    jp      #212b
// 2186  cd0618    call    #1806
// 2189  cd0618    call    #1806
// 218c  3a3a4d    ld      a,(#4d3a)
// 218f  d63d      sub     #3d
// 2191  c0        ret     nz
// 
// 2192  32064e    ld      (#4e06),a
// 2195  f7        rst     #30
// 2196  45        ld      b,l
// 2197  00        nop     
// 2198  00        nop     
// 2199  21044e    ld      hl,#4e04
// 219c  34        inc     (hl)
// 219d  c9        ret     
// 
// 219e  3a074e    ld      a,(#4e07)
// 21a1  fd21d241  ld      iy,#41d2
// 21a5  e7        rst     #20
// 21a6  c2210c    jp      nz,#0c21
// 21a9  00        nop     
// 21aa  e1        pop     hl
// 21ab  21f521    ld      hl,#21f5
// 21ae  0c        inc     c
// 21af  221e22    ld      (#221e),hl
// 21b2  44        ld      b,h
// 21b3  225d22    ld      (#225d),hl
// 21b6  0c        inc     c
// 21b7  00        nop     
// 21b8  6a        ld      l,d
// 21b9  220c00    ld      (#000c),hl
// 21bc  86        add     a,(hl)
// 21bd  220c00    ld      (#000c),hl
// 21c0  8d        adc     a,l
// 21c1  223e01    ld      (#013e),hl
// 21c4  32d245    ld      (#45d2),a
// 21c7  32d345    ld      (#45d3),a
// 21ca  32f245    ld      (#45f2),a
// 21cd  32f345    ld      (#45f3),a
// 21d0  cd0605    call    #0506
// 21d3  fd360060  ld      (iy+#00),#60
// 21d7  fd360161  ld      (iy+#01),#61
// 21db  f7        rst     #30
// 21dc  43        ld      b,e
// 21dd  08        ex      af,af'
// 21de  00        nop     
// 21df  180f      jr      #21f0           ; (15)
// 21e1  3a3a4d    ld      a,(#4d3a)
// 21e4  d62c      sub     #2c
// 21e6  c23021    jp      nz,#2130
// 21e9  3c        inc     a
// 21ea  32a04d    ld      (#4da0),a
// 21ed  32b74d    ld      (#4db7),a
// 21f0  21074e    ld      hl,#4e07
// 21f3  34        inc     (hl)
// 21f4  c9        ret     
// 
// 21f5  3a014d    ld      a,(#4d01)
// 21f8  fe77      cp      #77
// 21fa  2805      jr      z,#2201         ; (5)
// 21fc  fe78      cp      #78
// 21fe  c23021    jp      nz,#2130
// 2201  218420    ld      hl,#2084
// 2204  224e4d    ld      (#4d4e),hl
// 2207  22504d    ld      (#4d50),hl
// 220a  18e4      jr      #21f0           ; (-28)
// 220c  3a014d    ld      a,(#4d01)
// 220f  d678      sub     #78
// 2211  c23722    jp      nz,#2237
// 2214  fd360062  ld      (iy+#00),#62
// 2218  fd360163  ld      (iy+#01),#63
// 221c  18d2      jr      #21f0           ; (-46)
// 221e  3a014d    ld      a,(#4d01)
// 2221  d67b      sub     #7b
// 2223  2012      jr      nz,#2237        ; (18)
// 2225  fd360064  ld      (iy+#00),#64
// 2229  fd360165  ld      (iy+#01),#65
// 222d  fd362066  ld      (iy+#20),#66
// 2231  fd362167  ld      (iy+#21),#67
// 2235  18b9      jr      #21f0           ; (-71)
// 2237  cd0618    call    #1806
// 223a  cd0618    call    #1806
// 223d  cd361b    call    #1b36
// 2240  cd230e    call    #0e23
// 2243  c9        ret     
// 
// 2244  3a014d    ld      a,(#4d01)
// 2247  d67e      sub     #7e
// 2249  20ec      jr      nz,#2237        ; (-20)
// 224b  fd360068  ld      (iy+#00),#68
// 224f  fd360169  ld      (iy+#01),#69
// 2253  fd36206a  ld      (iy+#20),#6a
// 2257  fd36216b  ld      (iy+#21),#6b
// 225b  1893      jr      #21f0           ; (-109)
// 225d  3a014d    ld      a,(#4d01)
// 2260  d680      sub     #80
// 2262  20d3      jr      nz,#2237        ; (-45)
// 2264  f7        rst     #30
// 2265  4f        ld      c,a
// 2266  08        ex      af,af'
// 2267  00        nop     
// 2268  1886      jr      #21f0           ; (-122)
// 226a  21014d    ld      hl,#4d01
// 226d  34        inc     (hl)
// 226e  34        inc     (hl)
// 226f  fd36006c  ld      (iy+#00),#6c
// 2273  fd36016d  ld      (iy+#01),#6d
// 2277  fd362040  ld      (iy+#20),#40
// 227b  fd362140  ld      (iy+#21),#40
// 227f  f7        rst     #30
// 2280  4a        ld      c,d
// 2281  08        ex      af,af'
// 2282  00        nop     
// 2283  c3f021    jp      #21f0
// 2286  f7        rst     #30
// 2287  54        ld      d,h
// 2288  08        ex      af,af'
// 2289  00        nop     
// 228a  c3f021    jp      #21f0
// 228d  af        xor     a
// 228e  32074e    ld      (#4e07),a
// 2291  21044e    ld      hl,#4e04
// 2294  34        inc     (hl)
// 2295  34        inc     (hl)
// 2296  c9        ret     
// 
// 2297  3a084e    ld      a,(#4e08)
// 229a  e7        rst     #20
// 229b  a7        and     a
// 229c  22be22    ld      (#22be),hl
// 229f  0c        inc     c
// 22a0  00        nop     
// 22a1  dd22f522  ld      (#22f5),ix
// 22a5  fe22      cp      #22
// 22a7  3a3a4d    ld      a,(#4d3a)
// 22aa  d625      sub     #25
// 22ac  c23021    jp      nz,#2130
// 22af  3c        inc     a
// 22b0  32a04d    ld      (#4da0),a
// 22b3  32b74d    ld      (#4db7),a
// 22b6  cd0605    call    #0506
// 22b9  21084e    ld      hl,#4e08
// 22bc  34        inc     (hl)
// 22bd  c9        ret     
// 
// 22be  3a014d    ld      a,(#4d01)
// 22c1  feff      cp      #ff
// 22c3  2805      jr      z,#22ca         ; (5)
// 22c5  fefe      cp      #fe
// 22c7  c23021    jp      nz,#2130
// 22ca  3c        inc     a
// 22cb  3c        inc     a
// 22cc  32014d    ld      (#4d01),a
// 22cf  3e01      ld      a,#01
// 22d1  32b14d    ld      (#4db1),a
// 22d4  cdfe1e    call    #1efe
// 22d7  f7        rst     #30
// 22d8  4a        ld      c,d
// 22d9  09        add     hl,bc
// 22da  00        nop     
// 22db  18dc      jr      #22b9           ; (-36)
// 22dd  3a324d    ld      a,(#4d32)
// 22e0  d62d      sub     #2d
// 22e2  28d5      jr      z,#22b9         ; (-43)
// 22e4  3a004d    ld      a,(#4d00)
// 22e7  32d24d    ld      (#4dd2),a
// 22ea  3a014d    ld      a,(#4d01)
// 22ed  d608      sub     #08
// 22ef  32d34d    ld      (#4dd3),a
// 22f2  c33021    jp      #2130
// 22f5  3a324d    ld      a,(#4d32)
// 22f8  d61e      sub     #1e
// 22fa  28bd      jr      z,#22b9         ; (-67)
// 22fc  18e6      jr      #22e4           ; (-26)
// 22fe  af        xor     a
// 22ff  32084e    ld      (#4e08),a
// 2302  f7        rst     #30
// 2303  45        ld      b,l
// 2304  00        nop     
// 2305  00        nop     
// 2306  21044e    ld      hl,#4e04
// 2309  34        inc     (hl)
// 230a  c9        ret     
// 
// 	;; RAM/ROM test
// 
// 	;; Clear 74ls259 contents (irq off, sound off, flip off, etc...)
// 230b  210050    ld      hl,#5000
// 230e  0608      ld      b,#08
// 2310  af        xor     a		; a=0
// 2311  77        ld      (hl),a
// 2312  2c        inc     l
// 2313  10fc      djnz    #2311           ; (-4)
// 
// 	;; Set 4000-43ff to 0x40 (video ram)
// 2315  210040    ld      hl,#4000
// 2318  0604      ld      b,#04
// 231a  32c050    ld      (#50c0),a	; Kick the dog
kickWatchdog();
// 231d  320750    ld      (#5007),a	; Clear coin 
// 2320  3e40      ld      a,#40
// 2322  77        ld      (hl),a
// 2323  2c        inc     l
// 2324  20fc      jr      nz,#2322        ; (-4)
// 2326  24        inc     h
// 2327  10f1      djnz    #231a           ; (-15)
// 
// 	;; Set 4400-47ff to 0x0f (color ram)
// 2329  0604      ld      b,#04
// 232b  32c050    ld      (#50c0),a	; Kick the dog
kickWatchdog();
// 232e  af        xor     a		; a=0
// 232f  320750    ld      (#5007),a	; Clear coin
// 2332  3e0f      ld      a,#0f
// 2334  77        ld      (hl),a
// 2335  2c        inc     l
// 2336  20fc      jr      nz,#2334        ; (-4)
// 2338  24        inc     h
// 2339  10f0      djnz    #232b           ; (-16)
// 	
// 233b  ed5e      im      2		; interrupt mode 2
// 233d  3efa      ld      a,#fa		
// 233f  d300      out     (#00),a		; interrupt vector -> 0xfa
// 2341  af        xor     a		; a=0
// 2342  320750    ld      (#5007),a	; Clear coin
// 2345  3c        inc     a		; a=1 
// 2346  320050    ld      (#5000),a	; Enable interrupts
// 2349  fb        ei			; Enable interrupts
// 234a  76        halt			; Wait for interrupt
// 	
// 	;; Start the game ?
// 234b  32c050    ld      (#50c0),a	; Kick the dog
kickWatchdog();
// 234e  31c04f    ld      sp,#4fc0	; Set stack pointer to 0x4fc0
// 
// 2351  af        xor     a		; a=0
// 2352  210050    ld      hl,#5000	
// 2355  010808    ld      bc,#0808
// 2358  cf        rst     #8		; Restart at 0x08 (disable all)
memset (0x5000, 0, 8);

// 	;; Clear ram
// 2359  21004c    ld      hl,#4c00
// 235c  06be      ld      b,#be
// 235e  cf        rst     #8
// 235f  cf        rst     #8
// 2360  cf        rst     #8
// 2361  cf        rst     #8
memset (0x4c00, 0, 0x4be);

// 	;; Clear sound registers, sprite positions
// 2362  214050    ld      hl,#5040
// 2365  0640      ld      b,#40
// 2367  cf        rst     #8
memset (0x5040, 0, 0x40);

// 2368  32c050    ld      (#50c0),a	; Kick the dog
kickWatchdog();

// 236b  cd0d24    call    #240d		; Clear color ram
kickWatchdog();
// 2371  0600      ld      b,#00
// 2373  cded23    call    #23ed
kickWatchdog();
// 2379  21c04c    ld      hl,#4cc0
// 237c  22804c    ld      (#4c80),hl
// 237f  22824c    ld      (#4c82),hl
// 	;; 0xff -> 4cc0-4cff
// 2382  3eff      ld      a,#ff
// 2384  0640      ld      b,#40
// 2386  cf        rst     #8
memset (0x4c82, 0xff, 0x40);

// 2387  3e01      ld      a,#01
// 2389  320050    ld      (#5000),a	; enable interrupts
// 238c  fb        ei			; enable interrupts
// 238d  2a824c    ld      hl,(#4c82)
// 2390  7e        ld      a,(hl)
// 2391  a7        and     a
// 2392  fa8d23    jp      m,#238d
// 2395  36ff      ld      (hl),#ff
// 2397  2c        inc     l
// 2398  46        ld      b,(hl)
// 2399  36ff      ld      (hl),#ff
// 239b  2c        inc     l
// 239c  2002      jr      nz,#23a0        ; (2)
// 239e  2ec0      ld      l,#c0
// 23a0  22824c    ld      (#4c82),hl
// 23a3  218d23    ld      hl,#238d
// 23a6  e5        push    hl
// 23a7  e7        rst     #20
// 23a8  ed23      db      #ed, #23        ; Undocumented 8 T-State NOP
// 23aa  d7        rst     #10
// 23ab  24        inc     h
// 23ac  19        add     hl,de
// 23ad  24        inc     h
// 23ae  48        ld      c,b
// 23af  24        inc     h
// 23b0  3d        dec     a
// 23b1  25        dec     h
// 23b2  8b        adc     a,e
// 23b3  260d      ld      h,#0d
// 23b5  24        inc     h
// 23b6  98        sbc     a,b
// 23b7  2630      ld      h,#30
// 23b9  27        daa     
// 23ba  6c        ld      l,h
// 23bb  27        daa     
// 23bc  a9        xor     c
// 23bd  27        daa     
// 23be  f1        pop     af
// 23bf  27        daa     
// 23c0  3b        dec     sp
// 23c1  2865      jr      z,#2428         ; (101)
// 23c3  288f      jr      z,#2354         ; (-113)
// 23c5  28b9      jr      z,#2380         ; (-71)
// 23c7  280d      jr      z,#23d6         ; (13)
// 23c9  00        nop     
// 23ca  a2        and     d
// 23cb  26c9      ld      h,#c9
// 23cd  24        inc     h
// 23ce  35        dec     (hl)
// 23cf  2ad026    ld      hl,(#26d0)
// 23d2  87        add     a,a
// 23d3  24        inc     h
// 23d4  e8        ret     pe
// 
// 23d5  23        inc     hl
// 23d6  e3        ex      (sp),hl
// 23d7  28e0      jr      z,#23b9         ; (-32)
// 23d9  2a5a2a    ld      hl,(#2a5a)
// 23dc  6a        ld      l,d
// 23dd  2b        dec     hl
// 23de  ea2b5e    jp      pe,#5e2b
// 23e1  2c        inc     l
// 23e2  a1        and     c
// 23e3  2b        dec     hl
// 23e4  75        ld      (hl),l
// 23e5  26b2      ld      h,#b2
// 23e7  2621      ld      h,#21
// 23e9  04        inc     b
// 23ea  4e        ld      c,(hl)
// 23eb  34        inc     (hl)
// 23ec  c9        ret     
// 
// 	;; ?!?
// 23ed  78        ld      a,b
// 23ee  e7        rst     #20
// 23ef  f3        di      
// 23f0  23        inc     hl
// 23f1  00        nop     
// 23f2  24        inc     h
// 23f3  3e40      ld      a,#40
// 23f5  010400    ld      bc,#0004
// 23f8  210040    ld      hl,#4000
// 23fb  cf        rst     #8
memset (0x4000, 0x40, 256);

// 23fc  0d        dec     c
// 23fd  20fc      jr      nz,#23fb        ; (-4)
// 23ff  c9        ret     
// 
// 2400  3e40      ld      a,#40
// 2402  214040    ld      hl,#4040
// 2405  010480    ld      bc,#8004
// 2408  cf        rst     #8
memset (0x4040, 0x40, 0x80);
// 2409  0d        dec     c
// 240a  20fc      jr      nz,#2408        ; (-4)
// 240c  c9        ret     
// 
// 	;; Set Color ram to 0x00
// 240d  af        xor     a
// 240e  010400    ld      bc,#0004
// 2411  210044    ld      hl,#4400
// 2414  cf        rst     #8
memset (0x4040, 0x40, 0x80);
// 2415  0d        dec     c
// 2416  20fc      jr      nz,#2414        ; (-4)
// 2418  c9        ret     
// 
// 2419  210040    ld      hl,#4000
// 241c  013534    ld      bc,#3435
// 241f  0a        ld      a,(bc)
// 2420  a7        and     a
// 2421  c8        ret     z
// 
// 2422  fa2c24    jp      m,#242c
// 2425  5f        ld      e,a
// 2426  1600      ld      d,#00
// 2428  19        add     hl,de
// 2429  2b        dec     hl
// 242a  03        inc     bc
// 242b  0a        ld      a,(bc)
// 242c  23        inc     hl
// 242d  77        ld      (hl),a
// 242e  f5        push    af
// 242f  e5        push    hl
// 2430  11e083    ld      de,#83e0
// 2433  7d        ld      a,l
// 2434  e61f      and     #1f
// 2436  87        add     a,a
// 2437  2600      ld      h,#00
// 2439  6f        ld      l,a
// 243a  19        add     hl,de
// 243b  d1        pop     de
// 243c  a7        and     a
// 243d  ed52      sbc     hl,de
// 243f  f1        pop     af
// 2440  ee01      xor     #01
// 2442  77        ld      (hl),a
// 2443  eb        ex      de,hl
// 2444  03        inc     bc
// 2445  c31f24    jp      #241f
// 2448  210040    ld      hl,#4000
// 244b  dd21164e  ld      ix,#4e16
// 244f  fd21b535  ld      iy,#35b5
// 2453  1600      ld      d,#00
// 2455  061e      ld      b,#1e
// 2457  0e08      ld      c,#08
// 2459  dd7e00    ld      a,(ix+#00)
// 245c  fd5e00    ld      e,(iy+#00)
// 245f  19        add     hl,de
// 2460  07        rlca    
// 2461  3002      jr      nc,#2465        ; (2)
// 2463  3610      ld      (hl),#10
// 2465  fd23      inc     iy
// 2467  0d        dec     c
// 2468  20f2      jr      nz,#245c        ; (-14)
// 246a  dd23      inc     ix
// 246c  05        dec     b
// 246d  20e8      jr      nz,#2457        ; (-24)
// 246f  21344e    ld      hl,#4e34
// 2472  116440    ld      de,#4064
// 2475  eda0      ldi     
// 2477  117840    ld      de,#4078
// 247a  eda0      ldi     
// 247c  118443    ld      de,#4384
// 247f  eda0      ldi     
// 2481  119843    ld      de,#4398
// 2484  eda0      ldi     
// 2486  c9        ret     
// 
// 2487  210040    ld      hl,#4000
// 248a  dd21164e  ld      ix,#4e16
// 248e  fd21b535  ld      iy,#35b5
// 2492  1600      ld      d,#00
// 2494  061e      ld      b,#1e
// 2496  0e08      ld      c,#08
// 2498  fd5e00    ld      e,(iy+#00)
// 249b  19        add     hl,de
// 249c  7e        ld      a,(hl)
// 249d  fe10      cp      #10
// 249f  37        scf     
// 24a0  2801      jr      z,#24a3         ; (1)
// 24a2  3f        ccf     
// 24a3  ddcb0016  rl      (ix+#00)
// 24a7  fd23      inc     iy
// 24a9  0d        dec     c
// 24aa  20ec      jr      nz,#2498        ; (-20)
// 24ac  dd23      inc     ix
// 24ae  05        dec     b
// 24af  20e5      jr      nz,#2496        ; (-27)
// 24b1  216440    ld      hl,#4064
// 24b4  11344e    ld      de,#4e34
// 24b7  eda0      ldi     
// 24b9  217840    ld      hl,#4078
// 24bc  eda0      ldi     
// 24be  218443    ld      hl,#4384
// 24c1  eda0      ldi     
// 24c3  219843    ld      hl,#4398
// 24c6  eda0      ldi     
// 24c8  c9        ret     
// 
// 24c9  21164e    ld      hl,#4e16
// 24cc  3eff      ld      a,#ff
// 24ce  061e      ld      b,#1e
// 24d0  cf        rst     #8
memset (0x4040, 0x40, 0x80);
// 24d1  3e14      ld      a,#14
// 24d3  0604      ld      b,#04
// 24d5  cf        rst     #8
memset (0x4040, 0x40, 0x80);
// 24d6  c9        ret     
// 
// 24d7  58        ld      e,b
// 24d8  78        ld      a,b
// 24d9  fe02      cp      #02
// 24db  3e1f      ld      a,#1f
// 24dd  2802      jr      z,#24e1         ; (2)
// 24df  3e10      ld      a,#10
// 24e1  214044    ld      hl,#4440
// 24e4  010480    ld      bc,#8004
// 24e7  cf        rst     #8
memset (0x4040, 0x40, 0x80);
// 24e8  0d        dec     c
// 24e9  20fc      jr      nz,#24e7        ; (-4)
// 24eb  3e0f      ld      a,#0f
// 24ed  0640      ld      b,#40
// 24ef  21c047    ld      hl,#47c0
// 24f2  cf        rst     #8
memset (0x4040, 0x40, 0x80);
// 24f3  7b        ld      a,e
// 24f4  fe01      cp      #01
// 24f6  c0        ret     nz
// 
// 24f7  3e1a      ld      a,#1a
// 24f9  112000    ld      de,#0020
// 24fc  0606      ld      b,#06
// 24fe  dd21a045  ld      ix,#45a0
// 2502  dd770c    ld      (ix+#0c),a
// 2505  dd7718    ld      (ix+#18),a
// 2508  dd19      add     ix,de
// 250a  10f6      djnz    #2502           ; (-10)
// 250c  3e1b      ld      a,#1b
// 250e  0605      ld      b,#05
// 2510  dd214044  ld      ix,#4440
// 2514  dd770e    ld      (ix+#0e),a
// 2517  dd770f    ld      (ix+#0f),a
// 251a  dd7710    ld      (ix+#10),a
// 251d  dd19      add     ix,de
// 251f  10f3      djnz    #2514           ; (-13)
// 2521  0605      ld      b,#05
// 2523  dd212047  ld      ix,#4720
// 2527  dd770e    ld      (ix+#0e),a
// 252a  dd770f    ld      (ix+#0f),a
// 252d  dd7710    ld      (ix+#10),a
// 2530  dd19      add     ix,de
// 2532  10f3      djnz    #2527           ; (-13)
// 2534  3e18      ld      a,#18
// 2536  32ed45    ld      (#45ed),a
// 2539  320d46    ld      (#460d),a
// 253c  c9        ret     
// 
// 253d  dd21004c  ld      ix,#4c00
// 2541  dd360220  ld      (ix+#02),#20
// 2545  dd360420  ld      (ix+#04),#20
// 2549  dd360620  ld      (ix+#06),#20
// 254d  dd360820  ld      (ix+#08),#20
// 2551  dd360a2c  ld      (ix+#0a),#2c
// 2555  dd360c3f  ld      (ix+#0c),#3f
// 2559  dd360301  ld      (ix+#03),#01
// 255d  dd360503  ld      (ix+#05),#03
// 2561  dd360705  ld      (ix+#07),#05
// 2565  dd360907  ld      (ix+#09),#07
// 2569  dd360b09  ld      (ix+#0b),#09
// 256d  dd360d00  ld      (ix+#0d),#00
// 2571  78        ld      a,b
// 2572  a7        and     a
// 2573  c20f26    jp      nz,#260f
// 2576  216480    ld      hl,#8064
// 2579  22004d    ld      (#4d00),hl
// 257c  217c80    ld      hl,#807c
// 257f  22024d    ld      (#4d02),hl
// 2582  217c90    ld      hl,#907c
// 2585  22044d    ld      (#4d04),hl
// 2588  217c70    ld      hl,#707c
// 258b  22064d    ld      (#4d06),hl
// 258e  21c480    ld      hl,#80c4
// 2591  22084d    ld      (#4d08),hl
// 2594  212c2e    ld      hl,#2e2c
// 2597  220a4d    ld      (#4d0a),hl
// 259a  22314d    ld      (#4d31),hl
// 259d  212f2e    ld      hl,#2e2f
// 25a0  220c4d    ld      (#4d0c),hl
// 25a3  22334d    ld      (#4d33),hl
// 25a6  212f30    ld      hl,#302f
// 25a9  220e4d    ld      (#4d0e),hl
// 25ac  22354d    ld      (#4d35),hl
// 25af  212f2c    ld      hl,#2c2f
// 25b2  22104d    ld      (#4d10),hl
// 25b5  22374d    ld      (#4d37),hl
// 25b8  21382e    ld      hl,#2e38
// 25bb  22124d    ld      (#4d12),hl
// 25be  22394d    ld      (#4d39),hl
// 25c1  210001    ld      hl,#0100
// 25c4  22144d    ld      (#4d14),hl
// 25c7  221e4d    ld      (#4d1e),hl
// 25ca  210100    ld      hl,#0001
// 25cd  22164d    ld      (#4d16),hl
// 25d0  22204d    ld      (#4d20),hl
// 25d3  21ff00    ld      hl,#00ff
// 25d6  22184d    ld      (#4d18),hl
// 25d9  22224d    ld      (#4d22),hl
// 25dc  21ff00    ld      hl,#00ff
// 25df  221a4d    ld      (#4d1a),hl
// 25e2  22244d    ld      (#4d24),hl
// 25e5  210001    ld      hl,#0100
// 25e8  221c4d    ld      (#4d1c),hl
// 25eb  22264d    ld      (#4d26),hl
// 25ee  210201    ld      hl,#0102
// 25f1  22284d    ld      (#4d28),hl
// 25f4  222c4d    ld      (#4d2c),hl
// 25f7  210303    ld      hl,#0303
// 25fa  222a4d    ld      (#4d2a),hl
// 25fd  222e4d    ld      (#4d2e),hl
// 2600  3e02      ld      a,#02
// 2602  32304d    ld      (#4d30),a
// 2605  323c4d    ld      (#4d3c),a
// 2608  210000    ld      hl,#0000
// 260b  22d24d    ld      (#4dd2),hl
// 260e  c9        ret     
// 
// 260f  219400    ld      hl,#0094
// 2612  22004d    ld      (#4d00),hl
// 2615  22024d    ld      (#4d02),hl
// 2618  22044d    ld      (#4d04),hl
// 261b  22064d    ld      (#4d06),hl
// 261e  21321e    ld      hl,#1e32
// 2621  220a4d    ld      (#4d0a),hl
// 2624  220c4d    ld      (#4d0c),hl
// 2627  220e4d    ld      (#4d0e),hl
// 262a  22104d    ld      (#4d10),hl
// 262d  22314d    ld      (#4d31),hl
// 2630  22334d    ld      (#4d33),hl
// 2633  22354d    ld      (#4d35),hl
// 2636  22374d    ld      (#4d37),hl
// 2639  210001    ld      hl,#0100
// 263c  22144d    ld      (#4d14),hl
// 263f  22164d    ld      (#4d16),hl
// 2642  22184d    ld      (#4d18),hl
// 2645  221a4d    ld      (#4d1a),hl
// 2648  221e4d    ld      (#4d1e),hl
// 264b  22204d    ld      (#4d20),hl
// 264e  22224d    ld      (#4d22),hl
// 2651  22244d    ld      (#4d24),hl
// 2654  221c4d    ld      (#4d1c),hl
// 2657  22264d    ld      (#4d26),hl
// 265a  21284d    ld      hl,#4d28
// 265d  3e02      ld      a,#02
// 265f  0609      ld      b,#09
// 2661  cf        rst     #8
memset (0x4040, 0x40, 0x80);
// 2662  323c4d    ld      (#4d3c),a
// 2665  219408    ld      hl,#0894
// 2668  22084d    ld      (#4d08),hl
// 266b  21321f    ld      hl,#1f32
// 266e  22124d    ld      (#4d12),hl
// 2671  22394d    ld      (#4d39),hl
// 2674  c9        ret     
// 
// 2675  210000    ld      hl,#0000
// 2678  22d24d    ld      (#4dd2),hl
// 267b  22084d    ld      (#4d08),hl
// 267e  22004d    ld      (#4d00),hl
// 2681  22024d    ld      (#4d02),hl
// 2684  22044d    ld      (#4d04),hl
// 2687  22064d    ld      (#4d06),hl
// 268a  c9        ret     
// 
// 268b  3e55      ld      a,#55
// 268d  32944d    ld      (#4d94),a
// 2690  05        dec     b
// 2691  c8        ret     z
// 
// 2692  3e01      ld      a,#01
// 2694  32a04d    ld      (#4da0),a
// 2697  c9        ret     
// 
// 2698  3e01      ld      a,#01
// 269a  32004e    ld      (#4e00),a
// 269d  af        xor     a
// 269e  32014e    ld      (#4e01),a
// 26a1  c9        ret     
// 
// 26a2  af        xor     a
// 26a3  11004d    ld      de,#4d00
// 26a6  21004e    ld      hl,#4e00
// 26a9  12        ld      (de),a
// 26aa  13        inc     de
// 26ab  a7        and     a
// 26ac  ed52      sbc     hl,de
// 26ae  c2a626    jp      nz,#26a6
// 26b1  c9        ret     
// 
// 26b2  dd213641  ld      ix,#4136
// 26b6  3a714e    ld      a,(#4e71)
// 26b9  e60f      and     #0f
// 26bb  c630      add     a,#30
// 26bd  dd7700    ld      (ix+#00),a
// 26c0  3a714e    ld      a,(#4e71)
// 26c3  0f        rrca    
// 26c4  0f        rrca    
// 26c5  0f        rrca    
// 26c6  0f        rrca    
// 26c7  e60f      and     #0f
// 26c9  c8        ret     z
// 
// 26ca  c630      add     a,#30
// 26cc  dd7720    ld      (ix+#20),a
// 26cf  c9        ret     
// 
// 26d0  3a8050    ld      a,(#5080)
// 26d3  47        ld      b,a
// 26d4  e603      and     #03
// 26d6  c2de26    jp      nz,#26de
// 26d9  216e4e    ld      hl,#coinCredits
// 26dc  36ff      ld      (hl),#ff
// 26de  4f        ld      c,a
// 26df  1f        rra     
// 26e0  ce00      adc     a,#00
// 26e2  326b4e    ld      (#COINS_PER_CREDIT),a
// 26e5  e602      and     #02
// 26e7  a9        xor     c
// 26e8  326d4e    ld      (#CREDITS_PER_COIN),a
// 26eb  78        ld      a,b
// 26ec  0f        rrca    
// 26ed  0f        rrca    
// 26ee  e603      and     #03
// 26f0  3c        inc     a
// 26f1  fe04      cp      #04
// 26f3  2001      jr      nz,#26f6        ; (1)
// 26f5  3c        inc     a
// 26f6  326f4e    ld      (#LIVES_PER_GAME),a
// 26f9  78        ld      a,b
// 26fa  0f        rrca    
// 26fb  0f        rrca    
// 26fc  0f        rrca    
// 26fd  0f        rrca    
// 26fe  e603      and     #03
// 2700  212827    ld      hl,#2728
// 2703  d7        rst     #10
// 2704  32714e    ld      (#4e71),a
// 2707  78        ld      a,b
// 2708  07        rlca    
// 2709  2f        cpl     
// 270a  e601      and     #01
// 270c  32754e    ld      (#4e75),a
// 270f  78        ld      a,b
// 2710  07        rlca    
// 2711  07        rlca    
// 2712  2f        cpl     
// 2713  e601      and     #01
// 2715  47        ld      b,a
// 2716  212c27    ld      hl,#272c
// 2719  df        rst     #18
// 271a  22734e    ld      (#4e73),hl
// 271d  3a4050    ld      a,(#5040)
// 2720  07        rlca    
// 2721  2f        cpl     
// 2722  e601      and     #01
// 2724  32724e    ld      (#4e72),a
// 2727  c9        ret     
// 
// 2728  1015      djnz    #273f           ; (21)
// 272a  20ff      jr      nz,#272b        ; (-1)
// 272c  68        ld      l,b
// 272d  00        nop     
// 272e  7d        ld      a,l
// 272f  00        nop     
// 2730  3ac14d    ld      a,(#4dc1)
// 2733  cb47      bit     0,a
// 2735  c25827    jp      nz,#2758
// 2738  3ab64d    ld      a,(#4db6)
// 273b  a7        and     a
// 273c  201a      jr      nz,#2758        ; (26)
// 273e  3a044e    ld      a,(#4e04)
// 2741  fe03      cp      #03
// 2743  2013      jr      nz,#2758        ; (19)
// 2745  2a0a4d    ld      hl,(#4d0a)
// 2748  3a2c4d    ld      a,(#4d2c)
// 274b  111d22    ld      de,#221d
// 274e  cd6629    call    #2966
// 2751  221e4d    ld      (#4d1e),hl
// 2754  322c4d    ld      (#4d2c),a
// 2757  c9        ret     
// 
// 2758  2a0a4d    ld      hl,(#4d0a)
// 275b  ed5b394d  ld      de,(#4d39)
// 275f  3a2c4d    ld      a,(#4d2c)
// 2762  cd6629    call    #2966
// 2765  221e4d    ld      (#4d1e),hl
// 2768  322c4d    ld      (#4d2c),a
// 276b  c9        ret     
// 
// 276c  3ac14d    ld      a,(#4dc1)
// 276f  cb47      bit     0,a
// 2771  c28e27    jp      nz,#278e
// 2774  3a044e    ld      a,(#4e04)
// 2777  fe03      cp      #03
// 2779  2013      jr      nz,#278e        ; (19)
// 277b  2a0c4d    ld      hl,(#4d0c)
// 277e  3a2d4d    ld      a,(#4d2d)
// 2781  111d39    ld      de,#391d
// 2784  cd6629    call    #2966
// 2787  22204d    ld      (#4d20),hl
// 278a  322d4d    ld      (#4d2d),a
// 278d  c9        ret     
// 
// 278e  ed5b394d  ld      de,(#4d39)
// 2792  2a1c4d    ld      hl,(#4d1c)
// 2795  29        add     hl,hl
// 2796  29        add     hl,hl
// 2797  19        add     hl,de
// 2798  eb        ex      de,hl
// 2799  2a0c4d    ld      hl,(#4d0c)
// 279c  3a2d4d    ld      a,(#4d2d)
// 279f  cd6629    call    #2966
// 27a2  22204d    ld      (#4d20),hl
// 27a5  322d4d    ld      (#4d2d),a
// 27a8  c9        ret     
// 
// 27a9  3ac14d    ld      a,(#4dc1)
// 27ac  cb47      bit     0,a
// 27ae  c2cb27    jp      nz,#27cb
// 27b1  3a044e    ld      a,(#4e04)
// 27b4  fe03      cp      #03
// 27b6  2013      jr      nz,#27cb        ; (19)
// 27b8  2a0e4d    ld      hl,(#4d0e)
// 27bb  3a2e4d    ld      a,(#4d2e)
// 27be  114020    ld      de,#2040
// 27c1  cd6629    call    #2966
// 27c4  22224d    ld      (#4d22),hl
// 27c7  322e4d    ld      (#4d2e),a
// 27ca  c9        ret     
// 
// 27cb  ed4b0a4d  ld      bc,(#4d0a)
// 27cf  ed5b394d  ld      de,(#4d39)
// 27d3  2a1c4d    ld      hl,(#4d1c)
// 27d6  29        add     hl,hl
// 27d7  19        add     hl,de
// 27d8  7d        ld      a,l
// 27d9  87        add     a,a
// 27da  91        sub     c
// 27db  6f        ld      l,a
// 27dc  7c        ld      a,h
// 27dd  87        add     a,a
// 27de  90        sub     b
// 27df  67        ld      h,a
// 27e0  eb        ex      de,hl
// 27e1  2a0e4d    ld      hl,(#4d0e)
// 27e4  3a2e4d    ld      a,(#4d2e)
// 27e7  cd6629    call    #2966
// 27ea  22224d    ld      (#4d22),hl
// 27ed  322e4d    ld      (#4d2e),a
// 27f0  c9        ret     
// 
// 27f1  3ac14d    ld      a,(#4dc1)
// 27f4  cb47      bit     0,a
// 27f6  c21328    jp      nz,#2813
// 27f9  3a044e    ld      a,(#4e04)
// 27fc  fe03      cp      #03
// 27fe  2013      jr      nz,#2813        ; (19)
// 2800  2a104d    ld      hl,(#4d10)
// 2803  3a2f4d    ld      a,(#4d2f)
// 2806  11403b    ld      de,#3b40
// 2809  cd6629    call    #2966
// 280c  22244d    ld      (#4d24),hl
// 280f  322f4d    ld      (#4d2f),a
// 2812  c9        ret     
// 
// 2813  dd21394d  ld      ix,#4d39
// 2817  fd21104d  ld      iy,#4d10
// 281b  cdea29    call    #29ea
// 281e  114000    ld      de,#0040
// 2821  a7        and     a
// 2822  ed52      sbc     hl,de
// 2824  da0028    jp      c,#2800
// 2827  2a104d    ld      hl,(#4d10)
// 282a  ed5b394d  ld      de,(#4d39)
// 282e  3a2f4d    ld      a,(#4d2f)
// 2831  cd6629    call    #2966
// 2834  22244d    ld      (#4d24),hl
// 2837  322f4d    ld      (#4d2f),a
// 283a  c9        ret     
// 
// 283b  3aac4d    ld      a,(#4dac)
// 283e  a7        and     a
// 283f  ca5528    jp      z,#2855
// 2842  112c2e    ld      de,#2e2c
// 2845  2a0a4d    ld      hl,(#4d0a)
// 2848  3a2c4d    ld      a,(#4d2c)
// 284b  cd6629    call    #2966
// 284e  221e4d    ld      (#4d1e),hl
// 2851  322c4d    ld      (#4d2c),a
// 2854  c9        ret     
// 
// 2855  2a0a4d    ld      hl,(#4d0a)
// 2858  3a2c4d    ld      a,(#4d2c)
// 285b  cd1e29    call    #291e
// 285e  221e4d    ld      (#4d1e),hl
// 2861  322c4d    ld      (#4d2c),a
// 2864  c9        ret     
// 
// 2865  3aad4d    ld      a,(#4dad)
// 2868  a7        and     a
// 2869  ca7f28    jp      z,#287f
// 286c  112c2e    ld      de,#2e2c
// 286f  2a0c4d    ld      hl,(#4d0c)
// 2872  3a2d4d    ld      a,(#4d2d)
// 2875  cd6629    call    #2966
// 2878  22204d    ld      (#4d20),hl
// 287b  322d4d    ld      (#4d2d),a
// 287e  c9        ret     
// 
// 287f  2a0c4d    ld      hl,(#4d0c)
// 2882  3a2d4d    ld      a,(#4d2d)
// 2885  cd1e29    call    #291e
// 2888  22204d    ld      (#4d20),hl
// 288b  322d4d    ld      (#4d2d),a
// 288e  c9        ret     
// 
// 288f  3aae4d    ld      a,(#4dae)
// 2892  a7        and     a
// 2893  caa928    jp      z,#28a9
// 2896  112c2e    ld      de,#2e2c
// 2899  2a0e4d    ld      hl,(#4d0e)
// 289c  3a2e4d    ld      a,(#4d2e)
// 289f  cd6629    call    #2966
// 28a2  22224d    ld      (#4d22),hl
// 28a5  322e4d    ld      (#4d2e),a
// 28a8  c9        ret     
// 
// 28a9  2a0e4d    ld      hl,(#4d0e)
// 28ac  3a2e4d    ld      a,(#4d2e)
// 28af  cd1e29    call    #291e
// 28b2  22224d    ld      (#4d22),hl
// 28b5  322e4d    ld      (#4d2e),a
// 28b8  c9        ret     
// 
// 28b9  3aaf4d    ld      a,(#4daf)
// 28bc  a7        and     a
// 28bd  cad328    jp      z,#28d3
// 28c0  112c2e    ld      de,#2e2c
// 28c3  2a104d    ld      hl,(#4d10)
// 28c6  3a2f4d    ld      a,(#4d2f)
// 28c9  cd6629    call    #2966
// 28cc  22244d    ld      (#4d24),hl
// 28cf  322f4d    ld      (#4d2f),a
// 28d2  c9        ret     
// 
// 28d3  2a104d    ld      hl,(#4d10)
// 28d6  3a2f4d    ld      a,(#4d2f)
// 28d9  cd1e29    call    #291e
// 28dc  22244d    ld      (#4d24),hl
// 28df  322f4d    ld      (#4d2f),a
// 28e2  c9        ret     
// 
// 28e3  3aa74d    ld      a,(#4da7)
// 28e6  a7        and     a
// 28e7  cafe28    jp      z,#28fe
// 28ea  2a124d    ld      hl,(#4d12)
// 28ed  ed5b0c4d  ld      de,(#4d0c)
// 28f1  3a3c4d    ld      a,(#4d3c)
// 28f4  cd6629    call    #2966
// 28f7  22264d    ld      (#4d26),hl
// 28fa  323c4d    ld      (#4d3c),a
// 28fd  c9        ret     
// 
// 28fe  2a394d    ld      hl,(#4d39)
// 2901  ed4b0c4d  ld      bc,(#4d0c)
// 2905  7d        ld      a,l
// 2906  87        add     a,a
// 2907  91        sub     c
// 2908  6f        ld      l,a
// 2909  7c        ld      a,h
// 290a  87        add     a,a
// 290b  90        sub     b
// 290c  67        ld      h,a
// 290d  eb        ex      de,hl
// 290e  2a124d    ld      hl,(#4d12)
// 2911  3a3c4d    ld      a,(#4d3c)
// 2914  cd6629    call    #2966
// 2917  22264d    ld      (#4d26),hl
// 291a  323c4d    ld      (#4d3c),a
// 291d  c9        ret     
// 
// 291e  223e4d    ld      (#4d3e),hl
// 2921  ee02      xor     #02
// 2923  323d4d    ld      (#4d3d),a
// 2926  cd232a    call    #2a23
// 2929  e603      and     #03
// 292b  213b4d    ld      hl,#4d3b
// 292e  77        ld      (hl),a
// 292f  87        add     a,a
// 2930  5f        ld      e,a
// 2931  1600      ld      d,#00
// 2933  dd21ff32  ld      ix,#32ff
// 2937  dd19      add     ix,de
// 2939  fd213e4d  ld      iy,#4d3e
// 293d  3a3d4d    ld      a,(#4d3d)
// 2940  be        cp      (hl)
// 2941  ca5729    jp      z,#2957
// 2944  cd0f20    call    #200f
// 2947  e6c0      and     #c0
// 2949  d6c0      sub     #c0
// 294b  280a      jr      z,#2957         ; (10)
// 294d  dd6e00    ld      l,(ix+#00)
// 2950  dd6601    ld      h,(ix+#01)
// 2953  3a3b4d    ld      a,(#4d3b)
// 2956  c9        ret     
// 
// 2957  dd23      inc     ix
// 2959  dd23      inc     ix
// 295b  213b4d    ld      hl,#4d3b
// 295e  7e        ld      a,(hl)
// 295f  3c        inc     a
// 2960  e603      and     #03
// 2962  77        ld      (hl),a
// 2963  c33d29    jp      #293d
// 2966  223e4d    ld      (#4d3e),hl
// 2969  ed53404d  ld      (#4d40),de
// 296d  323b4d    ld      (#4d3b),a
// 2970  ee02      xor     #02
// 2972  323d4d    ld      (#4d3d),a
// 2975  21ffff    ld      hl,#ffff
// 2978  22444d    ld      (#4d44),hl
// 297b  dd21ff32  ld      ix,#32ff
// 297f  fd213e4d  ld      iy,#4d3e
// 2983  21c74d    ld      hl,#4dc7
// 2986  3600      ld      (hl),#00
// 2988  3a3d4d    ld      a,(#4d3d)
// 298b  be        cp      (hl)
// 298c  cac629    jp      z,#29c6
// 298f  cd0020    call    #2000
// 2992  22424d    ld      (#4d42),hl
// 2995  cd6500    call    #0065
// 2998  7e        ld      a,(hl)
// 2999  e6c0      and     #c0
// 299b  d6c0      sub     #c0
// 299d  2827      jr      z,#29c6         ; (39)
// 299f  dde5      push    ix
// 29a1  fde5      push    iy
// 29a3  dd21404d  ld      ix,#4d40
// 29a7  fd21424d  ld      iy,#4d42
// 29ab  cdea29    call    #29ea
// 29ae  fde1      pop     iy
// 29b0  dde1      pop     ix
// 29b2  eb        ex      de,hl
// 29b3  2a444d    ld      hl,(#4d44)
// 29b6  a7        and     a
// 29b7  ed52      sbc     hl,de
// 29b9  dac629    jp      c,#29c6
// 29bc  ed53444d  ld      (#4d44),de
// 29c0  3ac74d    ld      a,(#4dc7)
// 29c3  323b4d    ld      (#4d3b),a
// 29c6  dd23      inc     ix
// 29c8  dd23      inc     ix
// 29ca  21c74d    ld      hl,#4dc7
// 29cd  34        inc     (hl)
// 29ce  3e04      ld      a,#04
// 29d0  be        cp      (hl)
// 29d1  c28829    jp      nz,#2988
// 29d4  3a3b4d    ld      a,(#4d3b)
// 29d7  87        add     a,a
// 29d8  5f        ld      e,a
// 29d9  1600      ld      d,#00
// 29db  dd21ff32  ld      ix,#32ff
// 29df  dd19      add     ix,de
// 29e1  dd6e00    ld      l,(ix+#00)
// 29e4  dd6601    ld      h,(ix+#01)
// 29e7  cb3f      srl     a
// 29e9  c9        ret     
// 
// 29ea  dd7e00    ld      a,(ix+#00)
// 29ed  fd4600    ld      b,(iy+#00)
// 29f0  90        sub     b
// 29f1  d2f929    jp      nc,#29f9
// 29f4  78        ld      a,b
// 29f5  dd4600    ld      b,(ix+#00)
// 29f8  90        sub     b
// 29f9  cd122a    call    #2a12
// 29fc  e5        push    hl
// 29fd  dd7e01    ld      a,(ix+#01)
// 2a00  fd4601    ld      b,(iy+#01)
// 2a03  90        sub     b
// 2a04  d20c2a    jp      nc,#2a0c
// 2a07  78        ld      a,b
// 2a08  dd4601    ld      b,(ix+#01)
// 2a0b  90        sub     b
// 2a0c  cd122a    call    #2a12
// 2a0f  c1        pop     bc
// 2a10  09        add     hl,bc
// 2a11  c9        ret     
// 
// 2a12  67        ld      h,a
// 2a13  5f        ld      e,a
// 2a14  2e00      ld      l,#00
// 2a16  55        ld      d,l
// 2a17  0e08      ld      c,#08
// 2a19  29        add     hl,hl
// 2a1a  d21e2a    jp      nc,#2a1e
// 2a1d  19        add     hl,de
// 2a1e  0d        dec     c
// 2a1f  c2192a    jp      nz,#2a19
// 2a22  c9        ret     
// 
// 2a23  2ac94d    ld      hl,(#4dc9)
// 2a26  54        ld      d,h
// 2a27  5d        ld      e,l
// 2a28  29        add     hl,hl
// 2a29  29        add     hl,hl
// 2a2a  19        add     hl,de
// 2a2b  23        inc     hl
// 2a2c  7c        ld      a,h
// 2a2d  e61f      and     #1f
// 2a2f  67        ld      h,a
// 2a30  7e        ld      a,(hl)
// 2a31  22c94d    ld      (#4dc9),hl
// 2a34  c9        ret     
// 
// 2a35  114040    ld      de,#4040
// 2a38  21c043    ld      hl,#43c0
// 2a3b  a7        and     a
// 2a3c  ed52      sbc     hl,de
// 2a3e  c8        ret     z
// 
// 2a3f  1a        ld      a,(de)
// 2a40  fe10      cp      #10
// 2a42  ca532a    jp      z,#2a53
// 2a45  fe12      cp      #12
// 2a47  ca532a    jp      z,#2a53
// 2a4a  fe14      cp      #14
// 2a4c  ca532a    jp      z,#2a53
// 2a4f  13        inc     de
// 2a50  c3382a    jp      #2a38
// 2a53  3e40      ld      a,#40
// 2a55  12        ld      (de),a
// 2a56  13        inc     de
// 2a57  c3382a    jp      #2a38
// 2a5a  3a004e    ld      a,(#4e00)
// 2a5d  fe01      cp      #01
// 2a5f  c8        ret     z

// 2a60  21172b    ld      hl,#2b17
hl = scoreTable;

// 2a63  df        rst     #18
// 2a64  eb        ex      de,hl
// 2a65  cd0b2b    call    #2b0b
// 2a68  7b        ld      a,e
// 2a69  86        add     a,(hl)
// 2a6a  27        daa     
// 2a6b  77        ld      (hl),a
// 2a6c  23        inc     hl
// 2a6d  7a        ld      a,d
// 2a6e  8e        adc     a,(hl)
// 2a6f  27        daa     
// 2a70  77        ld      (hl),a
// 2a71  5f        ld      e,a
// 2a72  23        inc     hl
// 2a73  3e00      ld      a,#00
// 2a75  8e        adc     a,(hl)
// 2a76  27        daa     
// 2a77  77        ld      (hl),a
// 2a78  57        ld      d,a
// 2a79  eb        ex      de,hl
// 2a7a  29        add     hl,hl
// 2a7b  29        add     hl,hl
// 2a7c  29        add     hl,hl
// 2a7d  29        add     hl,hl
// 2a7e  3a714e    ld      a,(#4e71)
// 2a81  3d        dec     a
// 2a82  bc        cp      h
// 2a83  dc332b    call    c,#2b33
// 2a86  cdaf2a    call    #2aaf
// 2a89  13        inc     de
// 2a8a  13        inc     de
// 2a8b  13        inc     de
// 2a8c  218a4e    ld      hl,#4e8a	; High score?
// 2a8f  0603      ld      b,#03
// 2a91  1a        ld      a,(de)
// 2a92  be        cp      (hl)
// 2a93  d8        ret     c
// 
// 2a94  2005      jr      nz,#2a9b        ; (5)
// 2a96  1b        dec     de
// 2a97  2b        dec     hl
// 2a98  10f7      djnz    #2a91           ; (-9)
// 2a9a  c9        ret     
// 
// 2a9b  cd0b2b    call    #2b0b

// 2a9e  11884e    ld      de,#4e88
highScore = (de);

// 2aa1  010300    ld      bc,#0003
// 2aa4  edb0      ldir    
// 2aa6  1b        dec     de
// 2aa7  010403    ld      bc,#0304
// 2aaa  21f243    ld      hl,#43f2
// 2aad  180f      jr      #2abe           ; (15)
// 2aaf  3a094e    ld      a,(#4e09)
// 2ab2  010403    ld      bc,#0304
// 2ab5  21fc43    ld      hl,#43fc
// 2ab8  a7        and     a
// 2ab9  2803      jr      z,#2abe         ; (3)
// 2abb  21e943    ld      hl,#43e9
// 
// 	;; Draw score, (b) bytes
// 2abe  1a        ld      a,(de)
// 2abf  0f        rrca    
// 2ac0  0f        rrca    
// 2ac1  0f        rrca    
// 2ac2  0f        rrca    
// 2ac3  cdce2a    call    #2ace
// 2ac6  1a        ld      a,(de)
// 2ac7  cdce2a    call    #2ace
// 2aca  1b        dec     de
// 2acb  10f1      djnz    #2abe           ; (-15)
// 2acd  c9        ret     
// 
// 	;;  Draw digit (discard leading 0's)
// 2ace  e60f      and     #0f
// 2ad0  2804      jr      z,#2ad6         ; a=0?
// 2ad2  0e00      ld      c,#00
// 2ad4  1807      jr      #2add           ; 
// 2ad6  79        ld      a,c		; c->a 
// 2ad7  a7        and     a
// 2ad8  2803      jr      z,#2add         ; (3)
// 2ada  3e40      ld      a,#40
// 2adc  0d        dec     c
// 2add  77        ld      (hl),a
// 2ade  2b        dec     hl
// 2adf  c9        ret     
// 
// 2ae0  0600      ld      b,#00		; Draw 'High Score' 
// 2ae2  cd5e2c    call    #2c5e

// 2ae5  af        xor     a		; Clear P1 score 
// 2ae6  21804e    ld      hl,#4e80
// 2ae9  0608      ld      b,#08
// 2aeb  cf        rst     #8
P1Score = 0;

// ;2aec  010403    ld      bc,#0304	; Draw Score P1
// ;2aef  11824e    ld      de,#4e82
// 2aec  010403    ld      bc,#0407	; 4 bytes, drop 7 leading zeroes 
// 2aef  11824e    ld      de,#4e83	 
// 2af2  21fc43    ld      hl,#43fc	; location 
// 2af5  cdbe2a    call    #2abe
// 	
// ;2af8  010403    ld      bc,#0304	; Draw Score P2
// ;2afb  11864e    ld      de,#4e86
// 2af8  010403    ld      bc,#0407
// 2afb  11864e    ld      de,#4e87
// 2afe  21e943    ld      hl,#43e9
// 2b01  3a704e    ld      a,(#4e70)
// 2b04  a7        and     a
// 2b05  20b7      jr      nz,#2abe        ; score needed
// 
// 2b07  0e06      ld      c,#06
// 2b09  18b3      jr      #2abe           ; draw blanks
// 
// 	
// 2b0b  3a094e    ld      a,(#4e09)
// 2b0e  21804e    ld      hl,#4e80
// 2b11  a7        and     a
// 2b12  c8        ret     z
// 
// 2b13  21844e    ld      hl,#4e84
hl = &p2Score;
// 2b16  c9        ret     
// 
uint16_t scoreTable[] =
{
    0x0001,			// dot
    0x0005,			// pellet
    0x0020,			// ghost 1
    0x0040,			// ghost 2
    0x0080,			// ghost 3
    0x0160,			// ghost 4
    0x0010,			// fruit
    0x0030,			// fruit
    0x0050,			// fruit
    0x0070,			// fruit
    0x0100,			// fruit
    0x0200,			// fruit
    0x0300,			// fruit
    0x0500		        // fruit
};

// 
// 2b33  13        inc     de
// 2b34  6b        ld      l,e
// 2b35  62        ld      h,d
// 2b36  1b        dec     de
// 2b37  cb46      bit     0,(hl)
// 2b39  c0        ret     nz
// 
// 2b3a  cbc6      set     0,(hl)
// 2b3c  219c4e    ld      hl,#4e9c
// 2b3f  cbc6      set     0,(hl)
// 2b41  21144e    ld      hl,#4e14
// 2b44  34        inc     (hl)
// 2b45  21154e    ld      hl,#4e15
// 2b48  34        inc     (hl)
// 2b49  46        ld      b,(hl)
// 2b4a  211a40    ld      hl,#401a
// 2b4d  0e05      ld      c,#05
// 2b4f  78        ld      a,b
// 2b50  a7        and     a
// 2b51  280e      jr      z,#2b61         ; (14)
// 2b53  fe06      cp      #06
// 2b55  300a      jr      nc,#2b61        ; (10)
// 2b57  3e20      ld      a,#20
// 2b59  cd8f2b    call    #2b8f
// 2b5c  2b        dec     hl
// 2b5d  2b        dec     hl
// 2b5e  0d        dec     c
// 2b5f  10f6      djnz    #2b57           ; (-10)
// 2b61  0d        dec     c
// 2b62  f8        ret     m
// 
// 2b63  cd7e2b    call    #2b7e
// 2b66  2b        dec     hl
// 2b67  2b        dec     hl
// 2b68  18f7      jr      #2b61           ; (-9)
// 2b6a  3a004e    ld      a,(#4e00)
// 2b6d  fe01      cp      #01
// 2b6f  c8        ret     z
// 
// 2b70  cdcd2b    call    #2bcd
// 2b73  12        ld      (de),a
// 2b74  44        ld      b,h
// 2b75  09        add     hl,bc
// 2b76  0a        ld      a,(bc)
// 2b77  02        ld      (bc),a
// 2b78  21154e    ld      hl,#4e15
// 2b7b  46        ld      b,(hl)
// 2b7c  18cc      jr      #2b4a           ; (-52)
// 2b7e  3e40      ld      a,#40
// 	;; Draw [a] to a 2x2 char square
// 2b80  e5        push    hl
// 2b81  d5        push    de
// 2b82  77        ld      (hl),a
// 2b83  23        inc     hl
// 2b84  77        ld      (hl),a
// 2b85  111f00    ld      de,#001f
// 2b88  19        add     hl,de
// 2b89  77        ld      (hl),a
// 2b8a  23        inc     hl
// 2b8b  77        ld      (hl),a
// 2b8c  d1        pop     de
// 2b8d  e1        pop     hl
// 2b8e  c9        ret     
// 
// 	;; Used to draw fruit
// 2b8f  e5        push    hl
// 2b90  d5        push    de
// 2b91  111f00    ld      de,#001f
// 2b94  77        ld      (hl),a
// 2b95  3c        inc     a
// 2b96  23        inc     hl
// 2b97  77        ld      (hl),a
// 2b98  3c        inc     a
// 2b99  19        add     hl,de
// 2b9a  77        ld      (hl),a
// 2b9b  3c        inc     a
// 2b9c  23        inc     hl
// 2b9d  77        ld      (hl),a
// 2b9e  d1        pop     de
// 2b9f  e1        pop     hl
// 2ba0  c9        ret     
// 
// 	;; Draw # credits/free play on bottom of screen
// 2ba1  3a6e4e    ld      a,(#coinCredits)		; Check # credits	
// 2ba4  feff      cp      #ff
// 2ba6  2005      jr      nz,#2bad        ; (5)
// 2ba8  0602      ld      b,#02
// 2baa  c35e2c    jp      #2c5e
// 2bad  0601      ld      b,#01
// 2baf  cd5e2c    call    #2c5e
// 2bb2  3a6e4e    ld      a,(#coinCredits)
// 2bb5  e6f0      and     #f0
// 2bb7  2809      jr      z,#2bc2         ; (9)
// 2bb9  0f        rrca    
// 2bba  0f        rrca    
// 2bbb  0f        rrca    
// 2bbc  0f        rrca    
// 2bbd  c630      add     a,#30
// 2bbf  323440    ld      (#4034),a
// 2bc2  3a6e4e    ld      a,(#coinCredits)
// 2bc5  e60f      and     #0f
// 2bc7  c630      add     a,#30
// 2bc9  323340    ld      (#4033),a
// 2bcc  c9        ret     
// 
// 2bcd  e1        pop     hl
// 2bce  5e        ld      e,(hl)
// 2bcf  23        inc     hl
// 2bd0  56        ld      d,(hl)
// 2bd1  23        inc     hl
// 2bd2  4e        ld      c,(hl)
// 2bd3  23        inc     hl
// 2bd4  46        ld      b,(hl)
// 2bd5  23        inc     hl
// 2bd6  7e        ld      a,(hl)
// 2bd7  23        inc     hl
// 2bd8  e5        push    hl
// 2bd9  eb        ex      de,hl
// 2bda  112000    ld      de,#0020
// 2bdd  e5        push    hl
// 2bde  c5        push    bc
// 2bdf  71        ld      (hl),c
// 2be0  23        inc     hl
// 2be1  10fc      djnz    #2bdf           ; (-4)
// 2be3  c1        pop     bc
// 2be4  e1        pop     hl
// 2be5  19        add     hl,de
// 2be6  3d        dec     a
// 2be7  20f4      jr      nz,#2bdd        ; (-12)
// 2be9  c9        ret     
// 
// 2bea  3a004e    ld      a,(#4e00)
// 2bed  fe01      cp      #01
// 2bef  c8        ret     z
// 
// 2bf0  3a134e    ld      a,(#4e13)	; Load level # 
// 2bf3  3c        inc     a		; Increment  
// 2bf4  fe08      cp      #08		; >= 8? 
// 2bf6  d22e2c    jp      nc,#2c2e	; No -> 0x2c2e 
// 2bf9  11083b    ld      de,#3b08	; Fruit table?  
// 2bfc  47        ld      b,a
// 2bfd  0e07      ld      c,#07		; Fruit count	 
// 2bff  210440    ld      hl,#4004	; Starting loc 
// 2c02  1a        ld      a,(de)		;  
// 2c03  cd8f2b    call    #2b8f		; Draw fruit 
// 
// 2c06  3e04      ld      a,#04		; v
// 2c08  84        add     a,h		; v
// 2c09  67        ld      h,a		; v
// 2c0a  13        inc     de		; v
// 2c0b  1a        ld      a,(de)		; v
// 2c0c  cd802b    call    #2b80		; Erase next fruit 
// 2c0f  3efc      ld      a,#fc		; 
// 2c11  84        add     a,h		; 
// 2c12  67        ld      h,a		; 
// 2c13  13        inc     de
// 2c14  23        inc     hl
// 2c15  23        inc     hl
// 2c16  0d        dec     c
// 2c17  10e9      djnz    #2c02           ; (-23)
// 2c19  0d        dec     c
// 2c1a  f8        ret     m
// 
// 2c1b  cd7e2b    call    #2b7e
// 2c1e  3e04      ld      a,#04
// 2c20  84        add     a,h
// 2c21  67        ld      h,a
// 2c22  af        xor     a
// 2c23  cd802b    call    #2b80
// 2c26  3efc      ld      a,#fc
// 2c28  84        add     a,h
// 2c29  67        ld      h,a
// 2c2a  23        inc     hl
// 2c2b  23        inc     hl
// 2c2c  18eb      jr      #2c19           ; (-21)
// 
// 2c2e  fe13      cp      #13
// 2c30  3802      jr      c,#2c34         ; (2)
// 2c32  3e13      ld      a,#13
// 2c34  d607      sub     #07
// 2c36  4f        ld      c,a
// 2c37  0600      ld      b,#00
// 2c39  21083b    ld      hl,#3b08
// 2c3c  09        add     hl,bc
// 2c3d  09        add     hl,bc
// 2c3e  eb        ex      de,hl
// 2c3f  0607      ld      b,#07
// 2c41  c3fd2b    jp      #2bfd
// 
// 
// 2c44  47        ld      b,a
// 2c45  e60f      and     #0f
// 2c47  c600      add     a,#00
// 2c49  27        daa     
// 2c4a  4f        ld      c,a
// 2c4b  78        ld      a,b
// 2c4c  e6f0      and     #f0
// 2c4e  280b      jr      z,#2c5b         ; (11)
// 2c50  0f        rrca    
// 2c51  0f        rrca    
// 2c52  0f        rrca    
// 2c53  0f        rrca    
// 2c54  47        ld      b,a
// 2c55  af        xor     a
// 2c56  c616      add     a,#16
// 2c58  27        daa     
// 2c59  10fb      djnz    #2c56           ; (-5)
// 2c5b  81        add     a,c
// 2c5c  27        daa     
// 2c5d  c9        ret     
// 
// 	;; This gets called a lot...
// 	;; Appears to draw messages from a table with
// 	;;   coordinates and message data
// 	;;   b=message # in table
void drawMsgFromTable (int msg)
{
// 2c5e  21a536    ld      hl,#36a5
// 2c61  df        rst     #18		; (hl+2*b) -> hl 
    uint16_t hl = 0x36a5;
    hl = hl + msg * 2;
// 2c62  5e        ld      e,(hl)
// 2c63  23        inc     hl
// 2c64  56        ld      d,(hl)
// 2c65  dd210044  ld      ix,#4400	; Start of Color RAM
// 2c69  dd19      add     ix,de		; Calculate starting pos in CRAM
// 2c6b  dde5      push    ix		; 4400 + (hl) -> stack 
// 2c6d  1100fc    ld      de,#fc00	
// 2c70  dd19      add     ix,de		; Calculate starting pos in VRAM
// 2c72  11ffff    ld      de,#ffff	; Offset for normal text  
// 2c75  cb7e      bit     7,(hl)  
// 2c77  2003      jr      nz,#2c7c        ; (3) 
// 2c79  11e0ff    ld      de,#ffe0	; Offset for top + bottom 2 lines 
// 2c7c  23        inc     hl
// 2c7d  78        ld      a,b		; b -> a
// 2c7e  010000    ld      bc,#0000	; 0 -> b,c 
// 2c81  87        add     a,a		; 2*a -> a 
// 2c82  3828      jr      c,#2cac         ; Special Draw routine for entries 80+
// 2c84  7e        ld      a,(hl)		; Read next char 
// 2c85  fe2f      cp      #2f		; #2f = end of text
// 2c87  2809      jr      z,#2c92         ; Done with VRAM
// 2c89  dd7700    ld      (ix+#00),a	; Write char to screen 
// 2c8c  23        inc     hl		; Next char
// 2c8d  dd19      add     ix,de		; Calc next VRAM pos
// 2c8f  04        inc     b		; Inc char count
// 2c90  18f2      jr      #2c84           ; loop
// 2c92  23        inc     hl
// 2c93  dde1      pop     ix		; Get CRAM start pos
// 2c95  7e        ld      a,(hl)		; Get color 
// 2c96  a7        and     a
// 2c97  faa42c    jp      m,#2ca4		; Jump if > #80 
// 2c9a  7e        ld      a,(hl)		; Get color  
// 2c9b  dd7700    ld      (ix+#00),a	; Drop in CRAM
// 2c9e  23        inc     hl		; Next color 
// 2c9f  dd19      add     ix,de		; Calc next CRAM pos
// 2ca1  10f7      djnz    #2c9a           ; Loop until b=0
// 2ca3  c9        ret     
// 
// 	;; Same as above, but all the same color
// 2ca4  dd7700    ld      (ix+#00),a	; Drop in CRAM
// 2ca7  dd19      add     ix,de		; Calc next CRAM pos
// 2ca9  10f9      djnz    #2ca4           ; Loop until b=0
// 2cab  c9        ret     
// 
// 	;; Message # > 80 (erase previous message?!), use 2nd color code
// 2cac  7e        ld      a,(hl)		; Read next char
// 2cad  fe2f      cp      #2f
// 2caf  280a      jr      z,#2cbb         ; Done with VRAM
// 2cb1  dd360040  ld      (ix+#00),#40	; Write 40 to VRAM? 
// 2cb5  23        inc     hl		; Next char 
// 2cb6  dd19      add     ix,de		; Next screen pos
// 2cb8  04        inc     b		; Inc char count  
// 2cb9  18f1      jr      #2cac           ; Loop
// 2cbb  23        inc     hl		; Next char 
// 2cbc  04        inc     b		; Inc char count 
// 2cbd  edb1      cpir			; Loop until [hl] = 2f 
// 2cbf  18d2      jr      #2c93           ; Do CRAM
// 
// 	;; 
// 2cc1  21c83b    ld      hl,#3bc8
// 2cc4  dd21cc4e  ld      ix,#4ecc
// 2cc8  fd218c4e  ld      iy,#4e8c
// 2ccc  cd442d    call    #2d44
// 2ccf  47        ld      b,a
// 2cd0  3acc4e    ld      a,(#4ecc)
// 2cd3  a7        and     a
// 2cd4  2804      jr      z,#2cda         ; (4)
// 2cd6  78        ld      a,b
// 2cd7  32914e    ld      (#4e91),a
// 2cda  21cc3b    ld      hl,#3bcc
// 2cdd  dd21dc4e  ld      ix,#4edc
// 2ce1  fd21924e  ld      iy,#4e92
// 2ce5  cd442d    call    #2d44
// 2ce8  47        ld      b,a
// 2ce9  3adc4e    ld      a,(#4edc)
// 2cec  a7        and     a
// 2ced  2804      jr      z,#2cf3         ; (4)
// 2cef  78        ld      a,b
// 2cf0  32964e    ld      (#4e96),a
// 2cf3  21d03b    ld      hl,#3bd0
// 2cf6  dd21ec4e  ld      ix,#4eec
// 2cfa  fd21974e  ld      iy,#4e97
// 2cfe  cd442d    call    #2d44
// 2d01  47        ld      b,a
// 2d02  3aec4e    ld      a,(#4eec)
// 2d05  a7        and     a
// 2d06  c8        ret     z
// 
// 2d07  78        ld      a,b
// 2d08  329b4e    ld      (#4e9b),a
// 2d0b  c9        ret     
// 
// 2d0c  21303b    ld      hl,#3b30
// 2d0f  dd219c4e  ld      ix,#4e9c
// 2d13  fd218c4e  ld      iy,#4e8c
// 2d17  cdee2d    call    #2dee
// 2d1a  32914e    ld      (#4e91),a
// 2d1d  21403b    ld      hl,#3b40
// 2d20  dd21ac4e  ld      ix,#4eac
// 2d24  fd21924e  ld      iy,#4e92
// 2d28  cdee2d    call    #2dee
// 2d2b  32964e    ld      (#4e96),a
// 2d2e  21803b    ld      hl,#3b80
// 2d31  dd21bc4e  ld      ix,#4ebc
// 2d35  fd21974e  ld      iy,#4e97
// 2d39  cdee2d    call    #2dee
// 2d3c  329b4e    ld      (#4e9b),a
// 2d3f  af        xor     a
// 2d40  32904e    ld      (#4e90),a
// 2d43  c9        ret     
// 
// 2d44  dd7e00    ld      a,(ix+#00)
// 2d47  a7        and     a
// 2d48  caf42d    jp      z,#2df4
// 2d4b  4f        ld      c,a
// 2d4c  0608      ld      b,#08
// 2d4e  1e80      ld      e,#80
// 2d50  7b        ld      a,e
// 2d51  a1        and     c
// 2d52  2005      jr      nz,#2d59        ; (5)
// 2d54  cb3b      srl     e
// 2d56  10f8      djnz    #2d50           ; (-8)
// 2d58  c9        ret     
// 
// 2d59  dd7e02    ld      a,(ix+#02)
// 2d5c  a3        and     e
// 2d5d  2007      jr      nz,#2d66        ; (7)
// 2d5f  dd7302    ld      (ix+#02),e
// 2d62  05        dec     b
// 2d63  df        rst     #18
// 2d64  180c      jr      #2d72           ; (12)
// 2d66  dd350c    dec     (ix+#0c)
// 2d69  c2d72d    jp      nz,#2dd7
// 2d6c  dd6e06    ld      l,(ix+#06)
// 2d6f  dd6607    ld      h,(ix+#07)
// 2d72  7e        ld      a,(hl)
// 2d73  23        inc     hl
// 2d74  dd7506    ld      (ix+#06),l
// 2d77  dd7407    ld      (ix+#07),h
// 2d7a  fef0      cp      #f0
// 2d7c  3827      jr      c,#2da5         ; (39)
// 2d7e  216c2d    ld      hl,#2d6c
// 2d81  e5        push    hl
// 2d82  e60f      and     #0f
// 2d84  e7        rst     #20
// 2d85  55        ld      d,l
// 2d86  2f        cpl     
// 2d87  65        ld      h,l
// 2d88  2f        cpl     
// 2d89  77        ld      (hl),a
// 2d8a  2f        cpl     
// 2d8b  89        adc     a,c
// 2d8c  2f        cpl     
// 2d8d  9b        sbc     a,e
// 2d8e  2f        cpl     
// 2d8f  0c        inc     c
// 2d90  00        nop     
// 2d91  0c        inc     c
// 2d92  00        nop     
// 2d93  0c        inc     c
// 2d94  00        nop     
// 2d95  0c        inc     c
// 2d96  00        nop     
// 2d97  0c        inc     c
// 2d98  00        nop     
// 2d99  0c        inc     c
// 2d9a  00        nop     
// 2d9b  0c        inc     c
// 2d9c  00        nop     
// 2d9d  0c        inc     c
// 2d9e  00        nop     
// 2d9f  0c        inc     c
// 2da0  00        nop     
// 2da1  0c        inc     c
// 2da2  00        nop     
// 2da3  ad        xor     l
// 2da4  2f        cpl     
// 2da5  47        ld      b,a
// 2da6  e61f      and     #1f
// 2da8  2803      jr      z,#2dad         ; (3)
// 2daa  dd700d    ld      (ix+#0d),b
// 2dad  dd4e09    ld      c,(ix+#09)
// 2db0  dd7e0b    ld      a,(ix+#0b)
// 2db3  e608      and     #08
// 2db5  2802      jr      z,#2db9         ; (2)
// 2db7  0e00      ld      c,#00
// 2db9  dd710f    ld      (ix+#0f),c
// 2dbc  78        ld      a,b
// 2dbd  07        rlca    
// 2dbe  07        rlca    
// 2dbf  07        rlca    
// 2dc0  e607      and     #07
// 2dc2  21b03b    ld      hl,#3bb0
// 2dc5  d7        rst     #10
// 2dc6  dd770c    ld      (ix+#0c),a
// 2dc9  78        ld      a,b
// 2dca  e61f      and     #1f
// 2dcc  2809      jr      z,#2dd7         ; (9)
// 2dce  e60f      and     #0f
// 2dd0  21b83b    ld      hl,#3bb8
// 2dd3  d7        rst     #10
// 2dd4  dd770e    ld      (ix+#0e),a
// 2dd7  dd6e0e    ld      l,(ix+#0e)
// 2dda  2600      ld      h,#00
// 2ddc  dd7e0d    ld      a,(ix+#0d)
// 2ddf  e610      and     #10
// 2de1  2802      jr      z,#2de5         ; (2)
// 2de3  3e01      ld      a,#01
// 2de5  dd8604    add     a,(ix+#04)
// 2de8  cae82e    jp      z,#2ee8
// 2deb  c3e42e    jp      #2ee4
// 2dee  dd7e00    ld      a,(ix+#00)
// 2df1  a7        and     a
// 2df2  2027      jr      nz,#2e1b        ; (39)
// 2df4  dd7e02    ld      a,(ix+#02)
// 2df7  a7        and     a
// 2df8  c8        ret     z
// 
// 2df9  dd360200  ld      (ix+#02),#00
// 2dfd  dd360d00  ld      (ix+#0d),#00
// 2e01  dd360e00  ld      (ix+#0e),#00
// 2e05  dd360f00  ld      (ix+#0f),#00
// 2e09  fd360000  ld      (iy+#00),#00
// 2e0d  fd360100  ld      (iy+#01),#00
// 2e11  fd360200  ld      (iy+#02),#00
// 2e15  fd360300  ld      (iy+#03),#00
// 2e19  af        xor     a
// 2e1a  c9        ret     
// 
// 2e1b  4f        ld      c,a
// 2e1c  0608      ld      b,#08
// 2e1e  1e80      ld      e,#80
// 2e20  7b        ld      a,e
// 2e21  a1        and     c
// 2e22  2005      jr      nz,#2e29        ; (5)
// 2e24  cb3b      srl     e
// 2e26  10f8      djnz    #2e20           ; (-8)
// 2e28  c9        ret     
// 
// 2e29  dd7e02    ld      a,(ix+#02)
// 2e2c  a3        and     e
// 2e2d  203f      jr      nz,#2e6e        ; (63)
// 2e2f  dd7302    ld      (ix+#02),e
// 2e32  05        dec     b
// 2e33  78        ld      a,b
// 2e34  07        rlca    
// 2e35  07        rlca    
// 2e36  07        rlca    
// 2e37  4f        ld      c,a
// 2e38  0600      ld      b,#00
// 2e3a  e5        push    hl
// 2e3b  09        add     hl,bc
// 2e3c  dde5      push    ix
// 2e3e  d1        pop     de
// 2e3f  13        inc     de
// 2e40  13        inc     de
// 2e41  13        inc     de
// 2e42  010800    ld      bc,#0008
// 2e45  edb0      ldir    
// 2e47  e1        pop     hl
// 2e48  dd7e06    ld      a,(ix+#06)
// 2e4b  e67f      and     #7f
// 2e4d  dd770c    ld      (ix+#0c),a
// 2e50  dd7e04    ld      a,(ix+#04)
// 2e53  dd770e    ld      (ix+#0e),a
// 2e56  dd7e09    ld      a,(ix+#09)
// 2e59  47        ld      b,a
// 2e5a  0f        rrca    
// 2e5b  0f        rrca    
// 2e5c  0f        rrca    
// 2e5d  0f        rrca    
// 2e5e  e60f      and     #0f
// 2e60  dd770b    ld      (ix+#0b),a
// 2e63  e608      and     #08
// 2e65  2007      jr      nz,#2e6e        ; (7)
// 2e67  dd700f    ld      (ix+#0f),b
// 2e6a  dd360d00  ld      (ix+#0d),#00
// 2e6e  dd350c    dec     (ix+#0c)
// 2e71  205a      jr      nz,#2ecd        ; (90)
// 2e73  dd7e08    ld      a,(ix+#08)
// 2e76  a7        and     a
// 2e77  2810      jr      z,#2e89         ; (16)
// 2e79  dd3508    dec     (ix+#08)
// 2e7c  200b      jr      nz,#2e89        ; (11)
// 2e7e  7b        ld      a,e
// 2e7f  2f        cpl     
// 2e80  dda600    and     (ix+#00)
// 2e83  dd7700    ld      (ix+#00),a
// 2e86  c3ee2d    jp      #2dee
// 2e89  dd7e06    ld      a,(ix+#06)
// 2e8c  e67f      and     #7f
// 2e8e  dd770c    ld      (ix+#0c),a
// 2e91  ddcb067e  bit     7,(ix+#06)
// 2e95  2816      jr      z,#2ead         ; (22)
// 2e97  dd7e05    ld      a,(ix+#05)
// 2e9a  ed44      neg     
// 2e9c  dd7705    ld      (ix+#05),a
// 2e9f  ddcb0d46  bit     0,(ix+#0d)
// 2ea3  ddcb0dc6  set     0,(ix+#0d)
// 2ea7  2824      jr      z,#2ecd         ; (36)
// 2ea9  ddcb0d86  res     0,(ix+#0d)
// 2ead  dd7e04    ld      a,(ix+#04)
// 2eb0  dd8607    add     a,(ix+#07)
// 2eb3  dd7704    ld      (ix+#04),a
// 2eb6  dd770e    ld      (ix+#0e),a
// 2eb9  dd7e09    ld      a,(ix+#09)
// 2ebc  dd860a    add     a,(ix+#0a)
// 2ebf  dd7709    ld      (ix+#09),a
// 2ec2  47        ld      b,a
// 2ec3  dd7e0b    ld      a,(ix+#0b)
// 2ec6  e608      and     #08
// 2ec8  2003      jr      nz,#2ecd        ; (3)
// 2eca  dd700f    ld      (ix+#0f),b
// 2ecd  dd7e0e    ld      a,(ix+#0e)
// 2ed0  dd8605    add     a,(ix+#05)
// 2ed3  dd770e    ld      (ix+#0e),a
// 2ed6  6f        ld      l,a
// 2ed7  2600      ld      h,#00
// 2ed9  dd7e03    ld      a,(ix+#03)
// 2edc  e670      and     #70
// 2ede  2808      jr      z,#2ee8         ; (8)
// 2ee0  0f        rrca    
// 2ee1  0f        rrca    
// 2ee2  0f        rrca    
// 2ee3  0f        rrca    
// 2ee4  47        ld      b,a
// 2ee5  29        add     hl,hl
// 2ee6  10fd      djnz    #2ee5           ; (-3)
// 2ee8  fd7500    ld      (iy+#00),l
// 2eeb  7d        ld      a,l
// 2eec  0f        rrca    
// 2eed  0f        rrca    
// 2eee  0f        rrca    
// 2eef  0f        rrca    
// 2ef0  fd7701    ld      (iy+#01),a
// 2ef3  fd7402    ld      (iy+#02),h
// 2ef6  7c        ld      a,h
// 2ef7  0f        rrca    
// 2ef8  0f        rrca    
// 2ef9  0f        rrca    
// 2efa  0f        rrca    
// 2efb  fd7703    ld      (iy+#03),a
// 2efe  dd7e0b    ld      a,(ix+#0b)
// 2f01  e7        rst     #20
// 2f02  222f26    ld      (#262f),hl
// 2f05  2f        cpl     
// 2f06  2b        dec     hl
// 2f07  2f        cpl     
// 2f08  3c        inc     a
// 2f09  2f        cpl     
// 2f0a  43        ld      b,e
// 2f0b  2f        cpl     
// 2f0c  4a        ld      c,d
// 2f0d  2f        cpl     
// 2f0e  4b        ld      c,e
// 2f0f  2f        cpl     
// 2f10  4c        ld      c,h
// 2f11  2f        cpl     
// 2f12  4d        ld      c,l
// 2f13  2f        cpl     
// 2f14  4e        ld      c,(hl)
// 2f15  2f        cpl     
// 2f16  4f        ld      c,a
// 2f17  2f        cpl     
// 2f18  50        ld      d,b
// 2f19  2f        cpl     
// 2f1a  51        ld      d,c
// 2f1b  2f        cpl     
// 2f1c  52        ld      d,d
// 2f1d  2f        cpl     
// 2f1e  53        ld      d,e
// 2f1f  2f        cpl     
// 2f20  54        ld      d,h
// 2f21  2f        cpl     
// 2f22  dd7e0f    ld      a,(ix+#0f)
// 2f25  c9        ret     
// 
// 2f26  dd7e0f    ld      a,(ix+#0f)
// 2f29  1809      jr      #2f34           ; (9)
// 2f2b  3a844c    ld      a,(#4c84)
// 2f2e  e601      and     #01
// 2f30  dd7e0f    ld      a,(ix+#0f)
// 2f33  c0        ret     nz
// 
// 2f34  e60f      and     #0f
// 2f36  c8        ret     z
// 
// 2f37  3d        dec     a
// 2f38  dd770f    ld      (ix+#0f),a
// 2f3b  c9        ret     
// 
// 2f3c  3a844c    ld      a,(#4c84)
// 2f3f  e603      and     #03
// 2f41  18ed      jr      #2f30           ; (-19)
// 2f43  3a844c    ld      a,(#4c84)
// 2f46  e607      and     #07
// 2f48  18e6      jr      #2f30           ; (-26)
// 2f4a  c9        ret     
// 
// 2f4b  c9        ret     
// 
// 2f4c  c9        ret     
// 
// 2f4d  c9        ret     
// 
// 2f4e  c9        ret     
// 
// 2f4f  c9        ret     
// 
// 2f50  c9        ret     
// 
// 2f51  c9        ret     
// 
// 2f52  c9        ret     
// 
// 2f53  c9        ret     
// 
// 2f54  c9        ret     
// 
// 2f55  dd6e06    ld      l,(ix+#06)
// 2f58  dd6607    ld      h,(ix+#07)
// 2f5b  7e        ld      a,(hl)
// 2f5c  dd7706    ld      (ix+#06),a
// 2f5f  23        inc     hl
// 2f60  7e        ld      a,(hl)
// 2f61  dd7707    ld      (ix+#07),a
// 2f64  c9        ret     
// 
// 2f65  dd6e06    ld      l,(ix+#06)
// 2f68  dd6607    ld      h,(ix+#07)
// 2f6b  7e        ld      a,(hl)
// 2f6c  23        inc     hl
// 2f6d  dd7506    ld      (ix+#06),l
// 2f70  dd7407    ld      (ix+#07),h
// 2f73  dd7703    ld      (ix+#03),a
// 2f76  c9        ret     
// 
// 2f77  dd6e06    ld      l,(ix+#06)
// 2f7a  dd6607    ld      h,(ix+#07)
// 2f7d  7e        ld      a,(hl)
// 2f7e  23        inc     hl
// 2f7f  dd7506    ld      (ix+#06),l
// 2f82  dd7407    ld      (ix+#07),h
// 2f85  dd7704    ld      (ix+#04),a
// 2f88  c9        ret     
// 
// 2f89  dd6e06    ld      l,(ix+#06)
// 2f8c  dd6607    ld      h,(ix+#07)
// 2f8f  7e        ld      a,(hl)
// 2f90  23        inc     hl
// 2f91  dd7506    ld      (ix+#06),l
// 2f94  dd7407    ld      (ix+#07),h
// 2f97  dd7709    ld      (ix+#09),a
// 2f9a  c9        ret     
// 
// 2f9b  dd6e06    ld      l,(ix+#06)
// 2f9e  dd6607    ld      h,(ix+#07)
// 2fa1  7e        ld      a,(hl)
// 2fa2  23        inc     hl
// 2fa3  dd7506    ld      (ix+#06),l
// 2fa6  dd7407    ld      (ix+#07),h
// 2fa9  dd770b    ld      (ix+#0b),a
// 2fac  c9        ret     
// 
// 2fad  dd7e02    ld      a,(ix+#02)
// 2fb0  2f        cpl     
// 2fb1  dda600    and     (ix+#00)
// 2fb4  dd7700    ld      (ix+#00),a
// 2fb7  c3f42d    jp      #2df4
// 2fba  00        nop     
// 2fbb  00        nop     
// 2fbc  00        nop     
// 2fbd  00        nop     
// 2fbe  00        nop     
// 2fbf  00        nop     
// 2fc0  00        nop     
// 2fc1  00        nop     
// 2fc2  00        nop     
// 2fc3  00        nop     
// 2fc4  00        nop     
// 2fc5  00        nop     
// 2fc6  00        nop     
// 2fc7  00        nop     
// 2fc8  00        nop     
// 2fc9  00        nop     
// 2fca  00        nop     
// 2fcb  00        nop     
// 2fcc  00        nop     
// 2fcd  00        nop     
// 2fce  00        nop     
// 2fcf  00        nop     
// 2fd0  00        nop     
// 2fd1  00        nop     
// 2fd2  00        nop     
// 2fd3  00        nop     
// 2fd4  00        nop     
// 2fd5  00        nop     
// 2fd6  00        nop     
// 2fd7  00        nop     
// 2fd8  00        nop     
// 2fd9  00        nop     
// 2fda  00        nop     
// 2fdb  00        nop     
// 2fdc  00        nop     
// 2fdd  00        nop     
// 2fde  00        nop     
// 2fdf  00        nop     
// 2fe0  00        nop     
// 2fe1  00        nop     
// 2fe2  00        nop     
// 2fe3  00        nop     
// 2fe4  00        nop     
// 2fe5  00        nop     
// 2fe6  00        nop     
// 2fe7  00        nop     
// 2fe8  00        nop     
// 2fe9  00        nop     
// 2fea  00        nop     
// 2feb  00        nop     
// 2fec  00        nop     
// 2fed  00        nop     
// 2fee  00        nop     
// 2fef  00        nop     
// 2ff0  00        nop     
// 2ff1  00        nop     
// 2ff2  00        nop     
// 2ff3  00        nop     
// 2ff4  00        nop     
// 2ff5  00        nop     
// 2ff6  00        nop     
// 2ff7  00        nop     
// 2ff8  00        nop     
// 2ff9  00        nop     
// 2ffa  00        nop     
// 2ffb  00        nop     
// 2ffc  00        nop     
// 2ffd  00        nop     
// 2ffe  83        add     a,e
// 2fff  4c        ld      c,h
// 
// 	;; Interrupt routine for vector #3ffa
// 
// 	;; Check rom checksums
// 3000  210000    ld      hl,#0000
// 3003  010010    ld      bc,#1000
// 3006  32c050    ld      (#50c0),a	; Kick the dog
kickWatchdog();
// 3009  79        ld      a,c		; a=0
// 300a  86        add     a,(hl)
// 300b  4f        ld      c,a
// 300c  7d        ld      a,l
// 300d  c602      add     a,#02
// 300f  6f        ld      l,a
// 3010  fe02      cp      #02
// 3012  d20930    jp      nc,#3009
// 3015  24        inc     h
// 3016  10ee      djnz    #3006           ; (-18)
// 3018  79        ld      a,c
// 3019  a7        and     a
// 301a  2015      jr      nz,#3031        ; Rom checksum bad (?)
// 
// 301c  320750    ld      (#5007),a	; Clear coin
// 301f  7c        ld      a,h
// 3020  fe30      cp      #30
// 3022  c20330    jp      nz,#3003	; Continue for other roms
// 3025  2600      ld      h,#00
// 3027  2c        inc     l
// 3028  7d        ld      a,l
// 3029  fe02      cp      #02
// 302b  da0330    jp      c,#3003
// 302e  c34230    jp      #3042
// 
// 	;; Bad rom checksum (?)
// 3031  25        dec     h
// 3032  7c        ld      a,h
// 53033  e6f0      and     #f0
// 3035  320750    ld      (#5007),a	; Clear coin
// 3038  0f        rrca    
// 3039  0f        rrca    
// 303a  0f        rrca    
// 303b  0f        rrca    
// 303c  5f        ld      e,a		; Failed rom -> e (?)
// 303d  0600      ld      b,#00
// 303f  c3bd30    jp      #30bd
// 
// 	;; RAM test (4c00)
// 3042  315431    ld      sp,#3154
// 3045  06ff      ld      b,#ff
// 3047  e1        pop     hl		; 4c00 (first time)
// 3048  d1        pop     de		; 040f (first time)
// 3049  48        ld      c,b		; 0xff -> c
// 
// 	;; Write crap to ram
// 304a  32c050    ld      (#50c0),a	; Kick the dog
kickWatchdog();
// 304d  79        ld      a,c		; 0xff -> a
// 304e  a3        and     e		; e -> a
// 304f  77        ld      (hl),a
// 3050  c633      add     a,#33
// 3052  4f        ld      c,a
// 3053  2c        inc     l
// 3054  7d        ld      a,l
// 3055  e60f      and     #0f
// 3057  c24d30    jp      nz,#304d
// 305a  79        ld      a,c
// 305b  87        add     a,a
// 305c  87        add     a,a
// 305d  81        add     a,c
// 305e  c631      add     a,#31
// 3060  4f        ld      c,a
// 3061  7d        ld      a,l
// 3062  a7        and     a		
// 3063  c24d30    jp      nz,#304d
// 3066  24        inc     h
// 3067  15        dec     d
// 3068  c24a30    jp      nz,#304a
// 306b  3b        dec     sp
// 306c  3b        dec     sp
// 306d  3b        dec     sp
// 306e  3b        dec     sp
// 306f  e1        pop     hl		; 4c00
// 3070  d1        pop     de		; 040f 
// 3071  48        ld      c,b
// 
// 	;; Check crap in ram
// 3072  32c050    ld      (#50c0),a	; Kick the dog
kickWatchdog();
// 3075  79        ld      a,c
// 3076  a3        and     e
// 3077  4f        ld      c,a
// 3078  7e        ld      a,(hl)
// 3079  a3        and     e
// 307a  b9        cp      c
// 307b  c2b530    jp      nz,#30b5	; Ram test failed
// 307e  c633      add     a,#33
// 3080  4f        ld      c,a
// 3081  2c        inc     l
// 3082  7d        ld      a,l
// 3083  e60f      and     #0f
// 3085  c27530    jp      nz,#3075
// 3088  79        ld      a,c
// 3089  87        add     a,a
// 308a  87        add     a,a
// 308b  81        add     a,c
// 308c  c631      add     a,#31
// 308e  4f        ld      c,a
// 308f  7d        ld      a,l
// 3090  a7        and     a
// 3091  c27530    jp      nz,#3075
// 3094  24        inc     h
// 3095  15        dec     d
// 3096  c27230    jp      nz,#3072
// 3099  3b        dec     sp
// 309a  3b        dec     sp
// 309b  3b        dec     sp
// 309c  3b        dec     sp
// 309d  78        ld      a,b
// 309e  d610      sub     #10
// 30a0  47        ld      b,a
// 30a1  10a4      djnz    #3047           ; (-92)
// 
// 30a3  f1        pop     af		; 4c00 
// 30a4  d1        pop     de
// 30a5  fe44      cp      #44
// 30a7  c24530    jp      nz,#3045	; Check if 0x44xx done
// 30aa  7b        ld      a,e
// 30ab  eef0      xor     #f0
// 30ad  c24530    jp      nz,#3045	; Check if totally done
// 30b0  0601      ld      b,#01
// 30b2  c3bd30    jp      #30bd
// 
// 	;; Display bad ram (?)
// 30b5  7b        ld      a,e
// 30b6  e601      and     #01
// 30b8  ee01      xor     #01
// 30ba  5f        ld      e,a
// 30bb  0600      ld      b,#00
// 
// 	;; Display bad rom (?)
// 30bd  31c04f    ld      sp,#4fc0
// 30c0  d9        exx			; Swap register pairs 
// 
// 	;; Clear all program ram
// 30c1  21004c    ld      hl,#4c00
// 30c4  0604      ld      b,#04
// 30c6  32c050    ld      (#50c0),a	; Kick watchdog
kickWatchdog();
// 30c9  3600      ld      (hl),#00
// 30cb  2c        inc     l
// 30cc  20fb      jr      nz,#30c9        ; (-5)
// 30ce  24        inc     h
// 30cf  10f5      djnz    #30c6           ; (-11)
// 
// 	;; Set all video ram to 0x40
// 30d1  210040    ld      hl,#4000
// 30d4  0604      ld      b,#04
// 30d6  32c050    ld      (#50c0),a	; Kick watchdog
kickWatchdog();
// 30d9  3e40      ld      a,#40
// 30db  77        ld      (hl),a
// 30dc  2c        inc     l
// 30dd  20fc      jr      nz,#30db        ; (-4)
// 30df  24        inc     h
// 30e0  10f4      djnz    #30d6           ; (-12)
// 
// 	;; Set all color ram to 0x0f
// 30e2  0604      ld      b,#04
// 30e4  32c050    ld      (#50c0),a
kickWatchdog();
// 30e7  3e0f      ld      a,#0f
// 30e9  77        ld      (hl),a
// 30ea  2c        inc     l
// 30eb  20fc      jr      nz,#30e9        ; (-4)
// 30ed  24        inc     h
// 30ee  10f4      djnz    #30e4           ; (-12)
// 
// 30f0  d9        exx			; Reswap register pairs 
// 30f1  1008      djnz    #30fb           ; b=1 -> no errors
// 30f3  0623      ld      b,#2
// 30f5  cd5e2c    call    #2c5e	
// 30f8  c37431    jp      #3174		; Run code ?!?!?
// 
// 
// 30fb  7b        ld      a,e		; Bad rom # -> a 
// 30fc  c630      add     a,#30 
// 30fe  328441    ld      (#4184),a	; Write to screen  [31] [30]
// 3101  c5        push    bc		; [ff0f] 
// 3102  e5        push    hl		; [4c00] 
// 3103  0624      ld      b,#24
// 3105  cd5e2c    call    #2c5e		; <=- gets called. 
// 3108  e1        pop     hl
// 3109  7c        ld      a,h
// 310a  fe40      cp      #40
// 310c  2a6c31    ld      hl,(#316c)
// 310f  3811      jr      c,#3122         ; (17)
// 3111  fe4c      cp      #4c
// 3113  2a6e31    ld      hl,(#316e)
// 3116  300a      jr      nc,#3122        ; (10)
// 3118  fe44      cp      #44
// 311a  2a7031    ld      hl,(#3170)
// 311d  3803      jr      c,#3122         ; (3)
// 311f  2a7231    ld      hl,(#3172)
// 3122  7d        ld      a,l
// 3123  320442    ld      (#4204),a
// 3126  7c        ld      a,h
// 3127  326442    ld      (#4264),a
// 312a  3a0050    ld      a,(#5000)
// 312d  47        ld      b,a
// 312e  3a4050    ld      a,(#5040)
// 3131  b0        or      b
// 3132  e601      and     #01
// 3134  2011      jr      nz,#3147        ; (17)
// 3136  c1        pop     bc
// 3137  79        ld      a,c
// 3138  e60f      and     #0f
// 313a  47        ld      b,a
// 313b  79        ld      a,c
// 313c  e6f0      and     #f0
// 313e  0f        rrca    
// 313f  0f        rrca    
// 3140  0f        rrca    
// 3141  0f        rrca    
// 3142  4f        ld      c,a
// 3143  ed438541  ld      (#4185),bc
// 3147  32c050    ld      (#50c0),a
kickWatchdog();
// 314a  3a4050    ld      a,(#5040)
// 314d  e610      and     #10
// 314f  28f6      jr      z,#3147         ; (-10)
// 3151  c30b23    jp      #230b
// 
// 
// 	;; Stack stuff used in ram test (?)
// 3154  004c
// 3156  0f04
// 
// 3158  004c
// 315a  f004
// 
// 315c  0040
// 315e  0f04
// 
// 3160  0040
// 3162  f004
// 	
// 3164  0044
// 3166  0f04
// 	
// 3168  0044
// 316a  f004
// 
// 	;; RAM Error data
// 316c  4f40				; O _ -> BAD   ROM 
// 316e  4157				; A W -> BAD W RAM 
// 3170  4156				; A V -> BAD V RAM 
// 3172  4143				; A C -> BAD C RAM 
// 
// 
// 	;; Start the game ?!?!?
// 3174  210650    ld      hl,#5006
// 3177  3e01      ld      a,#01
// 3179  77        ld      (hl),a		; Enable all
// 317a  2d        dec     l	
// 317b  20fc      jr      nz,#3179        ; (-4)
// 317d  af        xor     a		; 0x00->a
// 317e  320350    ld      (#5003),a	; unflip screen
// 3181  d604      sub     #04		; 0xfc->a
// 3183  d300      out     (#00),a		; set vector
// 3185  31c04f    ld      sp,#4fc0
// 3188  32c050    ld      (#50c0),a	; Kick the dog
kickWatchdog();
// 318b  af        xor     a		; 0x00->a
// 318c  32004e    ld      (#4e00),a
// 318f  3c        inc     a		; 0x01->a
// 3190  32014e    ld      (#4e01),a
// 3193  320050    ld      (#5000),a	; enable interrupts
// 3196  fb        ei			; enable interrupts
// 
// 	;; Test mode sound checks
// 3197  3a0050    ld      a,(#5000)	
// 319a  2f        cpl     
// 319b  47        ld      b,a
// 319c  e6e0      and     #e0		; Check coin/credit inputs
// 319e  2805      jr      z,#31a5         ; (5)
// 31a0  3e02      ld      a,#02
// 31a2  329c4e    ld      (#4e9c),a	; Choose sound 2
// 	
// 31a5  3a4050    ld      a,(#5040)
// 31a8  2f        cpl     
// 31a9  4f        ld      c,a
// 31aa  e660      and     #60		; Check p1/p2 start 
// 31ac  2805      jr      z,#31b3         ; (5)
// 31ae  3e01      ld      a,#01
// 31b0  329c4e    ld      (#4e9c),a	; Choose sound 1
// 	
// 31b3  78        ld      a,b
// 31b4  b1        or      c
// 31b5  e601      and     #01		; Check up
// 31b7  2805      jr      z,#31be         ; (5)
// 31b9  3e08      ld      a,#08
// 31bb  32bc4e    ld      (#4ebc),a	; Choose sound 8
// 	
// 31be  78        ld      a,b
// 31bf  b1        or      c
// 31c0  e602      and     #02		; Check left
// 31c2  2805      jr      z,#31c9         ; (5)
// 31c4  3e04      ld      a,#04
// 31c6  32bc4e    ld      (#4ebc),a	; Choose sound 4
// 	
// 31c9  78        ld      a,b
// 31ca  b1        or      c
// 31cb  e604      and     #04		; Check right
// 31cd  2805      jr      z,#31d4         ; (5)
// 31cf  3e10      ld      a,#10
// 31d1  32bc4e    ld      (#4ebc),a	; Choose sound 16
// 	
// 31d4  78        ld      a,b
// 31d5  b1        or      c
// 31d6  e608      and     #08		; Check down
// 31d8  2805      jr      z,#31df         ; (5)
// 31da  3e20      ld      a,#20
// 31dc  32bc4e    ld      (#4ebc),a	; Choose sound 32
// 
// 31df  3a8050    ld      a,(#5080)	; Read dips
// 31e2  e603      and     #03		; Mask coin info
// 31e4  c625      add     a,#25
// 31e6  47        ld      b,a
// 31e7  cd5e2c    call    #2c5e		
// 		
// 31ea  3a8050	ld      a,(#5080)	; Read dips
// 31ed  0f        rrca    
// 31ee  0f        rrca    
// 31ef  0f        rrca    
// 31f0  0f        rrca    
// 31f1  e603      and     #03		; Mask extras
// 31f3  fe03      cp      #03
// 31f5  2008      jr      nz,#31ff        ; (8)
// 31f7  062a      ld      b,#2a
// 31f9  cd5e2c    call    #2c5e
// 31fc  c31c32    jp      #321c
// 31ff  07        rlca    
// 3200  5f        ld      e,a
// 3201  d5        push    de
// 3202  062b      ld      b,#2b
// 3204  cd5e2c    call    #2c5e
// 3207  062e      ld      b,#2e
// 3209  cd5e2c    call    #2c5e
// 320c  d1        pop     de
// 320d  1600      ld      d,#00
// 320f  21f932    ld      hl,#32f9
// 3212  19        add     hl,de
// 3213  7e        ld      a,(hl)
// 3214  322a42    ld      (#422a),a
// 3217  23        inc     hl
// 3218  7e        ld      a,(hl)
// 3219  324a42    ld      (#424a),a
// 321c  3a8050    ld      a,(#5080)
// 321f  0f        rrca    
// 3220  0f        rrca    
// 3221  e603      and     #03
// 3223  c631      add     a,#31
// 3225  fe34      cp      #34
// 3227  2001      jr      nz,#322a        ; (1)
// 3229  3c        inc     a
// 322a  320c42    ld      (#420c),a
// 322d  0629      ld      b,#29
// 322f  cd5e2c    call    #2c5e
// 3232  3a4050    ld      a,(#5040)
// 3235  07        rlca    
// 3236  e601      and     #01
// 3238  c62c      add     a,#2c
// 323a  47        ld      b,a
// 323b  cd5e2c    call    #2c5e
// 323e  3a4050    ld      a,(#5040)
// 3241  e610      and     #10
// 3243  ca8831    jp      z,#3188
// 3246  af        xor     a
// 3247  320050    ld      (#5000),a
// 324a  f3        di      
// 324b  210750    ld      hl,#5007
// 324e  af        xor     a
// 324f  77        ld      (hl),a
// 3250  2d        dec     l
// 3251  20fc      jr      nz,#324f        ; (-4)
// 3253  31e23a    ld      sp,#3ae2
// 3256  0603      ld      b,#03
// 3258  d9        exx     
// 3259  e1        pop     hl
// 325a  d1        pop     de
// 325b  32c050    ld      (#50c0),a
kickWatchdog();
// 325e  c1        pop     bc
// 325f  3e3c      ld      a,#3c
// 3261  77        ld      (hl),a
// 3262  23        inc     hl
// 3263  72        ld      (hl),d
// 3264  23        inc     hl
// 3265  10f8      djnz    #325f           ; (-8)
// 3267  3b        dec     sp
// 3268  3b        dec     sp
// 3269  c1        pop     bc
// 326a  71        ld      (hl),c
// 326b  23        inc     hl
// 326c  3e3f      ld      a,#3f
// 326e  77        ld      (hl),a
// 326f  23        inc     hl
// 3270  10f8      djnz    #326a           ; (-8)
// 3272  3b        dec     sp
// 3273  3b        dec     sp
// 3274  1d        dec     e
// 3275  c25b32    jp      nz,#325b
// 3278  f1        pop     af
// 3279  d9        exx     
// 327a  10dc      djnz    #3258           ; (-36)
// 327c  31c04f    ld      sp,#4fc0
// 327f  0608      ld      b,#08
// 3281  cded32    call    #32ed
// 3284  10fb      djnz    #3281           ; (-5)
// 3286  32c050    ld      (#50c0),a	; Kick the dog
kickWatchdog();
// 3289  3a4050    ld      a,(#5040)
// 328c  e610      and     #10
// 328e  28f6      jr      z,#3286         ; Wait until test switch is off
// 	
// 3290  3a4050    ld      a,(#5040)	; Check P1/P2 start 
// 3293  e660      and     #60
// 3295  c24b23    jp      nz,#234b
// 3298  0608      ld      b,#08
// 329a  cded32    call    #32ed
// 329d  10fb      djnz    #329a           ; (-5)
// 329f  3a4050    ld      a,(#5040)
// 32a2  e610      and     #10
// 32a4  c24b23    jp      nz,#234b
// 32a7  1e01      ld      e,#01
// 32a9  0604      ld      b,#04
// 32ab  32c050    ld      (#50c0),a
kickWatchdog();
// 32ae  cded32    call    #32ed
// 32b1  3a0050    ld      a,(#5000)
// 32b4  a3        and     e
// 32b5  20f4      jr      nz,#32ab        ; (-12)
// 32b7  cded32    call    #32ed
// 32ba  32c050    ld      (#50c0),a
kickWatchdog();
// 32bd  3a0050    ld      a,(#5000)
// 32c0  eeff      xor     #ff
// 32c2  20f3      jr      nz,#32b7        ; (-13)
// 32c4  10e5      djnz    #32ab           ; (-27)
// 32c6  cb03      rlc     e
// 32c8  7b        ld      a,e
// 32c9  fe10      cp      #10
// 32cb  daa932    jp      c,#32a9
// 32ce  210040    ld      hl,#4000
// 32d1  0604      ld      b,#04
// 32d3  3e40      ld      a,#40
// 32d5  77        ld      (hl),a
// 32d6  2c        inc     l
// 32d7  20fc      jr      nz,#32d5        ; (-4)
// 32d9  24        inc     h
// 32da  10f7      djnz    #32d3           ; (-9)
// 32dc  cdf43a    call    #3af4
// 32df  32c050    ld      (#50c0),a
kickWatchdog();
// 32e2  3a4050    ld      a,(#5040)
// 32e5  e610      and     #10
// 32e7  cadf32    jp      z,#32df
// 32ea  c34b23    jp      #234b
// 32ed  32c050    ld      (#50c0),a
kickWatchdog();
// 32f0  210028    ld      hl,#2800
// 32f3  2b        dec     hl
// 32f4  7c        ld      a,h
// 32f5  b5        or      l
// 32f6  20fb      jr      nz,#32f3        ; (-5)
// 32f8  c9        ret     
// 
// 32f9  3031      jr      nc,#332c        ; (49)
// 32fb  35        dec     (hl)
// 32fc  313032    ld      sp,#3230
// 32ff  00        nop     
// 3300  ff        rst     #38
// 3301  010000    ld      bc,#0000
// 3304  01ff00    ld      bc,#00ff
// 3307  00        nop     
// 3308  ff        rst     #38
// 3309  010000    ld      bc,#0000
// 330c  01ff00    ld      bc,#00ff
// 330f  55        ld      d,l
// 3310  2a552a    ld      hl,(#2a55)
// 3313  55        ld      d,l
// 3314  55        ld      d,l
// 3315  55        ld      d,l
// 3316  55        ld      d,l
// 3317  55        ld      d,l
// 3318  2a552a    ld      hl,(#2a55)
// 331b  52        ld      d,d
// 331c  4a        ld      c,d
// 331d  a5        and     l
// 331e  94        sub     h
// 331f  25        dec     h
// 3320  25        dec     h
// 3321  25        dec     h
// 3322  25        dec     h
// 3323  222222    ld      (#2222),hl
// 3326  220101    ld      (#0101),hl
// 3329  010158    ld      bc,#5801
// 332c  02        ld      (bc),a
// 332d  08        ex      af,af'
// 332e  07        rlca    
// 332f  60        ld      h,b
// 3330  09        add     hl,bc
// 3331  100e      djnz    #3341           ; (14)
// 3333  68        ld      l,b
// 3334  1070      djnz    #33a6           ; (112)
// 3336  17        rla     
// 3337  14        inc     d
// 3338  19        add     hl,de
// 3339  52        ld      d,d
// 333a  4a        ld      c,d
// 333b  a5        and     l
// 333c  94        sub     h
// 333d  aa        xor     d
// 333e  2a5555    ld      hl,(#5555)
// 3341  55        ld      d,l
// 3342  2a552a    ld      hl,(#2a55)
// 3345  52        ld      d,d
// 3346  4a        ld      c,d
// 3347  a5        and     l
// 3348  94        sub     h
// 3349  92        sub     d
// 334a  24        inc     h
// 334b  25        dec     h
// 334c  49        ld      c,c
// 334d  48        ld      c,b
// 334e  24        inc     h
// 334f  229101    ld      (#0191),hl
// 3352  010101    ld      bc,#0101
// 3355  00        nop     
// 3356  00        nop     
// 3357  00        nop     
// 3358  00        nop     
// 3359  00        nop     
// 335a  00        nop     
// 335b  00        nop     
// 335c  00        nop     
// 335d  00        nop     
// 335e  00        nop     
// 335f  00        nop     
// 3360  00        nop     
// 3361  00        nop     
// 3362  00        nop     
// 3363  55        ld      d,l
// 3364  2a552a    ld      hl,(#2a55)
// 3367  55        ld      d,l
// 3368  55        ld      d,l
// 3369  55        ld      d,l
// 336a  55        ld      d,l
// 336b  aa        xor     d
// 336c  2a5555    ld      hl,(#5555)
// 336f  55        ld      d,l
// 3370  2a552a    ld      hl,(#2a55)
// 3373  52        ld      d,d
// 3374  4a        ld      c,d
// 3375  a5        and     l
// 3376  94        sub     h
// 3377  48        ld      c,b
// 3378  24        inc     h
// 3379  229121    ld      (#2191),hl
// 337c  44        ld      b,h
// 337d  44        ld      b,h
// 337e  08        ex      af,af'
// 337f  58        ld      e,b
// 3380  02        ld      (bc),a
// 3381  34        inc     (hl)
// 3382  08        ex      af,af'
// 3383  d8        ret     c
// 
// 3384  09        add     hl,bc
// 3385  b4        or      h
// 3386  0f        rrca    
// 3387  58        ld      e,b
// 3388  110816    ld      de,#1608
// 338b  34        inc     (hl)
// 338c  17        rla     
// 338d  55        ld      d,l
// 338e  55        ld      d,l
// 338f  55        ld      d,l
// 3390  55        ld      d,l
// 3391  d5        push    de
// 3392  6a        ld      l,d
// 3393  d5        push    de
// 3394  6a        ld      l,d
// 3395  aa        xor     d
// 3396  6a        ld      l,d
// 3397  55        ld      d,l
// 3398  d5        push    de
// 3399  55        ld      d,l
// 339a  55        ld      d,l
// 339b  55        ld      d,l
// 339c  55        ld      d,l
// 339d  aa        xor     d
// 339e  2a5555    ld      hl,(#5555)
// 33a1  92        sub     d
// 33a2  24        inc     h
// 33a3  92        sub     d
// 33a4  24        inc     h
// 33a5  222222    ld      (#2222),hl
// 33a8  22a401    ld      (#01a4),hl
// 33ab  54        ld      d,h
// 33ac  06f8      ld      b,#f8
// 33ae  07        rlca    
// 33af  a8        xor     b
// 33b0  0c        inc     c
// 33b1  d40d84    call    nc,#840d
// 33b4  12        ld      (de),a
// 33b5  b0        or      b
// 33b6  13        inc     de
// 33b7  d5        push    de
// 33b8  6a        ld      l,d
// 33b9  d5        push    de
// 33ba  6a        ld      l,d
// 33bb  d65a      sub     #5a
// 33bd  ad        xor     l
// 33be  b5        or      l
// 33bf  d65a      sub     #5a
// 33c1  ad        xor     l
// 33c2  b5        or      l
// 33c3  d5        push    de
// 33c4  6a        ld      l,d
// 33c5  d5        push    de
// 33c6  6a        ld      l,d
// 33c7  aa        xor     d
// 33c8  6a        ld      l,d
// 33c9  55        ld      d,l
// 33ca  d5        push    de
// 33cb  92        sub     d
// 33cc  24        inc     h
// 33cd  25        dec     h
// 33ce  49        ld      c,c
// 33cf  48        ld      c,b
// 33d0  24        inc     h
// 33d1  2291a4    ld      (#a491),hl
// 33d4  015406    ld      bc,#0654
// 33d7  f8        ret     m
// 
// 33d8  07        rlca    
// 33d9  a8        xor     b
// 33da  0c        inc     c
// 33db  d40dfe    call    nc,#fe0d
// 33de  ff        rst     #38
// 33df  ff        rst     #38
// 33e0  ff        rst     #38
// 33e1  6d        ld      l,l
// 33e2  6d        ld      l,l
// 33e3  6d        ld      l,l
// 33e4  6d        ld      l,l
// 33e5  6d        ld      l,l
// 33e6  6d        ld      l,l
// 33e7  6d        ld      l,l
// 33e8  6d        ld      l,l
// 33e9  b6        or      (hl)
// 33ea  6d        ld      l,l
// 33eb  6d        ld      l,l
// 33ec  db6d      in      a,(#6d)
// 33ee  6d        ld      l,l
// 33ef  6d        ld      l,l
// 33f0  6d        ld      l,l
// 33f1  d65a      sub     #5a
// 33f3  ad        xor     l
// 33f4  b5        or      l
// 33f5  25        dec     h
// 33f6  25        dec     h
// 33f7  25        dec     h
// 33f8  25        dec     h
// 33f9  92        sub     d
// 33fa  24        inc     h
// 33fb  92        sub     d
// 33fc  24        inc     h
// 33fd  2c        inc     l
// 33fe  01dc05    ld      bc,#05dc
// 3401  08        ex      af,af'
// 3402  07        rlca    
// 3403  b8        cp      b
// 3404  0b        dec     bc
// 3405  e40cfe    call    po,#fe0c
// 3408  ff        rst     #38
// 3409  ff        rst     #38
// 340a  ff        rst     #38
// 340b  d5        push    de
// 340c  6a        ld      l,d
// 340d  d5        push    de
// 340e  6a        ld      l,d
// 340f  d5        push    de
// 3410  6a        ld      l,d
// 3411  d5        push    de
// 3412  6a        ld      l,d
// 3413  b6        or      (hl)
// 3414  6d        ld      l,l
// 3415  6d        ld      l,l
// 3416  db6d      in      a,(#6d)
// 3418  6d        ld      l,l
// 3419  6d        ld      l,l
// 341a  6d        ld      l,l
// 341b  d65a      sub     #5a
// 341d  ad        xor     l
// 341e  b5        or      l
// 341f  48        ld      c,b
// 3420  24        inc     h
// 3421  229192    ld      (#9291),hl
// 3424  24        inc     h
// 3425  92        sub     d
// 3426  24        inc     h
// 3427  2c        inc     l
// 3428  01dc05    ld      bc,#05dc
// 342b  08        ex      af,af'
// 342c  07        rlca    
// 342d  b8        cp      b
// 342e  0b        dec     bc
// 342f  e40cfe    call    po,#fe0c
// 3432  ff        rst     #38
// 3433  ff        rst     #38
// 3434  ff        rst     #38
// 3435  40        ld      b,b
// 3436  fcd0d2    call    m,#d2d0
// 3439  d2d2d2    jp      nc,#d2d2
// 343c  d2d2d2    jp      nc,#d2d2
// 343f  d2d4fc    jp      nc,#fcd4
// 3442  fcfcda    call    m,#dafc
// 3445  02        ld      (bc),a
// 3446  dcfcfc    call    c,#fcfc
// 3449  fcd0d2    call    m,#d2d0
// 344c  d2d2d2    jp      nc,#d2d2
// 344f  d6d8      sub     #d8
// 3451  d2d2d2    jp      nc,#d2d2
// 3454  d2d4fc    jp      nc,#fcd4
// 3457  da09dc    jp      c,#dc09
// 345a  fcfcfc    call    m,#fcfc
// 345d  da02dc    jp      c,#dc02
// 3460  fcfcfc    call    m,#fcfc
// 3463  da05de    jp      c,#de05
// 3466  e405dc    call    po,#dc05
// 3469  fcda02    call    m,#02da
// 346c  e6e8      and     #e8
// 346e  ea02e6    jp      pe,#e602
// 3471  ea02dc    jp      pe,#dc02
// 3474  fcfcfc    call    m,#fcfc
// 3477  da02dc    jp      c,#dc02
// 347a  fcfcfc    call    m,#fcfc
// 347d  da02e6    jp      c,#e602
// 3480  ea02e7    jp      pe,#e702
// 3483  eb        ex      de,hl
// 3484  02        ld      (bc),a
// 3485  e6ea      and     #ea
// 3487  02        ld      (bc),a
// 3488  dcfcda    call    c,#dafc
// 348b  02        ld      (bc),a
// 348c  defc      sbc     a,#fc
// 348e  e402de    call    po,#de02
// 3491  e402dc    call    po,#dc02
// 3494  fcfcfc    call    m,#fcfc
// 3497  da02dc    jp      c,#dc02
// 349a  fcfcfc    call    m,#fcfc
// 349d  da02de    jp      c,#de02
// 34a0  e405de    call    po,#de05
// 34a3  e402dc    call    po,#dc02
// 34a6  fcda02    call    m,#02da
// 34a9  defc      sbc     a,#fc
// 34ab  e402de    call    po,#de02
// 34ae  e402dc    call    po,#dc02
// 34b1  fcfcfc    call    m,#fcfc
// 34b4  da02dc    jp      c,#dc02
// 34b7  fcfcfc    call    m,#fcfc
// 34ba  da02de    jp      c,#de02
// 34bd  f2e8e8    jp      p,#e8e8
// 34c0  ea02de    jp      pe,#de02
// 34c3  e402dc    call    po,#dc02
// 34c6  fcda02    call    m,#02da
// 34c9  e7        rst     #20
// 34ca  e9        jp      (hl)
// 34cb  eb        ex      de,hl
// 34cc  02        ld      (bc),a
// 34cd  e7        rst     #20
// 34ce  eb        ex      de,hl
// 34cf  02        ld      (bc),a
// 34d0  e7        rst     #20
// 34d1  d2d2d2    jp      nc,#d2d2
// 34d4  eb        ex      de,hl
// 34d5  02        ld      (bc),a
// 34d6  e7        rst     #20
// 34d7  d2d2d2    jp      nc,#d2d2
// 34da  eb        ex      de,hl
// 34db  02        ld      (bc),a
// 34dc  e7        rst     #20
// 34dd  e9        jp      (hl)
// 34de  e9        jp      (hl)
// 34df  e9        jp      (hl)
// 34e0  eb        ex      de,hl
// 34e1  02        ld      (bc),a
// 34e2  dee4      sbc     a,#e4
// 34e4  02        ld      (bc),a
// 34e5  dcfcda    call    c,#dafc
// 34e8  1b        dec     de
// 34e9  dee4      sbc     a,#e4
// 34eb  02        ld      (bc),a
// 34ec  dcfcda    call    c,#dafc
// 34ef  02        ld      (bc),a
// 34f0  e6e8      and     #e8
// 34f2  f8        ret     m
// 
// 34f3  02        ld      (bc),a
// 34f4  f6e8      or      #e8
// 34f6  e8        ret     pe
// 
// 34f7  e8        ret     pe
// 
// 34f8  e8        ret     pe
// 
// 34f9  e8        ret     pe
// 
// 34fa  e8        ret     pe
// 
// 34fb  f8        ret     m
// 
// 34fc  02        ld      (bc),a
// 34fd  f6e8      or      #e8
// 34ff  e8        ret     pe
// 
// 3500  e8        ret     pe
// 
// 3501  ea02e6    jp      pe,#e602
// 3504  f8        ret     m
// 
// 3505  02        ld      (bc),a
// 3506  f6e8      or      #e8
// 3508  e8        ret     pe
// 
// 3509  f4e402    call    p,#02e4
// 350c  dcfcda    call    c,#dafc
// 350f  02        ld      (bc),a
// 3510  defc      sbc     a,#fc
// 3512  e402f7    call    po,#f702
// 3515  e9        jp      (hl)
// 3516  e9        jp      (hl)
// 3517  f5        push    af
// 3518  f3        di      
// 3519  e9        jp      (hl)
// 351a  e9        jp      (hl)
// 351b  f9        ld      sp,hl
// 351c  02        ld      (bc),a
// 351d  f7        rst     #30
// 351e  e9        jp      (hl)
// 351f  e9        jp      (hl)
// 3520  e9        jp      (hl)
// 3521  eb        ex      de,hl
// 3522  02        ld      (bc),a
// 3523  dee4      sbc     a,#e4
// 3525  02        ld      (bc),a
// 3526  f7        rst     #30
// 3527  e9        jp      (hl)
// 3528  e9        jp      (hl)
// 3529  f5        push    af
// 352a  e402dc    call    po,#dc02
// 352d  fcda02    call    m,#02da
// 3530  defc      sbc     a,#fc
// 3532  e405de    call    po,#de05
// 3535  e40bde    call    po,#de0b
// 3538  e405de    call    po,#de05
// 353b  e402dc    call    po,#dc02
// 353e  fcda02    call    m,#02da
// 3541  defc      sbc     a,#fc
// 3543  e402e6    call    po,#e602
// 3546  ea02de    jp      pe,#de02
// 3549  e402ec    call    po,#ec02
// 354c  d3d3      out     (#d3),a
// 354e  d3ee      out     (#ee),a
// 3550  02        ld      (bc),a
// 3551  e6ea      and     #ea
// 3553  02        ld      (bc),a
// 3554  dee4      sbc     a,#e4
// 3556  02        ld      (bc),a
// 3557  e6ea      and     #ea
// 3559  02        ld      (bc),a
// 355a  dee4      sbc     a,#e4
// 355c  02        ld      (bc),a
// 355d  dcfcda    call    c,#dafc
// 3560  02        ld      (bc),a
// 3561  e7        rst     #20
// 3562  e9        jp      (hl)
// 3563  eb        ex      de,hl
// 3564  02        ld      (bc),a
// 3565  dee4      sbc     a,#e4
// 3567  02        ld      (bc),a
// 3568  e7        rst     #20
// 3569  eb        ex      de,hl
// 356a  02        ld      (bc),a
// 356b  dcfcfc    call    c,#fcfc
// 356e  fcda02    call    m,#02da
// 3571  dee4      sbc     a,#e4
// 3573  02        ld      (bc),a
// 3574  e7        rst     #20
// 3575  eb        ex      de,hl
// 3576  02        ld      (bc),a
// 3577  dee4      sbc     a,#e4
// 3579  02        ld      (bc),a
// 357a  e7        rst     #20
// 357b  eb        ex      de,hl
// 357c  02        ld      (bc),a
// 357d  dcfcda    call    c,#dafc
// 3580  06de      ld      b,#de
// 3582  e405f0    call    po,#f005
// 3585  fcfcfc    call    m,#fcfc
// 3588  da02de    jp      c,#de02
// 358b  e405de    call    po,#de05
// 358e  e405dc    call    po,#dc05
// 3591  fcfae8    call    m,#e8fa
// 3594  e8        ret     pe
// 
// 3595  e8        ret     pe
// 
// 3596  ea02de    jp      pe,#de02
// 3599  f2e8e8    jp      p,#e8e8
// 359c  ea02ce    jp      pe,#ce02
// 359f  fcfcfc    call    m,#fcfc
// 35a2  da02de    jp      c,#de02
// 35a5  f2e8e8    jp      p,#e8e8
// 35a8  ea02de    jp      pe,#de02
// 35ab  f2e8e8    jp      p,#e8e8
// 35ae  ea02dc    jp      pe,#dc02
// 35b1  00        nop     
// 35b2  00        nop     
// 35b3  00        nop     
// 35b4  00        nop     
// 35b5  62        ld      h,d
// 35b6  010201    ld      bc,#0102
// 35b9  010101    ld      bc,#0101
// 35bc  0c        inc     c
// 35bd  010104    ld      bc,#0401
// 35c0  010101    ld      bc,#0101
// 35c3  04        inc     b
// 35c4  04        inc     b
// 35c5  03        inc     bc
// 35c6  0c        inc     c
// 35c7  03        inc     bc
// 35c8  03        inc     bc
// 35c9  03        inc     bc
// 35ca  04        inc     b
// 35cb  04        inc     b
// 35cc  03        inc     bc
// 35cd  0c        inc     c
// 35ce  03        inc     bc
// 35cf  010101    ld      bc,#0101
// 35d2  03        inc     bc
// 35d3  04        inc     b
// 35d4  04        inc     b
// 35d5  03        inc     bc
// 35d6  0c        inc     c
// 35d7  0603      ld      b,#03
// 35d9  04        inc     b
// 35da  04        inc     b
// 35db  03        inc     bc
// 35dc  0c        inc     c
// 35dd  0603      ld      b,#03
// 35df  04        inc     b
// 35e0  010101    ld      bc,#0101
// 35e3  010101    ld      bc,#0101
// 35e6  010101    ld      bc,#0101
// 35e9  010101    ld      bc,#0101
// 35ec  010101    ld      bc,#0101
// 35ef  010101    ld      bc,#0101
// 35f2  010101    ld      bc,#0101
// 35f5  010101    ld      bc,#0101
// 35f8  010304    ld      bc,#0403
// 35fb  04        inc     b
// 35fc  0f        rrca    
// 35fd  03        inc     bc
// 35fe  0604      ld      b,#04
// 3600  04        inc     b
// 3601  0f        rrca    
// 3602  03        inc     bc
// 3603  0604      ld      b,#04
// 3605  04        inc     b
// 3606  010101    ld      bc,#0101
// 3609  0c        inc     c
// 360a  03        inc     bc
// 360b  010101    ld      bc,#0101
// 360e  03        inc     bc
// 360f  04        inc     b
// 3610  04        inc     b
// 3611  03        inc     bc
// 3612  0c        inc     c
// 3613  03        inc     bc
// 3614  03        inc     bc
// 3615  03        inc     bc
// 3616  04        inc     b
// 3617  04        inc     b
// 3618  03        inc     bc
// 3619  0c        inc     c
// 361a  03        inc     bc
// 361b  03        inc     bc
// 361c  03        inc     bc
// 361d  04        inc     b
// 361e  010101    ld      bc,#0101
// 3621  01030c    ld      bc,#0c03
// 3624  010101    ld      bc,#0101
// 3627  03        inc     bc
// 3628  010101    ld      bc,#0101
// 362b  08        ex      af,af'
// 362c  1808      jr      #3636           ; (8)
// 362e  1804      jr      #3634           ; (4)
// 3630  010101    ld      bc,#0101
// 3633  01030c    ld      bc,#0c03
// 3636  010101    ld      bc,#0101
// 3639  03        inc     bc
// 363a  010101    ld      bc,#0101
// 363d  04        inc     b
// 363e  04        inc     b
// 363f  03        inc     bc
// 3640  0c        inc     c
// 3641  03        inc     bc
// 3642  03        inc     bc
// 3643  03        inc     bc
// 3644  04        inc     b
// 3645  04        inc     b
// 3646  03        inc     bc
// 3647  0c        inc     c
// 3648  03        inc     bc
// 3649  03        inc     bc
// 364a  03        inc     bc
// 364b  04        inc     b
// 364c  04        inc     b
// 364d  010101    ld      bc,#0101
// 3650  0c        inc     c
// 3651  03        inc     bc
// 3652  010101    ld      bc,#0101
// 3655  03        inc     bc
// 3656  04        inc     b
// 3657  04        inc     b
// 3658  0f        rrca    
// 3659  03        inc     bc
// 365a  0604      ld      b,#04
// 365c  04        inc     b
// 365d  0f        rrca    
// 365e  03        inc     bc
// 365f  0604      ld      b,#04
// 3661  010101    ld      bc,#0101
// 3664  010101    ld      bc,#0101
// 3667  010101    ld      bc,#0101
// 366a  010101    ld      bc,#0101
// 366d  010101    ld      bc,#0101
// 3670  010101    ld      bc,#0101
// 3673  010101    ld      bc,#0101
// 3676  010101    ld      bc,#0101
// 3679  010304    ld      bc,#0403
// 367c  04        inc     b
// 367d  03        inc     bc
// 367e  0c        inc     c
// 367f  0603      ld      b,#03
// 3681  04        inc     b
// 3682  04        inc     b
// 3683  03        inc     bc
// 3684  0c        inc     c
// 3685  0603      ld      b,#03
// 3687  04        inc     b
// 3688  04        inc     b
// 3689  03        inc     bc
// 368a  0c        inc     c
// 368b  03        inc     bc
// 368c  010101    ld      bc,#0101
// 368f  03        inc     bc
// 3690  04        inc     b
// 3691  04        inc     b
// 3692  03        inc     bc
// 3693  0c        inc     c
// 3694  03        inc     bc
// 3695  03        inc     bc
// 3696  03        inc     bc
// 3697  04        inc     b
// 3698  010201    ld      bc,#0102
// 369b  010101    ld      bc,#0101
// 369e  0c        inc     c
// 369f  010104    ld      bc,#0401
// 36a2  010101    ld      bc,#0101
// 
// 	;; Indirect Lookup table for 2c5e routine  (0x48 entries) 
// 36a5  1337			; 0         HIGH SCORE
// 36a7  2337			; 1	    CREDIT   
// 36a9  3237			; 2	    FREE PLAY
// 36ab  4137			; 3         PLAYER ONE
// 36ad  5a37			; 4         PLAYER TWO
// 36af  6a37			; 5         GAME  OVER
// 36b1  7a37			; 6         READY?
// 36b3  8637			; 7	    PUSH START BUTTON
// 36b5  9d37			; 8         1 PLAYER ONLY 
// 36b7  b137			; 9         1 OR 2 PLAYERS
// 36b9  003d			; a  c837   BONUS PAC-MAN FOR   000 Pts
// 36bb  213d			; b  e937   @ 1980 MIDWAY MFG.CO.
// 36bd  fd37			; c         CHARACTER / NICKNAME
// 36bf  673d			; d  1738   "BLINKY" 
// 36c1  e33d			; e  2538   "BBBBBBBB"
// 36c3  863d			; f  3238   "PINKY"  
// 36c5  023e			; 10 3f38   "DDDDDDDD"
// 36c7  4c38			; 11        . 10 Pts
// 36c9  5a38			; 12        o 50 Pts
// 36cb  3c3d			; 13 6838   @ 1980 MIDWAY MFG.CO.
// 36cd  573d			; 14 7538   -SHADOW
// 36cf  d33d			; 15 8638   "AAAAAAAA"
// 36d1  763d			; 16 9838   -SPEEDY
// 36d3  f23d			; 17 aa38   "CCCCCCCC"
// 36d5  0100			; 18 
// 36d7  0200			; 19
// 36d9  0300			; 1a
// 36db  bc38			; 1b ce38    100
// 36dd  c438			; 1c d838    300
// 36df  ce38			; 1d e238    500
// 36e1  d838			; 1e ec38    700
// 36e3  e238			; 1f f638    1000
// 36e5  ec38			; 20 0039    2000
// 36e7  f638			; 21 0039    3000
// 36e9  0039			; 22 0039    5000
// 36eb  0a39                      ; 23         MEMORY  OK
// 36ed  1a39			; 24         BAD    R M
// 36ef  6f39			; 25         FREE  PLAY       
// 36f1  2a39                      ; 26         1 COIN  1 CREDIT 
// 36f3  5839			; 27         1 COIN  2 CREDITS
// 36f5  4139			; 28         2 COINS 1 CREDIT 
// 36f7  4f3e			; 29 a339    PAC-MAN
// 36f8  8639			; 2a	     BONUS  NONE
// 36fb  9739			; 2b         BONUS
// 36fd  b039			; 2c         TABLE  
// 36ff  bd39			; 2d         UPRIGHT
// 3701  ca39			; 2e	     000
// 3703  a53d			; 2f d339    "INKY"    
// 3705  213e			; 30 e139    "FFFFFFFF"
// 3707  c43d			; 31 ee39    "CLYDE"  
// 3709  403e			; 32 fc39    "HHHHHHHH"
// 370b  953d			; 33 093a    -BASHFUL  
// 370d  113e			; 34 1a3a    "EEEEEEEE"
// 3711  b43d			; 35 2c3a    -POKEY   
// 3711  303e			; 36 3d3a    "GGGGGGGG"
// 
// 	;; 36a5 Table Entry 0
// 3713  d483
// NOTE space is 0x40
"HIGH SCORE"
// 371f  2f
// 3720  8f
// 3721  2f
// 3722  80
// 
// 	;; 36a5 Table Entry 1
// 3723  3b        dec     sp
// 3724  80        add     a,b
"CREDIT   "
// 372e  2f        cpl     
// 372f  8f        adc     a,a
// 3730  2f        cpl     
// 3731  80        add     a,b
// 
// 	;; 36a5 Table Entry 2
// 3732  3b        dec     sp
// 3733  80        add     a,b
"FREE PLAY"
// 373d  2f        cpl     
// 373e  8f        adc     a,a
// 373f  2f        cpl     
// 3740  80        add     a,b
// 
// 	;; 36a5 Table Entry 3
// 3741  8c        adc     a,h
// 3742  02        ld      (bc),a
"PLAYER ONE"
// 374d  2f        cpl     
// 374e  85        add     a,l
// 374f  2f        cpl     
// 3750  1010      djnz    #3762           ; (16)
// 3752  1a        ld      a,(de)
// 3753  1a        ld      a,(de)
// 3754  1a        ld      a,(de)
// 3755  1a        ld      a,(de)
// 3756  1a        ld      a,(de)
// 3757  1a        ld      a,(de)
// 3758  1010      djnz    #376a           ; (16)
// 
// 	;; 36a5 Table Entry 4
// 375a  8c        adc     a,h
// 375b  02        ld      (bc),a
"PLAYER TWO"
// 3766  2f        cpl     
// 3767  85        add     a,l
// 3768  2f        cpl     
// 3769  80        add     a,b
// 
// 	;; 36a5 Table Entry 5
// 376a  92        sub     d
// 376b  02        ld      (bc),a
"GAME  OVER"
// 3776  2f        cpl     
// 3777  81        add     a,c
// 3778  2f        cpl     
// 3779  80        add     a,b
// 
// 	;; 36a5 Table Entry 6
// 377a  52        ld      d,d
// 377b  02        ld      (bc),a
"READY?"
// 3782  2f        cpl     
// 3783  89        adc     a,c
// 3784  2f        cpl     
// 3785  90        sub     b
// 
// 	;; 36a5 Table Entry 7
// 3786  ee02      xor     #02
// 3788  50        ld      d,b
// 3789  55        ld      d,l
// 378a  53        ld      d,e
// 378b  48        ld      c,b
// 378c  40        ld      b,b
// 378d  53        ld      d,e
// 378e  54        ld      d,h
// 378f  41        ld      b,c
// 3790  52        ld      d,d
// 3791  54        ld      d,h
// 3792  40        ld      b,b
// 3793  42        ld      b,d
// 3794  55        ld      d,l
// 3795  54        ld      d,h
// 3796  54        ld      d,h
// 3797  4f        ld      c,a
// 3798  4e        ld      c,(hl)
// 3799  2f        cpl     
// 379a  87        add     a,a
// 379b  2f        cpl     
// 379c  80        add     a,b
// 379d  b2        or      d
// 
// 	;; 36a5 Table Entry 8
// 379e  02        ld      (bc),a
// 379f  314050    ld      sp,#5040
// 37a2  4c        ld      c,h
// 37a3  41        ld      b,c
// 37a4  59        ld      e,c
// 37a5  45        ld      b,l
// 37a6  52        ld      d,d
// 37a7  40        ld      b,b
// 37a8  4f        ld      c,a
// 37a9  4e        ld      c,(hl)
// 37aa  4c        ld      c,h
// 37ab  59        ld      e,c
// 37ac  40        ld      b,b
// 37ad  2f        cpl     
// 37ae  85        add     a,l
// 37af  2f        cpl     
// 37b0  80        add     a,b
// 
// 	;; 36a5 Table Entry 9
// 37b1  b2        or      d
// 37b2  02        ld      (bc),a
// 37b3  31404f    ld      sp,#4f40
// 37b6  52        ld      d,d
// 37b7  40        ld      b,b
// 37b8  324050    ld      (#5040),a
// 37bb  4c        ld      c,h
// 37bc  41        ld      b,c
// 37bd  59        ld      e,c
// 37be  45        ld      b,l
// 37bf  52        ld      d,d
// 37c0  53        ld      d,e
// 37c1  2f        cpl     
// 37c2  85        add     a,l
// 37c3  00        nop     
// 37c4  2f        cpl     
// 37c5  00        nop     
// 37c6  80        add     a,b
// 
// 	;; 36a5 Table Entry ??
// 37c7  00        nop     
// 37c8  96        sub     (hl)
// 37c9  03        inc     bc
// 37ca  42        ld      b,d
// 37cb  4f        ld      c,a
// 37cc  4e        ld      c,(hl)
// 37cd  55        ld      d,l
// 37ce  53        ld      d,e
// 37cf  40        ld      b,b
// 37d0  50        ld      d,b
// 37d1  55        ld      d,l
// 37d2  43        ld      b,e
// 37d3  4b        ld      c,e
// 37d4  4d        ld      c,l
// 37d5  41        ld      b,c
// 37d6  4e        ld      c,(hl)
// 37d7  40        ld      b,b
// 37d8  46        ld      b,(hl)
// 37d9  4f        ld      c,a
// 37da  52        ld      d,d
// 37db  40        ld      b,b
// 37dc  40        ld      b,b
// 37dd  40        ld      b,b
// 37de  3030      jr      nc,#3810        ; (48)
// 37e0  3040      jr      nc,#3822        ; (64)
// 37e2  5d        ld      e,l
// 37e3  5e        ld      e,(hl)
// 37e4  5f        ld      e,a
// 37e5  2f        cpl     
// 37e6  8e        adc     a,(hl)
// 37e7  2f        cpl     
// 37e8  80        add     a,b
// 37e9  ba        cp      d
// 
// 37ea  02        ld      (bc),a		; NAMCO
// 37eb  5c        ld      e,h
// 37ec  40        ld      b,b
// 37ed  28R29      jr      z,#3818         ; (41)
// 37ef  2a2b2c    ld      hl,(#2c2b)
// 37f2  2d        dec     l
// 37f3  2e40      ld      l,#40
// 37f5  313938    ld      sp,#3839
// 37f8  302f      jr      nc,#3829        ; (47)
// 37fa  83        add     a,e
// 37fb  2f        cpl     
// 37fc  80        add     a,b
// 
// 	;; 36a5 Table Entry c
// 37fd  c30243    jp      #4302
// 3800  48        ld      c,b
// 3801  41        ld      b,c
// 3802  52        ld      d,d
// 3803  41        ld      b,c
// 3804  43        ld      b,e
// 3805  54        ld      d,h
// 3806  45        ld      b,l
// 3807  52        ld      d,d
// 3808  40        ld      b,b
// 3809  3a404e    ld      a,(#4e40)
// 380c  49        ld      c,c
// 380d  43        ld      b,e
// 380e  4b        ld      c,e
// 380f  4e        ld      c,(hl)
// 3810  41        ld      b,c
// 3811  4d        ld      c,l
// 3812  45        ld      b,l
// 3813  2f        cpl     
// 3814  8f        adc     a,a
// 3815  2f        cpl     
// 3816  80        add     a,b
// 
// 3817  65        ld      h,l
// 3818  012641    ld      bc,#4126
// 381b  4b        ld      c,e
// 381c  41        ld      b,c
// 381d  42        ld      b,d
// 381e  45        ld      b,l
// 381f  49        ld      c,c
// 3820  262f      ld      h,#2f
// 3822  81        add     a,c
// 3823  2f        cpl     
// 3824  80        add     a,b
// 3825  45        ld      b,l
// 3826  01264d    ld      bc,#4d26
// 3829  41        ld      b,c
// 382a  43        ld      b,e
// 382b  4b        ld      c,e
// 382c  59        ld      e,c
// 382d  262f      ld      h,#2f
// 382f  81        add     a,c
// 3830  2f        cpl     
// 3831  80        add     a,b
// 3832  48        ld      c,b
// 3833  012650    ld      bc,#5026
// 3836  49        ld      c,c
// 3837  4e        ld      c,(hl)
// 3838  4b        ld      c,e
// 3839  59        ld      e,c
// 383a  262f      ld      h,#2f
// 383c  83        add     a,e
// 383d  2f        cpl     
// 383e  80        add     a,b
// 383f  48        ld      c,b
// 3840  01264d    ld      bc,#4d26
// 3843  49        ld      c,c
// 3844  43        ld      b,e
// 3845  4b        ld      c,e
// 3846  59        ld      e,c
// 3847  262f      ld      h,#2f
// 3849  83        add     a,e
// 384a  2f        cpl     
// 384b  80        add     a,b
// 
// 	;; 36a5 Table Entry 11
// 384c  76        halt    
// 384d  02        ld      (bc),a
// 384e  1040      djnz    #3890           ; (64)
// 3850  313040    ld      sp,#4030
// 3853  5d        ld      e,l
// 3854  5e        ld      e,(hl)
// 3855  5f        ld      e,a
// 3856  2f        cpl     
// 3857  9f        sbc     a,a
// 3858  2f        cpl     
// 3859  80        add     a,b
// 
// 	;; 36a5 Table Entry 12
// 385a  78        ld      a,b
// 385b  02        ld      (bc),a
// 385c  14        inc     d
// 385d  40        ld      b,b
// 385e  35        dec     (hl)
// 385f  3040      jr      nc,#38a1        ; (64)
// 3861  5d        ld      e,l
// 3862  5e        ld      e,(hl)
// 3863  5f        ld      e,a
// 3864  2f        cpl     
// 3865  9f        sbc     a,a
// 3866  2f        cpl     
// 3867  80        add     a,b
// 
// 3868  5d        ld      e,l
// 3869  02        ld      (bc),a
// 386a  2829      jr      z,#3895         ; (41)
// 386c  2a2b2c    ld      hl,(#2c2b)
// 386f  2d        dec     l
// 3870  2e2f      ld      l,#2f
// 3872  83        add     a,e
// 3873  2f        cpl     
// 3874  80        add     a,b
// 3875  c5        push    bc
// 3876  02        ld      (bc),a
// 3877  40        ld      b,b
// 3878  4f        ld      c,a
// 3879  49        ld      c,c
// 387a  4b        ld      c,e
// 387b  41        ld      b,c
// 387c  4b        ld      c,e
// 387d  45        ld      b,l
// 387e  3b        dec     sp
// 387f  3b        dec     sp
// 3880  3b        dec     sp
// 3881  3b        dec     sp
// 3882  2f        cpl     
// 3883  81        add     a,c
// 3884  2f        cpl     
// 3885  80        add     a,b
// 3886  c5        push    bc
// 3887  02        ld      (bc),a
// 3888  40        ld      b,b
// 3889  55        ld      d,l
// 388a  52        ld      d,d
// 388b  43        ld      b,e
// 388c  48        ld      c,b
// 388d  49        ld      c,c
// 388e  4e        ld      c,(hl)
// 388f  3b        dec     sp
// 3890  3b        dec     sp
// 3891  3b        dec     sp
// 3892  3b        dec     sp
// 3893  3b        dec     sp
// 3894  2f        cpl     
// 3895  81        add     a,c
// 3896  2f        cpl     
// 3897  80        add     a,b
// 3898  c8        ret     z
// 3899  02        ld      (bc),a
// 389a  40        ld      b,b
// 389b  4d        ld      c,l
// 389c  41        ld      b,c
// 389d  43        ld      b,e
// 389e  48        ld      c,b
// 389f  49        ld      c,c
// 38a0  42        ld      b,d
// 38a1  55        ld      d,l
// 38a2  53        ld      d,e
// 38a3  45        ld      b,l
// 38a4  3b        dec     sp
// 38a5  3b        dec     sp
// 38a6  2f        cpl     
// 38a7  83        add     a,e
// 38a8  2f        cpl     
// 38a9  80        add     a,b
// 38aa  c8        ret     z
// 38ab  02        ld      (bc),a
// 38ac  40        ld      b,b
// 38ad  52        ld      d,d
// 38ae  4f        ld      c,a
// 38af  4d        ld      c,l
// 38b0  50        ld      d,b
// 38b1  3b        dec     sp
// 38b2  3b        dec     sp
// 38b3  3b        dec     sp
// 38b4  3b        dec     sp
// 38b5  3b        dec     sp
// 38b6  3b        dec     sp
// 38b7  3b        dec     sp
// 38b8  2f        cpl     
// 38b9  83        add     a,e
// 38ba  2f        cpl     
// 38bb  80        add     a,b
// 
// 	;; 36a5 Table Entry 21
// 38bc  12        ld      (de),a
// 38bd  02        ld      (bc),a
// 38be  81        add     a,c
// 38bf  85        add     a,l
// 38c0  2f        cpl     
// 38c1  83        add     a,e
// 38c2  2f        cpl     
// 38c3  90        sub     b
// 
// 	;; 36a5 Table Entry 22
// 38c4  3202
// 38c6  40
// 38c7  82        add     a,d
// 38c8  85        add     a,l
// 38c9  40        ld      b,b
// 38ca  2f        cpl     
// 38cb  83        add     a,e
// 38cc  2f        cpl     
// 38cd  90        sub     b
// 
// 	;; 36a5 Table Entry 23
// 38ce  3202				; OFFSET 
// 38d0  40
// 38d1  83        add     a,e
// 38d2  85        add     a,l
// 38d3  40        ld      b,b
// 38d4  2f        cpl     
// 38d5  83        add     a,e
// 38d6  2f        cpl     
// 38d7  90        sub     b
// 
// 	;; 36a5 Table Entry 24
// 38d8  320240    ld      (#4002),a
// 38db  84        add     a,h
// 38dc  85        add     a,l
// 38dd  40        ld      b,b
// 38de  2f        cpl     
// 38df  83        add     a,e
// 38e0  2f        cpl     
// 38e1  90        sub     b
// 
// 38e2  320240    ld      (#4002),a
// 38e5  86        add     a,(hl)
// 38e6  8d        adc     a,l
// 38e7  8e        adc     a,(hl)
// 38e8  2f        cpl     
// 38e9  83        add     a,e
// 38ea  2f        cpl     
// 38eb  90        sub     b
// 38ec  320287    ld      (#8702),a
// 38ef  88        adc     a,b
// 38f0  8d        adc     a,l
// 38f1  8e        adc     a,(hl)
// 38f2  2f        cpl     
// 38f3  83        add     a,e
// 38f4  2f        cpl     
// 38f5  90        sub     b
// 38f6  320289    ld      (#8902),a
// 38f9  8a        adc     a,d
// 38fa  8d        adc     a,l
// 38fb  8e        adc     a,(hl)
// 38fc  2f        cpl     
// 38fd  83        add     a,e
// 38fe  2f        cpl     
// 38ff  90        sub     b
// 3900  32028b    ld      (#8b02),a
// 3903  8c        adc     a,h
// 3904  8d        adc     a,l
// 3905  8e        adc     a,(hl)
// 3906  2f        cpl     
// 3907  83        add     a,e
// 3908  2f        cpl     
// 3909  90        sub     b
// 
// 	;; 36a5 Table Entry 23
// 390a  04        inc     b
// 390b  03        inc     bc
// 390c  4d        ld      c,l
// 390d  45        ld      b,l
// 390e  4d        ld      c,l
// 390f  4f        ld      c,a
// 3910  52        ld      d,d
// 3911  59        ld      e,c
// 3912  40        ld      b,b
// 3913  40        ld      b,b
// 3914  4f        ld      c,a
// 3915  4b        ld      c,e
// 3916  2f        cpl     
// 3917  8f        adc     a,a
// 3918  2f        cpl     
// 3919  80        add     a,b
// 
// 	;; 36a5 Table Entry 24
// 391a  04        inc     b
// 391b  03        inc     bc
// 391c  42        ld      b,d
// 391d  41        ld      b,c
// 391e  44        ld      b,h
// 391f  40        ld      b,b
// 3920  40        ld      b,b
// 3921  40        ld      b,b
// 3922  40        ld      b,b
// 3923  52        ld      d,d
// 3924  40        ld      b,b
// 3925  4d        ld      c,l
// 3926  2f        cpl     
// 3927  8f        adc     a,a
// 3928  2f        cpl     
// 3929  80        add     a,b
// 
// 	;; 36a5 Table Entry 26
// 392a  08        ex      af,af'
// 392b  03        inc     bc
// 392c  314043    ld      sp,#4340
// 392f  4f        ld      c,a
// 3930  49        ld      c,c
// 3931  4e        ld      c,(hl)
// 3932  40        ld      b,b
// 3933  40        ld      b,b
// 3934  314043    ld      sp,#4340
// 3937  52        ld      d,d
// 3938  45        ld      b,l
// 3939  44        ld      b,h
// 393a  49        ld      c,c
// 393b  54        ld      d,h
// 393c  40        ld      b,b
// 393d  2f        cpl     
// 393e  8f        adc     a,a
// 393f  2f        cpl     
// 3940  80        add     a,b
// 
// 	;; 36a5 Table Entry 28
// 3941  08        ex      af,af'a
// 3942  03        inc     bc
// 3943  324043    ld      (#4340),a
// 3946  4f        ld      c,a
// 3947  49        ld      c,c
// 3948  4e        ld      c,(hl)
// 3949  53        ld      d,e
// 394a  40        ld      b,b
// 394b  314043    ld      sp,#4340
// 394e  52        ld      d,d
// 394f  45        ld      b,l
// 3950  44        ld      b,h
// 3951  49        ld      c,c
// 3952  54        ld      d,h
// 3953  40        ld      b,b
// 3954  2f        cpl     
// 3955  8f        adc     a,a
// 3956  2f        cpl     
// 3957  80        add     a,b
// 
// 	;; 36a5 Table Entry 27
// 3958  08        ex      af,af'
// 3959  03        inc     bc
// 395a  314043    ld      sp,#4340
// 395d  4f        ld      c,a
// 395e  49        ld      c,c
// 395f  4e        ld      c,(hl)
// 3960  40        ld      b,b
// 3961  40        ld      b,b
// 3962  324043    ld      (#4340),a
// 3965  52        ld      d,d
// 3966  45        ld      b,l
// 3967  44        ld      b,h
// 3968  49        ld      c,c
// 3969  54        ld      d,h
// 396a  53        ld      d,e
// 396b  2f        cpl     
// 396c  8f        adc     a,a
// 396d  2f        cpl     
// 396e  80        add     a,b
// 
// 	;; 36a5 Table Entry 25
// 396f  08        ex      af,af'
// 3970  03        inc     bc
// 3971  46        ld      b,(hl)
// 3972  52        ld      d,d
// 3973  45        ld      b,l
// 3974  45        ld      b,l
// 3975  40        ld      b,b
// 3976  40        ld      b,b
// 3977  50        ld      d,b
// 3978  4c        ld      c,h
// 3979  41        ld      b,c
// 397a  59        ld      e,c
// 397b  40        ld      b,b
// 397c  40        ld      b,b
// 397d  40        ld      b,b
// 397e  40        ld      b,b
// 397f  40        ld      b,b
// 3980  40        ld      b,b
// 3981  40        ld      b,b
// 3982  2f        cpl     
// 3983  8f        adc     a,a
// 3984  2f        cpl     
// 3985  80        add     a,b
// 
// 	;; 36a5 Table Entry 2a
// 3986  0a        ld      a,(bc)
// 3987  03        inc     bc
// 3988  42        ld      b,d
// 3989  4f        ld      c,a
// 398a  4e        ld      c,(hl)
// 398b  55        ld      d,l
// 398c  53        ld      d,e
// 398d  40        ld      b,b
// 398e  40        ld      b,b
// 398f  4e        ld      c,(hl)
// 3990  4f        ld      c,a
// 3991  4e        ld      c,(hl)
// 3992  45        ld      b,l
// 3993  2f        cpl     
// 3994  8f        adc     a,a
// 3995  2f        cpl     
// 3996  80        add     a,b
// 
// 	;; 36a5 Table Entry 2b
// 3997  0a        ld      a,(bc)
// 3998  03        inc     bc
// 3999  42        ld      b,d
// 399a  4f        ld      c,a
// 399b  4e        ld      c,(hl)
// 399c  55        ld      d,l
// 399d  53        ld      d,e
// 399e  40        ld      b,b
// 399f  2f        cpl     
// 39a0  8f        adc     a,a
// 39a1  2f        cpl     
// 39a2  80        add     a,b
// 
// 39a3  0c        inc     c
// 39a4  03        inc     bc
// 39a5  50        ld      d,b
// 39a6  55        ld      d,l
// 39a7  43        ld      b,e
// 39a8  4b        ld      c,e
// 39a9  4d        ld      c,l
// 39aa  41        ld      b,c
// 39ab  4e        ld      c,(hl)
// 39ac  2f        cpl     
// 39ad  8f        adc     a,a
// 39ae  2f        cpl     
// 39af  80        add     a,b
// 
// 	;; 36a5 Table Entry 2c
// 39b0  0e03      ld      c,#03
// 39b2  54        ld      d,h
// 39b3  41        ld      b,c
// 39b4  42        ld      b,d
// 39b5  4c        ld      c,h
// 39b6  45        ld      b,l
// 39b7  40        ld      b,b
// 39b8  40        ld      b,b
// 39b9  2f        cpl     
// 39ba  8f        adc     a,a
// 39bb  2f        cpl     
// 39bc  80        add     a,b
// 
// 	;; 36a5 Table Entry 2d
// 39bd  0e03      ld      c,#03
// 39bf  55        ld      d,l
// 39c0  50        ld      d,b
// 39c1  52        ld      d,d
// 39c2  49        ld      c,c
// 39c3  47        ld      b,a
// 39c4  48        ld      c,b
// 39c5  54        ld      d,h
// 39c6  2f        cpl     
// 39c7  8f        adc     a,a
// 39c8  2f        cpl     
// 39c9  80        add     a,b
// 
// 	;; 36a5 Table Entry 2e
// 39ca  0a        ld      a,(bc)
// 39cb  02        ld      (bc),a
// 39cc  3030      jr      nc,#39fe        ; (48)
// 39ce  302f      jr      nc,#39ff        ; (47)
// 39d0  8f        adc     a,a
// 39d1  2f        cpl     
// 39d2  80        add     a,b
// 
// 	;; 36a5 Table Entry
// 39d3  6b        ld      l,e
// 39d4  012641    ld      bc,#4126
// 39d7  4f        ld      c,a
// 39d8  53        ld      d,e
// 39d9  55        ld      d,l
// 39da  4b        ld      c,e
// 39db  45        ld      b,l
// 39dc  262f      ld      h,#2f
// 39de  85        add     a,l
// 39df  2f        cpl     
// 39e0  80        add     a,b
// 39e1  4b        ld      c,e
// 39e2  01264d    ld      bc,#4d26
// 39e5  55        ld      d,l
// 39e6  43        ld      b,e
// 39e7  4b        ld      c,e
// 39e8  59        ld      e,c
// 39e9  262f      ld      h,#2f
// 39eb  85        add     a,l
// 39ec  2f        cpl     
// 39ed  80        add     a,b
// 39ee  6e        ld      l,(hl)
// 39ef  012647    ld      bc,#4726
// 39f2  55        ld      d,l
// 39f3  5a        ld      e,d
// 39f4  55        ld      d,l
// 39f5  54        ld      d,h
// 39f6  41        ld      b,c
// 39f7  262f      ld      h,#2f
// 39f9  87        add     a,a
// 39fa  2f        cpl     
// 39fb  80        add     a,b
// 39fc  4e        ld      c,(hl)
// 39fd  01264d    ld      bc,#4d26
// 3a00  4f        ld      c,a
// 3a01  43        ld      b,e
// 3a02  4b        ld      c,e
// 3a03  59        ld      e,c
// 3a04  262f      ld      h,#2f
// 3a06  87        add     a,a
// 3a07  2f        cpl     
// 3a08  80        add     a,b
// 3a09  cb02      rlc     d
// 3a0b  40        ld      b,b
// 3a0c  4b        ld      c,e
// 3a0d  49        ld      c,c
// 3a0e  4d        ld      c,l
// 3a0f  41        ld      b,c
// 3a10  47        ld      b,a
// 3a11  55        ld      d,l
// 3a12  52        ld      d,d
// 3a13  45        ld      b,l
// 3a14  3b        dec     sp
// 3a15  3b        dec     sp
// 3a16  2f        cpl     
// 3a17  85        add     a,l
// 3a18  2f        cpl     
// 3a19  80        add     a,b
// 3a1a  cb02      rlc     d
// 3a1c  40        ld      b,b
// 3a1d  53        ld      d,e
// 3a1e  54        ld      d,h
// 3a1f  59        ld      e,c
// 3a20  4c        ld      c,h
// 3a21  49        ld      c,c
// 3a22  53        ld      d,e
// 3a23  54        ld      d,h
// 3a24  3b        dec     sp
// 3a25  3b        dec     sp
// 3a26  3b        dec     sp
// 3a27  3b        dec     sp
// 3a28  2f        cpl     
// 3a29  85        add     a,l
// 3a2a  2f        cpl     
// 3a2b  80        add     a,b
// 3a2c  ce02      adc     a,#02
// 3a2e  40        ld      b,b
// 3a2f  4f        ld      c,a
// 3a30  54        ld      d,h
// 3a31  4f        ld      c,a
// 3a32  42        ld      b,d
// 3a33  4f        ld      c,a
// 3a34  4b        ld      c,e
// 3a35  45        ld      b,l
// 3a36  3b        dec     sp
// 3a37  3b        dec     sp
// 3a38  3b        dec     sp
// 3a39  2f        cpl     
// 3a3a  87        add     a,a
// 3a3b  2f        cpl     
// 3a3c  80        add     a,b
// 3a3d  ce02      adc     a,#02
// 3a3f  40        ld      b,b
// 3a40  43        ld      b,e
// 3a41  52        ld      d,d
// 3a42  59        ld      e,c
// 3a43  42        ld      b,d
// 3a44  41        ld      b,c
// 3a45  42        ld      b,d
// 3a46  59        ld      e,c
// 3a47  3b        dec     sp
// 3a48  3b        dec     sp
// 3a49  3b        dec     sp
// 3a4a  3b        dec     sp
// 3a4b  2f        cpl     
// 3a4c  87        add     a,a
// 3a4d  2f        cpl     
// 3a4e  80        add     a,b
// 3a4f  010103    ld      bc,#0301
// 3a52  010101    ld      bc,#0101
// 3a55  03        inc     bc
// 3a56  02        ld      (bc),a
// 3a57  02        ld      (bc),a
// 3a58  02        ld      (bc),a
// 3a59  010101    ld      bc,#0101
// 3a5c  010204    ld      bc,#0402
// 3a5f  04        inc     b
// 3a60  04        inc     b
// 3a61  0602      ld      b,#02
// 3a63  02        ld      (bc),a
// 3a64  02        ld      (bc),a
// 3a65  02        ld      (bc),a
// 3a66  04        inc     b
// 3a67  02        ld      (bc),a
// 3a68  04        inc     b
// 3a69  04        inc     b
// 3a6a  04        inc     b
// 3a6b  0602      ld      b,#02
// 3a6d  02        ld      (bc),a
// 3a6e  02        ld      (bc),a
// 3a6f  02        ld      (bc),a
// 3a70  010101    ld      bc,#0101
// 3a73  010204    ld      bc,#0402
// 3a76  04        inc     b
// 3a77  04        inc     b
// 3a78  0602      ld      b,#02
// 3a7a  02        ld      (bc),a
// 3a7b  02        ld      (bc),a
// 3a7c  02        ld      (bc),a
// 3a7d  0604      ld      b,#04
// 3a7f  05        dec     b
// 3a80  010103    ld      bc,#0301
// 3a83  010101    ld      bc,#0101
// 3a86  04        inc     b
// 3a87  010101    ld      bc,#0101
// 3a8a  03        inc     bc
// 3a8b  010104    ld      bc,#0401
// 3a8e  010101    ld      bc,#0101
// 3a91  6c        ld      l,h
// 3a92  05        dec     b
// 3a93  010101    ld      bc,#0101
// 3a96  1804      jr      #3a9c           ; (4)
// 3a98  04        inc     b
// 3a99  1805      jr      #3aa0           ; (5)
// 3a9b  010101    ld      bc,#0101
// 3a9e  17        rla     
// 3a9f  02        ld      (bc),a
// 3aa0  03        inc     bc
// 3aa1  04        inc     b
// 3aa2  1604      ld      d,#04
// 3aa4  03        inc     bc
// 3aa5  010101    ld      bc,#0101
// 3aa8  76        halt    
// 3aa9  010101    ld      bc,#0101
// 3aac  010301    ld      bc,#0103
// 3aaf  010102    ld      bc,#0201
// 3ab2  04        inc     b
// 3ab3  02        ld      (bc),a
// 3ab4  04        inc     b
// 3ab5  0e02      ld      c,#02
// 3ab7  04        inc     b
// 3ab8  02        ld      (bc),a
// 3ab9  04        inc     b
// 3aba  02        ld      (bc),a
// 3abb  04        inc     b
// 3abc  0b        dec     bc
// 3abd  010101    ld      bc,#0101
// 3ac0  02        ld      (bc),a
// 3ac1  04        inc     b
// 3ac2  02        ld      (bc),a
// 3ac3  010101    ld      bc,#0101
// 3ac6  010202    ld      bc,#0202
// 3ac9  02        ld      (bc),a
// 3aca  0e02      ld      c,#02
// 3acc  04        inc     b
// 3acd  02        ld      (bc),a
// 3ace  04        inc     b
// 3acf  02        ld      (bc),a
// 3ad0  010201    ld      bc,#0102
// 3ad3  0a        ld      a,(bc)
// 3ad4  010101    ld      bc,#0101
// 3ad7  010301    ld      bc,#0103
// 3ada  010103    ld      bc,#0301
// 3add  010103    ld      bc,#0301
// 3ae0  04        inc     b
// 3ae1  00        nop     
// 3ae2  02        ld      (bc),a
// 3ae3  40        ld      b,b
// 3ae4  013e3d    ld      bc,#3d3e
// 3ae7  1040      djnz    #3b29           ; (64)
// 3ae9  40        ld      b,b
// 3aea  0e3d      ld      c,#3d
// 3aec  3e10      ld      a,#10
// 3aee  c24301    jp      nz,#0143
// 3af1  3e3d      ld      a,#3d
// 3af3  1021      djnz    #3b16           ; (33)
// 3af5  a2        and     d
// 3af6  40        ld      b,b
// 3af7  114f3a    ld      de,#3a4f
// 3afa  3614      ld      (hl),#14
// 3afc  1a        ld      a,(de)
// 3afd  a7        and     a
// 3afe  c8        ret     z
// 
// 3aff  13        inc     de
// 3b00  85        add     a,l
// 3b01  6f        ld      l,a
// 3b02  d2fa3a    jp      nc,#3afa
// 3b05  24        inc     h
// 3b06  18f2      jr      #3afa           ; (-14)
// 3b08  90        sub     b
// 3b09  14        inc     d
// 3b0a  94        sub     h
// 3b0b  0f        rrca    
// 3b0c  98        sbc     a,b
// 3b0d  15        dec     d
// 3b0e  98        sbc     a,b
// 3b0f  15        dec     d
// 3b10  a0        and     b
// 3b11  14        inc     d
// 3b12  a0        and     b
// 3b13  14        inc     d
// 3b14  a4        and     h
// 3b15  17        rla     
// 3b16  a4        and     h
// 3b17  17        rla     
// 3b18  a8        xor     b
// 3b19  09        add     hl,bc
// 3b1a  a8        xor     b
// 3b1b  09        add     hl,bc
// 3b1c  9c        sbc     a,h
// 3b1d  169c      ld      d,#9c
// 3b1f  16ac      ld      d,#ac
// 3b21  16ac      ld      d,#ac
// 3b23  16ac      ld      d,#ac
// 3b25  16ac      ld      d,#ac
// 3b27  16ac      ld      d,#ac
// 3b29  16ac      ld      d,#ac
// 3b2b  16ac      ld      d,#ac
// 3b2d  16ac      ld      d,#ac
// 3b2f  1673      ld      d,#73
// 3b31  2000      jr      nz,#3b33        ; (0)
// 3b33  0c        inc     c
// 3b34  00        nop     
// 3b35  0a        ld      a,(bc)
// 3b36  1f        rra     
// 3b37  00        nop     
// 3b38  72        ld      (hl),d
// 3b39  20fb      jr      nz,#3b36        ; (-5)
// 3b3b  87        add     a,a
// 3b3c  00        nop     
// 3b3d  02        ld      (bc),a
// 3b3e  0f        rrca    
// 3b3f  00        nop     
// 3b40  3620      ld      (hl),#20
// 3b42  04        inc     b
// 3b43  8c        adc     a,h
// 3b44  00        nop     
// 3b45  00        nop     
// 3b46  0600      ld      b,#00
// 3b48  3628      ld      (hl),#28
// 3b4a  05        dec     b
// 3b4b  8b        adc     a,e
// 3b4c  00        nop     
// 3b4d  00        nop     
// 3b4e  0600      ld      b,#00
// 3b50  3630      ld      (hl),#30
// 3b52  068a      ld      b,#8a
// 3b54  00        nop     
// 3b55  00        nop     
// 3b56  0600      ld      b,#00
// 3b58  363c      ld      (hl),#3c
// 3b5a  07        rlca    
// 3b5b  89        adc     a,c
// 3b5c  00        nop     
// 3b5d  00        nop     
// 3b5e  0600      ld      b,#00
// 3b60  3648      ld      (hl),#48
// 3b62  08        ex      af,af'
// 3b63  88        adc     a,b
// 3b64  00        nop     
// 3b65  00        nop     
// 3b66  0600      ld      b,#00
// 3b68  24        inc     h
// 3b69  00        nop     
// 3b6a  0608      ld      b,#08
// 3b6c  00        nop     
// 3b6d  00        nop     
// 3b6e  0a        ld      a,(bc)
// 3b6f  00        nop     
// 3b70  40        ld      b,b
// 3b71  70        ld      (hl),b
// 3b72  fa1000    jp      m,#0010
// 3b75  00        nop     
// 3b76  0a        ld      a,(bc)
// 3b77  00        nop     
// 3b78  70        ld      (hl),b
// 3b79  04        inc     b
// 3b7a  00        nop     
// 3b7b  00        nop     
// 3b7c  00        nop     
// 3b7d  00        nop     
// 3b7e  08        ex      af,af'
// 3b7f  00        nop     
// 3b80  42        ld      b,d
// 3b81  18fd      jr      #3b80           ; (-3)
// 3b83  0600      ld      b,#00
// 3b85  010c00    ld      bc,#000c
// 3b88  42        ld      b,d
// 3b89  04        inc     b
// 3b8a  03        inc     bc
// 3b8b  0600      ld      b,#00
// 3b8d  010c00    ld      bc,#000c
// 3b90  56        ld      d,(hl)
// 3b91  0c        inc     c
// 3b92  ff        rst     #38
// 3b93  8c        adc     a,h
// 3b94  00        nop     
// 3b95  02        ld      (bc),a
// 3b96  0f        rrca    
// 3b97  00        nop     
// 3b98  05        dec     b
// 3b99  00        nop     
// 3b9a  02        ld      (bc),a
// 3b9b  2000      jr      nz,#3b9d        ; (0)
// 3b9d  010c00    ld      bc,#000c
// 3ba0  41        ld      b,c
// 3ba1  20ff      jr      nz,#3ba2        ; (-1)
// 3ba3  86        add     a,(hl)
// 3ba4  fe1c      cp      #1c
// 3ba6  0f        rrca    
// 3ba7  ff        rst     #38
// 3ba8  70        ld      (hl),b
// 3ba9  00        nop     
// 3baa  010c00    ld      bc,#000c
// 3bad  010800    ld      bc,#0008
// 3bb0  010204    ld      bc,#0402
// 3bb3  08        ex      af,af'
// 3bb4  1020      djnz    #3bd6           ; (32)
// 3bb6  40        ld      b,b
// 3bb7  80        add     a,b
// 3bb8  00        nop     
// 3bb9  57        ld      d,a
// 3bba  5c        ld      e,h
// 3bbb  61        ld      h,c
// 3bbc  67        ld      h,a
// 3bbd  6d        ld      l,l
// 3bbe  74        ld      (hl),h
// 3bbf  7b        ld      a,e
// 3bc0  82        add     a,d
// 3bc1  8a        adc     a,d
// 3bc2  92        sub     d
// 3bc3  9a        sbc     a,d
// 3bc4  a3        and     e
// 3bc5  ad        xor     l
// 3bc6  b8        cp      b
// 3bc7  c3d43b    jp      #3bd4
// 3bca  f3        di      
// 3bcb  3b        dec     sp
// 3bcc  58        ld      e,b
// 3bcd  3c        inc     a
// 3bce  95        sub     l
// 3bcf  3c        inc     a
// 3bd0  de3c      sbc     a,#3c
// 3bd2  df        rst     #18
// 3bd3  3c        inc     a
// 3bd4  f1        pop     af
// 3bd5  02        ld      (bc),a
// 3bd6  f203f3    jp      p,#f303
// 3bd9  0f        rrca    
// 3bda  f40182    call    p,#8201
// 3bdd  70        ld      (hl),b
// 3bde  69        ld      l,c
// 3bdf  82        add     a,d
// 3be0  70        ld      (hl),b
// 3be1  69        ld      l,c
// 3be2  83        add     a,e
// 3be3  70        ld      (hl),b
// 3be4  6a        ld      l,d
// 3be5  83        add     a,e
// 3be6  70        ld      (hl),b
// 3be7  6a        ld      l,d
// 3be8  82        add     a,d
// 3be9  70        ld      (hl),b
// 3bea  69        ld      l,c
// 3beb  82        add     a,d
// 3bec  70        ld      (hl),b
// 3bed  69        ld      l,c
// 3bee  89        adc     a,c
// 3bef  8b        adc     a,e
// 3bf0  8d        adc     a,l
// 3bf1  8e        adc     a,(hl)
// 3bf2  ff        rst     #38
// 3bf3  f1        pop     af
// 3bf4  02        ld      (bc),a
// 3bf5  f203f3    jp      p,#f303
// 3bf8  0f        rrca    
// 3bf9  f40167    call    p,#6701
// 3bfc  50        ld      d,b
// 3bfd  3047      jr      nc,#3c46        ; (71)
// 3bff  3067      jr      nc,#3c68        ; (103)
// 3c01  50        ld      d,b
// 3c02  3047      jr      nc,#3c4b        ; (71)
// 3c04  3067      jr      nc,#3c6d        ; (103)
// 3c06  50        ld      d,b
// 3c07  3047      jr      nc,#3c50        ; (71)
// 3c09  304b      jr      nc,#3c56        ; (75)
// 3c0b  104c      djnz    #3c59           ; (76)
// 3c0d  104d      djnz    #3c5c           ; (77)
// 3c0f  104e      djnz    #3c5f           ; (78)
// 3c11  1067      djnz    #3c7a           ; (103)
// 3c13  50        ld      d,b
// 3c14  3047      jr      nc,#3c5d        ; (71)
// 3c16  3067      jr      nc,#3c7f        ; (103)
// 3c18  50        ld      d,b
// 3c19  3047      jr      nc,#3c62        ; (71)
// 3c1b  3067      jr      nc,#3c84        ; (103)
// 3c1d  50        ld      d,b
// 3c1e  3047      jr      nc,#3c67        ; (71)
// 3c20  304b      jr      nc,#3c6d        ; (75)
// 3c22  104c      djnz    #3c70           ; (76)
// 3c24  104d      djnz    #3c73           ; (77)
// 3c26  104e      djnz    #3c76           ; (78)
// 3c28  1067      djnz    #3c91           ; (103)
// 3c2a  50        ld      d,b
// 3c2b  3047      jr      nc,#3c74        ; (71)
// 3c2d  3067      jr      nc,#3c96        ; (103)
// 3c2f  50        ld      d,b
// 3c30  3047      jr      nc,#3c79        ; (71)
// 3c32  3067      jr      nc,#3c9b        ; (103)
// 3c34  50        ld      d,b
// 3c35  3047      jr      nc,#3c7e        ; (71)
// 3c37  304b      jr      nc,#3c84        ; (75)
// 3c39  104c      djnz    #3c87           ; (76)
// 3c3b  104d      djnz    #3c8a           ; (77)
// 3c3d  104e      djnz    #3c8d           ; (78)
// 3c3f  1077      djnz    #3cb8           ; (119)
// 3c41  204e      jr      nz,#3c91        ; (78)
// 3c43  104d      djnz    #3c92           ; (77)
// 3c45  104c      djnz    #3c93           ; (76)
// 3c47  104a      djnz    #3c93           ; (74)
// 3c49  1047      djnz    #3c92           ; (71)
// 3c4b  1046      djnz    #3c93           ; (70)
// 3c4d  1065      djnz    #3cb4           ; (101)
// 3c4f  3066      jr      nc,#3cb7        ; (102)
// 3c51  3067      jr      nc,#3cba        ; (103)
// 3c53  40        ld      b,b
// 3c54  70        ld      (hl),b
// 3c55  f0        ret     p
// 
// 3c56  fb        ei      
// 3c57  3b        dec     sp
// 3c58  f1        pop     af
// 3c59  00        nop     
// 3c5a  f202f3    jp      p,#f302
// 3c5d  0f        rrca    
// 3c5e  f40042    call    p,#4200
"POPIPFPOI"
// 3c6a  70        ld      (hl),b
// 3c6b  66        ld      h,(hl)
// 3c6c  70        ld      (hl),b
"CPOPJPGPOJ"
// 3c77  70        ld      (hl),b
// 3c78  67        ld      h,a
// 3c79  70        ld      (hl),b
"BPNPIPFPNI"
// 3c84  70        ld      (hl),b
// 3c85  66        ld      h,(hl)
// 3c86  70        ld      (hl),b
"EFGPGHIPIJKP"
// 3c93  6e        ld      l,(hl)
// 3c94  ff        rst     #38
// 3c95  f1        pop     af
// 3c96  01f201    ld      bc,#01f2
// 3c99  f3        di      
// 3c9a  0f        rrca    
// 3c9b  f40026    call    p,#2600
// 3c9e  67        ld      h,a
// 3c9f  2667      ld      h,#67
// 3ca1  2667      ld      h,#67
// 3ca3  23        inc     hl
// 3ca4  44        ld      b,h
// 3ca5  42        ld      b,d
// 3ca6  47        ld      b,a
// 3ca7  3067      jr      nc,#3d10        ; (103)
// 3ca9  2a8b70    ld      hl,(#708b)
// 3cac  2667      ld      h,#67
// 3cae  2667      ld      h,#67
// 3cb0  2667      ld      h,#67
// 3cb2  23        inc     hl
// 3cb3  44        ld      b,h
// 3cb4  42        ld      b,d
// 3cb5  47        ld      b,a
// 3cb6  3067      jr      nc,#3d1f        ; (103)
// 3cb8  23        inc     hl
// 3cb9  84        add     a,h
// 3cba  70        ld      (hl),b
// 3cbb  2667      ld      h,#67
// 3cbd  2667      ld      h,#67
// 3cbf  2667      ld      h,#67
// 3cc1  23        inc     hl
// 3cc2  44        ld      b,h
// 3cc3  42        ld      b,d
// 3cc4  47        ld      b,a
// 3cc5  3067      jr      nc,#3d2e        ; (103)
// 3cc7  29        add     hl,hl
// 3cc8  6a        ld      l,d
// 3cc9  2b        dec     hl
// 3cca  6c        ld      l,h
// 3ccb  302c      jr      nc,#3cf9        ; (44)
// 3ccd  6d        ld      l,l
// 3cce  40        ld      b,b
// 3ccf  2b        dec     hl
// 3cd0  6c        ld      l,h
// 3cd1  29        add     hl,hl
// 3cd2  6a        ld      l,d
// 3cd3  67        ld      h,a
// 3cd4  2029      jr      nz,#3cff        ; (41)
// 3cd6  6a        ld      l,d
// 3cd7  40        ld      b,b
// 3cd8  2687      ld      h,#87
// 3cda  70        ld      (hl),b
// 3cdb  f0        ret     p
// 
// 3cdc  9d        sbc     a,l
// 3cdd  3c        inc     a
// 3cde  00        nop     
// ........
// 3cff  00        nop     
// 
// 	;; 36a5 Table Entry a
// 3d00  96        sub     (hl)		
// 3d01  03        inc     bc
// 3d02  42        ld      b,d
// 3d03  4f        ld      c,a
// 3d04  4e        ld      c,(hl)
// 3d05  55        ld      d,l
// 3d06  53        ld      d,e
// 3d07  40        ld      b,b
// 3d08  50        ld      d,b
// 3d09  41        ld      b,c
// 3d0a  43        ld      b,e
// 3d0b  3b        dec     sp
// 3d0c  4d        ld      c,l
// 3d0d  41        ld      b,c
// 3d0e  4e        ld      c,(hl)
// 3d0f  40        ld      b,b
// 3d10  46        ld      b,(hl)
// 3d11  4f        ld      c,a
// 3d12  52        ld      d,d
// 3d13  40        ld      b,b
// 3d14  40        ld      b,b
// 3d15  40        ld      b,b
// 3d16  3030      jr      nc,#3d48        ; (48)
// 3d18  3040      jr      nc,#3d5a        ; (64)
// 3d1a  5d        ld      e,l
// 3d1b  5e        ld      e,(hl)
// 3d1c  5f        ld      e,a
// 3d1d  2f        cpl     
// 3d1e  8e        adc     a,(hl)
// 3d1f  2f        cpl     
// 3d20  80        add     a,b
// 
// 	;; 36a5 Table Entry b
// 3d21  3a035c    ld      a,(#5c03)
// 3d24  40        ld      b,b
// 3d25  313938    ld      sp,#3839
// 3d28  3040      jr      nc,#3d6a        ; (64)
// 3d2a  4d        ld      c,l
// 3d2b  49        ld      c,c
// 3d2c  44        ld      b,h
// 3d2d  57        ld      d,a
// 3d2e  41        ld      b,c
// 3d2f  59        ld      e,c
// 3d30  40        ld      b,b
// 3d31  4d        ld      c,l
// 3d32  46        ld      b,(hl)
// 3d33  47        ld      b,a
// 3d34  25        dec     h
// 3d35  43        ld      b,e
// 3d36  4f        ld      c,a
// 3d37  25        dec     h
// 3d38  2f        cpl     
// 3d39  83        add     a,e
// 3d3a  2f        cpl     
// 3d3b  80        add     a,b
// 
// 	;; 36a5 Table Entry 13
// 3d3c  3d        dec     a
// 3d3d  03        inc     bc
// 3d3e  5c        ld      e,h
// 3d3f  40        ld      b,b
// 3d40  313938    ld      sp,#3839
// 3d43  3040      jr      nc,#3d85        ; (64)
// 3d45  4d        ld      c,l
// 3d46  49        ld      c,c
// 3d47  44        ld      b,h
// 3d48  57        ld      d,a
// 3d49  41        ld      b,c
// 3d4a  59        ld      e,c
// 3d4b  40        ld      b,b
// 3d4c  4d        ld      c,l
// 3d4d  46        ld      b,(hl)
// 3d4e  47        ld      b,a
// 3d4f  25        dec     h
// 3d50  43        ld      b,e
// 3d51  4f        ld      c,a
// 3d52  25        dec     h
// 3d53  2f        cpl     
// 3d54  83        add     a,e
// 3d55  2f        cpl     
// 3d56  80        add     a,b
// 
// 	;; 36a5 Table Entry 14
// 3d57  c5        push    bc
// 3d58  02        ld      (bc),a
// 3d59  3b        dec     sp
// 3d5a  53        ld      d,e
// 3d5b  48        ld      c,b
// 3d5c  41        ld      b,c
// 3d5d  44        ld      b,h
// 3d5e  4f        ld      c,a
// 3d5f  57        ld      d,a
// 3d60  40        ld      b,b
// 3d61  40        ld      b,b
// 3d62  40        ld      b,b
// 3d63  2f        cpl     
// 3d64  81        add     a,c
// 3d65  2f        cpl     
// 3d66  80        add     a,b
// 
// 	;; 36a5 Table Entry d
// 3d67  65        ld      h,l
// 3d68  012642    ld      bc,#4226
// 3d6b  4c        ld      c,h
// 3d6c  49        ld      c,c
// 3d6d  4e        ld      c,(hl)
// 3d6e  4b        ld      c,e
// 3d6f  59        ld      e,c
// 3d70  2640      ld      h,#40
// 3d72  2f        cpl     
// 3d73  81        add     a,c
// 3d74  2f        cpl     
// 3d75  80        add     a,b
// 
// 	;; 36a5 Table Entry 16
// 3d76  c8        ret     z
// 3d77  02        ld      (bc),a
// 3d78  3b        dec     sp
// 3d79  53        ld      d,e
// 3d7a  50        ld      d,b
// 3d7b  45        ld      b,l
// 3d7c  45        ld      b,l
// 3d7d  44        ld      b,h
// 3d7e  59        ld      e,c
// 3d7f  40        ld      b,b
// 3d80  40        ld      b,b
// 3d81  40        ld      b,b
// 3d82  2f        cpl     
// 3d83  83        add     a,e
// 3d84  2f        cpl     
// 3d85  80        add     a,b
// 
// 	;; 36a5 Table Entry f
// 3d86  68        ld      l,b
// 3d87  012650    ld      bc,#5026
// 3d8a  49        ld      c,c
// 3d8b  4e        ld      c,(hl)
// 3d8c  4b        ld      c,e
// 3d8d  59        ld      e,c
// 3d8e  2640      ld      h,#40
// 3d90  40        ld      b,b
// 3d91  2f        cpl     
// 3d92  83        add     a,e
// 3d93  2f        cpl     
// 3d94  80        add     a,b
// 
// 	;; 36a5 Table Entry 33
// 3d95  cb02      rlc     d
// 3d97  3b        dec     sp
// 3d98  42        ld      b,d
// 3d99  41        ld      b,c
// 3d9a  53        ld      d,e
// 3d9b  48        ld      c,b
// 3d9c  46        ld      b,(hl)
// 3d9d  55        ld      d,l
// 3d9e  4c        ld      c,h
// 3d9f  40        ld      b,b
// 3da0  40        ld      b,b
// 3da1  2f        cpl     
// 3da2  85        add     a,l
// 3da3  2f        cpl     
// 3da4  80        add     a,b
// 
// 	;; 36a5 Table Entry 2f
// 3da5  6b        ld      l,e
// 3da6  012649    ld      bc,#4926
// 3da9  4e        ld      c,(hl)
// 3daa  4b        ld      c,e
// 3dab  59        ld      e,c
// 3dac  2640      ld      h,#40
// 3dae  40        ld      b,b
// 3daf  40        ld      b,b
// 3db0  2f        cpl     
// 3db1  85        add     a,l
// 3db2  2f        cpl     
// 3db3  80        add     a,b
// 
// 	;; 36a5 Table Entry 35
// 3db4  ce02      adc     a,#02
// 3db6  3b        dec     sp
// 3db7  50        ld      d,b
// 3db8  4f        ld      c,a
// 3db9  4b        ld      c,e
// 3dba  45        ld      b,l
// 3dbb  59        ld      e,c
// 3dbc  40        ld      b,b
// 3dbd  40        ld      b,b
// 3dbe  40        ld      b,b
// 3dbf  40        ld      b,b
// 3dc0  2f        cpl     
// 3dc1  87        add     a,a
// 3dc2  2f        cpl     
// 3dc3  80        add     a,b
// 
// 	;; 36a5 Table Entry 31
// 3dc4  6e        ld      l,(hl)
// 3dc5  0126
"CLYDE"
// 3dcc  2640      ld      h,#40
// 3dce  40        ld      b,b
// 3dcf  2f        cpl     
// 3dd0  87        add     a,a
// 3dd1  2f        cpl     
// 3dd2  80        add     a,b
// 
// 	;; 36a5 Table Entry 15
// 3dd3  c5        push    bc
// 3dd4  02        ld      (bc),a
// 3dd5  3b        dec     sp
"AAAAAAAA"
// 3dde  3b        dec     sp
// 3ddf  2f        cpl     
// 3de0  81        add     a,c
// 3de1  2f        cpl     
// 3de2  80        add     a,b
// 
// 	;; 36a5 Table Entry e
// 3de3  65        ld      h,l
// 3de4  0126
"BBBBBBB"
// 3ded  262f      ld      h,#2f
// 3def  81        add     a,c
// 3df0  2f        cpl     
// 3df1  80        add     a,b
// 
// 	;; 36a5 Table Entry 17
// 3df2  c8        ret     z
// 3df3  02        ld      (bc),a
// 3df4  3b        dec     sp
"CCCCCCCC"
// 3dfd  3b        dec     sp
// 3dfe  2f        cpl     
// 3dff  83        add     a,e
// 3e00  2f        cpl     
// 3e01  80        add     a,b
// 
// 	;; 36a5 Table Entry 10
// 3e02  68        ld      l,b
// 3e03  012644    ld      bc,#4426
"DDDDDD"
// 3e0c  262f      ld      h,#2f
// 3e0e  83        add     a,e
// 3e0f  2f        cpl     
// 3e10  80        add     a,b
// 
// 	;; 36a5 Table Entry 34
// 3e11  cb02      rlc     d
// 3e13  3b        dec     sp
"EEEEEEEE"
// 3e1c  3b        dec     sp
// 3e1d  2f        cpl     
// 3e1e  85        add     a,l
// 3e1f  2f        cpl     
// 3e20  80        add     a,b
// 
// 	;; 36a5 Table Entry 30
// 3e21  6b        ld      l,e
// 3e22  012646    ld      bc,#4626
"FFFFFF"
// 3e2b  262f      ld      h,#2f
// 3e2d  85        add     a,l
// 3e2e  2f        cpl     
// 3e2f  80        add     a,b
// 
// 	;; 36a5 Table Entry 36
// 3e30  ce02      adc     a,#02
// 3e32  3b        dec     sp
"GGGGGGGG"
// 3e3b  3b        dec     sp
// 3e3c  2f        cpl     
// 3e3d  87        add     a,a
// 3e3e  2f        cpl     
// 3e3f  80        add     a,b
// 
// 	;; 36a5 Table Entry 32
// 3e40  6e        ld      l,(hl)
// 3e41  0126
"HHHHHHH"
// 3e4a  262f      ld      h,#2f
// 3e4c  87        add     a,a
// 3e4d  2f        cpl     
// 3e4e  80        add     a,b
// 
// 	;; 36a5 Table Entry 29
// 3e4f  0c        inc     c
// 3e50  03        inc     bc
"PAC-MAN"
// 3e58  2f        cpl     
// 3e59  8f        adc     a,a
// 3e5a  2f        cpl     
// 3e5b  80        add     a,b

// 3e5c  00        nop     
// .......
// 3ff9  00        nop     
// 3ffa  0030				; Interrupt Vector 3000 
// 3ffc  8d00				; Interrupt Vector 008d 
// 
// 3ffe  75        ld      (hl),l		; Checksum data 
// 3fff  73        ld      (hl),e
// 
// Disassembled 9289 instructions.
