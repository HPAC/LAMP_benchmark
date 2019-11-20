function diagonal_elements(n)

  reps = parse(Int64, ENV["LAMP_REPS"])

  A = randn(n,n)
  B = randn(n,n)

  Benchmarker.add_data(csv, "diag_mult_nai", Benchmarker.measure(reps, implicit_diagonal_mult, A, B))
  Benchmarker.add_data(csv, "diag_add_nai", Benchmarker.measure(reps, implicit_diagonal, A, B))
  Benchmarker.add_data(csv, "diag_add_rec", Benchmarker.measure(reps, explicit_diagonal, A, B))

  @test isapprox(implicit_diagonal(A, B)[2], explicit_diagonal(A, B)[2])
end

function implicit_diagonal_mult(A, B)
  result = zeros(1, size(A,1))
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  result = diag(A*B)

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end

function implicit_diagonal(A, B)
  result = zeros(1, size(A,1))
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  result = diag(A+B)

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end

function explicit_diagonal(A, B)
  result = zeros(1, size(A,1))
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  result = diag(A) + diag(B)

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end
