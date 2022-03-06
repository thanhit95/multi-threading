'''
THE PRODUCER-CONSUMER PROBLEM

SOLUTION TYPE A: USING BLOCKING QUEUES
    Version A03: 1 slow producer, 2 fast consumers
'''

import time
from queue import Queue
import threading



def producer(q: Queue):
    i = 1

    while True:
        q.put(i)
        time.sleep(1)
        i += 1



def consumer(name: str, q: Queue):
    while True:
        data = q.get()
        print(f'Consumer {name}: {data}')



blkq = Queue()

threading.Thread(target=producer, args=(blkq,)).start()

threading.Thread(target=consumer, args=('foo', blkq)).start()
threading.Thread(target=consumer, args=('bar', blkq)).start()
