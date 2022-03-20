'''
READ-WRITE LOCKS
Read-write locks in Python are not supported by default.
So, I use mylib_rwlock for this demonstration.
'''

import time
import random
import threading
from mylib_rwlock import ReadWriteLock



rwlock = ReadWriteLock()
resource = 0



def read_func(wait_time):
    time.sleep(wait_time)

    with rwlock.readlock():
        print(f'read: {resource}')



def write_func(wait_time):
    global resource
    time.sleep(wait_time)

    with rwlock.writelock():
        resource = random.randint(0, 99)
        print(f'write: {resource}')



NUM_THREADS_READ = 10
NUM_THREADS_WRITE = 4
TIME_WAIT_MAX = 2

lstth_read = [
    threading.Thread(target=read_func, args=(random.randint(0, TIME_WAIT_MAX),))
    for _ in range(NUM_THREADS_READ)
]

lstth_write = [
    threading.Thread(target=write_func, args=(random.randint(0, TIME_WAIT_MAX),))
    for _ in range(NUM_THREADS_WRITE)
]

for th in lstth_read:
    th.start()

for th in lstth_write:
    th.start()
