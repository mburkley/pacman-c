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
pacman.6j

# $(ROMS): %.h: %
# 	@xxd -i $< > $@

pacman: $(SRCS)
	$(CC) -ggdb3 -Wall $^ -o $@ $(LIBS)
