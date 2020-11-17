export PS1="LAMP"${PS1}

#######################################################################
# Set up environment for RWTH cluster
module switch intel gcc/8
module load LIBRARIES
module load intelmkl/2020
module load cmake/3.16.4

#######################################################################
# Environment variables
export CC=gcc
export CXX=g++
export CFLAGS="-O3 -march=native -fopenmp -m64 -I${MKLROOT}/include"
export CXXFLAGS="-O3 -march=native -fopenmp -m64 -I${MKLROOT}/include"
export CPPFLAGS="-O3 -march=native -fopenmp -m64 -I${MKLROOT}/include"

export LOCAL_INSTALL_DIR=${HOME}/.lamp
export PATH=${LOCAL_INSTALL_DIR}/bin:${PATH}
export LD_LIBRARY_PATH=${LOCAL_INSTALL_DIR}:${LD_LIBRARY_PATH}

#######################################################################
# LAMP specific variables
export LAMP_EXPERIMENTS=${HOME}/projects/LAMP_benchmark
export LAMP_OUTPUT_DIR="${LAMP_EXPERIMENTS}/results/"
export LAMP_L3_CACHE_SIZE="7500000"
export LAMP_REPS=50
export LAMP_N=3000
#export LAMP_N=6000

#######################################################################
# Setup Languages

# Octave
export OCTAVE="${LOCAL_INSTALL_DIR}/bin/octave-cli"
alias octave="${OCTAVE}"

# Julia
export JULIA_DIR=${LOCAL_INSTALL_DIR}/julia
export JULIA=${JULIA_DIR}/julia
alias julia="${JULIA}"

# R
export R_SCRIPT=${LOCAL_INSTALL_DIR}/lib64/R/bin/Rscript
export R_PACK=${LOCAL_INSTALL_DIR}/lib64/R/packages
export R=${LOCAL_INSTALL_DIR}/lib64/R/bin/R
alias R="${R}"

# Python
export MKL_PYTHON=python3
alias python="${MKL_PYTHON}"

# Matlab
export MATLAB="/usr/local_rwth/sw/MATLAB/matlab_2020a/bin/matlab"
alias matlab="${MATLAB}"

#######################################################################
# Navigation 
alias lamp="cd ${LAMP_EXPERIMENTS}"
alias lampi="cd ${LOCAL_INSTALL_DIR}"
