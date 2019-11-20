function kernel_invocations_gemm(m, k, n)

  reps = parse(Int64, ENV["LAMP_REPS"])

  A = randn(m, k)
  B = randn(k, n)
  C = randn(m, n)

  Benchmarker.add_data(csv, "gemm_implicit", Benchmarker.measure(reps, gemm_implicit, A, B, C))
  Benchmarker.add_data(csv, "gemm_implicit_noup", Benchmarker.measure(reps, gemm_implicit_noup, A, B))
  Benchmarker.add_data(csv, "gemm_implicit_compact", Benchmarker.measure(reps, gemm_implicit_compact, A, B, C))
  Benchmarker.add_data(csv, "gemm_implicit_coeff", Benchmarker.measure(reps, gemm_implicit_coeff, A, B, C))
  Benchmarker.add_data(csv, "gemm_implicit_double_coeff", Benchmarker.measure(reps, gemm_implicit_double_coeff, A, B, C))
  Benchmarker.add_data(csv, "gemm_explicit", Benchmarker.measure(reps, gemm_explicit, A, B, C))
  Benchmarker.add_data(csv, "gemm_explicit_noup", Benchmarker.measure(reps, gemm_explicit_noup, A, B))
  Benchmarker.add_data(csv, "gemm_explicit_semi", Benchmarker.measure(reps, gemm_explicit_semi, A, B, C))

  @test(isapprox(gemm_implicit(A,B,C)[2], gemm_explicit(A,B,C)[2]))
  @test(isapprox(gemm_implicit(A,B,C)[2], gemm_implicit_compact(A,B,C)[2]))
  @test(isapprox(gemm_implicit(A,B,C)[2], gemm_explicit_semi(A,B,C)[2]))
  @test(isapprox(gemm_implicit_noup(A,B)[2], gemm_explicit_noup(A,B)[2]))

  A = randn(n, n)
  B = randn(n, n)
  Benchmarker.add_data(csv, "gemm_prop", Benchmarker.measure(reps, gemm_implicit_noup, A, B))

  A = LowerTriangular(randn(n, n))
  Benchmarker.add_data(csv, "trmm_implicit", Benchmarker.measure(reps, trmm_implicit, A, B))
  Benchmarker.add_data(csv, "trmm_implicit_compact", Benchmarker.measure(reps, trmm_implicit_compact, A, B))
  Benchmarker.add_data(csv, "trmm_explicit", Benchmarker.measure(reps, trmm_explicit, A, B))

  @test istril(A)
  @test(isapprox(trmm_implicit(A,B)[2], trmm_explicit(A,B)[2]))

  A = Diagonal(randn(n, n))
  B = randn(n, n)

  Benchmarker.add_data(csv, "diagmm", Benchmarker.measure(reps, diagmm, A, B))

  @test isdiag(A)
end

function diagmm(A::Diagonal{Float64}, B::DenseArray{Float64, 2})
  result = zeros(size(A,1), size(B,2))
  A_copy = Matrix(copy(A))
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  result = A_copy * B

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end

function gemm_implicit(A::DenseArray{Float64, 2}, B::DenseArray{Float64, 2}, C::DenseArray{Float64, 2})
  result = copy(C)
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  result = A * B + result

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end

function gemm_implicit_coeff(A::DenseArray{Float64, 2}, B::DenseArray{Float64, 2}, C::DenseArray{Float64, 2})
  result = copy(C)
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  result = 3.0 * A * B + result

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end

function gemm_implicit_double_coeff(A::DenseArray{Float64, 2}, B::DenseArray{Float64, 2}, C::DenseArray{Float64, 2})
  result = copy(C)
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  result = 3.0 * A * B + 3.0 * result

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end

function gemm_implicit_compact(A::DenseArray{Float64, 2}, B::DenseArray{Float64, 2}, C::DenseArray{Float64, 2})
  result = copy(C)
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  result += A * B

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end

function gemm_implicit_noup(A::DenseArray{Float64, 2}, B::DenseArray{Float64, 2})
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

function trmm_implicit_compact(A::LowerTriangular{Float64}, B::DenseArray{Float64, 2})
  result = copy(B)
  A_copy = Matrix(copy(A))
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  result *= A_copy

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end

function trmm_implicit(A::LowerTriangular{Float64}, B::DenseArray{Float64, 2})
  result = copy(B)
  A_copy = Matrix(copy(A))
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  result = A_copy * result

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end

function gemm_explicit(A::DenseArray{Float64, 2}, B::DenseArray{Float64, 2}, C::DenseArray{Float64, 2})
  result = copy(C)
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  LinearAlgebra.BLAS.gemm!('N', 'N', 1.0, A, B, 1.0, result)

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end

function trmm_explicit(A::LowerTriangular{Float64}, B::DenseArray{Float64, 2})
  result = copy(B)
  A_copy = Matrix(copy(A))
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  LinearAlgebra.BLAS.trmm!('L', 'L', 'N', 'N', 1.0, A_copy, result)

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end


function gemm_explicit_noup(A::DenseArray{Float64, 2}, B::DenseArray{Float64, 2})
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

function gemm_explicit_semi(A::DenseArray{Float64, 2}, B::DenseArray{Float64, 2}, C::DenseArray{Float64, 2})
  result = copy(C)
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  result = LinearAlgebra.BLAS.gemm('N', 'N', 1.0, A, B) + result

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end
