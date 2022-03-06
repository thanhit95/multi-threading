'''
THE PRODUCER-CONSUMER PROBLEM

SOLUTION TYPE B: USING SEMAPHORES
    Version B04: Multiple fast producers, multiple slow consumers
'''

import time
import threading



def producer(
    sem_fill: threading.Semaphore,
    sem_empty: threading.Semaphore,
    q: list,
    start_value: int
):
    time.sleep(1)
    i = 1

    while True:
        sem_empty.acquire()
        q.append(i + start_value)
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
        time.sleep(1)
        sem_empty.release()



s_fill = threading.Semaphore(0)  # item produced
s_empty = threading.Semaphore(1) # remaining space in queue
que = []

NUM_PRODUCERS = 3
NUM_CONSUMERS = 2

for i in range(NUM_PRODUCERS):
    threading.Thread(target=producer, args=(s_fill, s_empty, que, i * 1000)).start()

for _ in range(NUM_CONSUMERS):
    threading.Thread(target=consumer, args=(s_fill, s_empty, que)).start()
