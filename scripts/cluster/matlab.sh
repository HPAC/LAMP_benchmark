#!/bin/bash

source ~/.zshrc.lamp

module load MISC
module load matlab/2019a

export MKL_NUM_THREADS=1
export OMP_NUM_THREADS=1

export LAMP_MATLAB_DIR="${LAMP_EXPERIMENTS}/matlab"

export MATLAB_LOG_DIR=$LAMP_LOG_DIR
export MATLABPATH=$LAMP_MATLAB_DIR

cd $LAMP_MATLAB_DIR

# it is not possible to run runner.m directly here because of how importing in Matlab works.
/usr/local_rwth/sw/MATLAB/matlab_2019a/bin/matlab -singleCompThread -nodisplay -nodesktop -nosplash -logfile /dev/null <<EOF
main;
quit();
EOF
