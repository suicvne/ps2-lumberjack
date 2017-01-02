# _____     ___ ____     ___ ____
#  ____|   |    ____|   |        | |____|
# |     ___|   |____ ___|    ____| |    \    PS2DEV Open Source Project.
#-----------------------------------------------------------------------
# Copyright 2001-2004, ps2dev - http://www.ps2dev.org
# Licenced under Academic Free License version 2.0
# Review ps2sdk README & LICENSE files for further details.
#

#EE_ERL = cpp-hello.erl
EE_BIN = cpp-hello.elf
EE_OBJS = main.o lumber/log.o lumber/branch.o lumber/lumber_game.o globals.o sprite.o input.o 
EE_INCS := -I$(PS2DEV)/gsKit/include
EE_LDFLAGS := -L$(PS2DEV)/gsKit/lib -L$(PS2DEV)/libjpg -L$(PS2SDK)/sbv/lib -L$(PS2DEV)/libcdvd/lib -L$(PS2SDK)/ports/lib -s
EE_LIBS = -lgskit_toolkit -lgskit -ldmakit -lcdvd -lmc -lhdd -lfileXio -lpatches -lpoweroff -ldebug -lpad -ltiff -lpng -lm -lz

all: $(EE_BIN)
	$(EE_STRIP) --strip-all $(EE_BIN)

clean:
	rm -f $(EE_ERL) $(EE_OBJS) erl-loader.elf libc.erl libkernel.erl

erl-loader.elf:
	cp $(PS2SDK)/ee/bin/erl-loader.elf $@

libc.erl:
	cp $(PS2SDK)/ee/lib/libc.erl $@

libkernel.erl:
	cp $(PS2SDK)/ee/lib/libkernel.erl $@

run: $(EE_ERL)
	ps2client execee host:erl-loader.elf $(EE_ERL)

reset:
	ps2client reset

include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.eeglobal
