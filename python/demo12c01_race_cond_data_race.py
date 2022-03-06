'''
RACE CONDITIONS AND DATA RACES
'''

import time
import threading



counter = 0



def do_task():
    global counter

    for _ in range(1000):
        temp = counter + 1
        time.sleep(0.0001)
        counter = temp



lstth = [threading.Thread(target=do_task) for _ in range(32)]

for th in lstth:
    th.start()

for th in lstth:
    th.join()

print('counter =', counter)
# We are NOT sure that counter = 32000
