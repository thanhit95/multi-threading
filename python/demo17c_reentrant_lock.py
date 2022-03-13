'''
REENTRANT LOCKS (RECURSIVE MUTEXES)
Version C: A multithreaded app example
'''

import time
import threading



lock = threading.RLock()



def do_task(name):
    time.sleep(1)
    with lock:
        print(f'First time {name} acquiring the resource')
        with lock:
            print(f'Second time {name} acquiring the resource')



NUM_THREADS = 3

for i in range(NUM_THREADS):
    threading.Thread(target=do_task, args=(chr(i + 65),)).start()
