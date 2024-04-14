all: pacmanc


ROMS=\
pacman.5e \
pacman.5f \
pacman.6e \
pacman.6f \
pacman.6h \
pacman.6j

# $(ROMS): %.h: %
# 	@xxd -i $< > $@

pacmanc: ctrans.c cpu.c
	$(CC) -ggdb3 cpu.c ctrans.c -o pacmanc
