'''
TIMER OBJECTS
'''

import time
import threading



def func_time_out():
    print('Time out!!!')



threading.Timer(10, func_time_out).start()

for i in range(9, -1, -1):
    print(i)
    time.sleep(1)
