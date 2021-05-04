import copy
import inspect
import logging
import os
import numpy as np

logger = logging.getLogger('Benchmarker')

cs = np.random.randn(1, int(os.environ['LAMP_L3_CACHE_SIZE']))


def benchmark(f):
    source = inspect.getsource(f)
    source_lines = source.splitlines()
    del source_lines[0]  # remove decorator to avoid recursion
    # pos, start and end in indicate the space between lines of the function (-1 indicates the space before the last line)
    pos = 1
    start = 0
    end = -1
    source_lines.insert(pos, """    cache_scrub()""")
    source_lines.insert(pos + 1, """    start = time.perf_counter()""")
    source_lines.insert(end, """    end = time.perf_counter()""")
    source_lines.insert(start, """from benchmarker import cache_scrub""")
    source_lines.insert(start, """import numpy as np""")
    source_lines.insert(start, """from scipy import linalg""")
    source_lines.insert(start, """import tensorflow as tf""")
    source_lines.insert(start, """import time""")
    source_lines[-1] = source_lines[-1].replace("return ", "return end-start, ")
    new_source = "\n".join(source_lines)
    # print(source_lines)
    # print(new_source)
    scope = {}
    exec(new_source, scope)
    new_f = scope[f.__name__]

    def inner(*args):
        return new_f(*copy.deepcopy(args))

    return inner


def cache_scrub():
    for j in range(cs.shape[0]):
        cs[j] += 1e-3


class Benchmarker:

    def __init__(self, file_name):

        output_dir = str(os.environ['LAMP_OUTPUT_DIR'])

        self.file_timings = output_dir + file_name + '_timings.txt'
        self.file = output_dir + file_name + '.txt'

        self.reps = int(os.environ['LAMP_REPS'])

        with open(self.file, 'w') as f:
            f.write('algorithm;Python\n')
        with open(self.file_timings, 'w') as f:
            f.write('')

    def benchmark(self, name, func, *args):

        times = np.zeros(self.reps)
        logger.debug('Benchmarker runs started.')
        for i in range(self.reps):
            times[i], res = func(*args)
            logger.debug('Bench executed')
        logger.debug('Benchmarker runs finished.')

        logger.debug('Writing output to file.')
        with open(self.file, 'a') as f:
            f.write('{};'.format(name))
            f.write('{} '.format(np.min(times)))
            f.write('\n')
        with open(self.file_timings, 'a') as f:
            f.write('{};'.format(name))
            for item in times:
                f.write('{};'.format(item))
            f.write('\n')
        logger.debug('Output written to file.')
        return res
