function properties_solve(n)

  reps = parse(Int64, ENV["LAMP_REPS"])

  B = randn(n, 200)

  # SPD
  A = randn(n,n)
  A = Matrix(Symmetric(A, :L)) + I*n
  @test issymmetric(A)
  @test isposdef(A)
  Benchmarker.add_data(csv, "solve_spd", Benchmarker.measure(reps, solve, A, B))
  @test isposdef(A) && issymmetric(A)

  # Symmetric
  A = randn(n,n)
  A = Matrix(Symmetric(A, :L))
  A[1, 1] = -1.0
  Benchmarker.add_data(csv, "solve_sym", Benchmarker.measure(reps, solve, A, B))
  @test issymmetric(A) && !isposdef(A)

  # Triangular
  A = randn(n,n)
  A = Matrix(LowerTriangular(A))
  Benchmarker.add_data(csv, "solve_tri", Benchmarker.measure(reps, solve, A, B))
  @test istril(A)

  # Diagonal
  A = randn(n,n)
  A = Matrix(Diagonal(A))
  Benchmarker.add_data(csv, "solve_dia", Benchmarker.measure(reps, solve, A, B))
  @test isdiag(A)
end

function solve(A::DenseArray{Float64, 2}, B::DenseArray{Float64, 2})
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

