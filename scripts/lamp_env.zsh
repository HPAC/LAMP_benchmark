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

export LAMP_INSTALL_DIR=${HOME}/.lamp
export PATH=${LAMP_INSTALL_DIR}/bin:${PATH}
export LD_LIBRARY_PATH=${LAMP_INSTALL_DIR}:${LD_LIBRARY_PATH}

#######################################################################
# LAMP specific variables
export LAMP_EXPERIMENTS=${HOME}/projects/LAMP_benchmark
export LAMP_OUTPUT_DIR="${LAMP_EXPERIMENTS}/results/"
export LAMP_L3_CACHE_SIZE="7500000"
export LAMP_REPS=50
export LAMP_N=3000
#export LAMP_N=6000
export LAMP_SP_N=1000000
export LAMP_SP_DENSITY=0.000001

#######################################################################
# Setup Languages

# Octave
export OCTAVE="${LAMP_INSTALL_DIR}/bin/octave-cli"
alias octave="${OCTAVE}"

# Julia
export JULIA_DIR=${LAMP_INSTALL_DIR}/julia
export JULIA=${JULIA_DIR}/julia
alias julia="${JULIA}"

# R
export R_DIR=${LAMP_INSTALL_DIR}/lib64/R
export R_SCRIPT=${R_DIR}/bin/Rscript
export R_PACK=${R_DIR}/packages
export R=${R_DIR}/bin/R
alias R="${R}"

# Python
export PYTHON=python3
alias python="${PYTHON}"

# Matlab
export MATLAB="/usr/local_rwth/sw/MATLAB/matlab_2020a/bin/matlab"
alias matlab="${MATLAB}"

#######################################################################
# Navigation
alias lamp="cd ${LAMP_EXPERIMENTS}"
alias lampi="cd ${LOCAL_INSTALL_DIR}"
