'''
THREAD-LOCAL STORAGE
'''

import time
import threading



data = threading.local()



def print_local_value():
    print(data.value)



def do_task_apple():
    data.value = 'APPLE'
    time.sleep(2)
    print_local_value()



def do_task_banana():
    data.value = 'BANANA'
    time.sleep(2)
    print_local_value()



threading.Thread(target=do_task_apple).start()
threading.Thread(target=do_task_banana).start()
