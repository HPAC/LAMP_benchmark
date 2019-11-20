SRC				 := src
OBJ 			 := obj

ARMA_INC   := -I${HPC_DIR}/lib/include
MKL_INC 	 := -m64 -I${MKLROOT}/include
INC        := -Ilib $(ARMA_INC) $(MKL_INC)

ARMADILLO  := -L$(HPC_DIR)/lib/lib
MKL_LD		 := -L${MKLROOT}/lib/intel64 -Wall -Wl,--no-as-needed -lmkl_intel_lp64 -lmkl_sequential -lmkl_core
LDFLAGS    := $(ARMADILLO) $(MKL_LD) -lm -ldl -lpthread -larmadillo

CC 				 := g++
LINKER     := $(CC)
ARMA_DEFS  := -DARMA_NO_DEBUG\
 							-DARMA_OPTIMISE_SOLVE_SYMPD\
							-DARMA_OPTIMISE_SOLVE_BAND\
							-DARMA_USE_LAPACK -DARMA_USE_BLAS\
							-DARMA_DONT_USE_WRAPPER
DEFS  		 := $(ARMA_DEFS) -DLAMP_REPS=$(LAMP_REPS) -DLAMP_OUTPUT_DIR=\"results/\" -DLAMP_L3_CACHE_SIZE=$(LAMP_L3_CACHE_SIZE)
CFLAGS     := -O2 -march=native -std=c++14 -Wall $(INC) \


SOURCES 	 := $(wildcard $(SRC)/*.cpp)
OBJECTS 	 := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SOURCES))

MYAPP  		 := bench_armadillo

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) $(CFLAGS) $(DEFS) -c $< -o $@

$(MYAPP): $(OBJECTS)
	$(LINKER) $(OBJECTS) $(LDFLAGS) -o $(MYAPP)

clean:
	rm -f $(OBJECTS) $(MYAPP)
