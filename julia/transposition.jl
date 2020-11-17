function transposition(n)

  reps = parse(Int64, ENV["LAMP_REPS"])

  m = Int(floor(n / 10))
  A = randn(m, m)
  B = randn(m, m)
  C = randn(m, m)

  Benchmarker.add_data(csv, "tr_nn_implicit", Benchmarker.measure(reps, no_transpose, A, B))
  Benchmarker.add_data(csv, "tr_nn_explicit", Benchmarker.measure(reps, g_no_transpose, A, B))
  Benchmarker.add_data(csv, "tr_tn_implicit", Benchmarker.measure(reps, first_transpose, A, B))
  Benchmarker.add_data(csv, "tr_tn_explicit", Benchmarker.measure(reps, g_first_transpose, A, B))
  Benchmarker.add_data(csv, "tr_nt_implicit", Benchmarker.measure(reps, second_transpose, A, B))
  Benchmarker.add_data(csv, "tr_nt_explicit", Benchmarker.measure(reps, g_second_transpose, A, B))
  Benchmarker.add_data(csv, "tr_tt_implicit", Benchmarker.measure(reps, both_transpose, A, B))
  Benchmarker.add_data(csv, "tr_tt_explicit", Benchmarker.measure(reps, g_both_transpose, A, B))

  @test(isapprox(no_transpose(A, B)[2], g_no_transpose(A, B)[2]))
  @test(isapprox(first_transpose(A, B)[2], g_first_transpose(A, B)[2]))
  @test(isapprox(second_transpose(A, B)[2], g_second_transpose(A, B)[2]))
  @test(isapprox(both_transpose(A, B)[2], g_both_transpose(A, B)[2]))
end

function no_transpose(A::DenseArray{Float64, 2}, B::DenseArray{Float64, 2})
  result = zeros(size(A,1), size(B,2))
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  result = A * B

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end

function first_transpose(A::DenseArray{Float64, 2}, B::DenseArray{Float64, 2})
  result = zeros(size(A,2), size(B,2))
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  result = transpose(A)*B

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end

function second_transpose(A::DenseArray{Float64, 2}, B::DenseArray{Float64, 2})
  result = zeros(size(A,1), size(B,1))
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  result = A * transpose(B)

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end

function both_transpose(A::DenseArray{Float64, 2}, B::DenseArray{Float64, 2})
  result = zeros(size(A,2), size(B,1))
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  result = transpose(A)*transpose(B)

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end

function g_no_transpose(A::DenseArray{Float64, 2}, B::DenseArray{Float64, 2})
  result = zeros(size(A,1), size(B,2))
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  LinearAlgebra.BLAS.gemm!('N', 'N', 1.0, A, B, 0.0, result)

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end

function g_first_transpose(A::DenseArray{Float64, 2}, B::DenseArray{Float64, 2})
  result = zeros(size(A,2), size(B,2))
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  LinearAlgebra.BLAS.gemm!('T', 'N', 1.0, A, B, 0.0, result)

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end

function g_second_transpose(A::DenseArray{Float64, 2}, B::DenseArray{Float64, 2})
  result = zeros(size(A,1), size(B,1))
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  LinearAlgebra.BLAS.gemm!('N', 'T', 1.0, A, B, 0.0, result)

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end

function g_both_transpose(A::DenseArray{Float64, 2}, B::DenseArray{Float64, 2})
  result = zeros(size(A,2), size(B,1))
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  LinearAlgebra.BLAS.gemm!('T', 'T', 1.0, A, B, 0.0, result)

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end
