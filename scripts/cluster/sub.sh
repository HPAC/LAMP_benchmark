#!/bin/bash

source ${HOME}/.zshrc.lamp

#export TOP="0,2,4,6,8,10,12,14,16,18,20,22,1,3,5,7,9,11,13,15,17,19,21,23"
#export TOP="0 2 4 6 8 10 12 14 16 18 20 22 1 3 5 7 9 11 13 15 17 19 21 23"
export LAMP_LOG_DIR=${LAMP_EXPERIMENTS}/scripts/cluster/log
export THR=24

#sbatch -J C      -o ${LAMP_LOG_DIR}/c.log         -t 02:00:00 -p ih -A aices2 --nodelist=linuxihdc072 --exclusive ${LAMP_EXPERIMENTS}/scripts/cluster/c.sh $THR $TOP
#sbatch -J CppArm -o ${LAMP_LOG_DIR}/cpp_arma.log  -t 02:00:00 -p ih -A aices2 --nodelist=linuxihdc072 --exclusive ${LAMP_EXPERIMENTS}/scripts/cluster/cpp_arma.sh $THR $TOP
sbatch -J CppEig -o ${LAMP_LOG_DIR}/cpp_eigen.log -t 02:00:00 -p ih -A aices2 --nodelist=linuxihdc072 --exclusive ${LAMP_EXPERIMENTS}/scripts/cluster/cpp_eig.sh $THR $TOP
#sbatch -J Julia  -o ${LAMP_LOG_DIR}/julia.log     -t 02:00:00 -p ih -A aices2 --nodelist=linuxihdc072 --exclusive ${LAMP_EXPERIMENTS}/scripts/cluster/julia.sh $THR $TOP
#sbatch -J Matlab -o ${LAMP_LOG_DIR}/matlab.log    -t 02:00:00 -p ih -A aices2 --nodelist=linuxihdc072 --exclusive ${LAMP_EXPERIMENTS}/scripts/cluster/matlab.sh $THR $TOP
#sbatch -J Octave -o ${LAMP_LOG_DIR}/octave.log    -t 02:00:00 -p ih -A aices2 --nodelist=linuxihdc072 --exclusive ${LAMP_EXPERIMENTS}/scripts/cluster/octave.sh $THR $TOP
#sbatch -J Python -o ${LAMP_LOG_DIR}/python.log    -t 02:00:00 -p ih -A aices2 --nodelist=linuxihdc072 --exclusive ${LAMP_EXPERIMENTS}/scripts/cluster/python.sh $THR $TOP
#sbatch -J R      -o ${LAMP_LOG_DIR}/R.log         -t 02:00:00 -p ih -A aices2 --nodelist=linuxihdc072 --exclusive ${LAMP_EXPERIMENTS}/scripts/cluster/r.sh $THR $TOP
