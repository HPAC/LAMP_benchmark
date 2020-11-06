function solve_linear_systems(n)

  reps = parse(Int64, ENV["LAMP_REPS"])

  m = Int(floor(n / 10))
  A = randn(n, n)
  B = randn(n, m)

  Benchmarker.add_data(csv, "solve_nai", Benchmarker.measure(reps, implicit_solve, A, B))
  Benchmarker.add_data(csv, "solve_rec", Benchmarker.measure(reps, explicit_solve, A, B))
  @test isapprox(implicit_solve(A, B)[2], explicit_solve(A, B)[2])

  k = Int(floor(n / 2))
  B = randn(n, k)
  Benchmarker.add_data(csv, "solve_large_nai", Benchmarker.measure(reps, implicit_solve, A, B))
  Benchmarker.add_data(csv, "solve_large_rec", Benchmarker.measure(reps, explicit_solve, A, B))
  @test isapprox(implicit_solve(A, B)[2], explicit_solve(A, B)[2])
end

function implicit_solve(A::DenseArray{Float64, 2}, B::DenseArray{Float64, 2})
  result = zeros(size(B))
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  result = inv(A) * B

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end

function explicit_solve(A::DenseArray{Float64, 2}, B::DenseArray{Float64, 2})
  result = zeros(size(B))
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  result = A \ B

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end

