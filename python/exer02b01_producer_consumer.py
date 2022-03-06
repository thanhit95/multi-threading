'''
THE PRODUCER-CONSUMER PROBLEM

SOLUTION TYPE B: USING SEMAPHORES
    Version B01: 1 slow producer, 1 fast consumer
'''

import time
import threading



def producer(
    sem_fill: threading.Semaphore,
    sem_empty: threading.Semaphore,
    q: list
):
    i = 1

    while True:
        sem_empty.acquire()
        q.append(i)
        time.sleep(1)
        sem_fill.release()
        i += 1



def consumer(
    sem_fill: threading.Semaphore,
    sem_empty: threading.Semaphore,
    q: list
):
    while True:
        sem_fill.acquire()
        data = q.pop(0)
        print('Consumer', data)
        sem_empty.release()



s_fill = threading.Semaphore(0)  # item produced
s_empty = threading.Semaphore(1) # remaining space in queue
que = []

threading.Thread(target=producer, args=(s_fill, s_empty, que)).start()
threading.Thread(target=consumer, args=(s_fill, s_empty, que)).start()
