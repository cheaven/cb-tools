
#
#require KDIR var
#KDIR=
#

INCLUDES=-I${KDIR}/include -I.
CROSS_COMPILE=arm-linux-gnueabihf-
CC=${CROSS_COMPILE}gcc
ALL_BINARIES=cb-display-tool


binaries:${ALL_BINARIES}

cb-display-tool:
	${CC} ${INCLUDES} -o cb-display-tool cb-display-tool.c

all:binaries

clean:
	rm -rf *.o ${ALL_BINARIES}

