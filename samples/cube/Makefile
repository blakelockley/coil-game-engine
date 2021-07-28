# Usage:
# make        		# compile sample

CC = gcc
CFLAGS = -Wall -g
CLIBS = -lglfw3 -framework OpenGL -framework Cocoa -framework IOKit

ROOT_DIR = ../..

LIB = engine
LIB_DIR = ${ROOT_DIR}/build
LIB_FILE = ${LIB_DIR}/lib${LIB}.a

TARGET = cube.out

SRCS = ${wildcard *.c}
OBJS = ${SRCS:.c=.o}

.PHONY: ${LIB_FILE}

${TARGET}: ${SRCS} ${LIB_FILE}
	${CC} ${CFLAGS} ${SRCS} -o ${TARGET} -L${LIB_DIR} -l${LIB} -I${LIB_DIR} -I${ROOT_DIR}/includes ${CLIBS}

${LIB_FILE}:
	@(cd ${ROOT_DIR} && make)
	
.PHONY: clean
clean:
	rm ${TARGET}
