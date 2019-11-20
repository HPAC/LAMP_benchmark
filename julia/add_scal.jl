function add_scal(n)

  reps = parse(Int64, ENV["LAMP_REPS"])

  A = randn(n,n)
  B = randn(n,n)

  Benchmarker.add_data(csv, "add", Benchmarker.measure(reps, add, A, B))
  Benchmarker.add_data(csv, "scal", Benchmarker.measure(reps, scal, A))

end

function add(A::DenseArray{Float64, 2}, B::DenseArray{Float64, 2})
  K = copy(A)
  X = copy(B)
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  K = X + K

  finish = time_ns()
  return ((finish-start)*1e-9, K)
end

function scal(A::DenseArray{Float64, 2})
  K = copy(A)
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  K = 3.0 * K

  finish = time_ns()
  return ((finish-start)*1e-9, K)
end
