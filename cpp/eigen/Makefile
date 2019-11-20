SRC				 := src
OBJ 			 := obj

EIGEN_INC  := -I${HPC_DIR}/lib/include/eigen3
MKL_INC 	 := -m64 -I${MKLROOT}/include
INC        := -Ilib $(EIGEN_INC) $(MKL_INC)

EIGEN      := -L${HPC_DIR}/lib/lib
MKL_LD		 := -L${MKLROOT}/lib/intel64 -Wall -Wl,--no-as-needed -lmkl_intel_lp64 -lmkl_sequential -lmkl_core
LDFLAGS    := $(EIGEN) $(MKL_LD) -lm -ldl -lpthread

CC 				 := g++
LINKER     := $(CC)
EIGEN_DEFS := -DEIGEN_USE_BLAS \
 							-DEIGEN_USE_LAPACK \
						 	-DEIGEN_USE_MKL_ALL \
							-DEIGEN_USE_MKL \
							-DEIGEN_MAX_CPP_VER=11 \
							-DEIGEN_NO_DEBUG \
							-DEIGEN_DONT_PARALLELIZE \
							-DEIGEN_NO_CUDA
DEFS  		 := $(EIGEN_DEFS) -DLAMP_REPS=$(LAMP_REPS) -DLAMP_OUTPUT_DIR=\"results/\" -DLAMP_L3_CACHE_SIZE=$(LAMP_L3_CACHE_SIZE)
CFLAGS     := -O2 -march=native -std=c++14 -Wall $(INC) \


SOURCES 	 := $(wildcard $(SRC)/*.cpp)
OBJECTS 	 := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SOURCES))

MYAPP  		 := bench_eigen

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) $(CFLAGS) $(DEFS) -c $< -o $@

$(MYAPP): $(OBJECTS)
	$(LINKER) $(OBJECTS) $(LDFLAGS) -o $(MYAPP)

clean:
	rm -f $(OBJECTS) $(MYAPP)
