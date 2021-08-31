# # Usage:
# # make        		# compile engine library
# # make clean  		# remove build object files
# # make clean_all	# remove all build files and library

# CC = gcc
# CFLAGS = -Wall -Iincludes -g

# TARGET_LIB = build/libengine.a

# SRCS = ${wildcard src/*.c}
# OBJS = ${SRCS:src/%.c=build/%.o}

# .PHONY: engine header
# engine: build header ${TARGET_LIB}

# ${TARGET_LIB}: ${OBJS}
# 	ar -crs ${TARGET_LIB} ${OBJS}
 
# header: src/engine.h build
# 	cp src/engine.h build/engine.h


# Usage:
# make        		# compile sample
# make clean  		# remove build object files

CC = gcc
CFLAGS = -Wall -g -Iincludes
LFLAGS = -lglfw3 -framework OpenGL -framework Cocoa -framework IOKit

SRCEDIR = src/
OUTDIR = build/

NAME = main.out
TARGET = $(addprefix $(OUTDIR), $(NAME))

SRCS 	= ${wildcard src/*.c}
# OBJS  	= $(patsubst src/%.c, %.o, $(SRC))

$(TARGET): $(SRCS) $(OUTDIR)
	$(CC) $(CFLAGS) $(LFLAGS) $(SRCS) -o $(TARGET)

$(OUTDIR):
	mkdir -p $(OUTDIR)

.PHONY: clean
clean:
	rm -rf $(OUTDIR)

print-% :
	@echo $* = $($*)

