#!/bin/bash

source ${HOME}/.zshrc.lamp
export LAMP_OCTAVE_DIR="${LAMP_EXPERIMENTS}/octave"
cd $LAMP_OCTAVE_DIR

echo "-----------------------------"
echo "$1 Threads"
echo "-----------------------------"
export MKL_NUM_THREADS=$1
export OMP_NUM_THREADS=$1
#export GOMP_CPU_AFFINITY=$2
#export KMP_AFFINITY=compact,verbose
export KMP_AFFINITY=verbose,granularity=core,proclist=[$2],explicit

octave --version
octave main.m
