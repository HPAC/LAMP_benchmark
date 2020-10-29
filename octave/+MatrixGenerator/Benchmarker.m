classdef Benchmarker < handle

properties
Timings = cell(0, 0);
Results = cell(0, 5);
cs = rand(1, 7500000);
    end

    methods

    function res = benchmark(obj, label, iters, f)
    timings = zeros(iters, 1);

    obj.cs = obj.cs + 1e-4;
    [res, time] = f();
    timings(1) = time;

    for i=2:iters
                obj.cs = obj.cs + 1e-4;
                [res, time] = f();
                timings(i) = time;
            end

            % Process results (exclude first warmup run)
            avg_ = mean(timings(2:end));
            stddev_ = std(timings(2:end));
            min_ = min(timings(2:end));
            max_ = max(timings(2:end));
            obj.Results(size(obj.Results, 1) + 1, :) = {label avg_ stddev_ min_ max_};
            obj.Timings(size(obj.Timings, 1) + 1, :) = {label timings(:)};
        end

        function save(obj, filename)
            fid = fopen (filename, "w");
            fprintf (fid, "algorithm;Time;StdDev;Min;Max\n");
            fprintf (fid, "%s;%f;%f;%f;%f\n", obj.Results'{:});
            fclose (fid);
        end

    end

end

