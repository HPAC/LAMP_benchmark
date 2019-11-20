function properties_solve(m, rhs)

  reps = parse(Int64, ENV["LAMP_REPS"])

  B = randn(m, rhs)

  # SPD
  A = randn(m, m)
  A = Matrix(Symmetric(A, :L)) + I*m
  Benchmarker.add_data(csv, "solve_spd", Benchmarker.measure(reps, solve, A, B))
  @test isposdef(A) && issymmetric(A)

  # Symmetric
  A = randn(m, m)
  A = Matrix(Symmetric(A, :L))
  A[1, 1] = -1.0
  Benchmarker.add_data(csv, "solve_sym", Benchmarker.measure(reps, solve, A, B))
  @test issymmetric(A) && !isposdef(A)

  # Triangular
  A = randn(m, m)
  A = Matrix(LowerTriangular(A))
  Benchmarker.add_data(csv, "solve_tri", Benchmarker.measure(reps, solve, A, B))
  @test istril(A)

  # Diagonal
  A = randn(m, m)
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

