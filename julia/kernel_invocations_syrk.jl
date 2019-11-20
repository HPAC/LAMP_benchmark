function kernel_invocations_syrk(n, k)

  reps = parse(Int64, ENV["LAMP_REPS"])

  A = randn(n,k)
  C = Symmetric(randn(n,n))

  Benchmarker.add_data(csv, "syrk_implicit", Benchmarker.measure(reps, syrk_implicit, A, C))
  Benchmarker.add_data(csv, "syrk_implicit_compact", Benchmarker.measure(reps, syrk_implicit_compact, A, C))
  Benchmarker.add_data(csv, "syrk_explicit", Benchmarker.measure(reps, syrk_explicit, A, C))
  Benchmarker.add_data(csv, "syrk_implicit_noup", Benchmarker.measure(reps, syrk_implicit_noup, A))
  Benchmarker.add_data(csv, "syrk_explicit_noup", Benchmarker.measure(reps, syrk_explicit_noup, A))

  @test(isapprox(syrk_implicit(A, C)[2], Symmetric(syrk_explicit(A, C)[2], :L)))
  @test(isapprox(syrk_implicit(A, C)[2], syrk_implicit_compact(A, C)[2]))
  @test(isapprox(syrk_implicit_noup(A)[2], Symmetric(syrk_explicit_noup(A)[2], :L)))
end

function syrk_implicit(A::DenseArray{Float64, 2}, C::Symmetric{Float64})
  result = copy(C)
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()
  result = A*transpose(A) + result
  finish = time_ns()
  return ((finish-start)*1e-9, result)
end

function syrk_implicit_compact(A::DenseArray{Float64, 2}, C::Symmetric{Float64})
  result = copy(C)
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()
  result += A*transpose(A)
  finish = time_ns()
  return ((finish-start)*1e-9, result)
end

function syrk_implicit_noup(A::DenseArray{Float64, 2})
  result = zeros(size(A,1), size(A,1))
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()
  result = A*transpose(A)
  finish = time_ns()
  return ((finish-start)*1e-9, result)
end

function syrk_explicit(A::DenseArray{Float64, 2}, C::Symmetric{Float64})
  result = Matrix(copy(C))
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()
  LinearAlgebra.BLAS.syrk!('L', 'N', 1.0, A, 1.0, result)
  finish = time_ns()
  return ((finish-start)*1e-9, result)
end

function syrk_explicit_noup(A::DenseArray{Float64, 2})
  result = zeros(size(A,1), size(A,1))
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()
  LinearAlgebra.BLAS.syrk!('L', 'N', 1.0, A, 0.0, result)
  finish = time_ns()
  return ((finish-start)*1e-9, result)
end
