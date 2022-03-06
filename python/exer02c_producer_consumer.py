'''
THE PRODUCER-CONSUMER PROBLEM

SOLUTION TYPE C: USING CONDITION VARIABLES & MONITORS
    Multiple fast producers, multiple slow consumers
'''

import time
import threading



class Monitor:
    def __init__(self, max_queue_size: int, q: list):
        self.__q = q
        self.__max_queue_size = max_queue_size
        self.__lk = threading.Lock()
        self.__cond_full = threading.Condition(self.__lk)
        self.__cond_empty = threading.Condition(self.__lk)


    def add(self, item):
        with self.__lk:
            while len(self.__q) == self.__max_queue_size:
                self.__cond_full.wait()

            self.__q.append(item)

            if len(self.__q) == 1:
                self.__cond_empty.notify()


    def remove(self):
        with self.__lk:
            while len(self.__q) == 0:
                self.__cond_empty.wait()

            item = self.__q.pop(0)

            if len(self.__q) == self.__max_queue_size - 1:
                self.__cond_full.notify()

            return item



def producer(mon: Monitor, start_value: int):
    time.sleep(1)
    i = 1

    while True:
        mon.add(i + start_value)
        i += 1



def consumer(mon: Monitor):
    while True:
        data = mon.remove()
        print('Consumer', data)
        time.sleep(1)



MAX_QUEUE_SIZE = 6
NUM_PRODUCERS = 3
NUM_CONSUMERS = 2

q = []
monitor = Monitor(MAX_QUEUE_SIZE, q)

for i in range(NUM_PRODUCERS):
    threading.Thread(target=producer, args=(monitor, i * 1000)).start()

for _ in range(NUM_CONSUMERS):
    threading.Thread(target=consumer, args=(monitor,)).start()
