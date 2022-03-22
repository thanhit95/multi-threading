'''
MAXIMUM NUMBER OF DIVISORS
'''

import time
import threading



lk = threading.Lock()
final_res = { 'value': 0, 'numdiv': 0 }



def prepare_arg(rng_start: int, rng_end: int, num_threads: int) -> list[dict]:
    rng_block = (rng_end - rng_start + 1) // num_threads
    rng_a = rng_start
    lst_arg = []

    for i in range(num_threads):
        rng_b = rng_a + rng_block - 1 if i < num_threads - 1 else rng_end
        lst_arg.append({ 'start': rng_a, 'end': rng_b })
        rng_a += rng_block

    return lst_arg



def do_task(arg: dict):
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
        if final_res['numdiv'] < res_numdiv:
            final_res['numdiv'] = res_numdiv
            final_res['value'] = res_value



##########################################################



RANGE_START = 1
RANGE_END = 30000
NUM_THREADS = 8

lst_worker_arg = prepare_arg(RANGE_START, RANGE_END, NUM_THREADS)

lstth = [
    threading.Thread( target=do_task, args=(arg,) )
    for arg in lst_worker_arg
]


tp_start = time.time()

for th in lstth:
    th.start()

for th in lstth:
    th.join()

time_elapsed = time.time() - tp_start


print('The integer which has largest number of divisors is', final_res['value'])
print('The largest number of divisor is', final_res['numdiv'])
print('Time elapsed =', time_elapsed)
