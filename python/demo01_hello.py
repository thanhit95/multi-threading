'''
HELLO WORLD VERSION MULTITHREADING
'''

import threading



def do_task():
    print('Hello from example thread')



th = threading.Thread(target=do_task)
th.start()

print('Hello from main thread')
