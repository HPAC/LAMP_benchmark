#!/bin/bash

source ${HOME}/.zshrc.lamp
cd ${LAMP_EXPERIMENTS}/c

echo "-----------------------------"
echo "$1 Threads"
echo "-----------------------------"
export MKL_NUM_THREADS=$1
export OMP_NUM_THREADS=$1
#export GOMP_CPU_AFFINITY=$2
export KMP_AFFINITY=compact,verbose
export LD_LIBRARY_PATH="${MKLROOT}/../lib/intel64:$LD_LIBRARY_PATH"  # Runtime cannot find libiomp5.

export LAMP_C_OUTPUT_DIR=${LAMP_OUTPUT_DIR}/c_${OMP_NUM_THREADS}.txt

make clean
make all -j 24

echo "algorithm;m;k;n;C;cs_time"                    > ${LAMP_C_OUTPUT_DIR}
export LAMP_m=3000
export LAMP_k=550
export LAMP_n=3000
./bin/gemm.x       $LAMP_m $LAMP_k $LAMP_n          >> ${LAMP_C_OUTPUT_DIR}
./bin/gemm.x       $LAMP_n $LAMP_n $LAMP_n large    >> ${LAMP_C_OUTPUT_DIR}
./bin/gemm_noup.x  $LAMP_m $LAMP_k $LAMP_n          >> ${LAMP_C_OUTPUT_DIR}

./bin/syrk.x       $LAMP_n $LAMP_k                  >> ${LAMP_C_OUTPUT_DIR}
./bin/syrk_noup.x  $LAMP_n $LAMP_k                  >> ${LAMP_C_OUTPUT_DIR}

./bin/syr2k.x      $LAMP_n $LAMP_k                  >> ${LAMP_C_OUTPUT_DIR}
./bin/syr2k_noup.x $LAMP_n $LAMP_k                  >> ${LAMP_C_OUTPUT_DIR}

./bin/trmm.x       $LAMP_m $LAMP_n                  >> ${LAMP_C_OUTPUT_DIR}
./bin/diagmm.x     $LAMP_n                          >> ${LAMP_C_OUTPUT_DIR}

./bin/subexpr_nai.x $LAMP_m $LAMP_k                 >> ${LAMP_C_OUTPUT_DIR}
./bin/subexpr_rec.x $LAMP_m $LAMP_k                 >> ${LAMP_C_OUTPUT_DIR}

./bin/mc_mixed.x $LAMP_m $LAMP_k $LAMP_n            >> ${LAMP_C_OUTPUT_DIR}

export LAMP_tr_m=80
export LAMP_tr_k=80
export LAMP_tr_n=80
./bin/transposition.x $LAMP_tr_m $LAMP_tr_k $LAMP_tr_n >> ${LAMP_C_OUTPUT_DIR}

export LAMP_rhs_small=100
./bin/solve_naive.x       $LAMP_n $LAMP_rhs_small      >> ${LAMP_C_OUTPUT_DIR}
./bin/solve_recommended.x $LAMP_n $LAMP_rhs_small      >> ${LAMP_C_OUTPUT_DIR}

./bin/solve_recommended_spd.x $LAMP_n $LAMP_rhs_small  >> ${LAMP_C_OUTPUT_DIR}
./bin/solve_recommended_sym.x $LAMP_n $LAMP_rhs_small  >> ${LAMP_C_OUTPUT_DIR}
./bin/solve_recommended_tri.x $LAMP_n $LAMP_rhs_small  >> ${LAMP_C_OUTPUT_DIR}
./bin/solve_recommended_dia.x $LAMP_n $LAMP_rhs_small  >> ${LAMP_C_OUTPUT_DIR}

export LAMP_rhs_large=6000
./bin/solve_naive.x       $LAMP_n $LAMP_rhs_large large >> ${LAMP_C_OUTPUT_DIR}
./bin/solve_recommended.x $LAMP_n $LAMP_rhs_large large >> ${LAMP_C_OUTPUT_DIR}
