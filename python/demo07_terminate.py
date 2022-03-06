'''
FORCING A THREAD TO TERMINATE (i.e. killing the thread)
Using a flag to notify the thread
'''

import time
import threading



flag_stop = False



def do_task():
    while True:
        if flag_stop:
            break

        print('Running...')
        time.sleep(1)



th = threading.Thread(target=do_task)
th.start()

time.sleep(3)
flag_stop = True
