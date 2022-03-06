'''
REENTRANT LOCKS (RECURSIVE MUTEXES)
Version B: Solving the problem from version A
'''

import threading



lock = threading.RLock()



def do_task():
    with lock:
        print('First time acquiring the resource')
        with lock:
            print('Second time acquiring the resource')



th = threading.Thread(target=do_task)
th.start()
th.join()
