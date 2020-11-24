function properties_solve_sparse(n, density)

  reps = parse(Int64, ENV["LAMP_REPS"])

  B = randn(n, 10)

  # Generic
  A = sprandn(n, n, density)
  A = A + sparse(I, n, n)
  @test !issymmetric(A)
  @test !isposdef(A)
  Benchmarker.add_data(csv, "solve_gen", Benchmarker.measure(reps, solve, A, B))
  @test !isposdef(A) && !issymmetric(A)

  # SPD
  A = sprandn(n, n, density/2)
  A = A + A' + n * sparse(I, n, n)
  @test issymmetric(A)
  @test isposdef(A)
  Benchmarker.add_data(csv, "solve_spd", Benchmarker.measure(reps, solve, A, B))
  @test isposdef(A) && issymmetric(A)

  # Symmetric
  A = sprandn(n, n, density)
  A = A + A' + sparse(I, n, n)
  Benchmarker.add_data(csv, "solve_sym", Benchmarker.measure(reps, solve, A, B))
  @test issymmetric(A) && !isposdef(A)

  # Triangular
  A = sprandn(n, n, 2.0 * density)
  A = sparse(LowerTriangular(A)) + sparse(I,n,n)
  Benchmarker.add_data(csv, "solve_tri", Benchmarker.measure(reps, solve, A, B))
  @test istril(A)
end

function solve(A::SparseMatrixCSC{Float64,Int64}, B::DenseArray{Float64, 2})
  println("doing")
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

