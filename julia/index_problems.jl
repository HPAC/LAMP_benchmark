function index_problems(n)

  reps = parse(Int64, ENV["LAMP_REPS"])

  m = Int(floor(n / 10))
  A = randn(m, m)
  B = randn(m, m)
  C = Vector(randn(m))

  Benchmarker.add_data(csv, "loop_nai", Benchmarker.measure(reps, naive_loop, A, B, C))
  Benchmarker.add_data(csv, "loop_rec", Benchmarker.measure(reps, recommended_loop, A, B, C))

  @test(isapprox(naive_loop(A,B,C)[2], recommended_loop(A,B,C)[2]))
end

function naive_loop( A::DenseArray{Float64, 2},  B::DenseArray{Float64, 2},  C::Vector{Float64})
  result = copy(C)
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  temp::DenseArray{Float64, 2} = zeros(size(A, 1), size(B, 2))
  for i in range(1, size(result, 1), step=1)
    temp = A*B
    @inbounds result[i] = temp[i, i]
  end

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end

function recommended_loop( A::DenseArray{Float64, 2},  B::DenseArray{Float64, 2},  C::Vector{Float64})
  result = copy(C)
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  temp::DenseArray{Float64, 2} = A*B
  for i in range(1, size(result, 1), step=1)
    @inbounds result[i] = temp[i, i]
  end

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end
