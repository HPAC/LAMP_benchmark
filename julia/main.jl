using LinearAlgebra
using Logging
using Test

LinearAlgebra.BLAS.set_num_threads(parse(Int, ENV["OMP_NUM_THREADS"]))

include("benchmarker/Benchmarker.jl")
include("kernel_invocations_syrk.jl")
include("kernel_invocations_gemm.jl")
include("kernel_invocations_syr2k.jl")
include("transposition.jl")
include("common_subexpressions.jl")
include("solve_linear_systems.jl")
include("matrix_chain.jl")
include("diagonal_elements.jl")
include("index_problems.jl")
include("partitioned_matrices.jl")
include("properties_solve.jl")
include("partial_operand.jl")
include("loop_translation.jl")
include("add_scal.jl")

csv = Benchmarker.CSV(string(ENV["LAMP_OUTPUT_DIR"], "julia_", string(ENV["OMP_NUM_THREADS"])))

m = parse(Int32, ENV["LAMP_m"])
k = parse(Int32, ENV["LAMP_k"])
n = parse(Int32, ENV["LAMP_n"])

tr_n = parse(Int32, ENV["LAMP_tr_n"])

ip_n = parse(Int32, ENV["LAMP_tr_n"])

p_n = parse(Int32, ENV["LAMP_p_n"])

rhs_small = parse(Int32, ENV["LAMP_rhs_small"])
rhs_large = parse(Int32, ENV["LAMP_rhs_large"])

add_scal(n)

properties_solve(n, rhs_small)

kernel_invocations_syrk(n, k)

kernel_invocations_gemm(m, k, n)

kernel_invocations_syr2k(n, k)

transposition(tr_n)

common_subexpressions(m, k, n)

solve_linear_systems(n, rhs_small, rhs_large)

matrix_chain(m, k, n)

diagonal_elements(n)

partial_operand(n)

index_problems(ip_n)

loop_translation(n)

partitioned_matrices(p_n)
