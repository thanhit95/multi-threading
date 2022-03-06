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
        # Notify all waiting threads
        condition_var.notify_all()



_ = [ threading.Thread(target=foo).start() for _ in range(3) ]
threading.Thread(target=bar).start()
