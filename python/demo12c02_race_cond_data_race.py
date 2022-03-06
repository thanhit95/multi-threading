'''
RACE CONDITIONS AND DATA RACES
'''

import time
import threading



counter = 0



def do_task_a():
    global counter
    time.sleep(1)

    while counter < 10:
        counter += 1

    print('A won !!!')



def do_task_b():
    global counter
    time.sleep(1)

    while counter > -10:
        counter -= 1

    print('B won !!!')



threading.Thread(target=do_task_a).start()
threading.Thread(target=do_task_b).start()
