'''
REENTRANT LOCKS (RECURSIVE MUTEXES)
Version A: Introduction to reentrant locks
'''

import threading



lock = threading.Lock()



def do_task():
    with lock:
        print('First time acquiring the resource')
        with lock:
            print('Second time acquiring the resource')



th = threading.Thread(target=do_task)
th.start()

# The thread th shall meet deadlock.
# So, you will never get output "Second time the acquiring resource".
