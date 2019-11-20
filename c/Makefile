SRC				 := src
OBJ 			 := obj
BIN        := bin

MKL_INC 	 := -m64 -I${MKLROOT}/include
INC        := -Isrc/timer $(MKL_INC)
MKL_LD		 := -L${MKLROOT}/lib/intel64 -Wall -Wl,--no-as-needed -lmkl_intel_lp64 -lmkl_sequential -lmkl_core

CC 				 := gcc
LINKER     := $(CC)
DEFS  		 := -DLAMP_REPS=$(LAMP_REPS) -DLAMP_L3_CACHE_SIZE=$(LAMP_L3_CACHE_SIZE)
CFLAGS     := -O3 -march=native -Wall $(INC)
LDFLAGS    := $(MKL_LD) -lm -ldl -lpthread

SOURCES 	 := $(wildcard $(SRC)/*.c)
BINARIES 	 := $(patsubst $(SRC)/%.c, $(BIN)/%.x, $(SOURCES))

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
