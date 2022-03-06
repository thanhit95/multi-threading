'''
MONITORS
Implementation of a monitor for managing a counter
'''

import time
import threading



class Monitor:
    def __init__(self, res: dict, field_name: str):
        self.__lock = threading.Lock()
        self.__res = res
        self.__field_name = field_name

    def increase_counter(self):
        with self.__lock:
            tmp = self.__res[self.__field_name] + 1
            time.sleep(0.0001)
            self.__res[self.__field_name] = tmp



def do_task(mon: Monitor):
    for _ in range(1000):
        mon.increase_counter()



result = { 'data': 0 }
monitor = Monitor(result, 'data')

NUM_THREADS = 32
lstth = [threading.Thread(target=do_task, args=(monitor,)) for _ in range(NUM_THREADS)]

for th in lstth:
    th.start()

for th in lstth:
    th.join()

print('counter =', result['data'])
# We are sure that counter = 32000
