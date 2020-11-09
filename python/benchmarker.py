import numpy as np
import os
import time
import logging

logger = logging.getLogger('Benchmarker')

l3_size = int(os.environ['LAMP_L3_CACHE_SIZE'])
# cs = np.random.randn(1, l3_size)
cs = np.random.randn(1, 1)


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
