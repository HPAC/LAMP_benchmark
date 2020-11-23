using LinearAlgebra
using SparseArrays
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
include("properties_solve_sparse.jl")
include("partial_operand.jl")
include("loop_translation.jl")
include("add_scal.jl")

csv = Benchmarker.CSV(string(ENV["LAMP_OUTPUT_DIR"], "julia_", string(ENV["OMP_NUM_THREADS"])))

n = parse(Int32, ENV["LAMP_N"])
sp_n = parse(Int32, ENV["LAMP_SP_N"])
density = parse(Float64, ENV["LAMP_SP_DENSITY"])
println(Threads.nthreads())

# add_scal(n)
# properties_solve(n)
properties_solve_sparse(sp_n, density)
# kernel_invocations_syrk(n)
# kernel_invocations_gemm(n)
# kernel_invocations_syr2k(n)
# transposition(n)
# common_subexpressions(n)
# solve_linear_systems(n)
# matrix_chain(n)
# diagonal_elements(n)
# partial_operand(n)
# index_problems(n)
# loop_translation(n)
# partitioned_matrices(n)
