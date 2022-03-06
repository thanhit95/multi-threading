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
    time.sleep(3)
    with condition_var:
        condition_var.notify()



threading.Thread(target=foo).start()
threading.Thread(target=bar).start()
