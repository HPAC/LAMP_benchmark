library("sets")

source("kernel_invocations_syrk.R")
source("kernel_invocations_syr2k.R")
source("kernel_invocations_gemm.R")
source("common_subexpressions.R")
source("solve_linear_systems.R")
source("matrix_chain.R")
source("transposition.R")
source("diagonal_elements.R")
source("index_problems.R")
source("partitioned_matrices.R")
source("properties_solve.R")
source("properties_solve_sparse.R")
source("add_scal.R")
source("loop_translation.R")
source("partial_operand.R")
source("benchmarker.R")

n <- strtoi(Sys.getenv("LAMP_N"))
sp_n <- strtoi(Sys.getenv("LAMP_SP_N"))
density <- strtod(Sys.getenv("LAMP_SP_DENSITY"))
print(n)
print(sp_n)
print(density)

threads <- Sys.getenv("OMP_NUM_THREADS")
file_name <- paste("R_", threads, sep="")
init_benchmarker(file_name)

properties_solve_sparse(b, sp_n, 10, density)

#A = matrix(data = rnorm(n*n), nrow = n, ncol = n)
#B = matrix(data = rnorm(n*n), nrow = n, ncol = n)
#add_scal(b, A, B)

###! Properties Solve
#properties_solve(b, n, n / 10)

###! SYRK
#A = matrix(data = rnorm(n*n), nrow = n, ncol = n)
#C = matrix(data = rnorm(n*n), nrow = n, ncol = n); C = C + t(C);

#kernel_invocations_syrk(b, A, C)

###! GEMM

#A = matrix(data = rnorm(n*n), nrow = n, ncol = n)
#B = matrix(data = rnorm(n*n), nrow = n, ncol = n)
#C = matrix(data = rnorm(n*n), nrow = n, ncol = n)

#kernel_invocations_gemm(b, A, B, C)

###! SYR2K

#A = matrix(data = rnorm(n*n), nrow = n, ncol = n)
#B = matrix(data = rnorm(n*n), nrow = n, ncol = n)
#C = matrix(data = rnorm(n*n), nrow = n, ncol = n); C = C + t(C);

#kernel_invocations_syr2k(b, A, B, C)

###! Transposition

#tn <- n / 10
#A = matrix(data = rnorm(tn * tn), nrow = tn, ncol = tn)
#B = matrix(data = rnorm(tn * tn), nrow = tn, ncol = tn)
#C = matrix(data = rnorm(tn * tn), nrow = tn, ncol = tn)

#transposition(b, A, B, C)

###! Common Subexpression

#A = matrix(data = rnorm(n*n), nrow = n, ncol = n)
#B = matrix(data = rnorm(n*n), nrow = n, ncol = n)

#common_subexpressions(b, A, B)

###! Composed Operations

#A = matrix(data = rnorm(n*n), nrow = n, ncol = n)
#B = matrix(data = rnorm(n*(n/10)), nrow = n, ncol = n/10)

#solve_linear_systems(b, A, B)

###! Matrix Chain Problem

#A = matrix(data = rnorm(n*n), nrow = n, ncol = n)
#B = matrix(data = rnorm(n*n), nrow = n, ncol = n)

#matrix_chain(b, A, B)

###! Diagonal elements

#A = matrix(data = rnorm(n*n), nrow = n, ncol = n)
#B = matrix(data = rnorm(n*n), nrow = n, ncol = n)

#diagonal_elements(b, A, B)

###! Partial Operand

#A = matrix(data = rnorm(n*n), nrow = n, ncol = n)
#B = matrix(data = rnorm(n*n), nrow = n, ncol = n)

#partial_operand(b, A, B)

###! Index problems

#ipn <- n / 10
#A = matrix(data = rnorm(ipn*ipn), nrow = ipn, ncol = ipn)
#B = matrix(data = rnorm(ipn*ipn), nrow = ipn, ncol = ipn)
#C = matrix(data = rnorm(ipn*1)  , nrow = 1  , ncol = ipn)

#index_problems(b, A, B, C)

###! Loop Translation

#A = matrix(data = rnorm(n*n), nrow = n, ncol = n)
#B = matrix(data = rnorm(n*n), nrow = n, ncol = n)
#C = matrix(data = rnorm(n*n), nrow = n, ncol = n)

#loop_translation(b, A, B, C)

###! Partitioned Matrices

#p <- n / 2
#A1 = matrix(data = rnorm(p*p), nrow = p, ncol =  p)
#A2 = matrix(data = rnorm(p*p), nrow = p, ncol =  p)
#B  = matrix(data = rnorm(2*p, 2*p), nrow = 2*p, ncol = 2*p)

#partitioned_matrices(b, A1, A2, B)
