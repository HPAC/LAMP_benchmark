#!/bin/bash

source ${HOME}/.zshrc.lamp

export LAMP_LOG_DIR=${LAMP_EXPERIMENTS}/scripts/cluster/log
export THR=24

sbatch -J C      -o ${LAMP_LOG_DIR}/c.log         -t 09:00:00 -p ih -A aices2 --nodelist=linuxihdc072 --exclusive ${LAMP_EXPERIMENTS}/scripts/cluster/c.sh $THR
sbatch -J CppArm -o ${LAMP_LOG_DIR}/cpp_arma.log  -t 09:00:00 -p ih -A aices2 --nodelist=linuxihdc072 --exclusive ${LAMP_EXPERIMENTS}/scripts/cluster/cpp_arma.sh $THR
sbatch -J CppEig -o ${LAMP_LOG_DIR}/cpp_eigen.log -t 09:00:00 -p ih -A aices2 --nodelist=linuxihdc072 --exclusive ${LAMP_EXPERIMENTS}/scripts/cluster/cpp_eig.sh $THR
sbatch -J Julia  -o ${LAMP_LOG_DIR}/julia.log     -t 09:00:00 -p ih -A aices2 --nodelist=linuxihdc072 --exclusive ${LAMP_EXPERIMENTS}/scripts/cluster/julia.sh $THR
sbatch -J Matlab -o ${LAMP_LOG_DIR}/matlab.log    -t 09:00:00 -p ih -A aices2 --nodelist=linuxihdc072 --exclusive ${LAMP_EXPERIMENTS}/scripts/cluster/matlab.sh $THR
sbatch -J Octave -o ${LAMP_LOG_DIR}/octave.log    -t 09:00:00 -p ih -A aices2 --nodelist=linuxihdc072 --exclusive ${LAMP_EXPERIMENTS}/scripts/cluster/octave.sh $THR
sbatch -J Python -o ${LAMP_LOG_DIR}/python.log    -t 09:00:00 -p ih -A aices2 --nodelist=linuxihdc072 --exclusive ${LAMP_EXPERIMENTS}/scripts/cluster/python.sh $THR
sbatch -J R      -o ${LAMP_LOG_DIR}/R.log         -t 09:00:00 -p ih -A aices2 --nodelist=linuxihdc072 --exclusive ${LAMP_EXPERIMENTS}/scripts/cluster/r.sh $THR
