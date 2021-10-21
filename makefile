# ### A simple basic-purpose makefile ###
# 1) Change the exec name.

# Executable
EXEC = OCP

# Binary
BIN = ./bin/$(EXEC)

# Source files
SRC = $(wildcard ./src/*.c)

# Objects
OBJ = $(subst src,obj,$(subst .c,.o,$(SRC)))

# Compiler
CC = cc

# Compiler flags
CFLAGS = -lm -Wall
CCFLAGS = $(CFLAGS)


# Compiling and linking
#
all: objFolder binFolder $(BIN)
.PHONY: all

$(BIN): $(OBJ)
	@ echo 'Building binary $@ using $(CC)...'
	@ $(CC) $(OBJ) -o $@ $(CCFLAGS)
	@ echo 'Finished building $@.'

./obj/%.o: ./src/%.c
	@ echo 'Building $@ from $<...'
	@ $(CC)  -c $< -o $@ $(CCFLAGS)
	@ echo 'ok'

objFolder:
	@ if [ ! -d ./obj ]; then \
		echo 'Creating objects folder...' ; \
		mkdir -p obj ; \
		echo 'ok'; \
	fi

binFolder:
	@ if [ ! -d ./bin ]; then \
		echo 'Creating binary folder...' ; \
		mkdir -p bin ; \
		echo 'ok'; \
	fi

clean:
	@ echo 'Cleanning up...'
	@ rm -rf ./obj/* ./obj
	@ rm -rf ./bin/* ./bin
	@ echo 'ok'
.PHONY: clean
