SRC       := src
OBJ       := obj

CXX       := g++
LINKER    := $(CXX)

EIGEN_INC := -I${LOCAL_INSTALL_DIR}/include/eigen3
MKL_INC   := -m64 -I${MKLROOT}/include
INC       := -Ilib $(EIGEN_INC) $(MKL_INC)
CXXFLAGS  := -O3 -march=native -std=c++14 -Wall -fopenmp $(INC)

EIGEN_LD  := -L${LOCAL_INSTALL_DIR}/lib
MKL_LD	  := -L${MKLROOT}/lib/intel64 -L${MKLROOT}/../lib/intel64 -Wall -Wl,--no-as-needed -lmkl_intel_lp64 -lmkl_intel_thread -lmkl_core -liomp5\
			 -lpthread -lm -ldl
LDFLAGS   := $(EIGEN_LD) $(MKL_LD)

EIGEN_DEFS := -DEIGEN_USE_BLAS \
 			  -DEIGEN_USE_LAPACK \
			  -DEIGEN_USE_MKL_ALL \
			  -DEIGEN_USE_MKL \
			  -DEIGEN_MAX_CPP_VER=11 \
			  -DEIGEN_NO_DEBUG

DEFS       := $(EIGEN_DEFS) -DLAMP_REPS=$(LAMP_REPS) -DLAMP_L3_CACHE_SIZE=$(LAMP_L3_CACHE_SIZE)

SOURCES   := $(wildcard $(SRC)/*.cpp)
OBJECTS   := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SOURCES))

MYAPP     := bench_eigen

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CXX) $(CXXFLAGS) $(DEFS) -c $< -o $@

$(MYAPP): $(OBJECTS)
	$(LINKER) $(OBJECTS) $(LDFLAGS) -o $(MYAPP)

clean:
	rm -f $(OBJECTS) $(MYAPP)
