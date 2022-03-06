'''
MUTEXES
In Python, Lock objects can be used as mutexes
'''

import time
import threading



mutex = threading.Lock()
counter = 0



def do_task():
    global counter

    mutex.acquire()

    for _ in range(1000):
        temp = counter + 1
        time.sleep(0.0001)
        counter = temp

    mutex.release()



NUM_THREADS = 32
lstth = [threading.Thread(target=do_task) for _ in range(NUM_THREADS)]

for th in lstth:
    th.start()

for th in lstth:
    th.join()

print('counter =', counter)
# We are sure that counter = 32000
