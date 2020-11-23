function properties_solve(n, density)

  reps = parse(Int64, ENV["LAMP_REPS"])

  B = randn(n, 10)

  # SPD
  A = sprandn(n,n, density)
  A = sparse(Symmetric(A, :L)) + sparse(I,n,n)*n
  @test issymmetric(A)
  @test isposdef(A)
  Benchmarker.add_data(csv, "solve_spd", Benchmarker.measure(reps, solve, A, B))
  @test isposdef(A) && issymmetric(A)

  # Symmetric
  A = sprandn(n,n, density)
  A = sparse(Symmetric(A, :L)) + sparse(I,n,n)*0.01
  Benchmarker.add_data(csv, "solve_sym", Benchmarker.measure(reps, solve, A, B))
  @test issymmetric(A) && !isposdef(A)

  # Triangular
  A = sprandn(n,n,density)
  A = sparse(LowerTriangular(A))
  Benchmarker.add_data(csv, "solve_tri", Benchmarker.measure(reps, solve, A, B))
  @test istril(A)
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

