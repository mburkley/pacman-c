all: pacmanc

SRCS=\
ctrans.c \
cpu.c \
harness.c \
video.c \
kbd.c

LIBS=\
-l glut\
-l GL

ROMS=\
pacman.5e \
pacman.5f \
pacman.6e \
pacman.6f \
pacman.6h \
pacman.6j

# $(ROMS): %.h: %
# 	@xxd -i $< > $@

pacmanc: $(SRCS)
	$(CC) -ggdb3 $^ -o $@ $(LIBS)
