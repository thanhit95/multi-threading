'''
BLOCKING QUEUES
Version B: A fast producer and a slow consumer
'''

import time
from queue import Queue
import threading



def producer(q: Queue):
    q.put('Alice')
    q.put('likes')

    # Due to reaching the maximum capacity = 2, when executing q.put('singing'),
    # this thread is going to sleep until the queue removes an element.
    q.put('singing')



def consumer(q: Queue):
    time.sleep(2)

    for _ in range(3):
        print('\nWaiting for data...')
        data = q.get()
        print(f'    {data}')



blkq = Queue(maxsize=2) # blocking queue with capacity = 2

threading.Thread(target=producer, args=(blkq,)).start()
threading.Thread(target=consumer, args=(blkq,)).start()
