all: pacman

SRCS=\
pacman.c \
cpu.c \
harness.c \
video.c \
kbd.c

LIBS=\
-l m\
-l glut\
-l GL

ROMS=\
pacman.5e \
pacman.5f \
pacman.6e \
pacman.6f \
pacman.6h \
pacman.6j \
namcopac.6e \
namcopac.6f \
namcopac.6h \
namcopac.6j \
82s123.7f \
82s126.4a

FILES=$(patsubst %,rom/%,$(ROMS))
HDRS=$(patsubst %,%.h,$(ROMS))

# Header files containing ROM data
# ROM_HDRS = (patsubst roms/%, %.h, $(ROMS))

# $(ROM_HDRS): %: %
# 	@xxd -i $< > $@

$(HDRS) : %:
	xxd -i rom/$(subst .h,,$@) > $@

pacman: $(SRCS) $(HDRS)
	$(CC) -ggdb3 -Wall $^ -o $@ $(LIBS)
