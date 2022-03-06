'''
LIST OF MULTIPLE THREADS
'''

import time
import threading



def do_task(index):
    time.sleep(0.5)
    print(index, end='')



NUM_THREADS = 5
lstth = []

for i in range(NUM_THREADS):
    lstth.append(threading.Thread( target=do_task, args=(i,) ))

for th in lstth:
    th.start()
