'''
THE PRODUCER-CONSUMER PROBLEM

SOLUTION TYPE A: USING BLOCKING QUEUES
    Version A02: 2 slow producers, 1 fast consumer
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



def consumer(q: Queue):
    while True:
        data = q.get()
        print('Consumer', data)



blkq = Queue()

threading.Thread(target=producer, args=(blkq,)).start()
threading.Thread(target=producer, args=(blkq,)).start()

threading.Thread(target=consumer, args=(blkq,)).start()
