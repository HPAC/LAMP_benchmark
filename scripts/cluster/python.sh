#!/bin/bash

source ${HOME}/.zshrc.lamp
cd ${LAMP_EXPERIMENTS}/python

echo "-----------------------------"
echo "$1 Threads"
echo "-----------------------------"
export MKL_NUM_THREADS=$1
export OMP_NUM_THREADS=$1
#export GOMP_CPU_AFFINITY=$2
#export KMP_AFFINITY=compact,verbose
export KMP_AFFINITY=verbose,granularity=core,proclist=[$2],explicit

module load DEVELOP
module load pythoni/3.6.2019

${MKL_PYTHON} main.py

