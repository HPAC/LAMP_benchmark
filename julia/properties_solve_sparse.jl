using Printf

function properties_solve_sparse(n, density)

  reps = parse(Int64, ENV["LAMP_REPS"])

  B = randn(n, 10)

  # Generic
  A = sprandn(n, n, density)
  A = A + sparse(I, n, n)
  Printf.@printf("cond: %.1f, nnz: %d\n", cond(A,1), nnz(A))
  @test !issymmetric(A) && !isposdef(A)
  Benchmarker.add_data(csv, "solve_sp_gen", Benchmarker.measure(reps, solve, A, B))
  @test !isposdef(A) && !issymmetric(A)

  # Symmetric
  A = sprandn(n, n, density/2.0)
  A = A + A' + 2.0 * sparse(I, n, n)
  Printf.@printf("cond: %.1f, nnz: %d\n", cond(A,1), nnz(A))
  Benchmarker.add_data(csv, "solve_sp_sym", Benchmarker.measure(reps, solve, A, B))
  @test issymmetric(A) && !isposdef(A)

  # SPD
  A = sprandn(n, n, density/2.0)
  A = A + A' + n * sparse(I, n, n)
  Printf.@printf("cond: %.1f, nnz: %d\n", cond(A,1), nnz(A))
  @test issymmetric(A)
  @test isposdef(A)
  Benchmarker.add_data(csv, "solve_sp_spd", Benchmarker.measure(reps, solve, A, B))
  @test isposdef(A) && issymmetric(A)

  # Triangular
  A = sprandn(n, n, 2.0 * density)
  A = sparse(LowerTriangular(A)) + sparse(I,n,n)
  Printf.@printf("cond: %.1f, nnz: %d\n", cond(A,1), nnz(A))
  Benchmarker.add_data(csv, "solve_sp_tri", Benchmarker.measure(reps, solve, A, B))
  @test istril(A)
end

function solve(A::SparseMatrixCSC{Float64,Int64}, B::DenseArray{Float64, 2})
  result = zeros(size(B))
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  result = A\B

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end

