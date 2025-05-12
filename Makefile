all: pacman

OBJECTS=\
pacman.o \
cpu.o \
video.o \
sound.o \
kbd.o

LIBS=\
-l m\
-l glut\
-l GL\
-lpulse-simple\
-lpulse

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
82s126.4a \
82s126.1m \
82s126.3m

FILES=$(patsubst %,rom/%,$(ROMS))
HDRS=$(patsubst %,%.h,$(ROMS))

# Header files containing ROM data
# ROM_HDRS = (patsubst roms/%, %.h, $(ROMS))

# $(ROM_HDRS): %: %
# 	@xxd -i $< > $@

$(HDRS) : %:
	xxd -i rom/$(subst .h,,$@) > $@

CFLAGS=-Wall -ggdb3 -Wincompatible-pointer-types

pacman: $(OBJECTS) harness.o
	@echo "\t[LD] $@..."
	@$(CC) -ggdb3 -Wall -o $@ $^ $(LIBS)

test: $(OBJECTS) test.o
	@echo "\t[LD] $@..."
	@$(CC) -ggdb3 -Wall -o $@ $^ $(LIBS)

%.o: %.c $(HDRS)
	@echo "\t[CC] $<..."
	@$(CC) -c $(CFLAGS) $< -o $@
