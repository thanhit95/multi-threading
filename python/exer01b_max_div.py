'''
MAXIMUM NUMBER OF DIVISORS
'''

import time
import threading



lk = threading.Lock()



def prepare_arg(rng_start: int, rng_end: int, num_threads: int) -> list:
    rng_block = (rng_end - rng_start + 1) // num_threads
    rng_a = rng_start
    lst_arg = []

    for i in range(num_threads):
        rng_b = rng_a + rng_block - 1 if i < num_threads - 1 else rng_end
        lst_arg.append({ 'start': rng_a, 'end': rng_b })
        rng_a += rng_block

    return lst_arg



def do_task(arg, lst_res: list):
    res_value = 0
    res_numdiv = 0

    for i in range(arg['start'], arg['end'] + 1):
        numdiv = 0

        for j in range(1, i // 2):
            if i % j == 0:
                numdiv += 1

        if res_numdiv < numdiv:
            res_numdiv = numdiv
            res_value = i

    with lk:
        lst_res.append({ 'value': res_value, 'numdiv': res_numdiv })

    '''
    BETTER WAY (avoiding synchronization of lst_res):

    - Initialize lst_res with null objects.
        Of course, the number of objects is NUM_THREADS.

    - In thread function:
        lst_res[thread_index] = { 'value': res_value, 'numdiv': res_numdiv }
    '''



##########################################################



RANGE_START = 1
RANGE_END = 30000
NUM_THREADS = 8

lst_worker_arg = prepare_arg(RANGE_START, RANGE_END, NUM_THREADS)
lst_worker_res = []

lstth = [
    threading.Thread( target=do_task, args=(arg, lst_worker_res) )
    for arg in lst_worker_arg
]


tp_start = time.time()

for th in lstth:
    th.start()

for th in lstth:
    th.join()

final_res = sorted(lst_worker_res, key=lambda res: res['numdiv'])[-1]

time_elapsed = time.time() - tp_start


print('The integer which has largest number of divisors is', final_res['value'])
print('The largest number of divisor is', final_res['numdiv'])
print('Time elapsed =', time_elapsed)
