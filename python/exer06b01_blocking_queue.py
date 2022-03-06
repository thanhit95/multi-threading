'''
BLOCKING QUEUE IMPLEMENTATION
Version B01: General blocking queues
             Underlying mechanism: Semaphores
'''

import time
import threading



class BlockingQueue:
    def __init__(self, capacity: int):
        if capacity <= 0:
            raise ValueError('capacity must be a positive integer')
        # self.__capacity = capacity
        self.__sem_remain = threading.Semaphore(capacity)
        self.__sem_fill = threading.Semaphore(0)
        self.__lk = threading.Lock()
        self.__q = [] # queue


    def put(self, value):
        self.__sem_remain.acquire()

        with self.__lk:
            self.__q.append(value)

        self.__sem_fill.release()


    def take(self):
        self.__sem_fill.acquire()

        with self.__lk:
            result = self.__q.pop(0)

        self.__sem_remain.release()
        return result



def producer(q: BlockingQueue):
    arr = [ 'nice', 'to', 'meet', 'you' ]

    for data in arr:
        print(f'Producer: {data}')
        q.put(data)
        print(f'Producer: {data} \t\t\t[done]')



def consumer(q: BlockingQueue):
    time.sleep(5)

    for i in range(4):
        data = q.take()
        print(f'\tConsumer: {data}')

        if i == 0:
            time.sleep(5)



blkqueue = BlockingQueue(2) # capacity = 2
threading.Thread(target=producer, args=(blkqueue,)).start()
threading.Thread(target=consumer, args=(blkqueue,)).start()
