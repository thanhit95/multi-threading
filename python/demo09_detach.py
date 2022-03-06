'''
THREAD DETACHING
'''

import time
import threading



def do_task():
    print('foo is starting...')
    time.sleep(2)
    print('foo is exiting...')



th_foo = threading.Thread(target=do_task, daemon=True)
th_foo.start()

# If I comment this statement,
# th_foo will be forced into terminating with main thread
time.sleep(3)

print('Main thread is exiting')
