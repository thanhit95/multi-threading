'''
CONDITION VARIABLES
'''

import time
import threading



condition_var = threading.Condition()



def foo():
    print('foo is waiting...')
    with condition_var:
        condition_var.wait()
    print('foo resumed')



def bar():
    for _ in range(3):
        time.sleep(2)
        with condition_var:
            condition_var.notify()



_ = [ threading.Thread(target=foo).start() for _ in range(3) ]
threading.Thread(target=bar).start()
