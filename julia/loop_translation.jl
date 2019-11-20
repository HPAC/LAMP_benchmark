function loop_translation(n)

  reps = parse(Int64, ENV["LAMP_REPS"])

  A = randn(n,n)
  B = randn(n,n)
  C = randn(n,n)

  Benchmarker.add_data(csv, "loop_translation_nai", Benchmarker.measure(reps, naive_loop, A, B, C))
  Benchmarker.add_data(csv, "loop_translation_rec", Benchmarker.measure(reps, recommended_loop, A, B, C))

  @test(isapprox(naive_loop(A,B,C)[2], recommended_loop(A,B,C)[2]))
end

function naive_loop( A::DenseArray{Float64, 2},  B::DenseArray{Float64, 2},  C::DenseArray{Float64, 2})
  result = copy(C)
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  for i in range(1, size(result, 2), step=1)
    @inbounds result[:, i] = A * B[:, i]
  end

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end

function recommended_loop( A::DenseArray{Float64, 2},  B::DenseArray{Float64, 2},  C::DenseArray{Float64, 2})
  result = copy(C)
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  result = A * B

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end
