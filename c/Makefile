SRC     := src
OBJ     := obj
BIN     := bin

CC      := gcc
LINKER  := $(CC)

MKL_INC := -m64 -I${MKLROOT}/include
INC     := -Isrc/timer $(MKL_INC)
CFLAGS  := -O3 -march=native -Wall $(INC)

MKL_LD  := -L${MKLROOT}/lib/intel64 -Wall -Wl,--no-as-needed -lmkl_intel_lp64 -lmkl_intel_thread -lmkl_core -liomp5\
	         -lpthread -lm -ldl
LDFLAGS := $(MKL_LD)

DEFS    := -DLAMP_REPS=$(LAMP_REPS) -DLAMP_L3_CACHE_SIZE=$(LAMP_L3_CACHE_SIZE)

SOURCES  := $(wildcard $(SRC)/*.c)
BINARIES := $(patsubst $(SRC)/%.c, $(BIN)/%.x, $(SOURCES))

default: all
all: $(BINARIES)

$(OBJ)/%.o: $(SRC)/timer/%.c
	$(CC) $(CFLAGS) $(DEFS) -c $< -o $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $(DEFS) -c $< -o $@

$(BIN)/%.x: $(OBJ)/%.o $(OBJ)/timer.o
	$(LINKER) $< $(OBJ)/timer.o $(LDFLAGS) -o $@

clean:
	rm -f $(BIN)/* $(OBJ)/*
