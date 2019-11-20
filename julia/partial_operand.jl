function partial_operand(n)

  reps = parse(Int64, ENV["LAMP_REPS"])

  A = randn(n,n)
  B = randn(n,n)

  Benchmarker.add_data(csv, "part_op_col_mult_nai", Benchmarker.measure(reps, part_op_col_mult_nai, A, B))
  Benchmarker.add_data(csv, "part_op_col_add_nai", Benchmarker.measure(reps, part_op_col_add_nai, A, B))
  Benchmarker.add_data(csv, "part_op_col_add_rec", Benchmarker.measure(reps, part_op_col_add_rec, A, B))

  Benchmarker.add_data(csv, "part_op_ele_mult_nai", Benchmarker.measure(reps, part_op_ele_mult_nai, A, B))
  Benchmarker.add_data(csv, "part_op_ele_add_nai", Benchmarker.measure(reps, part_op_ele_add_nai, A, B))
  Benchmarker.add_data(csv, "part_op_ele_add_rec", Benchmarker.measure(reps, part_op_ele_add_rec, A, B))

  @test isapprox(implicit_diagonal(A, B)[2], explicit_diagonal(A, B)[2])
end

function part_op_col_mult_nai(A, B)
  result = zeros(size(A,1), 1)
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  result = (A*B)[:,2]

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end

function part_op_col_add_nai(A, B)
  result = zeros(size(A,1), 1)
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  result = (A+B)[:,2]

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end

function part_op_col_add_rec(A, B)
  result = zeros(size(A,1), 1)
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  result = A[:,2] + B[:,2]

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end

function part_op_ele_mult_nai(A, B)
  result = zeros(size(A,1), 1)
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  result = (A*B)[2,2]

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end

function part_op_ele_add_nai(A, B)
  result = zeros(size(A,1), 1)
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  result = (A+B)[2,2]

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end

function part_op_ele_add_rec(A, B)
  result = zeros(size(A,1), 1)
  start::Float64 = 0.0
  finish::Float64 = 0.0
  Benchmarker.cachescrub()
  Benchmarker.gcscrub()
  start = time_ns()

  result = A[2,2] + B[2,2]

  finish = time_ns()
  return ((finish-start)*1e-9, result)
end
