function partitioned_matrices(n)

  reps = parse(Int64, ENV["LAMP_REPS"])

  A1 = randn(n, n)
  A2 = randn(n, n)
  B = randn(2*n, 2*n)

  Benchmarker.add_data(csv, "compact", Benchmarker.measure(reps, blocked_solve_naive, A1, A2, B))
  Benchmarker.add_data(csv, "blocked", Benchmarker.measure(reps, blocked_solve_recommended, A1, A2, B))

  @test isapprox(blocked_solve_naive(A1, A2, B)[2], blocked_solve_recommended(A1, A2, B)[2])
end

function blocked_solve_naive(A1::DenseArray{Float64, 2}, A2::DenseArray{Float64, 2},B::DenseArray{Float64, 2})
  result = zeros(size(B))
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  result = [A1 zeros(size(A1,1), size(A1, 2)); zeros(size(A2,1), size(A2, 2)) A2]\B

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end

function blocked_solve_recommended(A1::DenseArray{Float64, 2}, A2::DenseArray{Float64, 2},B::DenseArray{Float64, 2})
  result = zeros(size(B))
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

b1 = @view B[1:size(A1, 1), 1:end] # do not use view with parenthesis
  b2 = @view B[size(A1, 1)+1:end, 1:end]
  result = [A1\b1; A2\b2]

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end
