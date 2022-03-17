'''
THE PRODUCER-CONSUMER PROBLEM

SOLUTION TYPE A: USING BLOCKING QUEUES
    Version A04: Multiple fast producers, multiple slow consumers
'''

import time
from queue import Queue
import threading



def producer(q: Queue, start_value: int):
    time.sleep(1)
    i = 1

    while True:
        q.put(i + start_value)
        i += 1



def consumer(q: Queue):
    while True:
        data = q.get()
        print('Consumer', data)
        time.sleep(1)



blkq = Queue(maxsize=5)
NUM_PRODUCERS = 3
NUM_CONSUMERS = 2

for i in range(NUM_PRODUCERS):
    threading.Thread(target=producer, args=(blkq, i * 1000)).start()

for _ in range(NUM_CONSUMERS):
    threading.Thread(target=consumer, args=(blkq,)).start()
