'''
SLEEP
'''

import time
import threading



def do_task():
    print('foo is sleeping')
    time.sleep(3)
    print('foo wakes up')



th_foo = threading.Thread(target=do_task)

th_foo.start()
th_foo.join()

print('Good bye')
