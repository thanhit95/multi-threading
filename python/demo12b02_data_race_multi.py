'''
DATA RACES
Version 02: Multithreading
'''

import threading



def count_div_2(a: list, n: int):
    for i in range(2, n + 1, 2):
        a[i] = True



def count_div_3(a: list, n: int):
    for i in range(3, n + 1, 3):
        a[i] = True



N = 8
A = [False] * (N + 1)

th_div_2 = threading.Thread(target=count_div_2, args=(A, N))
th_div_3 = threading.Thread(target=count_div_3, args=(A, N))

th_div_2.start()
th_div_3.start()
th_div_2.join()
th_div_3.join()

result = A.count(True)

print('Number of integers that are divisible by 2 or 3 is:', result)
