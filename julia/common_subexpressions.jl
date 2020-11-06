function common_subexpressions(n)

  reps = parse(Int64, ENV["LAMP_REPS"])

  A = randn(n,n)
  B = randn(n,n)

  Benchmarker.add_data(csv, "subexpr_nai", Benchmarker.measure(reps, implicit_subexpression, A, B))
  Benchmarker.add_data(csv, "subexpr_rec", Benchmarker.measure(reps, explicit_subexpression, A, B))

  @test isapprox(implicit_subexpression(A, B)[2], explicit_subexpression(A, B)[2])
end

function implicit_subexpression(A::DenseArray{Float64, 2}, B::DenseArray{Float64, 2})
  K = zeros(size(A))
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  K = A * B + A * B

  finish = time_ns()
  return ((finish-start)*1e-9, K)
end

function explicit_subexpression(A::DenseArray{Float64, 2}, B::DenseArray{Float64, 2})
  K = zeros(size(A))
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  K = A * B
  K = K + K

  finish = time_ns()
  return ((finish-start)*1e-9, K)
end
