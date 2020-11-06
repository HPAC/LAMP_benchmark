function matrix_chain(m, k, n)

  reps = parse(Int64, ENV["LAMP_REPS"])

  A = randn(n,n)
  B = randn(n,n)
  C = randn(n / 5, m)

  Benchmarker.add_data(csv, "mc_l_r_orig", Benchmarker.measure(reps, left_to_right_chain_original, A, B, C))
  Benchmarker.add_data(csv, "mc_l_r_guid", Benchmarker.measure(reps, left_to_right_chain_guided, A, B, C))

  @test isapprox(left_to_right_chain_original(A, B, C)[2], left_to_right_chain_guided(A, B, C)[2])

  C = randn(n, n / 5)
  Benchmarker.add_data(csv, "mc_r_l_orig", Benchmarker.measure(reps, right_to_left_chain_original, A, B, C))
  Benchmarker.add_data(csv, "mc_r_l_guid", Benchmarker.measure(reps, right_to_left_chain_guided, A, B, C))

  @test isapprox(right_to_left_chain_original(A, B, C)[2], right_to_left_chain_guided(A, B, C)[2])

  A = randn(n, n)
  B = randn(n, n / 5)
  C = randn(n / 5, n)
  D = randn(n, n)

  Benchmarker.add_data(csv, "mc_mixed_orig", Benchmarker.measure(reps, mixed_chain_original, A, B, C, D))
  Benchmarker.add_data(csv, "mc_mixed_guid", Benchmarker.measure(reps, mixed_chain_guided, A, B, C, D))

  @test isapprox(mixed_chain_original(A, B, C, D)[2], mixed_chain_guided(A, B, C, D)[2])
end

function left_to_right_chain_original(A::DenseArray{Float64, 2}, B::DenseArray{Float64, 2}, C::DenseArray{Float64, 2})
  result = zeros(size(C,1), size(B,2))
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  result = C * A * B

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end

function left_to_right_chain_guided(A::DenseArray{Float64, 2}, B::DenseArray{Float64, 2}, C::DenseArray{Float64, 2})
  result = zeros(size(C,1), size(B,2))
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  result = (C * A) * B

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end

function right_to_left_chain_original(A::DenseArray{Float64, 2}, B::DenseArray{Float64, 2}, C::DenseArray{Float64, 2})
  result = zeros(size(A,1), size(C,2))
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  result = A * B * C

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end

function right_to_left_chain_guided(A::DenseArray{Float64, 2}, B::DenseArray{Float64, 2}, C::DenseArray{Float64, 2})
  result = zeros(size(A,1), size(C,2))
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  result = A * (B * C)

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end

function mixed_chain_original(A::DenseArray{Float64, 2}, B::DenseArray{Float64, 2}, C::DenseArray{Float64, 2}, D::DenseArray{Float64, 2})
  result = zeros(size(A,1), size(D,2))
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  result = A * B * C * D

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end

function mixed_chain_guided(A::DenseArray{Float64, 2}, B::DenseArray{Float64, 2}, C::DenseArray{Float64, 2}, D::DenseArray{Float64, 2})
  result = zeros(size(A,1), size(D,2))
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  result = (A * B) * (C * D)

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end
