'''
BLOCKING QUEUES
Version A: A slow producer and a fast consumer
'''

import time
from queue import Queue
import threading



def producer(q: Queue):
    time.sleep(2)
    q.put('Alice')

    time.sleep(2)
    q.put('likes')

    time.sleep(2)
    q.put('singing')



def consumer(q: Queue):
    for _ in range(3):
        print('\nWaiting for data...')
        data = q.get()
        print(f'    {data}')



blkq = Queue()

threading.Thread(target=producer, args=(blkq,)).start()
threading.Thread(target=consumer, args=(blkq,)).start()
