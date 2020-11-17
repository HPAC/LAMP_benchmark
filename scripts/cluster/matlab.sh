#!/bin/bash

source ${HOME}/.zshrc.lamp
export LAMP_MATLAB_DIR="${LAMP_EXPERIMENTS}/matlab"
cd $LAMP_MATLAB_DIR

echo "-----------------------------"
echo "$1 Threads"
echo "-----------------------------"
export MKL_NUM_THREADS=$1
export OMP_NUM_THREADS=$1

module load MISC
module load matlab/2019a

export MATLAB_LOG_DIR=$LAMP_LOG_DIR
export MATLABPATH=$LAMP_MATLAB_DIR

# it is not possible to run runner.m directly here because of how importing in Matlab works.
if [[ "$1" == 1 ]] ; then
  export THREADING=-singleCompThread
else
  export THREADING=
fi
echo "Threading: ${THREADING}"
${MALTAB} ${THREADING} -nodisplay -nodesktop -nosplash -logfile /dev/null <<EOF
main;
quit();
EOF
