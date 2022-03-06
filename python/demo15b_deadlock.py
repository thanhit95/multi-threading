'''
DEADLOCK
Version B
'''

import time
import threading



mutex_a = threading.Lock()
mutex_b = threading.Lock()



def foo():
    with mutex_a:
        print('foo acquired resource A')
        time.sleep(1)
        with mutex_b:
            print('foo acquired resource B')



def bar():
    with mutex_b:
        print('bar acquired resource B')
        time.sleep(1)
        with mutex_a:
            print('bar acquired resource A')



th_foo = threading.Thread(target=foo)
th_bar = threading.Thread(target=bar)

th_foo.start()
th_bar.start()
th_foo.join()
th_bar.join()

print('You will never see this statement due to deadlock!')
