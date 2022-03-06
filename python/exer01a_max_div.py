'''
MAXIMUM NUMBER OF DIVISORS
'''

import time



RANGE_START = 1
RANGE_END = 30000

res_value = 0
res_numdiv = 0 # number of divisors of result

tp_start = time.time()


for i in range(RANGE_START, RANGE_END + 1):
    numdiv = 0

    for j in range(1, i // 2):
        if i % j == 0:
            numdiv += 1

    if res_numdiv < numdiv:
        res_numdiv = numdiv
        res_value = i


time_elapsed = time.time() - tp_start

print('The integer which has largest number of divisors is', res_value)
print('The largest number of divisor is', res_numdiv)
print('Time elapsed =', time_elapsed)
