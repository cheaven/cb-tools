KDIR=/build/matson/Work/a20-cubieboard/linux-sunxi
INCLUDES=-I${KDIR}/include -I.
CROSS_COMPILE=arm-linux-gnueabihf-
CC=${CROSS_COMPILE}gcc


all:
	${CC} ${INCLUDES} -o cb-display-tool cb-display-tool.c

