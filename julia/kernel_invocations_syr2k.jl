function kernel_invocations_syr2k(n, k)

  reps = parse(Int64, ENV["LAMP_REPS"])

  A = randn(n,n)
  B = randn(n,n)
  C = Symmetric(randn(n,n))

  Benchmarker.add_data(csv, "syr2k_implicit", Benchmarker.measure(reps, syr2k_implicit, A, B, C))
  Benchmarker.add_data(csv, "syr2k_implicit_compact", Benchmarker.measure(reps, syr2k_implicit_compact, A, B, C))
  Benchmarker.add_data(csv, "syr2k_explicit", Benchmarker.measure(reps, syr2k_explicit, A, B, C))
  Benchmarker.add_data(csv, "syr2k_implicit_noup", Benchmarker.measure(reps,syr2k_implicit_noup, A, B))
  Benchmarker.add_data(csv, "syr2k_explicit_noup", Benchmarker.measure(reps,syr2k_explicit_noup, A, B))

  @test(isapprox(syr2k_implicit(A,B,C)[2], Symmetric(syr2k_explicit(A,B,C)[2], :L)))
  @test(isapprox(syr2k_implicit(A,B,C)[2], syr2k_implicit_compact(A,B,C)[2]))
  @test(isapprox(syr2k_implicit_noup(A,B)[2], Symmetric(syr2k_explicit_noup(A,B)[2], :L)))
end

function syr2k_implicit(A::DenseArray{Float64, 2}, B::DenseArray{Float64, 2}, C::Symmetric{Float64})
  result = copy(C)
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  result = A * transpose(B) + B * transpose(A) + result

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end

function syr2k_implicit_noup(A::DenseArray{Float64, 2}, B::DenseArray{Float64, 2})
  result = zeros(size(A,1), size(B,1))
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  result = A * transpose(B) + B * transpose(A)

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end

function syr2k_implicit_compact(A::DenseArray{Float64, 2}, B::DenseArray{Float64, 2}, C::Symmetric{Float64})
  result = copy(C)
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  result += A * transpose(B) + B * transpose(A)

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end

function syr2k_explicit(A::DenseArray{Float64, 2}, B::DenseArray{Float64, 2}, C::Symmetric{Float64})
  result = Matrix(copy(C))
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  LinearAlgebra.BLAS.syr2k!('L', 'N', 1.0, A, B, 1.0, result)

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end

function syr2k_explicit_noup(A::DenseArray{Float64, 2}, B::DenseArray{Float64, 2})
  result = zeros(size(A,1), size(B,1))
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  LinearAlgebra.BLAS.syr2k!('L', 'N', 1.0, A, B, 0.0, result)

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end
