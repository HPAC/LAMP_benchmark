SRC	     := src
OBJ      := obj

CXX      := g++
LINKER   := $(CXX)

ARMA_INC := -I${LOCAL_INSTALL_DIR}/include -I../benchmarker
MKL_INC  := -m64 -I${MKLROOT}/include
INC      := -Iinclude $(ARMA_INC) $(MKL_INC)
CXXFLAGS := -O3 -march=native -std=c++14 -Wall -fopenmp $(INC)

ARMA_LD  := -L${LOCAL_INSTALL_DIR}/lib -larmadillo
MKL_LD	 := -L${MKLROOT}/lib/intel64 -L${MKLROOT}/../lib/intel64 -Wall -Wl,--no-as-needed -lmkl_intel_lp64 -lmkl_intel_thread -lmkl_core -liomp5\
			      -lpthread -lm -ldl
LDFLAGS  := $(ARMA_LD) $(MKL_LD)

ARMA_DEFS := -DARMA_NO_DEBUG\
 			 -DARMA_OPTIMISE_SOLVE_SYMPD\
			 -DARMA_OPTIMISE_SOLVE_BAND\
			 -DARMA_USE_LAPACK -DARMA_USE_BLAS\
			 -DARMA_DONT_USE_WRAPPER

DEFS      := $(ARMA_DEFS)

SOURCES   := $(wildcard $(SRC)/*.cpp)
OBJECTS   := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SOURCES))

MYAPP     := bench_armadillo

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CXX) $(CXXFLAGS) $(DEFS) -c $< -o $@

$(MYAPP): $(OBJECTS)
	$(LINKER) $(OBJECTS) $(LDFLAGS) -o $(MYAPP)

clean:
	rm -f $(OBJECTS) $(MYAPP)
