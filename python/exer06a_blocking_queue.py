'''
BLOCKING QUEUE IMPLEMENTATION
Version A: Synchronous queues
'''

import time
import threading



class SynchronousQueue:
    def __init__(self):
        self.__sem_put = threading.Semaphore(1)
        self.__sem_take = threading.Semaphore(0)
        self.__element = None

    def put(self, value):
        self.__sem_put.acquire()
        self.__element = value
        self.__sem_take.release()

    def take(self):
        self.__sem_take.acquire()
        result = self.__element
        self.__sem_put.release()
        return result



def producer(syncq: SynchronousQueue):
    arr = [ 'lorem', 'ipsum', 'dolor' ]

    for data in arr:
        print(f'Producer: {data}')
        syncq.put(data)
        print(f'Producer: {data} \t\t\t[done]')



def consumer(syncq: SynchronousQueue):
    time.sleep(5)

    for _ in range(3):
        value = syncq.take()
        print(f'\tConsumer: {value}')



syncqueue = SynchronousQueue()
threading.Thread(target=producer, args=(syncqueue,)).start()
threading.Thread(target=consumer, args=(syncqueue,)).start()
