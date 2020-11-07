#!/bin/bash

source ${HOME}/.zshrc.lamp
cd ${LAMP_EXPERIMENTS}/c

echo "-----------------------------"
echo "$1 Threads"
echo "-----------------------------"
export MKL_NUM_THREADS=$1
export OMP_NUM_THREADS=$1
#export GOMP_CPU_AFFINITY=$2
#export KMP_AFFINITY=compact,verbose
export LD_LIBRARY_PATH="${MKLROOT}/../lib/intel64:$LD_LIBRARY_PATH"  # Runtime cannot find libiomp5.

export LAMP_C_OUTPUT_DIR=${LAMP_OUTPUT_DIR}/c_${OMP_NUM_THREADS}.txt

make clean
make all -j 24

echo "algorithm;m;k;n;C;cs_time"                    > ${LAMP_C_OUTPUT_DIR}
./bin/gemm.x       $LAMP_N $LAMP_N $LAMP_N          >> ${LAMP_C_OUTPUT_DIR}
./bin/gemm_noup.x  $LAMP_N $LAMP_N $LAMP_N          >> ${LAMP_C_OUTPUT_DIR}

./bin/syrk.x       $LAMP_N $LAMP_N                  >> ${LAMP_C_OUTPUT_DIR}
./bin/syrk_noup.x  $LAMP_N $LAMP_N                  >> ${LAMP_C_OUTPUT_DIR}

./bin/syr2k.x      $LAMP_N $LAMP_N                  >> ${LAMP_C_OUTPUT_DIR}
./bin/syr2k_noup.x $LAMP_N $LAMP_N                  >> ${LAMP_C_OUTPUT_DIR}

./bin/trmm.x       $LAMP_N $LAMP_N                  >> ${LAMP_C_OUTPUT_DIR}
./bin/diagmm.x     $LAMP_N                          >> ${LAMP_C_OUTPUT_DIR}

./bin/subexpr_nai.x $LAMP_N $LAMP_N                 >> ${LAMP_C_OUTPUT_DIR}
./bin/subexpr_rec.x $LAMP_N $LAMP_N                 >> ${LAMP_C_OUTPUT_DIR}

./bin/mc_mixed.x $LAMP_N $LAMP_N $LAMP_N            >> ${LAMP_C_OUTPUT_DIR}

let N_10=LAMP_N/10
./bin/transposition.x $N_10 $N_10 $N_10             >> ${LAMP_C_OUTPUT_DIR}

let RHS_SMALL=LAMP_N/10
./bin/solve_naive.x       $LAMP_N $RHS_SMALL        >> ${LAMP_C_OUTPUT_DIR}
./bin/solve_recommended.x $LAMP_N $RHS_SMALL       >> ${LAMP_C_OUTPUT_DIR}

./bin/solve_recommended_spd.x $LAMP_N $RHS_SMALL    >> ${LAMP_C_OUTPUT_DIR}
./bin/solve_recommended_sym.x $LAMP_N $RHS_SMALL    >> ${LAMP_C_OUTPUT_DIR}
./bin/solve_recommended_tri.x $LAMP_N $RHS_SMALL    >> ${LAMP_C_OUTPUT_DIR}
./bin/solve_recommended_dia.x $LAMP_N $RHS_SMALL    >> ${LAMP_C_OUTPUT_DIR}

let RHS_LARGE=LAMP_N/2
./bin/solve_naive.x       $LAMP_N $RHS_LARGE large >> ${LAMP_C_OUTPUT_DIR}
./bin/solve_recommended.x $LAMP_N $RHS_LARGE large >> ${LAMP_C_OUTPUT_DIR}
