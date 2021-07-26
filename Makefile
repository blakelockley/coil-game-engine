# Usage:
# make        		# compile engine library
# make clean  		# remove build object files
# make clean_all	# remove all build files and library

CC = cc
CFLAGS = -Wall -Iincludes

TARGET_LIB = build/libengine.a

SRCS = ${wildcard src/*.c}
OBJS = ${SRCS:src/%.c=build/%.o}

.PHONY: engine header
engine: build header ${TARGET_LIB}

${TARGET_LIB}: ${OBJS}
	ar -cr ${TARGET_LIB} ${OBJS}
 
header: src/engine.h build
	cp src/engine.h build/engine.h
	
build/%.o: src/%.c
	${CC} ${CFLAGS} -c $< -o $@

build:
	mkdir -p build

.PHONY: clean clean_all
clean_all:
	rm -fr build/

clean:
	rm -f ${OBJS}
